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
  this->lock            = new pthread_mutex_t;
  this->camSimple       = new pthread_t;
  this->camPositioning  = new pthread_t;
  this->Que             = new tbb::concurrent_bounded_queue<CameraManager::S_Payload*>;
  this->pData           = new S_Payload;
  this->testpayload     = new S_Payload;

  this->trackingManager = new trackingManager::C_trackingManager(GlobalObjects);
  this->vecImgShow      = new std::vector<cv::Mat*>;
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
  this->test = "Print test string successfull";

  }
/**************************************************************** Destruktor ****************************************************************/
C_CameraManager::~C_CameraManager ()
  {
  delete (testpayload);
  delete (filterFlags);
  delete (vecImgShow);
  delete (trackingManager);
  delete (pData);
  delete (Que);
  delete (camPositioning);
  delete (camSimple);
  delete (camPipeline);
  delete (lock);
  delete (ImageFilter);
  delete (saveManager);
  delete (loadManager);
  this->globalObjects = nullptr;
  }

pthread_mutex_t *C_CameraManager::getLock() const
  {
  return lock;
  }

void C_CameraManager::setLock(pthread_mutex_t *value)
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
                        Pipeline      += "height=" + std::to_string(this->frameHeight) +" ! jpegdec ! videoconvert ! appsink";

      auto              camera        = new Camera::C_Camera2;
      camera->setPipeline             (Pipeline);
      camera->setCameraID             (this->globalObjects->absCameras);
      if(!camera->open())
        std::cout << "**ERROR** Could not open device on path" << devicePath << std::endl;
      vecCameras.push_back            (camera);
      this->globalObjects->absCameras++;
      }
    std::cout << "**INFO** Created " << std::to_string(this->globalObjects->absCameras) << " Devices" << std::endl;

    }

  //Reorder recently created Cameras
  if(this->loadManager->loadCameraPositioning(globalObjects->camera_order))
                  this->mvVecCamera2Temp(*globalObjects->camera_order);

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
  if(int err = pthread_create(camPositioning,NULL, (THREADFUNCPTR) &CameraManager::C_CameraManager::threadCameraPositioning, this) !=0)
    {
      std::cout << "**ERROR** Kamerathread konnte nicht gestartet werden" << std::endl;
      return false;
    }
  std::cout << "**INFO** Kamerathread wurde gestartet" << std::endl;
  return true;
  }
bool C_CameraManager::stopThreadCameraPositioning()
  {
  if(pthread_join(*camPositioning, NULL) !=0)
    {
      std::cout << "**ERROR** Kamerathread konnte nicht gestoppt werden" << std::endl;
      return false;
    }
  std::cout << "**INFO** Kamerathread wurde gestoppt" << std::endl;
  return true;
   }
bool C_CameraManager::startPipelineTracking()
  {
  Que->set_capacity(10);

  this->camPipeline     = new thread(&CameraManager::C_CameraManager::pipelineHelper,this);

  //                std::thread(grabAndConvertTBB, std::ref(cam_vector), std::ref(Que));
//  if(int err = pthread_create(camPipeline,NULL, (THREADFUNCPTR) &CameraManager::C_CameraManager::pipelineHelper, this) !=0)
//    {
//    printf("\n**ERROR** Kamerapipeline konnte nicht gestartet werden");
//    return false;
//    }
  printf("\n**INFO** Kamerapipeline wurde gestartet");
  return true;
  }
bool C_CameraManager::stopPipelineTracking()
  {
  this->pipelineDone = true;
  this->camPipeline->join();
//  if(pthread_join(*camPipeline, NULL) !=0)
//    {
//      printf("\n**ERROR** Kamerathread konnte nicht gestoppt werden");
//      return false;
//    }
  printf("\n**INFO** Kamerapipeline wurde gestoppt");
  return true;
  }

void C_CameraManager::mvVecCamera2Temp (std::vector<int> vecCamOrder)
  {
  std::vector<Camera::C_Camera2*> vecCamerastemp;
  vecCamerastemp.resize(globalObjects->absCameras);
  for(int i =0; i < globalObjects->absCameras; i++)
    {
    vecCamerastemp[i] = std::move(this->vecCameras[vecCamOrder[i]]);
    }
  mvTemp2VecCamera(vecCamerastemp);
  }
