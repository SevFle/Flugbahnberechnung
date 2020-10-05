/****************************************************************** Includes ****************************************************************/
#include "headers/camera_manager.h"


/****************************************************************** Namespaces***************************************************************/
using namespace CameraManager;
using namespace GlobalObjects;

/*************************************************************** Konstruktoren **************************************************************/
C_CameraManager::C_CameraManager ( C_GlobalObjects* GlobalObjects)
  {
  this->globalObjects     = GlobalObjects;
  this->vecCameras        = new std::vector<Camera::C_Camera2*>;
  this->saveManager       = new Savemanager::c_SaveManager(GlobalObjects);
  this->loadManager       = new LoadManager::C_LoadManager(GlobalObjects);
  this->trackingManager   = new trackingManager::C_trackingManager(GlobalObjects);
  this->ImageFilter       = new imagefilter::C_ImageFilter();

  this->camThread         = nullptr;
  this->lock              = new std::mutex;
  this->relPose           = new posen::C_RelativePose;
  this->absPose           = new posen::C_AbsolutePose;
  this->roistatus         = new roiStatus;

  this->pipelineQue       = new tbb::concurrent_bounded_queue<CameraManager::S_pipelinePayload*>;
  this->threadQue         = new tbb::concurrent_bounded_queue<CameraManager::S_threadPayload*>;

  this->payData           = nullptr;
  this->tData             = nullptr;
  this->filterFlags       = new S_filterflags;

   this->camera_id = 0;
   this->frameWidth = 0;
   this->frameHeight = 0;
   this->initZoneWidth = 0;
   this->initZoneHeight = 0;
   this->transferZoneWidth = 0;
   for(int i = 0; i < 4; i++)
     {
     this->arrActiveCameras[i] = 0;
     }
   this->delta_t = 0;
   this->deltaT_old = 0;

   this->calibrationDone = new std::atomic<bool>(false);
   this->positioningDone = new std::atomic<bool>(false);
   this->pipelineDone = new std::atomic<bool>(false);
   this->pipelineFlush = new std::atomic<bool>(false);

   this->initialize();

  }
/**************************************************************** Destruktor ****************************************************************/
C_CameraManager::~C_CameraManager ()
  {
  this->pipelineFlush.store(false);
  this->pipelineDone.store(false);
  this->positioningDone.store(false);
  this->calibrationDone.store(false);

  this->deltaT_old = 0;
  this->delta_t = 0;
  for(int i = 0; i < 4; i++)
    {
    this->arrActiveCameras[i] = 0;
    }
  this->transferZoneWidth = 0;
  this->initZoneHeight = 0;
  this->initZoneWidth = 0;
  this->frameHeight = 0;
  this->frameWidth = 0;
  this->camera_id = 0;

  delete (filterFlags);
  delete (tData);
  delete (payData);

  delete (threadQue);
  delete (pipelineQue);

  delete (roistatus);
  delete (absPose);
  delete (relPose);
  delete (lock);

  this->camThread         = nullptr;

  delete (ImageFilter);
  delete (trackingManager);
  delete (loadManager);
  delete (saveManager);
  for(auto it = std::begin(*this->vecCameras); it < std::end(*this->vecCameras); it++)
    {
      delete ((*it));
    }
  delete (vecCameras);
  this->globalObjects = nullptr;
  }

thread *C_CameraManager::getCamThread() const
  {
  return camThread;
  }

void C_CameraManager::setDelta_t(int value)
  {
  delta_t = value;
  }

/******************************************************* Öffentliche Anwender-Methoden ******************************************************/

void C_CameraManager::initialize()
  {
  this->frameWidth = 1280;
  this->frameHeight = 720;
  this->initZoneWidth = 200;
  this->initZoneHeight = this->frameHeight -1;
  this->transferZoneWidth = 200;
  }
bool C_CameraManager::openCameras ()
  {
  GstDeviceMonitor *Monitor;
  GstCaps *caps;
  GstDevice *device;
  GList *devlist = NULL, *devIter;

  Monitor = gst_device_monitor_new ();
  caps = gst_caps_new_empty_simple("image/jpeg");
  gst_device_monitor_add_filter(Monitor, "Video/Source", caps);
  gst_caps_unref(caps);

  devlist = gst_device_monitor_get_devices (Monitor);

  if (!gst_device_monitor_start(Monitor))
    {
    printf("\n GST-INFO: GstDeviceMonitor unsupported. May not be able to enumerate all video devices.\n");
    }
  else
    {
    devlist = gst_device_monitor_get_devices(Monitor);
    printf("\n GST-INFO: GstDeviceMonitor startet. \n");
    for (devIter = g_list_first(devlist); devIter != NULL; devIter = g_list_next(devIter))
      {
      device                          = (GstDevice*) devIter->data;
      if (device == NULL)
        continue;
      GstStructure *    DeviceProps   = gst_device_get_properties (device);
      gchar *           fieldname     = "device.path" ;
      std::string       devicePath    = gst_structure_get_string(DeviceProps, fieldname);
      std::string       Pipeline      = "v4l2src device="+ devicePath +" ! ";
                        Pipeline      += "image/jpeg, format=BGR, width=" + std::to_string(this->frameWidth) +",";
                        Pipeline      += "height=" + std::to_string(this->frameHeight) +" ! jpegdec ! videoconvert ! appsink";//sync=false

      auto              camera        = new Camera::C_Camera2;
      camera->setPipeline             (Pipeline);
      camera->setCameraID             (this->globalObjects->absCameras);
      if(!camera->open())
         std::cout << "**ERROR** Could not open device on path" << devicePath << std::endl;
      vecCameras->push_back            (camera);
      this->globalObjects->absCameras++;
      }
    std::cout << "**INFO** Cameraspeed is \033[1m\033[33m" << this->vecCameras->at(0)->getFPS() << "\033[0m fps" << std::endl;
    std::cout << "**INFO** Created \033[1m\033[31m" << std::to_string(this->globalObjects->absCameras) << " \033[0m Devices" << std::endl;

    }

  //Reorder recently created Cameras
  this->loadManager->loadCameraPositioning(*this->vecCameras);
  //Load Settings and Calibration for each camera created earlier
  loadCameras();

 return true;
  }
bool C_CameraManager::closeCameras ()
  {
  for (auto it = std::begin(*vecCameras); it < std::end(*vecCameras); it++)
    {
    (*it)->close();
      delete(*it);
    }
  return true;
  }

void C_CameraManager::loadCameras              ()
  {
  for (int i = 0; i < globalObjects->absCameras; i++)
    {
    this->loadManager->loadCameraCalibration(this->vecCameras->at(i));
    this->loadManager->loadCameraSettings(this->vecCameras->at(i));
    this->loadManager->loadCameraCos(this->vecCameras->at(i));
    this->trackingManager->load_posen(*this->vecCameras->at(i)->cameraPose);
    this->vecCameras->at(i)->initRectifyMap();
    }
  this->trackingManager->init_posen();

  }
bool C_CameraManager::startThreadCameraPositioning()
  {
  threadQue->set_capacity(10);
  this->camThread     = new thread(&CameraManager::C_CameraManager::threadHelper,this);
  std::cout << "**INFO** Kamerathread wurde gestartet" << std::endl;
  return true;
  }
bool C_CameraManager::stopThreadCameraPositioning()
  {
    this->positioningDone = true;
    std::this_thread::sleep_for (std::chrono::milliseconds (500));

    this->camThread->join();
    this->threadQue->clear();
  return true;
   }
bool C_CameraManager::startPipelineTracking  ()
  {
  pipelineQue->set_capacity(10);
  this->pipelineDone.store(false);
  this->camThread     = new thread(&CameraManager::C_CameraManager::pipelineHelper,this);

  printf("\n**INFO** Kamerapipeline wurde gestartet");
  return true;
  }
