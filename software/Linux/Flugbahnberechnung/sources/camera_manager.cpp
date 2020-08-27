/****************************************************************** Includes ****************************************************************/
#include "headers/camera_manager.h"


/****************************************************************** Namespaces***************************************************************/
using namespace CameraManager;
using namespace GlobalObjects;

/*************************************************************** Konstruktoren **************************************************************/
C_CameraManager::C_CameraManager ( C_GlobalObjects* GlobalObjects)
  {
  this->globalObjects   = GlobalObjects;
  this->loadManager     = new LoadManager::C_LoadManager(GlobalObjects);
  this->saveManager     = new Savemanager::c_SaveManager(GlobalObjects);
  this->ImageFilter     = new imagefilter::C_ImageFilter(GlobalObjects);
  this->lock            = new std::mutex;
  this->pipelineQue     = new tbb::concurrent_bounded_queue<CameraManager::S_pipelinePayload*>;
  this->threadQue       = new tbb::concurrent_bounded_queue<S_threadPayload*>;
  this->tData           = new S_threadPayload;

  this->payData           = new S_pipelinePayload;

  this->trackingManager = new trackingManager::C_trackingManager(GlobalObjects);
  this->filterFlags     = new S_filterflags;
  this->camera_id       = 0;
  this->frameWidth      = 1280;
  this->frameHeight     = 720;
  this->arrActiveCameras[0] = 0;
  this->arrActiveCameras[1] = 0;
  this->arrActiveCameras[2] = 0;
  this->arrActiveCameras[3] = 0;
  this->cntPipeline         = 0;
  this->calibrationDone     = false;
  this->positioningDone     = false;
  this->pipelineDone        = 0;
  this->initZoneWidth       = 200;
  this->initZoneHeight      = this->frameHeight;
  this->transferZoneWidth   = frameHeight - 200;
  this->flush = false;
  this->flushComplete = false;

  }
/**************************************************************** Destruktor ****************************************************************/
C_CameraManager::~C_CameraManager ()
  {
  this->initZoneWidth   =0;
  this->initZoneHeight  = 0;
  delete (tData);
  delete (filterFlags);
  delete (trackingManager);
  delete (payData);
  delete (threadQue);
  delete (pipelineQue);
  delete (camPipeline);
  delete (lock);
  delete (ImageFilter);
  delete (saveManager);
  delete (loadManager);
  this->globalObjects = nullptr;
}

bool C_CameraManager::getFlush() const
{
    return flush;
}

void C_CameraManager::setFlush(bool value)
{
    flush = value;
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

bool C_CameraManager::getPositioningDone() const
  {
  return positioningDone;
  }

void C_CameraManager::setPositioningDone(volatile bool value)
  {
  positioningDone = value;
  }

bool C_CameraManager::getPipelineDone() const
  {
  return pipelineDone;
  }

void C_CameraManager::setPipelineDone(volatile bool value)
  {
  pipelineDone = value;
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

/*************************************************** Nicht öffentliche private Methoden *****************************************************/

void C_CameraManager::start_camera_thread ()
  {

  }
/******************************************************* Öffentliche Anwender-Methoden ******************************************************/

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
          vecCameras.push_back            (camera);
          this->globalObjects->absCameras++;
      }
    std::cout << "**INFO** Cameraspeed is \033[1m\033[33m" << this->vecCameras[0]->getFPS() << "\033[0m fps" << std::endl;
    std::cout << "**INFO** Created \033[1m\033[31m" << std::to_string(this->globalObjects->absCameras) << " \033[0m Devices" << std::endl;

    }

  //Reorder recently created Cameras
  this->loadManager->loadCameraPositioning(this->vecCameras);
                  //this->mvVecCamera2Temp(*globalObjects->camera_order);

  //Load Settings and Calibration for each camera created earlier
  loadCameras();



  return true;
  }
bool C_CameraManager::closeCameras ()
  {
  for (auto it = std::begin(vecCameras); it < std::end(vecCameras); it++)
    {
    (*it)->close();
      delete(*it);
    }
  return true;
  }

void C_CameraManager::loadCameras              ()
  {
  for (auto it = std::begin(vecCameras); it < std::end(vecCameras); it++)
    {
    this->loadManager->loadCameraCalibration(*it);
    this->loadManager->loadCameraSettings(*it);
    this->loadManager->loadCameraCos(*it);
    this->trackingManager->load_posen(*(*it)->getCameraPose());
    (*it)->initRectifyMap();
    }
  }
bool C_CameraManager::startThreadCameraPositioning()
  {
  threadQue->set_capacity(4);
  this->camPositioning     = new thread(&CameraManager::C_CameraManager::threadHelper,this);
  std::cout << "**INFO** Kamerathread wurde gestartet" << std::endl;
  return true;
  }
bool C_CameraManager::stopThreadCameraPositioning()
  {
    this->positioningDone = true;
    this->camPositioning->detach();
    printf("\n**INFO** Kamerathread wurde gestoppt");
  return true;
   }
bool C_CameraManager::startPipelineTracking  (bool undistordActive, bool openActive, bool closeActive,  bool filterActive, bool objectDetectionActive,  bool roiAdjustmentActive, bool trackingActive)
  {
  pipelineQue->set_capacity(4);
  this->filterFlags->undistordActive        = undistordActive;
  this->filterFlags->openActive             = openActive;
  this->filterFlags->filterActive           = filterActive;
  this->filterFlags->objectDetectionActive  = objectDetectionActive;
  this->filterFlags->closeActive            = closeActive;
  this->filterFlags->roiAdjustmentActive    = roiAdjustmentActive;
  this->filterFlags->trackingActive         = trackingActive;
  for(auto it = std::begin(vecCameras); it < std::end(vecCameras); it++)
  this->camPipeline     = new thread(&CameraManager::C_CameraManager::pipelineHelper,this);

  printf("\n**INFO** Kamerapipeline wurde gestartet");
  return true;
  }
bool C_CameraManager::stopPipelineTracking()
  {
  this->pipelineDone = true;
  this->camPipeline->detach();
  printf("\n**INFO** Kamerapipeline wurde gestoppt");
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


    vecTempCameras.resize(this->vecCameras.size());
        for(int i = 0; i < globalObjects->absCameras; i++)
          {
          //vecTempCameras[vecCamOrder[i]] = std::move(this->vecCameras[i]);
          vecTempCameras[vecCamOrder[i]] = this->vecCameras[i];

          }
        this->vecCameras.clear();
        this->vecCameras.resize(vecTempCameras.size());
     for (int i = 0; i < globalObjects->absCameras; i++)
          {
          //this->vecCameras[i] = std::move (vecTempCameras[i]);
         this->vecCameras[i] = vecTempCameras[i];
          }
  }
void C_CameraManager::mvTemp2VecCamera (std::vector<Camera::C_Camera2*> vecCamerastemp)
  {
  for (int i = 0; i < globalObjects->absCameras; i++)
    {
    this->vecCameras[i] = std::move (vecCamerastemp[i]);
    }
  }