void C_CameraManager::mvTemp2VecCamera (std::vector<Camera::C_Camera2*> vecCamerastemp)
  {
  for (int i = 0; i < globalObjects->absCameras; i++)
    {
    vecCameras[i] = std::move (vecCamerastemp[i]);
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
      TCP_Orientation.push_back (Mat_Orientation);
      TCP_Position.push_back (Mat_Position);
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
    img1 = cv::imread ("../Parameter/Bilder/Camera_Stereo_Calibration_" + std::to_string (camera_id) + "_Snapshot_" + std::to_string (photoID) + ".png",1);
    img2 = cv::imread ("../Parameter/Bilder/Camera_Stereo_Calibration_" + std::to_string (camera_id + 1) + "_Snapshot_" + std::to_string (photoID) + ".png",1);

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
    for (int i = 0; i < absCornersHeight; i++) for (int j = 0; j < absCornersWidth; j++) obj.emplace_back (static_cast<float> (j) * absCornerLength,static_cast<float> (i) * absCornerLength,0);

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

  std::cout << "K1" << endl << K1 << endl << endl;
  std::cout << "K2" << endl << K2 << endl << endl;
  std::cout << "D1" << endl << D1 << endl << endl;
  std::cout << "D2" << endl << D2 << endl << endl;
  std::cout << "R" << endl << R << endl << endl;
  std::cout << "T" << endl << T << endl << endl;
  std::cout << "E" << endl << E << endl << endl;
  std::cout << "F" << endl << F << endl << endl;
  std::cout << "Done Calibration" << endl;

  this->calculate_camera_pose(camera_id, camera_id+1, T, R);

  this->calibrationDone = true;

//  std::cout << "Starting Rectification" << endl;

//  cv::Mat R1, R2, P1, P2, Q;
//  stereoRectify (K1,D1,K2,D2,img1.size(),R,T,R1,R2,P1,P2,Q);

//  std::cout << "R1" << R1 << endl;
//  std::cout << "R2" << R2 << endl;
//  std::cout << "P1" << P1 << endl;
//  std::cout << "P2" << P2 << endl;0
  }

void *C_CameraManager::threadCameraPositioning(void *This)
  {

   std::vector<cv::Mat*> vecImg;

  if (pthread_mutex_init(static_cast<CameraManager::C_CameraManager*>(This)->lock, NULL) !=0)
    printf("\n Mutex init failed for thread camera positioning");
  while(!static_cast<CameraManager::C_CameraManager*>(This)->positioningDone)
    {
      for(auto it = std::begin(static_cast<CameraManager::C_CameraManager*>(This)->vecCameras);
               it < std::end(static_cast<CameraManager::C_CameraManager*>(This)->vecCameras);
               it++)
        {
        (*it)->grabImg();
        }
      for(auto it = std::begin(static_cast<CameraManager::C_CameraManager*>(This)->vecCameras);
               it < std::end(static_cast<CameraManager::C_CameraManager*>(This)->vecCameras);
               it++)
        {
          auto img = new cv::Mat;
          (*it)->retrieveImg(*img);
          vecImg.push_back(img);

        }

      pthread_mutex_lock(static_cast<CameraManager::C_CameraManager*>(This)->lock);
      static_cast<CameraManager::C_CameraManager*>(This)->vecImgShow->clear();
      for(auto it = std::begin(vecImg); it < std::end(vecImg); it++)
        {
        static_cast<CameraManager::C_CameraManager*>(This)->vecImgShow->push_back(*it);
        }
      pthread_mutex_unlock(static_cast<CameraManager::C_CameraManager*>(This)->lock);
      vecImg.clear();
    }
  return 0;
  }
void C_CameraManager::threadCameraSimple()
  {

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


void C_CameraManager::smTracking (S_Payload* payload)
  {

  }
void *C_CameraManager::pipelineHelper(void* This)
  {
  static_cast<CameraManager::C_CameraManager*>(This)->pipelineTracking(static_cast<CameraManager::C_CameraManager*>(This)->vecCameras,
                                                                      static_cast<CameraManager::C_CameraManager*>(This)->Que);
  return 0;
  }
std::vector<cv::Mat*> C_CameraManager::getVecImgShow() const
  {
  return *vecImgShow;
  }

void C_CameraManager::setVecImgShow             (const std::vector<cv::Mat*> &value)
  {
  *vecImgShow = value;
  }
bool C_CameraManager::pollPipeline               (CameraManager::S_Payload* arg1)
  {
  std::cout << std::to_string(this->Que->size()) << std::endl;
  if(this->Que->size() < 2) return false;
  if(this->Que->try_pop(arg1))
      {
      return true;
      }
  return false;
  }


void C_CameraManager::pipelineTracking(std::vector<Camera::C_Camera2*> vecCameras, tbb::concurrent_bounded_queue<S_Payload*>* pipelineQue)
  {
  int frameheight = this->vecCameras[0]->getFrameHeight();
  int framewidth = this->vecCameras[0]->getFrameWidth();
  tbb::parallel_pipeline(7, tbb::make_filter<void, S_Payload*>(tbb::filter::serial_in_order, [&](tbb::flow_control& fc)->S_Payload*
    {                           
    if(pipelineDone)
      {
      this->pipelineDone = true;
      fc.stop();
      return 0;
      }
    //SET IMAGES
    auto pData          = new S_Payload;
    for(int i = 0; i < payloadSize; i++)
      {
      pData->cpuSrcImg[i].create (frameheight, framewidth, CV_32FC1);
      pData->cameraID[i]     = arrActiveCameras[i];
      if (pData->cameraID[i] > globalObjects->absCameras) return 0;
      pData->Filter[i]       = *vecCameras[arrActiveCameras[i]]->getFilterproperties();
      }
    return pData;
    }
  )&

  //STEP 1: GRAB PICTURE FROM ARRAY-ACTIVE_CAMERAS
  tbb::make_filter<S_Payload*, S_Payload*>(tbb::filter::serial_in_order, [&] (S_Payload *pData)->S_Payload*
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
  tbb::make_filter<S_Payload*, S_Payload*>(tbb::filter::serial_in_order, [&] (S_Payload *pData)->S_Payload*
    {
    pData->start = Clock::now();
    for(int i = 0; i <  payloadSize; i++)
      {
      vecCameras[arrActiveCameras[i]]->retrieveImg(pData->cpuSrcImg[i]);
      }
    pData->end = Clock::now();
    pData->executionTime[1] = std::chrono::duration_cast<milliseconds>(pData->end - pData->start);
    return pData;
    }
  )&
  //STEP 2: UNDISTORT SRC TO CPUDISTORT
  tbb::make_filter<S_Payload*, S_Payload*>(tbb::filter::serial_in_order, [&] (S_Payload *pData)->S_Payload*
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
  tbb::make_filter<S_Payload*, S_Payload*>(tbb::filter::serial_in_order, [&] (S_Payload *pData)->S_Payload*
    {
    pData->start = Clock::now();
    if(!this->filterFlags->filterActive) return pData;
    int i = 0;
    cv::cuda::GpuMat temp1(720, 1280, CV_8UC1), temp2(720, 1280, CV_8UC1), gputhresholded (720, 1280, CV_8UC1);
    for(auto it = std::begin(pData->gpuUndistortedImg); it< std::end(pData->gpuUndistortedImg); it++)
      {
      if(it->empty()) return pData;
        cv::Scalar min( pData->Filter[i].getHue_min(),
                        pData->Filter[i].getSaturation_min(),
                        pData->Filter[i].getValue_min());
        cv::Scalar max( pData->Filter[i].getHue_max(),
                        pData->Filter[i].getSaturation_max(),
                        pData->Filter[i].getValue_max());

        cv::cuda::cvtColor                (*it,temp1,cv::COLOR_BGR2HSV);
        this->ImageFilter->gpufGaussian   (temp1,temp2, pData->Filter[i]);
        cudaKernel::inRange_gpu           (temp2,min, max,gputhresholded);
        this->ImageFilter->gpufOpen       (gputhresholded,temp2, pData->Filter[i]);
        this->ImageFilter->gpufClose      (temp2,temp1, pData->Filter[i]);
        cv::cuda::cvtColor                (temp1, temp2 ,cv::COLOR_GRAY2BGR);
        if(this->filterFlags->erosionActive)
          {
          this->ImageFilter->gpufErode(temp2, temp1, pData->Filter[i]);
          temp1.copyTo(temp2);
          }

        if(this->filterFlags->dilationActive)
          {
          this->ImageFilter->gpufDilate(temp2, temp1, pData->Filter[i]);
          temp1.copyTo(temp2);
          }

        if(this->filterFlags->morphActive)
          {
          this->ImageFilter->gpufDilate(temp2, temp1, pData->Filter[i]);
          temp1.copyTo(temp2);
          }

        if(this->filterFlags->bilateralActive)
          {
          this->ImageFilter->gpufBilateral(temp2, temp1, pData->Filter[i]);
          temp1.copyTo(temp2);
          }
        cv::cuda::bitwise_and                   (*it,temp2,temp1);
        temp1.download                    (pData->cpuHSVImg[i]);
        i++;
        }
    pData->end = Clock::now();
    pData->executionTime[3] = std::chrono::duration_cast<milliseconds>(pData->end - pData->start);
    return pData;
    }
  )&
  //STEP 4: FIND CONTOURS ON CPUHSV, DRAW ON UNDISTORT
  tbb::make_filter<S_Payload*, S_Payload*>(tbb::filter::serial_in_order, [&] (S_Payload *pData)->S_Payload*
    {
    pData->start = Clock::now();
    if(!this->filterFlags->objectDetectionActive) return pData;
    int i = 0;
    for(auto it = std::begin(pData->cpuHSVImg); it< std::end(pData->cpuHSVImg); it +=2)
      {
      if(it->empty()) return pData;
      int offsetL[2];
      int offsetR[2];
      this->vecCameras[pData->cameraID[i]]->filterValues->getOffset(offsetL);
      this->vecCameras[pData->cameraID[i+1]]->filterValues->getOffset(offsetR);

      if(this->ImageFilter->findContours(it,   pData->cpuConturedImg[i], offsetL, *vecCameras[pData->cameraID[i]], *pData->Richtungsvektoren[i], pData->ist_X[i], pData->ist_Y[i], pData->radius[i]) &&
         this->ImageFilter->findContours(it++, pData->cpuConturedImg[i], offsetR, *vecCameras[pData->cameraID[i+1]],*pData->Richtungsvektoren[i+1], pData->ist_X[i+1], pData->ist_Y[i+1], pData->radius[i+1] ))
      pData->found = true;
    else
        {
        pData->found = false;
        pData->Richtungsvektoren[i]->X = 0;
        pData->Richtungsvektoren[i]->Y = 0;
        pData->Richtungsvektoren[i]->Z = 0;
        pData->Richtungsvektoren[i+1]->X = 0;
        pData->Richtungsvektoren[i+1]->Y = 0;
        pData->Richtungsvektoren[i+1]->Z = 0;
        }
      i++;
      }
    pData->end = Clock::now();
    pData->executionTime[4] = std::chrono::duration_cast<milliseconds>(pData->end - pData->start);
    return pData;
    }
  )&
  //STEP 5: CALCULATE OBJECT POSITION
  tbb::make_filter<S_Payload*, S_Payload*>(tbb::filter::serial_in_order, [&] (S_Payload *pData)->S_Payload*
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
      }
    pData->end = Clock::now();
    pData->executionTime[6] = std::chrono::duration_cast<milliseconds>(pData->end - pData->start);
    return pData;
    }
  )&
  //STEP 6: ADJUST ROI ON CPU UNDISTORT ****NOT NEEDED******
  tbb::make_filter<S_Payload*, S_Payload*>(tbb::filter::serial_in_order, [&] (S_Payload *pData)->S_Payload*
    {
    pData->start = Clock::now();
    if(!this->filterFlags->roiAdjustmentActive) return pData;
      for(int i = 0; i < payloadSize; i++)
        {
        if(pData->found)
          {
          this->vecCameras[pData->cameraID[i]]->setROI(pData->radius[i], pData->ist_X[i],pData->ist_Y[i]);
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

  tbb::make_filter<S_Payload*,void>(tbb::filter::serial_in_order, [&] (S_Payload *pData)
    {
    pData->start = Clock::now();
    // TBB NOTE: pipeline end point. dispatch to GUI
    if (! pipelineDone)
      {
      try
        {
//        for(int i = 0; i < payloadSize; i ++)
//          {
//          pData->cpuSrcImg[i].copyTo(arrImgShow[i]);
//          }
        pipelineQue->try_push(pData);
        //que.push(pData);
        //delete pData;
        }
      catch (...)
        {
        std::cout << "Pipeline caught an exception on the queue" << std::endl;
        pipelineDone = true;
        }//catch
        pData->executionTime[7] = std::chrono::duration_cast<milliseconds>(pData->end - pData->start);
        return pData;

      }//if (!done)
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