bool C_CameraManager::stopPipelineTracking()
  {
  this->pipelineDone.store(true);
  std::this_thread::sleep_for (std::chrono::milliseconds (500));

  this->camThread->join();
  this->pipelineQue->clear();
  return true;
  }

void C_CameraManager::mvVecCamera2Temp (std::vector<int> vecCamOrder)
  {
//  std::vector<Camera::C_Camera2*> vecCamerastemp;
//  vecCamerastemp.resize(globalObjects->absCameras);
//  for(int i =0; i < globalObjects->absCameras; i++)
//    {
//    vecCamerastemp[i] = std::move(this->vecCameras[vecCamOrder[i]]);
//    }
    std::vector<Camera::C_Camera2*>                         vecTempCameras;
    std::vector<int>                                        istCamIDs;
    std::vector<int>                                        sollCamIDs;

    vecTempCameras.resize(this->vecCameras->size());

    for(int i = 0; i < globalObjects->absCameras; i++)
      {
      //vecTempCameras[vecCamOrder[i]] = std::move(this->vecCameras[i]);
      vecTempCameras[vecCamOrder[i]] = this->vecCameras->at(i);
      }
      this->vecCameras->clear();
      this->vecCameras->resize(vecTempCameras.size());
    for (int i = 0; i < globalObjects->absCameras; i++)
      {
      //this->vecCameras[i] = std::move (vecTempCameras[i]);
      this->vecCameras->at(i) = vecTempCameras[i];
      }
  }
void C_CameraManager::mvTemp2VecCamera (std::vector<Camera::C_Camera2*> vecCamerastemp)
  {
  for (int i = 0; i < globalObjects->absCameras; i++)
    {
    this->vecCameras->at(i) = std::move (vecCamerastemp[i]);
  }
}

bool C_CameraManager::scanChAruco(cv::Mat &image, Camera::C_Camera2 &camera, cv::Mat &Pose)
  {
  if(image.type() != 16)
    return false;
  //    cv::Ptr<cv::aruco::Dictionary>            dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_250);
  //    cv::Ptr<cv::aruco::CharucoBoard>          board = cv::aruco::CharucoBoard::create(9, 6, 0.03190f, 0.02002f, dictionary);
  cv::Ptr<cv::aruco::DetectorParameters>    params = cv::aruco::DetectorParameters::create();

  cv::Ptr<cv::aruco::Dictionary>            dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_50);// (cv::aruco::DICT_6X6_250)
  cv::Ptr<cv::aruco::CharucoBoard>          board = cv::aruco::CharucoBoard::create(5, 8, 0.05f, 0.03745f, dictionary);

  cv::Size                                  imgSize;
  std::vector<int>                        markerIds;
  std::vector<std::vector<cv::Point2f>>   markerCorners;
  //rejectedPoints beschreibt alle Punkte, welche von der detectMarkers Funktion abgelehnt wurden.
  std::vector<std::vector<cv::Point2f> >  rejectedPoints;
  std::vector<cv::Point2f>                charucoCorners;
  std::vector<int>                        charucoIds;


  cv::Mat imagecopy, gray;
  image.copyTo(imagecopy);
  cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
  imgSize = image.size();

  cv::aruco::detectMarkers(gray, board->dictionary, markerCorners, markerIds, params,rejectedPoints,*camera.getIntrinsic(), *camera.getDistCoeffs());
  if (markerIds.size() > 4)
    {
    cv::aruco::drawDetectedMarkers(image, markerCorners, markerIds);
    cv::aruco::interpolateCornersCharuco(markerCorners, markerIds, image, board, charucoCorners, charucoIds, *camera.getIntrinsic(), *camera.getDistCoeffs(), 2);
  // if at least one charuco corner detected
    if (charucoIds.size() > 4)
      {
      cv::Scalar color = cv::Scalar(255, 0, 0);
      //This function draws a set of detected Charuco corners. If identifiers vector is provided, it also draws the id of each corner.
      cv::aruco::drawDetectedCornersCharuco(image, charucoCorners, charucoIds, color);


      cv::Vec3d rvecBoardAxis, tvecBoardAxis;
      //Pose estimation for a ChArUco board given some of their corners.
      bool valid = cv::aruco::estimatePoseCharucoBoard(charucoCorners, charucoIds, board, *camera.getIntrinsic(), *camera.getDistCoeffs(), rvecBoardAxis, tvecBoardAxis);
      if(valid)
        {
          cv::Mat rvecMarker, tvecMarker, objpoints;
          //      This function receives the detected markers and returns their pose estimation respect to the camera individually.
          //      So for each marker, one rotation and translation vector is returned.
          //      The returned transformation is the one that transforms points from each marker coordinate system to the camera coordinate system.
          //      The marker corrdinate system is centered on the middle of the marker, with the Z axis perpendicular to the marker plane.
          //      The coordinates of the four corners of the marker in its own coordinate system are:
          //      (-markerLength/2, markerLength/2, 0), (markerLength/2, markerLength/2, 0), (markerLength/2, -markerLength/2, 0), (-markerLength/2, -markerLength/2, 0)
        cv::aruco::drawAxis(image, *camera.getIntrinsic(), *camera.getDistCoeffs(), rvecBoardAxis, tvecBoardAxis, 0.4f);
        cv::Mat rvecM12, rvecAxisRodL, rvecAxisRodR;
        cv::Mat M10(cv::Mat_<double>(4,4));
        cv::Mat row = cv::Mat::zeros(1, 4, CV_64F);  // 3 cols, 1 row
        cv::Rodrigues(rvecBoardAxis, rvecAxisRodL);

        //Hconcat kombiniert zwei Matrizen
        cv::hconcat(rvecAxisRodL, tvecBoardAxis, M10);

        M10.push_back(row);
        M10.at<double>(3,3) =   1.0;

        M10.copyTo(Pose);

        return true;
        }
      }
    }
  return false;
  }