void C_CameraManager::calibrateSingleCamera (int current_camera_id,
                                             int absCornersWidth,
                                             int absCornersHeight,
                                             int absBoardImg,
                                             float absCornerLength)
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
  cv::calibrateCamera (Object_Points,Image_Points,Originalbild.size(),intrinsic,distCoeffs,Rvecs,Tvecs);

  std::cout << "Calculation finished. Saving data." << endl << endl;

  //Kopieren der berechneten Daten zur dazugehörigen Kamera
  vecCameras[current_camera_id]->setIntrinsic(intrinsic);
  vecCameras[current_camera_id]->setDistCoeffs(distCoeffs);

  //Speichern der berechenten Daten in CSV Datei
  this->saveManager->saveCameraCalibration(*vecCameras[current_camera_id]);
  //Reaktivierung der Bildentzerrung
  this->vecCameras[current_camera_id]->initRectifyMap();
  }
void C_CameraManager::calibrate_stereo_camera (int current_camera_id,
                                               int absCornersWidth,
                                               int absCornersHeight,
                                               int absBoardImg,
                                               float absCornerLength)
  {
    this->calibrationDone = false;
  vector<vector<cv::Point3f>>   object_points;
  vector<vector<cv::Point2f>>   imagePoints1;
  vector<vector<cv::Point2f>>   imagePoints2;
  vector<vector<cv::Point2f>>   left_img_points;
  vector<vector<cv::Point2f>>   right_img_points;

  vector<cv::Point2f>           corners1;
  vector<cv::Point2f>           corners2;

  cv::Mat img1;
  cv::Mat img2;
  cv::Mat gray1;
  cv::Mat gray2;

  int photoID        = 0;
  int absError = 0;

  cv::Size board_size = cv::Size (absCornersWidth,absCornersHeight);
  //int      board_n    =           this->numCornersWidth * this->numCornersHeight;


  //Iterate over all available photos
  while (photoID < absBoardImg)
    {
    //char left_img[100], right_img[100];
    img1 = cv::imread ("../Parameter/Bilder/Camera_Stereo_Calibration_" + std::to_string (current_camera_id) + "_Snapshot_" + std::to_string (photoID) + ".png",1);
    img2 = cv::imread ("../Parameter/Bilder/Camera_Stereo_Calibration_" + std::to_string (current_camera_id+1) + "_Snapshot_" + std::to_string (photoID) + ".png",1);

    cv::cvtColor (img1,gray1,cv::COLOR_BGR2GRAY);
    cv::cvtColor (img2,gray2,cv::COLOR_BGR2GRAY);

    bool found1 = false;
    bool found2 = false;

    found1 = cv::findChessboardCorners (img1,board_size,corners1,
                                        cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_FILTER_QUADS);
    found2 = cv::findChessboardCorners (img2,board_size,corners2,
                                        cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_FILTER_QUADS);


    if (!found1 || !found2)
      {
      std::cout << "Chessboard find error!" << endl;
      std::cout << "Setnumber: " << photoID << endl;
      photoID++;
      absError++;
      continue;
      }

    if (found1)
      {
      cv::cornerSubPix (gray1,corners1,cv::Size (5,5),cv::Size (-1,-1),
                        cv::TermCriteria (cv::TermCriteria::EPS | cv::TermCriteria::MAX_ITER,30,0.1));
      cv::drawChessboardCorners (gray1,board_size,corners1,found1);
      }
    if (found2)
      {
      cv::cornerSubPix (gray2,corners2,cv::Size (5,5),cv::Size (-1,-1),
                        cv::TermCriteria (cv::TermCriteria::EPS | cv::TermCriteria::MAX_ITER,30,0.1));
      cv::drawChessboardCorners (gray2,board_size,corners2,found2);
      }

    cv::imwrite ("../Parameter/Bilder/Camera_Stereo_Calibration_" + std::to_string (camera_id) + "_Gray_DrawCorners_" + std::to_string (photoID) + ".png",gray1);
    cv::imwrite ("../Parameter/Bilder/Camera_Stereo_Calibration_" + std::to_string (camera_id + 1) + "_Gray_DrawCorners_" + std::to_string (photoID) + ".png",gray2);

    vector<cv::Point3f> obj;
    for (int i = 0; i < absCornersHeight; i++)
      {
      for (int j = 0; j < absCornersWidth; j++)
        {
        obj.emplace_back (static_cast<float> (j) * absCornerLength,static_cast<float> (i) * absCornerLength,0);
        }
      }


    if (found1 && found2)
      {
      imagePoints1.push_back (corners1);
      imagePoints2.push_back (corners2);
      object_points.push_back (obj);
      }
    photoID++;
    }//  while (this->Photo_ID < this->numBoards_imgs)

  std::cout << endl << "Analyzed " << photoID - absError << " out of " << photoID << " source immages successfully." << endl;

  for (int i = 0; i < static_cast<int>(imagePoints1.size()); i++)
    {
    vector<cv::Point2f> v1, v2;
    for (int j = 0; j < static_cast<int>(imagePoints1[i].size()); j++)
      {
      v1.emplace_back (static_cast<double> (imagePoints1[i][j].x),static_cast<double> (imagePoints1[i][j].y));
      v2.emplace_back (static_cast<double> (imagePoints2[i][j].x),static_cast<double> (imagePoints2[i][j].y));
      }
    left_img_points.push_back (v1);
    right_img_points.push_back (v2);
    }
/********************************** STEREO CALIBRATE METHODE ***********************/
    std::cout << "Starting Calibration" << endl;
    cv::Mat   K1, K2, F, E;
    cv::Mat R(3, 3, CV_64F);
    cv::Mat T(3, 1, CV_64F);

    //cv::Vec3d T;
    cv::Mat   D1, D2;
    //cv::InputOutputArfilterFlagsray R, T;
    this->vecCameras[current_camera_id]->getIntrinsic()->copyTo(K1);
    this->vecCameras[current_camera_id + 1]->getIntrinsic()->copyTo(K2);
    this->vecCameras[current_camera_id]->getDistCoeffs()->copyTo(D1);
    this->vecCameras[current_camera_id + 1]->getDistCoeffs()->copyTo(D2);

    cv::stereoCalibrate (object_points,left_img_points,right_img_points,K1,D1,K2,D2,img1.size(),R,T,E,F,cv::CALIB_FIX_INTRINSIC);
    std::cout << "/********************************** STEREO CALIBRATE METHODE ***********************/" << endl << endl;
    std::cout << "Essential Calibration R" << endl << R << endl << endl;
    std::cout << "Essential Calibration T" << endl << T << endl << endl;
    std::cout << "Essential Calibration E" << endl << E << endl << endl << endl;


/****************************************** MANUAL METHODE ******************************/
    std::cout << "/********************************** MANUAL METHODE ***********************/" << endl << endl;
    int objposition = 0;
  cv::Mat                          distCoeffs;
  cv::Mat                          intrinsic;
  cv::Mat rvecPNPL(cv::Mat_<double>(1,3));
  cv::Mat rvecPNPR(cv::Mat_<double>(1,3));
  cv::Mat tvecPNP(cv::Mat_<double>(1,3));
  cv::Mat tvecPNPR(cv::Mat_<double>(1,3));
  cv::Mat tvecPNPL(cv::Mat_<double>(1,3));

  cv::Mat rvecPNP;

  cv::Mat rodriguesPNPL, rodriguesPNPR;
  vector<cv::Point2f>   imgPointsLReturn;
  vector<cv::Point2f>   imgPointsRReturn;

  //Berechne Objekt zu Kamera Matrix
  vecCameras[current_camera_id]->getDistCoeffs()->copyTo(distCoeffs);
  vecCameras[current_camera_id]->getIntrinsic()->copyTo(intrinsic);
  cv::solvePnP(object_points[objposition], left_img_points[objposition], intrinsic,  distCoeffs, rvecPNPL, tvecPNPL, false, cv::SOLVEPNP_IPPE);
  std::cout << "rvecPNPL: " << endl << rvecPNPL << std::endl << std::endl;
  std::cout << "tvecPNPL: " << endl << tvecPNPL << std::endl << std::endl << std::endl;


  vecCameras[current_camera_id+1]->getDistCoeffs()->copyTo(distCoeffs);
  vecCameras[current_camera_id+1]->getIntrinsic()->copyTo(intrinsic);
  cv::solvePnP(object_points[objposition], right_img_points[objposition], intrinsic,  distCoeffs, rvecPNPR, tvecPNPR, false, cv::SOLVEPNP_IPPE);

  std::cout << "rvecPNPR: " << endl << rvecPNPR << std::endl << std::endl;
  std::cout << "tvecPNPR: " << endl << tvecPNPR << std::endl << std::endl << std::endl;

  cv::Rodrigues(rvecPNPL, rodriguesPNPL);
  cv::Rodrigues(rvecPNPR, rodriguesPNPR);

  std::cout << "rodriguesPNPL: " << endl << rodriguesPNPL << std::endl << std::endl;
  std::cout << "rodriguesPNPR: " << endl << rodriguesPNPR << std::endl << std::endl << std::endl;




  //Kamera L zu Kamera R Matrix
  rvecPNP = rodriguesPNPL.inv() * rodriguesPNPR;
  tvecPNP  = rodriguesPNPL.inv() * (tvecPNPR- tvecPNPL);

  std::cout << "rvecPNP: " << endl << rvecPNP << std::endl << std::endl;
  std::cout << "tvecPNP: " << endl << tvecPNP << std::endl << std::endl << std::endl;

  //Überprüfe die jeweiligen rvec/tvec auf Differenz
  vecCameras[current_camera_id]->getIntrinsic()->copyTo(intrinsic);
  vecCameras[current_camera_id]->getDistCoeffs()->copyTo(distCoeffs);
  cv::projectPoints(object_points[objposition], rvecPNPL, tvecPNPL, intrinsic, distCoeffs, imgPointsLReturn);

  vecCameras[current_camera_id+1]->getIntrinsic()->copyTo(intrinsic);
  vecCameras[current_camera_id+1]->getDistCoeffs()->copyTo(distCoeffs);
  cv::projectPoints(object_points[objposition], rvecPNPR, tvecPNPR, intrinsic, distCoeffs, imgPointsRReturn);

  cv::Mat difL, difR;

  cv::absdiff(left_img_points[objposition], imgPointsLReturn, difL);
  cv::absdiff(right_img_points[objposition], imgPointsRReturn, difR);
  std::cout << "difL: " <<  endl << difL << std::endl << std::endl;
  std::cout << "difR: " << endl << difR << std::endl << std::endl << std::endl;

  cv::Mat Eleft, Eright, manEssentialRVecR, manEssentialRVecL, manEssentialTVecR, manEssentialTVecL;
  vecCameras[current_camera_id+1]->getIntrinsic()->copyTo(intrinsic);

  Eleft = cv::findEssentialMat(left_img_points[objposition], right_img_points[objposition], intrinsic,cv::RANSAC, 0.999, 2.0);
  cv::recoverPose(Eleft, left_img_points[objposition], right_img_points[objposition], intrinsic, manEssentialRVecL, manEssentialTVecL);
  std::cout << "essential Left: " << endl << Eleft << std::endl;
  std::cout << "rvecL: " << endl << manEssentialRVecL << std::endl;
  std::cout << "tvecL: " << endl << manEssentialTVecL << std::endl << std::endl;
  vecCameras[current_camera_id+1]->getIntrinsic()->copyTo(intrinsic);

   Eright = cv::findEssentialMat(right_img_points[objposition], left_img_points[objposition], intrinsic,cv::RANSAC, 0.999, 2.0);
   cv::recoverPose(Eright, right_img_points[objposition], left_img_points[objposition], intrinsic, manEssentialRVecR, manEssentialTVecR);
   std::cout << "essential right: " << endl << Eright << std::endl;
   std::cout << "rvecR: " << endl << manEssentialRVecR << std::endl;
   std::cout << "tvecR: " << endl << manEssentialTVecR << std::endl << std::endl;

   cv::Mat imgL = cv::imread ("../Parameter/Bilder/Camera_Stereo_Calibration_" + std::to_string (current_camera_id) + "_Snapshot_" + std::to_string (0) + ".png",1);
   cv::Mat imgR = cv::imread ("../Parameter/Bilder/Camera_Stereo_Calibration_" + std::to_string (current_camera_id+1) + "_Snapshot_" + std::to_string (0) + ".png",1);
   int x,y;
   x = left_img_points[objposition][0].x;
   y = left_img_points[objposition][0].y;

   cv::circle(imgL, cv::Point(x,y), 1, cv::Scalar(255,0,255), 5, cv::LINE_8, 0);
   x = right_img_points[objposition][0].x;
   y = right_img_points[objposition][0].y;

   cv::circle(imgR, cv::Point(x,y), 1, cv::Scalar(255,0,255), 5, cv::LINE_8, 0);
   cv::imwrite ("../Parameter/Bilder/_Draw_" + std::to_string (camera_id) + "_DrawPoint_" + std::to_string (0) + ".png",imgL);
   cv::imwrite ("../Parameter/Bilder/_Draw_" + std::to_string (camera_id + 1) + "_DrawPoint_" + std::to_string (0) + ".png",imgR);


   cv::Mat M10(cv::Mat_<double>(4,4));
   cv::Mat M20(cv::Mat_<double>(4,4));
   cv::Mat hM00(cv::Mat_<double>(4,4));
   cv::Mat M12(cv::Mat_<double>(4,4));
   cv::hconcat(manEssentialRVecL, manEssentialTVecL, M10);
   cv::hconcat(manEssentialRVecR, manEssentialTVecR, M20);


   for(int i = 0; i <= 3; i ++)
     {
     for(int j = 0; j <= 3; j ++)
       {
       hM00.at<double>(i,j) =   0.0;
       }
     }
   hM00.at<double>(0,0) =   -1.0;
   hM00.at<double>(1,1) =   -1.0;
   hM00.at<double>(2,2) =   1.0;
   hM00.at<double>(3,3) =   1.0;

   hM00.at<double>(0,3) =   absCornerLength*absCornersHeight;
   hM00.at<double>(1,3) =   absCornerLength*absCornersWidth;
   std::cout << "hM00: " << endl << hM00 << std::endl << std::endl;

   cv::Mat row = cv::Mat::zeros(1, 4, CV_64F);  // 3 cols, 1 row
   M10.push_back(row);
   M20.push_back(row);



   std::cout << "M10: " << endl << M10 << std::endl << std::endl;
   std::cout << "M20: " << endl << M20 << std::endl << std::endl;


   M20.inv();

   for(int i = 0; i <= 3; i ++)
     {
     for(int j = 0; j <= 3; j ++)
       {
       M12.at<double>(i,j) =   M10.at<double>(i,j)*hM00.at<double>(i,j)*M20.at<double>(i,j);
       }
     }
   std::cout << "M12: " << endl << M12 << std::endl << std::endl << std::endl;



  /***************************************************************************/
  //https://gist.github.com/cashiwamochi/8ac3f8bab9bf00e247a01f63075fedeb
   std::cout << endl << "/********************************** GITHUB METHODE ***********************/" << endl << endl;

     cv::Mat image1 = cv::imread ("../Parameter/Bilder/Camera_Stereo_Calibration_" + std::to_string (current_camera_id) + "_Snapshot_" + std::to_string (2) + ".png",1);
     cv::Mat image2 = cv::imread ("../Parameter/Bilder/Camera_Stereo_Calibration_" + std::to_string (current_camera_id+1) + "_Snapshot_" + std::to_string (2) + ".png",1);


       // Camera intristic parameter matrix
       // I did not calibration
       cv::Mat K;
       vecCameras[current_camera_id]->getIntrinsic()->copyTo(K);

       vector<cv::KeyPoint> kpts_vec1, kpts_vec2;
       cv::Mat desc1, desc2;
       cv::Ptr<cv::AKAZE> akaze = cv::AKAZE::create();

       // extract feature points and calculate descriptors
       akaze -> detectAndCompute(image1, cv::noArray(), kpts_vec1, desc1);
       akaze -> detectAndCompute(image2, cv::noArray(), kpts_vec2, desc2);


       cv::BFMatcher* matcher = new cv::BFMatcher(cv::NORM_L2, false);
       // cross check flag set to false
       // because i do cross-ratio-test match
       vector< vector<cv::DMatch> > matches_2nn_12, matches_2nn_21;
       matcher->knnMatch( desc1, desc2, matches_2nn_12, 2 );
       matcher->knnMatch( desc2, desc1, matches_2nn_21, 2 );
       const double ratio = 0.8;

       vector<cv::Point2f> selected_points1, selected_points2;

       for(int i = 0; i < matches_2nn_12.size(); i++) { // i is queryIdx
         if( matches_2nn_12[i][0].distance/matches_2nn_12[i][1].distance < ratio
             and
             matches_2nn_21[matches_2nn_12[i][0].trainIdx][0].distance
               / matches_2nn_21[matches_2nn_12[i][0].trainIdx][1].distance < ratio )
         {
           if(matches_2nn_21[matches_2nn_12[i][0].trainIdx][0].trainIdx
                 == matches_2nn_12[i][0].queryIdx)
           {
             selected_points1.push_back(kpts_vec1[matches_2nn_12[i][0].queryIdx].pt);
             selected_points2.push_back(
                 kpts_vec2[matches_2nn_21[matches_2nn_12[i][0].trainIdx][0].queryIdx].pt
                 );
           }
         }
       }

       if(true) {
         cv::Mat src;
         cv::hconcat(image1, image2, src);
         for(int i = 0; i < selected_points1.size(); i++) {
           cv::line( src, selected_points1[i],
                     cv::Point2f(selected_points2[i].x + image1.cols, selected_points2[i].y),
                     cv::Scalar(255, 255, 0), 1, 0 );
         }
         cv::imwrite("match-result.png", src);
       }

       cv::Mat Kd;
       K.convertTo(Kd, CV_64F);
       cv::Mat mask; // unsigned char array
       cv::Mat essentialGithub = cv::findEssentialMat(selected_points1, selected_points2, Kd.at<double>(0,0),
                                // cv::Point2f(0.f, 0.f),
                                cv::Point2d(image1.cols/2., image1.rows/2.),
                                cv::RANSAC, 0.999, 1.0, mask);
       std::cout << " essentialGithub E" << endl << essentialGithub << endl << endl;

       // E is CV_64F not 32F

       vector<cv::Point2f> inlier_match_points1, inlier_match_points2;
       for(int i = 0; i < mask.rows; i++) {
         if(mask.at<unsigned char>(i)){
           inlier_match_points1.push_back(selected_points1[i]);
           inlier_match_points2.push_back(selected_points2[i]);
         }
       }

       if(true) {
         cv::Mat src;
         cv::hconcat(image1, image2, src);
         for(int i = 0; i < inlier_match_points1.size(); i++) {
           cv::line( src, inlier_match_points1[i],
                     cv::Point2f(inlier_match_points2[i].x + image1.cols, inlier_match_points2[i].y),
                     cv::Scalar(255, 255, 0), 1, 0 );
         }
         cv::imwrite("inlier_match_points.png", src);
       }

       mask.release();
       cv::Mat RGithub, tGithub;
       cv::recoverPose(essentialGithub,
                       inlier_match_points1,
                       inlier_match_points2,
                       RGithub, tGithub, Kd.at<double>(0,0),
                       // cv::Point2f(0, 0),
                       cv::Point2d(image1.cols/2., image1.rows/2.),
                       mask);
       // R,t is CV_64F not 32F
       std::cout << "rvec: " << endl << RGithub << std::endl;
       std::cout << "tvec: " << endl << tGithub << std::endl << std::endl;



       vector<cv::Point2d> triangulation_points1, triangulation_points2;
       for(int i = 0; i < mask.rows; i++) {
         if(mask.at<unsigned char>(i)){
           triangulation_points1.push_back
                        (cv::Point2d((double)inlier_match_points1[i].x,(double)inlier_match_points1[i].y));
           triangulation_points2.push_back
                        (cv::Point2d((double)inlier_match_points2[i].x,(double)inlier_match_points2[i].y));
         }
       }

       if(true) {
         cv::Mat src;
         cv::hconcat(image1, image2, src);
         for(int i = 0; i < triangulation_points1.size(); i++) {
           cv::line( src, triangulation_points1[i],
                     cv::Point2f((float)triangulation_points2[i].x + (float)image1.cols,
                                 (float)triangulation_points2[i].y),
                     cv::Scalar(255, 255, 0), 1, 0 );
         }
         cv::imwrite("triangulatedPoints.png", src);
       }

       cv::Mat Rt0 = cv::Mat::eye(3, 4, CV_64FC1);
       cv::Mat Rt1 = cv::Mat::eye(3, 4, CV_64FC1);
       RGithub.copyTo(Rt1.rowRange(0,3).colRange(0,3));
       tGithub.copyTo(Rt1.rowRange(0,3).col(3));


       cv::Mat point3d_homo;
       cv::triangulatePoints(Kd * Rt0, Kd * Rt1,
                             triangulation_points1, triangulation_points2,
                             point3d_homo);
       //point3d_homo is 64F
       //available input type is here
       //https://stackoverflow.com/questions/16295551/how-to-correctly-use-cvtriangulatepoints

       assert(point3d_homo.cols == triangulation_points1.size());


       RGithub.convertTo(RGithub, CV_32F);
       tGithub.convertTo(tGithub, CV_32F);
       std::cout << " RGithub" << endl << RGithub << endl << endl;
       std::cout << " TGithub" << endl << tGithub << endl << endl;
       //this shows how a camera moves
       cv::Mat RinvGithub = RGithub.t();
       cv::Mat TGithub = -RinvGithub * tGithub;
       std::cout << " RinvGithub R" << endl << RinvGithub << endl << endl;
       std::cout << " TGithub T" << endl << TGithub << endl << endl;

     }