void C_CameraManager::calibrateSingleCamera (int current_camera_id,
                                             int absCornersWidth,
                                             int absCornersHeight,
                                             int absBoardImg,
                                             float absCornerLength,
                                             double* rms)
  {
  // Deklaration benötigter Variablen
  cv::Mat                     Originalbild;
  cv::Mat                     Grau_Bild;
  vector<cv::Point2f>         Corners;
  cv::Size                    Board_Sz = cv::Size (absCornersWidth,absCornersHeight);
  cv::Mat                     intrinsic (cv::Mat_<double> (3,3));
  cv::Mat                     distCoeffs;
  vector<cv::Point3f>         Obj;
  vector<vector<cv::Point3f>> Object_Points;
  vector<vector<cv::Point2f>> Image_Points;
  vector<cv::Mat>             Rvecs;
  vector<cv::Mat>             Tvecs;
  vector<cv::Mat>             TCP_Orientation;
  vector<cv::Mat>             TCP_Position;

  int photoID = 0;
  int error_count = 0;

  // Füllen des "Obj"-Vektors mit 3D-Koordinaten der Schachbrett-Ecken. Die Koordinaten werden manuell vorgegeben und ergeben sich über Länge
  // und Breite der Schachbrett-Rechtecke über die gesamte Länge und Breite des Schachbrettes. Das Schachbrett-Rechteck hat eine Größe von
  // 24.23mm x 24.23mm. Damit ergeben sich die Koordinaten (x, y, z) wie folgt: (0, 0, 0), (24.23, 0, 0), (48.46, 0, 0), .... z ist immer null,
  // da die Rechtecke auf einer Ebene liegen und der Koordinatensystemursprung (Welt) auf dem Schachbrett liegt.
  for (int i = 0; i < absCornersHeight; i++)
    {
    for (int j = 0; j < absCornersWidth; j++)
      {
      Obj.push_back (cv::Point3f ((float)j * absCornerLength,(float)i * absCornerLength,0.0f));
      }
    }

  // Abarbeiten aller gespeicherten Bilder
  while (photoID < absBoardImg)
    {
    std::cout << "Processing image " << photoID << " out of " << absBoardImg << " images." << endl;
    // Laden des Bildes mit der angegebenen Photo_ID
    Originalbild = cv::imread ("../Parameter/Bilder/Camera_Single_Calibration_" + std::to_string (current_camera_id) + "_Snapshot_" + std::to_string (photoID) + ".png",1);

    // Umwandeln des geladenen Bildes in ein Grauwertbild und abspeichern dieses in einem anderen Bild-Array
    cvtColor (Originalbild,Grau_Bild,cv::COLOR_BGR2GRAY);

    // Das geladenene Originalbild nach Schachbrett-Ecken absuchen. Die Anzahl der inneren Ecken über Länge und Breite wird über "Board_Sz" vorgegeben und
    // die gefundenen Ecken werden in "Corners" abgespeichert. Es wird eine adaptive Schwellwertbildung genutzt und das Bild wird nach Rechtecken
    // gefiltert. "Found" wird nur true, wenn alle Ecken gefunden wurden. Die Ecken-Koordinaten aus "Corners" sind 2D-Koordinaten der Bildebene.
    bool Found = findChessboardCorners (Grau_Bild,Board_Sz,Corners,cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_FILTER_QUADS + cv::CALIB_CB_NORMALIZE_IMAGE);

    if (!Found) error_count++;

    if (Found) // Falls Rechtecke gefunden wurden
      {
      // Mit Hilfe der gefundenen Ecken in "Corners" werden im Graustufenbild nun die Ecken-Standorte verfeinert. Mit den beiden "Size"-Angaben
      // wird die Größe der abzusuchenden Bereiche in jedem Iterationsschritt angegeben. Der erste Wert legt die Fenstergröße auf (2*5+1) x (2*5+1) = 11x11
      // fest, der zweite Wert legt die Mindestgröße fest, wobei die Werte -1 angeben, dass es keine "Totzone" gibt. Mit "TermCriteria" werden die
      // Ausstiegbedingungen für den Iterationsvorgang angegeben. "EPS" legt eine gewünschte Genauigkeit bzw. Parameteränderung von 0.1 fest. "MAX_ITER"
      // legt die Anzahl der maximalen Iterationen von 30 fest. Die Ausstiegsbedingung ist eine ODER-Bedingung.
      cornerSubPix (Grau_Bild,Corners,cv::Size (5,5),cv::Size (-1,-1),cv::TermCriteria (cv::TermCriteria::EPS | cv::TermCriteria::MAX_ITER,30,0.1));

      // Mit dieser Funktion werden die gefundenen Ecken aus "Corners" im Graustufenbild eingezeichnet. Ist "Found" true, wurde das Schachbrett und die
      // Ecken erkannt und diese werden markiert und mit Linien verbunden. Ist "Found" false, werden nur die gefundenen Ecken mit einem roten Kreis markiert.
      drawChessboardCorners (Grau_Bild,Board_Sz,Corners,Found);

      // Die gefundenen Ecken-Koordinaten (2D, ohne z-Koordinate) im Vektor "Image-Points" abspeichern.
      Image_Points.push_back (Corners);

      // Alle manuell vorgegebenen Ecken-Koordinaten aus "Obj" in Vektor "Object_Points" ablegen.
      Object_Points.push_back (Obj);

      // Die entsprechende Roboterpose zum aktuellen Bild in einem Vektor abspeichern. Dieser Vektor wird für
      // die Eye-In-Hand-Kalibrierung benötigt.
      cv::Mat Mat_Orientation (cv::Mat_<double> (3,3));
      cv::Mat Mat_Position (cv::Mat_<double> (3,1));

      //// Zuweisung der übermittelten Roboter-TCP-Positionen
      //for (int i = 0; i < 3; i++)
      //  {
      //  Mat_Position.ptr<double>(i)[0] = this->TCP_Poses->at(this->Photo_ID).ptr<double>(i)[3];
      // }
      //// Zuweisung der übermittelten Roboter-TCP-Orientierungen
      //for (int i = 0; i < 3; i++)
      //  {
      //  for (int j = 0; j < 3; j++)
      //    {
      //    Mat_Orientation.ptr<double>(i)[j] = this->TCP_Poses->at(this->Photo_ID).ptr<double>(i)[j];
      //    }
      //  }

      // Ablegen aller Roboter-TCP-Orientierungen und -Positionen in Vektoren
      //TCP_Orientation.push_back (Mat_Orientation);
      //TCP_Position.push_back (Mat_Position);
      }

    // Grauwertbild mit eingezeichneten Ecken abspeichern.
    imwrite ("../Parameter/Bilder/Camera_Single_Calibration_" + std::to_string (camera_id) + "_Gray_DrawCorners_" + std::to_string (photoID) + ".png",Grau_Bild);

    // Photo-ID für nächsten Durchlauf erhöhen.
    photoID++;
    }

  std::cout << "Analyzed " << absBoardImg - error_count << "good images out of " << absBoardImg << endl;

  // Mit den gefundenen Ecken in 2D-Koordinaten und den vorgegebenen 3D-Koordinaten werden die intrinsischen Parameter (Camera-Matrix) und
  // die Koeffizienten der Verzerrung berechnet. Rvecs und Tvecs erhalten dabei die Orientierung und die Position der Transformationsmatrix
  // zwischen Kamerakoordinatensystem und Schachbrettkoordinatensystem.
  //The intrinsic matrix contains 5 intrinsic parameters.These parameters encompass focal length, image format, and principal point.
  //The parameters \alpha_{ x } = f \cdot m_{ x } and \alpha_{ y } = f \cdot m_{ y } represent focal length in terms of pixels, 
  //where m_{ x } and m_{ y } are the scale factors relating pixels to distance and f is the focal length in terms of distance.
  std::cout << endl << "Calculating Intrinsic and DistCoeffs. This may take a while, please wait." << endl;
  double err = cv::calibrateCamera (Object_Points,Image_Points,Originalbild.size(),intrinsic,distCoeffs,Rvecs,Tvecs);
  std::cout << "RMS: " << err << std::endl << endl;
  std::cout << "Calculation finished. Saving data." << endl << endl;

  //Kopieren der berechneten Daten zur dazugehörigen Kamera
  vecCameras->at(current_camera_id)->setIntrinsic(intrinsic);
  vecCameras->at(current_camera_id)->setDistCoeffs(distCoeffs);

  //Speichern der berechenten Daten in CSV Datei
  this->saveManager->saveCameraCalibration(*vecCameras->at(current_camera_id));
  //Reaktivierung der Bildentzerrung
  this->vecCameras->at(current_camera_id)->initRectifyMap();
  }

void C_CameraManager::calibrate_stereo_camera_aruco(int current_camera_id)
  {
  //Verwendete ChAruco Parameter
  //  cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);
  //  cv::Ptr<cv::aruco::CharucoBoard> board = cv::aruco::CharucoBoard::create(9, 6, 0.40f, 0.25f, dictionary);
  //  cv::Mat boardImage;
  //  //DINA4 3508 x 2480 px
  //  board->draw(cv::Size(3200, 2200), boardImage, 10, 1);
  //  cv::imwrite("../Parameter/Charuco_BoardImage_5_7_0.04f_0.02f_Size(3200, 2200).jpg", boardImage);

  //3x1 Matrizen der jeweiligen Kameras (L+R)
  cv::Vec3d rBoardAxisL, tBoardAxisL, rBoardAxisR, tBoardAxisR;
  //Initialisierung der ChAruco Kalibrierung
  cv::Ptr<cv::aruco::Dictionary>            dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_50);// (cv::aruco::DICT_6X6_250)
//  cv::Ptr<cv::aruco::CharucoBoard>          board = cv::aruco::CharucoBoard::create(5, 8, 0.05f, 0.03745f, dictionary);
  cv::Ptr<cv::aruco::CharucoBoard>          board = cv::aruco::CharucoBoard::create(5, 8, 50.00f, 37.45f, dictionary);

  cv::Ptr<cv::aruco::DetectorParameters>    params = cv::aruco::DetectorParameters::create();

  cv::Size                                  imgSize;
  std::vector<std::vector<cv::Point2f>>     veccharucoCorners;
  std::vector<std::vector<int>>             veccharucoIds;
  //Vektoren zur Speicherung der einzelnen relativen Posen jedes einzelnen Aruco Tags
  std::vector<cv::Mat>                      vecRvec_right, vectec_right, vecRvec_left, vectvec_left;

  //Iterator über Kamera 0 + 1
  for(int j = 0; j < 2; j ++)
    {
    //Hole aktuelle Intrinsic und Verzerrungsdaten der abgefragten (j) Kamera
    cv::Mat cameraMatrix, distCoeffs;
    this->vecCameras->at(current_camera_id+j)->getIntrinsic()->copyTo(cameraMatrix);
    this->vecCameras->at(current_camera_id+j)->getDistCoeffs()->copyTo(distCoeffs);

    std::vector<int>                        markerIds;
    std::vector<std::vector<cv::Point2f>>   markerCorners;

    std::vector<cv::Point2f>                recoveredIdxs;
    std::vector<cv::Point2f>                charucoCorners;
    std::vector<int>                        charucoIds;

    //rejectedPoints beschreibt alle Punkte, welche von der detectMarkers Funktion abgelehnt wurden.
    std::vector<std::vector<cv::Point2f> >  rejectedPoints;

    cv::Mat image;
    cv::Mat gray;
    cv::Mat imageCopy;
    image = cv::imread ("../Parameter/Bilder/Charuco_Camera_Stereo_Calibration_" + std::to_string (current_camera_id+j) + "_Snapshot_" + std::to_string (0) + ".png",1);
    image.copyTo(imageCopy);
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
    imgSize = image.size();


    //Performs marker detection in the input image. Only markers included in the specific dictionary are searched.
    //For each detected marker, it returns the 2D position of its corner in the image and its corresponding identifier.
    //Note that this function does not perform pose estimation.
    cv::aruco::detectMarkers(gray, board->dictionary, markerCorners, markerIds, params,rejectedPoints,cameraMatrix, distCoeffs);
    std::cout << "Rejected Points size: " << std::to_string(rejectedPoints.size()) << std::endl;

    // if at least one marker detected
    std::cout << "MarkerIds: " << markerIds.size() << std::endl;
    if (markerIds.size() > 4)
      {
      //This function tries to find markers that were not detected in the basic detecMarkers function.
      //First, based on the current detected marker and the board layout, the function interpolates the position of the missing markers.
      //Then it tries to find correspondence between the reprojected markers and the rejected candidates based on the minRepDistance and
      //errorCorrectionRate parameters. If camera parameters and distortion coefficients are provided, missing markers are reprojected using
      //projectPoint function. If not, missing marker projections are interpolated using global homography, and
      //all the marker corners in the board must have the same Z coordinate.

      //cv::aruco::refineDetectedMarkers(gray, board, markerCorners, markerIds, rejectedPoints, cameraMatrix, distCoeffs,10.f, 3.f, true, recoveredIdxs,  cv::aruco::DetectorParameters::create());

      //Given an array of detected marker corners and its corresponding ids,
      //this functions draws the markers in the image. The marker borders are painted and the markers identifiers
      //if provided. Useful for debugging purposes.
      cv::aruco::drawDetectedMarkers(imageCopy, markerCorners, markerIds);
      cv::imwrite ("../Parameter/Bilder/Charuco_Camera_" + std::to_string (camera_id+j) + "_Markers_img_" + std::to_string(0) + ".png",imageCopy);


      //This function receives the detected markers and returns the 2D position of the chessboard corners from a ChArUco board using the detected Aruco markers.
      //If camera parameters are provided, the process is based in an approximated pose estimation, else it is based on local homography.
      //Only visible corners are returned. For each corner, its corresponding identifier is also returned in charucoIds. The function returns the number of interpolated corners.
      cv::aruco::interpolateCornersCharuco(markerCorners, markerIds, image, board, charucoCorners, charucoIds, cameraMatrix, distCoeffs, 2);
      // if at least one charuco corner detected
      std::cout << "CharucoIds: " << charucoIds.size() << std::endl;
      if (charucoIds.size() > 4)
        {
        cv::Scalar color = cv::Scalar(255, 0, 0);
        //This function draws a set of detected Charuco corners. If identifiers vector is provided, it also draws the id of each corner.
        cv::aruco::drawDetectedCornersCharuco(imageCopy, charucoCorners, charucoIds, color);
        cv::Vec3d rvecBoardAxis, tvecBoardAxis;
        //Pose estimation for a ChArUco board given some of their corners.
        bool valid = cv::aruco::estimatePoseCharucoBoard(charucoCorners, charucoIds, board, cameraMatrix, distCoeffs, rvecBoardAxis, tvecBoardAxis);
        // if charuco pose is valid
        if (valid)
          {
          cv::aruco::drawAxis(imageCopy, cameraMatrix, distCoeffs, rvecBoardAxis, tvecBoardAxis, 0.4f);
          }
        //XYZ, is represented as red green blue, respectively.
        std::cout << "rvecAxis: " << endl << rvecBoardAxis << std::endl << std::endl;
        std::cout << "tvecAxis: " << endl << tvecBoardAxis << std::endl << std::endl;

        if(j==0) // Kamera links
          {
          rBoardAxisL = rvecBoardAxis;
          tBoardAxisL = tvecBoardAxis;
          }
        if(j==1) // Kamera rechts
          {
          rBoardAxisR = rvecBoardAxis;
          tBoardAxisR = tvecBoardAxis;
          }
        cv::imwrite ("../Parameter/Bilder/Charuco_Camera_" + std::to_string (camera_id+j) + "_Axis_img_" + std::to_string(0) + ".png",imageCopy);
        veccharucoCorners.push_back(charucoCorners);
        veccharucoIds.push_back(charucoIds);
        }
      }

      cv::Mat rvecMarker, tvecMarker, objpoints;
      //      This function receives the detected markers and returns their pose estimation respect to the camera individually.
      //      So for each marker, one rotation and translation vector is returned.
      //      The returned transformation is the one that transforms points from each marker coordinate system to the camera coordinate system.
      //      The marker corrdinate system is centered on the middle of the marker, with the Z axis perpendicular to the marker plane.
      //      The coordinates of the four corners of the marker in its own coordinate system are:
      //      (-markerLength/2, markerLength/2, 0), (markerLength/2, markerLength/2, 0), (markerLength/2, -markerLength/2, 0), (-markerLength/2, -markerLength/2, 0)
      cv::aruco::estimatePoseSingleMarkers(markerCorners, board->getMarkerLength(), cameraMatrix, distCoeffs, rvecMarker, tvecMarker,  objpoints);
      /**************************************** GIBT MOMENTAN NUR EINEN RVEC AUS ************************************************/

      if(veccharucoCorners.size() > 0 && veccharucoIds.size() > 0)
      {
      cv::Mat                                   stdDeviationsIntrinsics, stdDeviationsExtrinsics,  	perViewErrors;
      std::vector<cv::Mat>                      vecRvec, vectvec;
      double                                    reprojectionError;
      //This function calibrates a camera using a set of corners of a Charuco Board.
      //The function receives a list of detected corners and its identifiers from several views of the Board.
      //The function returns the final re-projection error.
      reprojectionError = cv::aruco::calibrateCameraCharuco(veccharucoCorners, veccharucoIds, board, imgSize, cameraMatrix, distCoeffs, vecRvec, vectvec,
      stdDeviationsIntrinsics, stdDeviationsExtrinsics, perViewErrors, cv::CALIB_USE_INTRINSIC_GUESS,
      cv::TermCriteria(cv::TermCriteria::COUNT+cv::TermCriteria::EPS, 1000, DBL_EPSILON));
      std::cout << std::endl << "Reprojection Error Cam " << j << ": " << std::to_string(reprojectionError) << std::endl;

      if(j==0)
      {
      vecRvec_left = vecRvec;
      vectvec_left = vectvec;
      }
      if(j==1)
      {
      vecRvec_right = vecRvec;
      vectec_right = vectvec;
      }
      }
      else
      {
      std::cout << "No ChAruco Board found" << std::endl;
      cv::Mat zeroes(cv::Mat_<double>(4,4));
      return;
      }

    }

  //Posenberechnungen
  cv::Mat rvecM12, rBoardAxisRodL, rBoardAxisRodR;
  cv::Mat M10(cv::Mat_<double>(4,4));
  cv::Mat M20(cv::Mat_<double>(4,4));
  for(int i = 0; i < 4; i ++)
  {
      for(int j = 0; j < 4; j ++)
      {
      M10.at<double>(i,j) =   0.0;
      M20.at<double>(i,j) =   0.0;
      }
  }
  cv::Mat row = cv::Mat::zeros(1, 4, CV_64F);  // 3 cols, 1 row


  std::cout << "M10: " << endl << M10 << std::endl << std::endl;
  std::cout << "M20: " << endl << M20 << std::endl << std::endl;

  cv::Rodrigues(rBoardAxisL, rBoardAxisRodL);
  cv::Rodrigues(rBoardAxisR, rBoardAxisRodR);

  //Hconcat kombiniert zwei Matrizen
  cv::hconcat(rBoardAxisRodL, tBoardAxisL, M10);
  cv::hconcat(rBoardAxisRodR, tBoardAxisR, M20);
  M10.push_back(row);
  M20.push_back(row);
  M10.at<double>(3,3) =   1.0;
  M20.at<double>(3,3) =   1.0;


  std::cout << "M10: " << endl << M10 << std::endl << std::endl;
  std::cout << "M20: " << endl << M20 << std::endl << std::endl;


  this->calculate_camera_pose(current_camera_id, current_camera_id+1, &M10, &M20);
  }