void C_CameraManager::calibrate_stereo_camera_aruco(int current_camera_id, int absBoardImg)
  {
//  cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);

//  cv::Ptr<cv::aruco::CharucoBoard> board = cv::aruco::CharucoBoard::create(9, 6, 0.40f, 0.25f, dictionary);
//  cv::Mat boardImage;
//  //DINA4 3508 x 2480 px
//  board->draw(cv::Size(3200, 2200), boardImage, 10, 1);
//  cv::imwrite("../Parameter/Charuco_BoardImage_5_7_0.04f_0.02f_Size(3200, 2200).jpg", boardImage);

  cv::Ptr<cv::aruco::Dictionary>            dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);
  cv::Ptr<cv::aruco::CharucoBoard>          board = cv::aruco::CharucoBoard::create(9, 6, 0.03177f, 0.02002f, dictionary);
  cv::Ptr<cv::aruco::DetectorParameters>    params = cv::aruco::DetectorParameters::create();
  cv::Size imgSize;
  std::vector<cv::Mat>                      vecRvecR;
  std::vector<cv::Mat>                      vectvecR;
  std::vector<cv::Mat>                      vecRvecL;
  std::vector<cv::Mat>                      vectvecL;

for(int j = 0; j < 2; j ++)
  {
  std::vector<cv::Mat>                      vecRvec;
  std::vector<cv::Mat>                      vectvec;
  std::vector<std::vector<cv::Point2f>>     veccharucoCorners;
  std::vector<std::vector<int>>             veccharucoIds;
  std::cout << std::endl << "Analysiere Bilder von Kamera " << std::to_string(j+1) << std::endl;
  //Hole aktuelle Intrinsic und Verzerrungsdaten der abgefragten (j) Kamera
  cv::Mat cameraMatrix, distCoeffs;
  this->vecCameras[current_camera_id+j]->getIntrinsic()->copyTo(cameraMatrix);
  this->vecCameras[current_camera_id+j]->getDistCoeffs()->copyTo(distCoeffs);




  for(int i = j; i < absBoardImg; i++)
    {
    std::cout << std::endl << "Analysiere Bild: " << std::to_string(i) << std::endl;
    cv::Mat image;
    cv::Mat gray;
    cv::Mat imageCopy;
    image = cv::imread ("../Parameter/Bilder/Camera_Stereo_Calibration_" + std::to_string (current_camera_id+j) + "_Snapshot_" + std::to_string (i) + ".png",1);
    image.copyTo(imageCopy);
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

    imgSize = image.size();
    std::vector<int>                        markerIds;
    std::vector<std::vector<cv::Point2f>>   markerCorners;
    //rejectedPoints beschreibt alle Punkte, welche von der detectMarkers Funktion abgelehnt wurden.
    std::vector<std::vector<cv::Point2f> >  rejectedPoints;
    std::vector<cv::Point2f>               recoveredIdxs;
    std::vector<cv::Point2f>                charucoCorners;
    std::vector<int>                        charucoIds;

    cv::aruco::detectMarkers(gray, board->dictionary, markerCorners, markerIds, params,rejectedPoints,cameraMatrix, distCoeffs);
    std::cout << "Rejected Points size: " << std::to_string(rejectedPoints.size()) << std::endl;

    // if at least one marker detected
    if (markerIds.size() > 0)
      {
      //Versuche die Positionen von verdeckten Markern zu berechnen.
      //cv::aruco::refineDetectedMarkers(gray, board, markerCorners, markerIds, rejectedPoints, cameraMatrix, distCoeffs,10.f, 3.f, true, recoveredIdxs,  cv::aruco::DetectorParameters::create());
      //Zeichne alle gefundenen Marker auf das Bild
      cv::aruco::drawDetectedMarkers(imageCopy, markerCorners, markerIds);
      //This function receives the detected markers and returns the 2D position of the chessboard corners from a ChArUco board using the detected Aruco markers.
      //If camera parameters are provided, the process is based in an approximated pose estimation, else it is based on local homography.
      //Only visible corners are returned. For each corner, its corresponding identifier is also returned in charucoIds. The function returns the number of interpolated corners.
      cv::aruco::interpolateCornersCharuco(markerCorners, markerIds, image, board, charucoCorners, charucoIds, cameraMatrix, distCoeffs, 2);
      // if at least one charuco corner detected
      if (charucoIds.size() > 0)
        {
        cv::Scalar color = cv::Scalar(255, 0, 0);
        cv::aruco::drawDetectedCornersCharuco(imageCopy, charucoCorners, charucoIds, color);
        cv::Vec3d rvecAxis, tvecAxis;
        // cv::aruco::estimatePoseCharucoBoard(charucoCorners, charucoIds, board, cameraMatrix, distCoeffs, rvec, tvec);
        bool valid = cv::aruco::estimatePoseCharucoBoard(charucoCorners, charucoIds, board, cameraMatrix, distCoeffs, rvecAxis, tvecAxis);
        // if charuco pose is valid
        if (valid)
        cv::aruco::drawAxis(imageCopy, cameraMatrix, distCoeffs, rvecAxis, tvecAxis, 0.4f);
        cv::imwrite ("../Parameter/Bilder/Charuco_Camera_" + std::to_string (camera_id+j) + "_Axis_img_" + std::to_string(i) + ".png",imageCopy);
        veccharucoCorners.push_back(charucoCorners);
        veccharucoIds.push_back(charucoIds);
        }
      }
    }

  cv::Mat  	stdDeviationsIntrinsics, stdDeviationsExtrinsics,  	perViewErrors;

  cv::aruco::calibrateCameraCharuco(veccharucoCorners, veccharucoIds, board, imgSize, cameraMatrix, distCoeffs, vecRvec, vectvec,
                                    stdDeviationsIntrinsics, stdDeviationsExtrinsics, perViewErrors, 0,
                                    cv::TermCriteria(cv::TermCriteria::COUNT+cv::TermCriteria::EPS, 1000, DBL_EPSILON));
  std::cout << "stdDeviationsIntrinsics: " << endl << stdDeviationsIntrinsics << std::endl << std::endl;
  std::cout << "stdDeviationsExtrinsics: " << endl << stdDeviationsExtrinsics << std::endl << std::endl;
  std::cout << "perViewErrors: " << endl << perViewErrors << std::endl << std::endl;
  if(j==0)
    {
      vecRvecL = vecRvec;
      vectvecL = vectvec;
    }
  if(j==1)
    {
      vecRvecR = vecRvec;
      vectvecR = vectvec;
    }

  }