void C_CameraManager::threadCameraPositioning(std::vector<Camera::C_Camera2*> vecCameras, tbb::concurrent_bounded_queue<S_threadPayload*>* que)
  {
 std::cout << "**INFO** Thread " <<   std::this_thread::get_id() << " alive!" << std::endl;
  while(!this->positioningDone)
    {
    if(que->size() >=10)
        {
        return;
        }
     else
      {
      auto tData = new S_threadPayload;
      for(auto it = std::begin(vecCameras); it < std::end(vecCameras); it++)
        {
        bool err = (*it)->grabImg();
        if(!err)
          {
          std::cout << "***ERROR*** Failed to grab image! Camera: " << (*it)->getCameraID() << std::endl;
          delete (tData);
          this->tData = nullptr;
          return;
          }
        else
          {
          auto img = new cv::Mat;
          err = (*it)->retrieveImg(*img);
          if(!err)
            {
            std::cout << "***ERROR*** Failed to grab image! Camera: " << (*it)->getCameraID() << std::endl;
            delete (img);
            delete (tData);
            this->tData = nullptr;
            return;
            }
          if(img->empty())
              img->setTo(cv::Scalar(255,0,0));
          tData->srcImg.push_back(img);
          tData->queBuffer = que->size();
          if(!que->try_push(tData))
            {
            for(auto it = std::begin(tData->srcImg); it < std::end(tData->srcImg); it ++)
              {
              (*it)->release();
              delete (*it);
              }
            delete (tData);
            this->tData = nullptr;
            }
         }
      }//for
    }//else
    this->globalObjects->watchdog->pet();
  }//while
  std::cout << "**INFO** Thread " <<   std::this_thread::get_id() << " dying!" << std::endl;
  }//thread
void *C_CameraManager::threadHelper(void* This)
  {
  static_cast<CameraManager::C_CameraManager*>(This)->threadCameraPositioning(*static_cast<CameraManager::C_CameraManager*>(This)->vecCameras,
                                  static_cast<CameraManager::C_CameraManager*>(This)->threadQue);
  }
void C_CameraManager::calculate_camera_pose    (int camera1, int camera2, cv::Mat* M10, cv::Mat* M20)
  {
  //M12 = M10*M02
    cv::Mat M12(cv::Mat_<double>(4,4));
    double doubleM20[4][4];
    double doubleM20Inverse[4][4];

    //Erzeuge inverse von M20 = M02
    for(int i = 0; i <= 3; i ++)
      {
      for(int j = 0; j <= 3; j ++)
        {
        doubleM20[i][j] =   M20->at<double>(i,j);
        }
      }
    relPose->InversHomogenousPose(doubleM20, doubleM20Inverse);


    //Multiplizere Matrizen M10*M02
    for(int i=0;i<4;i++)
      {
      for(int j=0;j<4;j++)
          {
          M12.at<double>(i,j)=0;
          for(int k=0;k<4;k++)
              {
              M12.at<double>(i,j)+=M10->at<double>(i,k)*doubleM20Inverse[k][j];
              }
          }
      }
    std::cout << "M12 temp in pose: " << M12 << std::endl;

    //Buffer fr die M12 Mat zur erleichterten Verarbeitung
    double HomogenePosenMatrixTempPuffer[4][4];
    for (int i=0; i < 3; i++)
      {
      for (int j=0; j < 3; j++)
        {
        HomogenePosenMatrixTempPuffer[j][i] = M12.at<double>(j,i);
        }
      }

    //Berechne Absolute Pose fr Kamera 2 durch Pose Kamera 1 * M12
    for (int i = 0; i < 4; i++)
      {
      for (int j = 0; j < 4; j++)
        {
        this->vecCameras->at(camera2)->getCameraPose()->HomogenePosenMatrix[i][j] = 0;
        for (int k = 0; k < 4; k++)
          this->vecCameras->at(camera2)->getCameraPose()->HomogenePosenMatrix[i][j] += this->vecCameras->at(camera1)->getCameraPose()->HomogenePosenMatrix[i][k] *
                                 HomogenePosenMatrixTempPuffer[k][j];
        }
      }

    std::cout << std::endl << std::endl << "M12: " << M12 << std::endl;

    this->saveManager->saveCameraCos(*this->vecCameras->at(camera2));

  }//calculate_camera_pose

void *C_CameraManager::pipelineHelper(void* This)
  {
  static_cast<CameraManager::C_CameraManager*>(This)->pipelineTracking(*static_cast<CameraManager::C_CameraManager*>(This)->vecCameras,
                                                                      static_cast<CameraManager::C_CameraManager*>(This)->pipelineQue);
  }

bool C_CameraManager::pollPipeline               (CameraManager::S_pipelinePayload* arg1)
  {
  std::cout << std::to_string(this->pipelineQue->size()) << std::endl;
  if(this->pipelineQue->size() < 2) return false;
  if(this->pipelineQue->try_pop(arg1))
      {
      return true;
      }
  return false;
  }

void C_CameraManager::startTracking()
  {
  *this->roistatus = initZone;

  this->filterFlags->setObjectDetection(true);
  this->filterFlags->setRoiAdjustment(true);
  this->filterFlags->setTrackingActive(true);
  }

void C_CameraManager::stopTracking()
  {

  }


//MAIN PIPELINE DER KAMERAVERFOLGUNG

//STEP 1: Steuert die Pipeline durch erzwingen eines Bufferflushes oder eine Anweisung zur Terminierung der derzeitigen Ausführung
//Erzeugt ansonsten eine neue Payload für die Pipeline und setzt die derzeit verwendeten Parameter

void C_CameraManager::pipelineTracking(std::vector<Camera::C_Camera2*> vecCameras, tbb::concurrent_bounded_queue<S_pipelinePayload*>* que)
  {
//    +--------+----+----+----+----+------+------+------+------+
//    |        | C1 | C2 | C3 | C4 | C(5) | C(6) | C(7) | C(8) |
//    +--------+----+----+----+----+------+------+------+------+
//    | CV_8U  |  0 |  8 | 16 | 24 |   32 |   40 |   48 |   56 |
//    | CV_8S  |  1 |  9 | 17 | 25 |   33 |   41 |   49 |   57 |
//    | CV_16U |  2 | 10 | 18 | 26 |   34 |   42 |   50 |   58 |
//    | CV_16S |  3 | 11 | 19 | 27 |   35 |   43 |   51 |   59 |
//    | CV_32S |  4 | 12 | 20 | 28 |   36 |   44 |   52 |   60 |
//    | CV_32F |  5 | 13 | 21 | 29 |   37 |   45 |   53 |   61 |
//    | CV_64F |  6 | 14 | 22 | 30 |   38 |   46 |   54 |   62 |
//    +--------+----+----+----+----+------+------+------+------+
  int frameheight = this->vecCameras->at(0)->getFrameHeight();
  int framewidth = this->vecCameras->at(0)->getFrameWidth();
  std::cout << "**INFO** Thread " <<   std::this_thread::get_id() << " alive!" << std::endl;


  tbb::parallel_pipeline(3, tbb::make_filter<void, S_pipelinePayload*>(tbb::filter::serial_in_order, [&](tbb::flow_control& fc)->S_pipelinePayload*
    {
    //Flush ist aktiv, wenn die aktuell verwendeten Kameras gewechselt werden
    if(this->pipelineFlush)
      std::this_thread::sleep_for (std::chrono::milliseconds (100));

    //Flowcontrol steuert die Pipeline und beendet sie, falls pipelineDone true sein sollte
    if(pipelineDone)
      {
      std::cout << "**INFO** Pipeline stopped! " << std::endl;
      fc.stop();
      return 0;
      }
    if(que->size() >=10)
      {
      return nullptr;
      }
    else
     {
     //Erzeuge eine neue Payload
     CameraManager::S_pipelinePayload* pData          = new S_pipelinePayload;
     //Messung der aktuellen Zeit zur Berechnung der derzeitigen FPS
     pData->fpsStart = Clock::now();
     //Hole Lock um eineindeutigen Access an arrActiveCameras
     std::lock_guard<std::mutex> lck (*this->lock);
     for(int i = 0; i < payloadSize; i++)
       {
       //Initialisiere i cpu Mat Objekte
       pData->cpuSrcImg[i].create (frameheight, framewidth, CV_32SC1);//CV_32FC1);
       pData->cameraID[i]     = arrActiveCameras[i];
       if (pData->cameraID[i] > globalObjects->absCameras)
         {
         fc.stop();
         delete (pData);
         return 0;
         }

       pData->Filter[i]       = *vecCameras[pData->cameraID[i]]->getFilterproperties();
       }

     return pData;
     }
    }
  )&

  //STEP 1: GRAB PICTURE FROM ARRAY-ACTIVE_CAMERAS
  tbb::make_filter<S_pipelinePayload*, S_pipelinePayload*>(tbb::filter::serial_in_order, [&] (S_pipelinePayload *pData)->S_pipelinePayload*
    {
    if(pData == nullptr)
        return pData;
    pData->start = Clock::now();
    //if(cntPipeline == 4) cntPipeline = 0;
    for(int i = 0; i <  payloadSize; i++)
      {
      vecCameras[pData->cameraID[i]]->grabImg();
      }
    //cntPipeline++;
    pData->timestamp = Clock::now();
    pData->end = Clock::now();
    pData->executionTime[0] = std::chrono::duration_cast<milliseconds>(pData->end - pData->start);

    return pData;
    }
  )&

  tbb::make_filter<S_pipelinePayload*, S_pipelinePayload*>(tbb::filter::serial_in_order, [&] (S_pipelinePayload *pData)->S_pipelinePayload*
    {
    if(pData == nullptr)
      return pData;

    pData->start = Clock::now();
    for(int i = 0; i <  payloadSize; i++)
      {
      vecCameras[pData->cameraID[i]]->retrieveImg(pData->cpuSrcImg[i]);
      if(pData->cpuSrcImg[i].type() != CV_8UC3)
        {
        delete(pData);
        pData = nullptr;
        return pData;
        }
      }

    pData->end = Clock::now();
    pData->executionTime[1] = std::chrono::duration_cast<milliseconds>(pData->end - pData->start);
    return pData;
    }
  )&

  //STEP 2: UNDISTORT SRC TO CPUDISTORT
  tbb::make_filter<S_pipelinePayload*, S_pipelinePayload*>(tbb::filter::serial_in_order, [&] (S_pipelinePayload *pData)->S_pipelinePayload*
    {
    if(pData == nullptr)
      return pData;

    pData->start = Clock::now();
    if(!this->filterFlags->undistordActive)
    {
    pData->end = Clock::now();
    pData->executionTime[2] = std::chrono::duration_cast<milliseconds>(pData->end - pData->start);
    return pData;
    }

    int i = 0;
    for(auto it = std::begin(pData->cpuSrcImg); it< std::end(pData->cpuSrcImg); it++)
      {
      if(!it->empty())
        {
        cv::cuda::GpuMat temp;
        this->ImageFilter->gpufUnidstord(it, temp, *vecCameras[pData->cameraID[i]]->getXMap(), *vecCameras[pData->cameraID[i]]->getYMap());
        switch (*roistatus)
          {
          case initZone:
            for(int i = 0; i < payloadSize; i++)
              {
              cv::Rect initRoi;
              initRoi.y = 1;
              initRoi.height = initZoneHeight-1;
              initRoi.width = initZoneWidth;
              if(pData->cameraID[i] == 0 || pData->cameraID[i] %2 ==0)
                  initRoi.x = frameWidth-initZoneWidth-1;
              else
                  initRoi.x = 1;
              this->vecCameras->at(pData->cameraID[i])->setRoi(&initRoi);
              }
           break;
          case objectLost:
            for(int i = 0; i < payloadSize; i++)
            {
            this->vecCameras->at(pData->cameraID[i])->filterValues->setOffset(0, 0);
            this->vecCameras->at(pData->cameraID[i])->filterValues->setOffset(1, 0);
            cv::Rect roi;
            roi.x = 1;
            roi.y = 1;
            roi.width = this->frameWidth-1;
            roi.height = this->frameHeight-1;
            this->vecCameras->at(pData->cameraID[i])->setRoi(&roi);
            }
          break;
      case objectFound:
            //DO NOTHING - Wird von Step CALCULATE OBJECT POSITION angepasst
          break;
        }//switch
      this->ImageFilter->gpuROI(temp, pData->gpuUndistortedImg[i], *vecCameras[pData->cameraID[i]]->getRoi());
      i++;
      }//if empty
      else
        {
        }
    }//for
    pData->end = Clock::now();
    pData->executionTime[2] = std::chrono::duration_cast<milliseconds>(pData->end - pData->start);
    return pData;
    }
  )&


  //STEP 3: FILTER UNDISTORT TO CPUHSV; USE CUDA
  tbb::make_filter<S_pipelinePayload*, S_pipelinePayload*>(tbb::filter::serial_in_order, [&] (S_pipelinePayload *pData)->S_pipelinePayload*
    {
    if(pData == nullptr)
      return pData;

    pData->start = Clock::now();
    if(!this->filterFlags->filterActive)
    {
    pData->end = Clock::now();
    pData->executionTime[3] = std::chrono::duration_cast<milliseconds>(pData->end - pData->start);
    return pData;
    }

    int i = 0;
    cv::cuda::GpuMat temp1; //(720, 1280, CV_8UC1)
    cv::cuda::GpuMat temp2; //(720, 1280, CV_8UC1)
    cv::cuda::GpuMat gputhresholded (720, 1280, CV_8UC1);
    for(auto it = std::begin(pData->gpuUndistortedImg); it< std::end(pData->gpuUndistortedImg); it++)
      {
        if(!it->empty())
          {
      cv::Scalar min( pData->Filter[i].getHue_min(), pData->Filter[i].getSaturation_min(), pData->Filter[i].getValue_min());
      cv::Scalar max( pData->Filter[i].getHue_max(), pData->Filter[i].getSaturation_max(), pData->Filter[i].getValue_max());

      cv::cuda::cvtColor                (*it,temp1,cv::COLOR_BGR2HSV);
      this->ImageFilter->gpufGaussian   (temp1,temp2, pData->Filter[i]);
      onCuda::imageProcessing::inRange     (temp2,min, max,gputhresholded);
      this->ImageFilter->gpufOpen       (gputhresholded,temp2, pData->Filter[i]);
      this->ImageFilter->gpufClose      (temp2,temp1, pData->Filter[i]);
      //cv::cuda::cvtColor                (temp1, temp2 ,cv::COLOR_GRAY2BGR);
      if(this->filterFlags->erosionActive)
        {
        this->ImageFilter->gpufErode(temp1, temp2, pData->Filter[i]);
        temp2.copyTo(temp1);
        }
      if(this->filterFlags->dilationActive)
        {
        this->ImageFilter->gpufDilate(temp1, temp2, pData->Filter[i]);
        temp2.copyTo(temp1);
        }
      if(this->filterFlags->morphActive)
        {
        this->ImageFilter->gpufDilate(temp1, temp2, pData->Filter[i]);
        temp2.copyTo(temp1);
        }
      if(this->filterFlags->bilateralActive)
        {
        this->ImageFilter->gpufBilateral(temp1, temp2, pData->Filter[i]);
        temp2.copyTo(temp1);
        }
      temp1.download(pData->cpuGrayImg[i]);
      (*it).download(pData->cpuUndistortedImg[i]);
        }
        else
        {
        //NULL
        }
      i++;
      }
    pData->end = Clock::now();
    pData->executionTime[3] = std::chrono::duration_cast<milliseconds>(pData->end - pData->start);
    return pData;
    }
  )&


  //STEP 4: FIND CONTOURS ON CPUHSV, DRAW ON UNDISTORT
  tbb::make_filter<S_pipelinePayload*, S_pipelinePayload*>(tbb::filter::serial_in_order, [&] (S_pipelinePayload *pData)->S_pipelinePayload*
    {
    if(pData == nullptr)
       return pData;

    pData->start = Clock::now();
    if(!this->filterFlags->objectDetectionActive)
      {
      pData->end = Clock::now();
      pData->executionTime[4] = std::chrono::duration_cast<milliseconds>(pData->end - pData->start);
      return pData;
      }

    int i = 0;

    for(auto it = std::begin(pData->cpuGrayImg); it< std::end(pData->cpuGrayImg); it +=2)
      {
      if(!it->empty())
        {
        int offsetL[2];
        int offsetR[2];
        this->vecCameras->at(pData->cameraID[i])->getFilterproperties()->getOffset(offsetL);
        this->vecCameras->at(pData->cameraID[i+1])->getFilterproperties()->getOffset(offsetR);

        if(this->ImageFilter->findContours(it,   &pData->cpuUndistortedImg[i], offsetL, *vecCameras[pData->cameraID[i]], pData->Richtungsvektoren[i], pData->ist_X[i], pData->ist_Y[i], pData->radius[i]) &&
           this->ImageFilter->findContours(it+1, &pData->cpuUndistortedImg[i+1], offsetR, *vecCameras[pData->cameraID[i+1]],pData->Richtungsvektoren[i+1], pData->ist_X[i+1], pData->ist_Y[i+1], pData->radius[i+1] ))
          {
          if(*pData->ist_X < 0 || *pData->ist_X > this->frameWidth || *pData->ist_Y < 0 || *pData->ist_Y > this->frameHeight)
            {
            std::cout << "***ERROR*** Position out of bounds detected. X = " << *pData->ist_X << "; Y = " << *pData->ist_Y << std::endl;
            pData->found = false;
            if(*this->roistatus == objectFound)
               *roistatus = objectLost;
            break;
            }
          pData->found = true;
          *this->roistatus = objectFound;
          }
        else
          {
          pData->found = false;
          pData->Richtungsvektoren[i].X = 0.0;
          pData->Richtungsvektoren[i].Y = 0.0;
          pData->Richtungsvektoren[i].Z = 0.0;
          pData->Richtungsvektoren[i+1].X = 0.0;
          pData->Richtungsvektoren[i+1].Y = 0.0;
          pData->Richtungsvektoren[i+1].Z = 0.0;
          if(*this->roistatus == objectFound)
              *roistatus = objectLost;
          }
        }
      else
      {
      //NULL
      }
      i++;
      }
    for(int i = 0; i < payloadSize; i++)
      {
      this->trackingManager->setRichtungsvektor(&pData->Richtungsvektoren[i], i);
      }
    pData->end = Clock::now();
    pData->executionTime[4] = std::chrono::duration_cast<milliseconds>(pData->end - pData->start);
    return pData;
    }
  )&


  //STEP 5: CALCULATE OBJECT POSITION
  tbb::make_filter<S_pipelinePayload*, S_pipelinePayload*>(tbb::filter::serial_in_order, [&] (S_pipelinePayload *pData)->S_pipelinePayload*
    {
    if(pData == nullptr)
      return pData;

    pData->start = Clock::now();
    if(!this->filterFlags->trackingActive)
    {
    pData->end = Clock::now();
    pData->executionTime[6] = std::chrono::duration_cast<milliseconds>(pData->end - pData->start);
    return pData;
    }
    if(pData->found)
      {
      this->trackingManager->setTime();
      this->trackingManager->Get_Position_ObjectTracking    (pData->objektVektor);
      this->trackingManager->calcObjectVeloctiy             (pData->objektVektor);

      for(int i =0; i < payloadSize; i++)
        {
        this->trackingManager->calcPixelVeloctiy              (pData->ist_X[i], pData->ist_Y[i], pData->cameraID[i], pData->pred_X[i], pData->pred_Y[i]);
        }
      //Überprüfe ob das verfolgte Objekt sich dem Rand des derzeitigen Kamerapaares nähert. Falls true wird das nächste Kamerapaar in arrActiveCameras geladen und das predicted ROI + Toleranz gesetzt.
//      if(pData->ist_X[0] > this->transferZoneWidth)
//        {
//        int newCam[2];
//        newCam[0] = pData->cameraID[0] + 1;
//        newCam[1] = pData->cameraID[1] + 1;
////        vecCameras[newCam[0]]->setTrackingRoi(pData->radius[0], pData->radius[0],pData->pred_Y[0]);
////        vecCameras[newCam[1]]->setTrackingRoi(pData->radius[1], pData->radius[1],pData->pred_Y[1]);
//        std::lock_guard<std::mutex> lck (*this->lock);
//        this->arrActiveCameras[0] = newCam[0];
//        this->arrActiveCameras[1] = newCam[1];
//        }
//      for(int i = 0; i < payloadSize; i++)
//        {
//        this->vecCameras->at(pData->cameraID[i])->setTrackingRoi(pData->radius[i], pData->pred_X[i],pData->pred_Y[i]);
//        }

//          for(int i = 0; i < payloadSize; i++)
//            {
//            this->vecCameras->at(pData->cameraID[i])->setTrackingRoi(pData->radius[i], pData->ist_X[i],pData->ist_Y[i]);
//            }


      }
    *pData->objectVelocity = this->trackingManager->getObjectVelocity();
    *pData->objectAcceleration = this->trackingManager->getObjectAcceleration();

    pData->end = Clock::now();
    pData->executionTime[6] = std::chrono::duration_cast<milliseconds>(pData->end - pData->start);
    return pData;
    }
  )&


  //STEP 6: ADJUST ROI ON CPU UNDISTORT ****NOT NEEDED******
  tbb::make_filter<S_pipelinePayload*, S_pipelinePayload*>(tbb::filter::serial_in_order, [&] (S_pipelinePayload *pData)->S_pipelinePayload*
    {
    if(pData == nullptr)
       return pData;

    pData->start = Clock::now();
    if(!this->filterFlags->roiAdjustmentActive)
    {
    pData->end = Clock::now();
    pData->executionTime[5] = std::chrono::duration_cast<milliseconds>(pData->end - pData->start);
    return pData;
    }

//    switch (this->roistatus)
//      {
//      case initZone:
//        for(int i = 0; i < payloadSize; i++)
//          {
//          cv::Rect initRoi;
//          initRoi.x = 1;
//          initRoi.y = 1;
//          initRoi.width = initZoneWidth;
//          initRoi.height = initZoneHeight-1;

//          this->vecCameras[pData->cameraID[i]]->setRoi(&initRoi);
//          }
//        return pData;
//      case objectLost:
//        for(int i = 0; i < payloadSize; i++)
//          {
//          this->vecCameras[pData->cameraID[i]]->filterValues->setOffset(0, 0);
//          this->vecCameras[pData->cameraID[i]]->filterValues->setOffset(1, 0);
//          cv::Rect roi;
//          roi.x = 1;
//          roi.y = 1;
//          roi.width = this->frameWidth-1;
//          roi.height = this->frameHeight-1;
//          this->vecCameras[pData->cameraID[i]]->setRoi(&roi);
//          }


//        break;
//      case objectFound:
//        for(int i = 0; i < payloadSize; i++)
//          {
//          this->vecCameras[pData->cameraID[i]]->setTrackingRoi(pData->radius[i], pData->pred_X[i],pData->pred_Y[i]);
//          }
//        break;
//      }
      pData->end = Clock::now();
      pData->executionTime[5] = std::chrono::duration_cast<milliseconds>(pData->end - pData->start);
      return pData;
    }//make_filter
  )&

  //STEP 7: FINAL PUSH TO QUE
  tbb::make_filter<S_pipelinePayload*,void>(tbb::filter::serial_in_order, [&] (S_pipelinePayload *pData)
    {
    if(pData != nullptr)
    {
    pData->start            = Clock::now();
    // TBB NOTE: pipeline end point. dispatch to GUI
    pData->fpsEnd           = Clock::now();
    pData->frametime        = std::chrono::duration_cast<std::chrono::milliseconds>(pData->fpsEnd - pData->fpsStart);
    //this->globalObjects->watchdog->pet();
    pData->end              = Clock::now();
    pData->executionTime[7] = std::chrono::duration_cast<milliseconds>(pData->end - pData->start);
    pData->queBuffer        = que->size();

    //try to push pData into que if space is available
    if(!que->try_push(pData))
        delete pData;

    //end flushing process if Que is of size 0
    if(que->size() == 0)
        this->pipelineFlush.store(false);
    }

     }//STEP 5
    )//tbb::makefilter
  );//tbb pipeline
  std::cout << "**INFO** Thread " <<   std::this_thread::get_id() << " dying!" << std::endl;

}