std::vector<cv::Mat> vecM10, vecM20;
for(int i = 0; i < vecRvecL.size(); i ++)
  {
  cv::Mat M10, tempRod;
  cv::Rodrigues(vecRvecL[i], tempRod);
  cv::hconcat(tempRod, vectvecL[i], M10);

  cv::Mat row = cv::Mat::zeros(1, 4, CV_64F);  // 3 cols, 1 row
  M10.push_back(row);
  M10.at<double>(3,3) =   1.0;

  std::cout << "Marker " + std::to_string(i) + ": M10 = " << endl << M10 << std::endl << std::endl;
  vecM10.push_back(M10);
  }
for(int i = 0; i < vecRvecR.size(); i ++)
  {
    cv::Mat M20, tempRod;
    cv::Rodrigues(vecRvecR[i], tempRod);
    cv::hconcat(tempRod, vectvecR[i], M20);

    cv::Mat row = cv::Mat::zeros(1, 4, CV_64F);  // 3 cols, 1 row
    M20.push_back(row);
    M20.at<double>(3,3) =   1.0;

    std::cout << "Marker " + std::to_string(i) + ": M20 = " << endl << M20 << std::endl << std::endl;
    vecM20.push_back(M20);
  }
for(int i = 0; i < vecRvecR.size(); i ++)
  {
    cv::Mat M12(cv::Mat_<double>(4,4));
    M12 = vecM10[i].mul(vecM20[i].inv());
    std::cout << "Marker " + std::to_string(i) + ": M12 = " << endl << M12 << std::endl << std::endl;
  }