/********************************************************* GETTER SETTER *********************************************/
bool S_filterflags::getOpenActive() const
  {
  return openActive;
  }

void S_filterflags::setOpenActive(bool value)
  {
  openActive = value;
  }

bool S_filterflags::getCloseActive() const
  {
  return closeActive;
  }

void S_filterflags::setCloseActive(bool value)
  {
  closeActive = value;
  }

bool S_filterflags::getFilterActive() const
  {
  return filterActive;
  }

void S_filterflags::setFilterActive(bool value)
  {
  filterActive = value;
  }

bool S_filterflags::getObjectDetection() const
  {
  return objectDetectionActive;
  }

void S_filterflags::setObjectDetection(bool value)
  {
  objectDetectionActive = value;
  }

bool S_filterflags::getRoiAdjustment() const
  {
  return roiAdjustmentActive;
  }

void S_filterflags::setRoiAdjustment(bool value)
  {
  roiAdjustmentActive = value;
  }

bool S_filterflags::getTrackingActive() const
  {
  return trackingActive;
  }

void S_filterflags::setTrackingActive(bool value)
  {
  trackingActive = value;
  }

bool S_filterflags::getErosionActive() const
  {
  return erosionActive;
  }

void S_filterflags::setErosionActive(bool value)
  {
  erosionActive = value;
  }