//  cv::Mat M10(cv::Mat_<double>(4,4));
//  cv::Mat M12(cv::Mat_<double>(4,4));
//  cv::Mat M20(cv::Mat_<double>(4,4));
//  cv::hconcat(vecRvec[0], vectvec[0], M10);
//  cv::hconcat(vecRvec[1], vectvec[1], M20);
//  for(int i = 0; i <= 3; i ++)
//    {
//    for(int j = 0; j <= 3; j ++)
//      {
//      M12.at<double>(i,j) =   M10.at<double>(i,j)*M20.at<double>(i,j);
//      }
//    }
//    std::cout << "M10: " << endl << M10 << std::endl << std::endl;
//    std::cout << "M20: " << endl << M20 << std::endl << std::endl;
//    std::cout << "M12: " << endl << M12 << std::endl << std::endl;


}

//  std::cout << "Starting Calibration" << endl;
//  cv::Mat   K1, K2, F, E;
//  cv::Mat R(3, 3, CV_64F);
//  cv::Mat T(3, 1, CV_64F);

//  //cv::Vec3d T;
//  cv::Mat   D1, D2;
//  //cv::InputOutputArfilterFlagsray R, T;
//  this->vecCameras[current_camera_id]->getIntrinsic()->copyTo(K1);
//  this->vecCameras[current_camera_id + 1]->getIntrinsic()->copyTo(K2);
//  this->vecCameras[current_camera_id]->getDistCoeffs()->copyTo(D1);
//  this->vecCameras[current_camera_id + 1]->getDistCoeffs()->copyTo(D2);

//  cv::stereoCalibrate (object_points,left_img_points,right_img_points,K1,D1,K2,D2,img1.size(),R,T,E,F,cv::CALIB_FIX_INTRINSIC);

//  std::cout << "K1" << endl << K1 << endl << endl;
//  std::cout << "K2" << endl << K2 << endl << endl;
//  std::cout << "D1" << endl << D1 << endl << endl;
//  std::cout << "D2" << endl << D2 << endl << endl;
//  std::cout << "F" << endl << F << endl << endl;
//  std::cout << "Done Calibration" << endl;

//  this->calculate_camera_pose(camera_id, camera_id+1, T, R);

//  this->calibrationDone = true;

//  cv::Mat relativeR(3, 3, CV_64F);
//  cv::Mat relativeT(3, 1, CV_64F);
//  cv::Mat mask;


//  cv::recoverPose(E, left_img_points, right_img_points, K1, relativeR, relativeT, mask);

//  std::cout << "relativeR" << endl << relativeR << endl << endl;
//  std::cout << "relativeT" << endl << relativeT << endl << endl;


////  std::cout << "Starting Rectification" << endl;

////  cv::Mat R1, R2, P1, P2, Q;
////  stereoRectify (K1,D1,K2,D2,img1.size(),R,T,R1,R2,P1,P2,Q);

////  std::cout << "R1" << R1 << endl;
////  std::cout << "R2" << R2 << endl;
////  std::cout << "P1" << P1 << endl;
////  std::cout << "P2" << P2 << endl;0



void C_CameraManager::threadCameraPositioning(std::vector<Camera::C_Camera2*> vecCameras, tbb::concurrent_bounded_queue<S_threadPayload*>* que)
  {
 std::cout << "**INFO** Kamerathread wurde gestartet. ID:" <<   std::this_thread::get_id() << std::endl;
  while(!this->positioningDone)
    {
      auto thData = new S_threadPayload;
      for(auto it = std::begin(vecCameras); it < std::end(vecCameras); it++)
        {
        (*it)->grabImg();
        }
      for(auto it = std::begin(vecCameras); it < std::end(vecCameras); it++)
        {
        auto img = new cv::Mat;
        (*it)->retrieveImg(*img);
        if(img->empty()) img->setTo(cv::Scalar(255,0,0));
        //(*it)->capImage(*img);
        thData->srcImg.push_back(img);
        }
      thData->queBuffer = que->size();
      if(!que->try_push(thData))
        {
          for(auto it = std::begin(thData->srcImg); it < std::end(thData->srcImg); it ++)
            {
            (*it)->release();
            delete (*it);
            }
          delete (thData);

        }
    }
  std::cout << "**INFO** Kamerathread wurde gestoppt" << std::endl;
  }