bool S_filterflags::getDilationActive() const
  {
  return dilationActive;
  }

void S_filterflags::setDilationActive(bool value)
  {
  dilationActive = value;
  }

bool S_filterflags::getGaussianActive() const
  {
  return gaussianActive;
  }

void S_filterflags::setGaussianActive(bool value)
  {
  gaussianActive = value;
  }

bool S_filterflags::getMorphActive() const
  {
  return morphActive;
  }

void S_filterflags::setMorphActive(bool value)
  {
  morphActive = value;
  }

bool S_filterflags::getBilateralActive() const
  {
  return bilateralActive;
  }

void S_filterflags::setBilateralActive(bool value)
  {
  bilateralActive = value;
  }

bool S_filterflags::getUndistordActive() const
  {
  return undistordActive;
  }

void S_filterflags::setUndistordActive(bool value)
  {
  undistordActive = value;
}

std::mutex *C_CameraManager::getLock() const
{
    return lock;
}

void C_CameraManager::setLock(std::mutex *value)
{
  lock = value;
  }

S_filterflags *C_CameraManager::getFilterFlags() const
  {
  return filterFlags;
  }

void C_CameraManager::setFilterFlags(S_filterflags *value)
  {
  filterFlags = value;
  }

bool C_CameraManager::getCalibrationDone() const
  {
  return calibrationDone;
  }

void C_CameraManager::setCalibrationDone(volatile bool value)
  {
  calibrationDone = value;
  }

int  C_CameraManager::getArrActiveCameras(int position) const
  {
  return this->arrActiveCameras[position];
  }
void C_CameraManager::setArrActiveCameras                (int value, int position)
  {
  if (value > this->globalObjects->absCameras) return;
  this->arrActiveCameras[position] = value;
  }

void C_CameraManager::setRoiStatus(roiStatus status)
    {
    *this->roistatus = status;
    }