void *C_CameraManager::threadHelper(void* This)
  {
  static_cast<CameraManager::C_CameraManager*>(This)->threadCameraPositioning(static_cast<CameraManager::C_CameraManager*>(This)->vecCameras,
                                  static_cast<CameraManager::C_CameraManager*>(This)->threadQue);
  }
void C_CameraManager::calculate_camera_pose(int camera1, int camera2, cv::Vec3d T, cv::Mat R)
  {
   //P02 = P01*P12

  double HomogenePosenMatrixTempPuffer[4][4];
  for (int i=0; i < 3; i++)
    {
    for (int j=0; j < 3; j++)
      {
      HomogenePosenMatrixTempPuffer[j][i] = R.at<double>(j,i);
      }
    }
  HomogenePosenMatrixTempPuffer[3][0] = 0.0;
  HomogenePosenMatrixTempPuffer[3][1] = 0.0;
  HomogenePosenMatrixTempPuffer[3][2] = 0.0;
  HomogenePosenMatrixTempPuffer[3][3] = 1.0;
  for (int i = 0; i< 3; i++)
    {
    HomogenePosenMatrixTempPuffer[i][3] = T[i];
    }


  for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
      {
      this->vecCameras[camera2]->getCameraPose()->HomogenePosenMatrix[i][j] = 0;
      for (int k = 0; k < 4; k++)
        this->vecCameras[camera2]->getCameraPose()->HomogenePosenMatrix[i][j] += this->vecCameras[camera1]->getCameraPose()->HomogenePosenMatrix[i][k] *
                               HomogenePosenMatrixTempPuffer[k][j];
      }
    }
  this->saveManager->saveCameraCos(*this->vecCameras[camera2]);
  }//calculate_camera_pose

bool C_CameraManager::getObjectPosition2D                (trackingManager::S_trackingPayload& trackingPayload)
  {

  }


void C_CameraManager::smTracking (S_pipelinePayload* payload)
  {

  }
void *C_CameraManager::pipelineHelper(void* This)
  {
  static_cast<CameraManager::C_CameraManager*>(This)->pipelineTracking(static_cast<CameraManager::C_CameraManager*>(This)->vecCameras,
                                                                      static_cast<CameraManager::C_CameraManager*>(This)->pipelineQue);
  return 0;
  }
std::vector<cv::Mat*> C_CameraManager::getVecImgShow() const
  {
  //return *vecImgShow;
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
  int frameheight = this->vecCameras[0]->getFrameHeight();
  int framewidth = this->vecCameras[0]->getFrameWidth();
  tbb::parallel_pipeline(3, tbb::make_filter<void, S_pipelinePayload*>(tbb::filter::serial_in_order, [&](tbb::flow_control& fc)->S_pipelinePayload*
    {
    if(flush)
      std::this_thread::sleep_for (std::chrono::milliseconds (200));
    if(pipelineDone)
      {
      this->pipelineDone = true;
      fc.stop();
      return 0;
      }
    //SET IMAGES
    auto pData          = new S_pipelinePayload;
    pData->fpsStart = Clock::now();
    std::lock_guard<std::mutex> lck (*this->lock);
    for(int i = 0; i < payloadSize; i++)
      {
      pData->cpuSrcImg[i].create (frameheight, framewidth, CV_32SC1);//CV_32FC1);
      pData->cameraID[i]     = arrActiveCameras[i];
      if (pData->cameraID[i] > globalObjects->absCameras) return 0;
      pData->Filter[i]       = *vecCameras[pData->cameraID[i]]->getFilterproperties();
      }

    return pData;
    }
  )&

  //STEP 1: GRAB PICTURE FROM ARRAY-ACTIVE_CAMERAS
  tbb::make_filter<S_pipelinePayload*, S_pipelinePayload*>(tbb::filter::serial_in_order, [&] (S_pipelinePayload *pData)->S_pipelinePayload*
    {
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
    pData->start = Clock::now();
    for(int i = 0; i <  payloadSize; i++)
      {
      vecCameras[pData->cameraID[i]]->retrieveImg(pData->cpuSrcImg[i]);
      }

    pData->end = Clock::now();
    pData->executionTime[1] = std::chrono::duration_cast<milliseconds>(pData->end - pData->start);
    return pData;
    }
  )&
  //STEP 2: UNDISTORT SRC TO CPUDISTORT
  tbb::make_filter<S_pipelinePayload*, S_pipelinePayload*>(tbb::filter::serial_in_order, [&] (S_pipelinePayload *pData)->S_pipelinePayload*
    {
    pData->start = Clock::now();
    if(!this->filterFlags->undistordActive) return pData;
    int i = 0;
    for(auto it = std::begin(pData->cpuSrcImg); it< std::end(pData->cpuSrcImg); it++)
      {
      if(it->empty()) return pData;
      this->ImageFilter->gpufUnidstord(it, pData->gpuUndistortedImg[i], *vecCameras[pData->cameraID[i]]->getXMap(), *vecCameras[pData->cameraID[i]]->getYMap());
      i++;
      }
    pData->end = Clock::now();
    pData->executionTime[2] = std::chrono::duration_cast<milliseconds>(pData->end - pData->start);
    return pData;
    }
  )&
  //STEP 3: FILTER UNDISTORT TO CPUHSV; USE CUDA
  tbb::make_filter<S_pipelinePayload*, S_pipelinePayload*>(tbb::filter::serial_in_order, [&] (S_pipelinePayload *pData)->S_pipelinePayload*
    {
    pData->start = Clock::now();
    if(!this->filterFlags->filterActive) return pData;
    int i = 0;
    cv::cuda::GpuMat temp1; //(720, 1280, CV_8UC1)
    cv::cuda::GpuMat temp2; //(720, 1280, CV_8UC1)
    cv::cuda::GpuMat gputhresholded (720, 1280, CV_8UC1);
    for(auto it = std::begin(pData->gpuUndistortedImg); it< std::end(pData->gpuUndistortedImg); it++)
      {
      if(it->empty()) return pData;
        cv::Scalar min( pData->Filter[i].getHue_min(), pData->Filter[i].getSaturation_min(), pData->Filter[i].getValue_min());
        cv::Scalar max( pData->Filter[i].getHue_max(), pData->Filter[i].getSaturation_max(), pData->Filter[i].getValue_max());

        cv::cuda::cvtColor                (*it,temp1,cv::COLOR_BGR2HSV);
        this->ImageFilter->gpufGaussian   (temp1,temp2, pData->Filter[i]);
        cudaKernel::inRange_gpu           (temp2,min, max,gputhresholded);
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
    pData->start = Clock::now();
    if(!this->filterFlags->objectDetectionActive) return pData;
    int i = 0;

    for(auto it = std::begin(pData->cpuGrayImg); it< std::end(pData->cpuGrayImg); it +=2)
      {
      if(it->empty()) return pData;
      int offsetL[2];
      int offsetR[2];
      this->vecCameras[pData->cameraID[i]]->filterValues->getOffset(offsetL);
      this->vecCameras[pData->cameraID[i+1]]->filterValues->getOffset(offsetR);

      if(this->ImageFilter->findContours(it,   pData->cpuUndistortedImg[i], offsetL, *vecCameras[pData->cameraID[i]], pData->Richtungsvektoren[i], pData->ist_X[i], pData->ist_Y[i], pData->radius[i]) &&
         this->ImageFilter->findContours(it++, pData->cpuUndistortedImg[i], offsetR, *vecCameras[pData->cameraID[i+1]],pData->Richtungsvektoren[i+1], pData->ist_X[i+1], pData->ist_Y[i+1], pData->radius[i+1] ))
      pData->found = true;
    else
        {
        pData->found = false;
        pData->Richtungsvektoren[i].X = 0.0;
        pData->Richtungsvektoren[i].Y = 0.0;
        pData->Richtungsvektoren[i].Z = 0.0;
        pData->Richtungsvektoren[i+1].X = 0.0;
        pData->Richtungsvektoren[i+1].Y = 0.0;
        pData->Richtungsvektoren[i+1].Z = 0.0;
        }
      i++;
      }
    pData->end = Clock::now();
    pData->executionTime[4] = std::chrono::duration_cast<milliseconds>(pData->end - pData->start);
    return pData;
    }
  )&


  //STEP 5: CALCULATE OBJECT POSITION
  tbb::make_filter<S_pipelinePayload*, S_pipelinePayload*>(tbb::filter::serial_in_order, [&] (S_pipelinePayload *pData)->S_pipelinePayload*
    {
    pData->start = Clock::now();
    if(!this->filterFlags->trackingActive) return pData;

    if(pData->found)
      {
      milliseconds dTimestamp_ms;
      dTimestamp_ms = std::chrono::duration_cast<milliseconds>(pData->timestamp - this->timestampTm1);
      int dTimestamp = dTimestamp_ms.count();
      this->trackingManager->Get_Position_ObjectTracking    (pData->objektVektor, pData->Richtungsvektoren);
      this->trackingManager->calcObjectVeloctiy             (dTimestamp,          pData->objektVektor);

      for(int i =0; i < payloadSize; i++)
        {
        this->trackingManager->calcPixelVeloctiy              (dTimestamp, pData->ist_X[i], pData->ist_Y[i], pData->cameraID[i], pData->pred_X[i], pData->pred_Y[i]);
        }
      this->timestampTm1 = pData->timestamp;
      //Überprüfe ob das verfolgte Objekt sich dem Rand des derzeitigen Kamerapaares nähert. Falls true wird das nächste Kamerapaar in arrActiveCameras geladen und das predicted ROI + Toleranz gesetzt.
      if(pData->ist_X[0] > this->transferZoneWidth)
        {
        int newCam[2];
        newCam[0] = pData->cameraID[0] + 1;
        newCam[1] = pData->cameraID[1] + 1;
        vecCameras[newCam[0]]->setROI(pData->radius[0], pData->radius[0],pData->pred_Y[0]);
        vecCameras[newCam[1]]->setROI(pData->radius[1], pData->radius[1],pData->pred_Y[1]);
        std::lock_guard<std::mutex> lck (*this->lock);
        this->arrActiveCameras[0] = newCam[0];
        this->arrActiveCameras[1] = newCam[1];

        }
      }
    pData->end = Clock::now();
    pData->executionTime[6] = std::chrono::duration_cast<milliseconds>(pData->end - pData->start);
    return pData;
    }
  )&


  //STEP 6: ADJUST ROI ON CPU UNDISTORT ****NOT NEEDED******
  tbb::make_filter<S_pipelinePayload*, S_pipelinePayload*>(tbb::filter::serial_in_order, [&] (S_pipelinePayload *pData)->S_pipelinePayload*
    {
    pData->start = Clock::now();
    if(!this->filterFlags->roiAdjustmentActive) return pData;
      for(int i = 0; i < payloadSize; i++)
        {
        if(pData->found)
          {
          this->vecCameras[pData->cameraID[i]]->setROI(pData->radius[i], pData->pred_X[i],pData->pred_Y[i]);
          }
        else
          {
          this->vecCameras[pData->cameraID[i]]->filterValues->setOffset(0, 0);
          this->vecCameras[pData->cameraID[i]]->filterValues->setOffset(0, 0);
          this->vecCameras[pData->cameraID[i]]->getRoi()->x = 0;
          this->vecCameras[pData->cameraID[i]]->getRoi()->y = 0;
          this->vecCameras[pData->cameraID[i]]->getRoi()->width = this->frameWidth;
          this->vecCameras[pData->cameraID[i]]->getRoi()->height = this->frameHeight;
          }//else
        }//for
      pData->end = Clock::now();
      pData->executionTime[5] = std::chrono::duration_cast<milliseconds>(pData->end - pData->start);
      return pData;
    }//make_filter
  )&

  tbb::make_filter<S_pipelinePayload*,void>(tbb::filter::serial_in_order, [&] (S_pipelinePayload *pData)
    {
    pData->start = Clock::now();
    // TBB NOTE: pipeline end point. dispatch to GUI
    pData->fpsEnd = Clock::now();
    pData->frametime = std::chrono::duration_cast<std::chrono::nanoseconds>(pData->fpsEnd - pData->fpsStart);
    pData->fps = 1000000000/pData->frametime.count();
    pData->end = Clock::now();
    pData->executionTime[7] = std::chrono::duration_cast<milliseconds>(pData->end - pData->start);
    pData->queBuffer = que->size();

    if(!que->try_push(pData))
        delete pData;
    if(que->size() == 0)
        flush = false;
//    if (! pipelineDone)
//      {
//      try
//        {
//        for(int i = 0; i < payloadSize; i ++)
//          {
//          pData->cpuSrcImg[i].copyTo(arrImgShow[i]);
//          }
//        pData->fpsEnd = Clock::now();
//        pData->frametime = std::chrono::duration_cast<std::chrono::nanoseconds>(pData->fpsEnd - pData->fpsStart);
//        pData->fps = 1000000000/pData->frametime.count();
//        pData->end = Clock::now();
//        pData->executionTime[7] = std::chrono::duration_cast<milliseconds>(pData->end - pData->start);
//        pData->queBuffer = que->size();

//        if(!que->try_push(pData))
//            delete pData;
//        //que.push(pData);
//        //delete pData;
//        }
//      catch (...)
//        {
//        std::cout << "Pipeline caught an exception on the queue" << std::endl;
//        pipelineDone = true;
//        }//catch
//        return;

//      }//if (!done)
     }//STEP 5
    )//tbb::makefilter
  );//tbb pipeline

}





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

bool S_filterflags::getTracking() const
  {
  return trackingActive;
  }

void S_filterflags::setTracking(bool value)
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
