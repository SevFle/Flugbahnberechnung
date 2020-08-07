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
  this->camPipeline     = new pthread_t;
  this->camSimple       = new pthread_t;
  this->camPositioning  = new pthread_t;
  this->Que             = new tbb::concurrent_bounded_queue<S_Payload*>;
  this->pData           = new S_Payload;
  this->trackingManager = new trackingManager::C_trackingManager(GlobalObjects);
  }
/**************************************************************** Destruktor ****************************************************************/
C_CameraManager::~C_CameraManager ()
  {
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
    printf("\n PTB-INFO: GstDeviceMonitor unsupported. May not be able to enumerate all video devices.\n");
    }
  else
    {
    devlist = gst_device_monitor_get_devices(Monitor);

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
      camera->setPipeline(Pipeline);
      camera->setCameraID(this->globalObjects->absCameras);
      if(!camera->open())
        std::cout << "Could not open device on path" << devicePath << std::endl;
      vecCameras.push_back(camera);
      this->globalObjects->absCameras++;
      }
    std::cout << "Created " << std::to_string(this->globalObjects->absCameras) << " Devices" << std::endl;
    }

  //Reorder recently created Cameras
  *globalObjects->camera_order = this->loadManager->loadCameraPositioning();
  this->mvVecCamera2Temp(this->loadManager->loadCameraPositioning());

  //Load Settings and Calibration for each camera created earlier
  for (int i = 0; i < globalObjects->absCameras; i++)
    {
    this->loadManager->loadCameraCalibration(vecCameras[i]);
    this->loadManager->loadCameraSettings(vecCameras[i]);
    this->vecCameras[i]->initRectifyMap();
    }
  return true;
  }
bool C_CameraManager::closeCameras ()
  {
  for (auto it = std::begin(vecCameras); it < std::end(vecCameras); it++)
    {
    (*it)->close();
    }
  return true;
  }

bool C_CameraManager::startThreadCameraPositioning()
  {
  if(int err = pthread_create(camPositioning,NULL, (THREADFUNCPTR) &CameraManager::C_CameraManager::threadCameraPositioning, this) !=0)
    {
      printf("**ERROR** Kamerathread konnte nicht gestartet werden");
      return false;
    }
  else
    {
      return true;
    }
  }
bool C_CameraManager::stopThreadCameraPositioning()
  {
  if(int err = pthread_join(*camPositioning, NULL) !=0)
    {
      printf("**ERROR** Kamerathread konnte nicht gestoppt werden **ABORT**");
      return false;
    }
  else
    {
      return true;
    }
  }
bool C_CameraManager::startPipelineTracking()
  {
  Que->set_capacity(7);

  if(int err = pthread_create(camPipeline,NULL, (THREADFUNCPTR) &CameraManager::C_CameraManager::pipelineHelper, this) !=0)
    {
    printf("**ERROR** Kamerapipeline konnte nicht gestartet werden");
    return false;
    }
  else
    {
    return true;
    }
  }
bool C_CameraManager::stopPipelineTracking()
  {
  if(int err = pthread_join(*camPipeline, NULL) !=0)
    {
      printf("**ERROR** Kamerathread konnte nicht gestoppt werden **ABORT**");
      return false;
    }
  else
    {
      return true;
    }
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
  //cv::InputOutputArray R, T;
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
  cv::Mat* img;
  std::vector<cv::Mat*> vecImg;
  if (pthread_mutex_init(static_cast<CameraManager::C_CameraManager*>(This)->lock, NULL) !=0)
    printf("\n Mutex init failed for thread camera positioning");
  while(!static_cast<CameraManager::C_CameraManager*>(This)->positioningDone)
    {
      for(auto it = std::begin(static_cast<CameraManager::C_CameraManager*>(This)->vecCameras);
               it < std::end(static_cast<CameraManager::C_CameraManager*>(This)->vecCameras);
               it++)
        {
        img = new cv::Mat;
        (*it)->readImg(*img);
        vecImg.push_back(img);
        }
      pthread_mutex_lock(static_cast<CameraManager::C_CameraManager*>(This)->lock);
      static_cast<CameraManager::C_CameraManager*>(This)->vecImgShow.clear();
      for(auto it = std::begin(vecImg); it < std::end(vecImg); it++)
        {
        static_cast<CameraManager::C_CameraManager*>(This)->vecImgShow.push_back(*it);
        }
      pthread_mutex_unlock(static_cast<CameraManager::C_CameraManager*>(This)->lock);
      vecImg.clear();
    }
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

void C_CameraManager::pipelineTracking(std::vector<Camera::C_Camera2*> vecCamera, tbb::concurrent_bounded_queue<S_Payload*> &que)
  {
  int smTrackingState = 0;
  //STEP 1: GRAB PICTURE FROM ARRAY-ACTIVE_CAMERAS
  tbb::parallel_pipeline(7, tbb::make_filter<void, S_Payload*>(tbb::filter::serial_in_order, [&](tbb::flow_control& fc)->S_Payload*
    {
    if(cntPipeline == 4) cntPipeline = 0;
    auto pData          = new S_Payload;
    pData->cameraID     = arrActiveCameras[cntPipeline];
    if (pData->cameraID > globalObjects->absCameras) return 0;

    pData->Filter       = *vecCameras[arrActiveCameras[cntPipeline]]->getFilterproperties();

    if(pipelineDone || pData->cpuSrcImg.empty())
      {
      this->pipelineDone = true;
      fc.stop();
      return 0;
      }
    cntPipeline++;
    return pData;
    }
  )&
  //STEP 2: UNDISTORT SRC TO CPUDISTORT
  tbb::make_filter<S_Payload*, S_Payload*>(tbb::filter::serial_in_order, [&] (S_Payload *pData)->S_Payload*
    {
    this->ImageFilter->gpufUnidstord(pData->cpuSrcImg, pData->gpuUndistortedImg, *vecCamera[pData->cameraID]->getMap1(), *vecCamera[pData->cameraID]->getMap2());
    return pData;
    }
  )&
  //STEP 3: FILTER UNDISTORT TO CPUHSV; USE CUDA
  tbb::make_filter<S_Payload*, S_Payload*>(tbb::filter::serial_in_order, [&] (S_Payload *pData)->S_Payload*
    {
    this->ImageFilter->gpufHSV(pData->gpuUndistortedImg, pData->cpuHSVImg, pData->Filter);
    cv::circle(pData->gray, cv::Point(pData->gray.rows/2, pData->gray.cols/2), 50, cv::Scalar(0, 140, 50), cv::FILLED);
    return pData;
    }
  )&
  //STEP 4: FIND CONTOURS ON CPUHSV, DRAW ON UNDISTORT
  tbb::make_filter<S_Payload*, S_Payload*>(tbb::filter::serial_in_order, [&] (S_Payload *pData)->S_Payload*
    {
    if(this->ImageFilter->findContours(pData->cpuHSVImg, pData->cpuConturedImg, pData->offset, *vecCamera[pData->cameraID]))
      pData->found = true;
    else
      pData->found = false;
    return pData;
    }
  )&
  //STEP 5: ADJUST ROI ON CPU UNDISTORT ****NOT NEEDED******
  tbb::make_filter<S_Payload*, S_Payload*>(tbb::filter::serial_in_order, [&] (S_Payload *pData)->S_Payload*
    {
    this->ImageFilter->findContours(pData->cpuHSVImg, pData->cpuConturedImg, pData->offset, *vecCamera[pData->cameraID]);
    }
  )&
  //STEP 6: CALCULATE OBJECT POSITION
  tbb::make_filter<S_Payload*, S_Payload*>(tbb::filter::serial_in_order, [&] (S_Payload *pData)->S_Payload*
    {
    switch (this->trackingManager->getAlive())
      {
      case 0:
          //Lade alle fest definierten Welt-Kamera Posen und erstelle einen Vektor mit allen Posen. Vektor[0] bezieht sich auf Kamera[0], usw.
          smTrackingState = 1;
          break;
      case 1:
          if(!pData->found)
            {
              smTrackingState = 1;
            }
          else //Führe Berechnungen der aktuellen Objekte durch
            {
            smTrackingState = 2;
            }
          break;
      case 2:
          //Erstelle neues Ballobjekt
          tracked_object->set_ID_Cam_Links(0);
          tracked_object->set_ID_Cam_Rechts(0);
          v_tracked_objects.push_back(tracked_object);
          //ROI für die ersten Kameras ist selbstgeführt.
          statemachine_state = 3;
          break;
      case 3:
            //Get zugewiesene Kameras für Objekt an stelle it
            ID_Cam_Rechts = (*it)->get_ID_Cam_Rechts();
            //Get_2D_Pixel für zugewiesene Kamera
            this->camera_vector[ID_Cam_Links]->get_objectPosition_2D_Pixel (tracked_data.found_0, tracked_data.Richtungsvektor_0, temp1);
            this->camera_vector[ID_Cam_Rechts]->get_objectPosition_2D_Pixel (tracked_data.found_1, tracked_data.Richtungsvektor_1, temp2);
            //Wenn Ball gefunden
            if (tracked_data.found_0 && tracked_data.found_1)
              {
                //Berechne Pixel Velocity
                //Berechne POS + m/s
              (*it)->calculate_px_speed();
              (*it)->calculate_ms_speed();
              (*it)->calculate_pose();
              //Wenn 2D Pixel im Bereich x = 700-800
               if(tracked_data.Richtungsvektor_0.X > 700  || tracked_data.Richtungsvektor_1.X > 700)
               {
               //Assign nächstes Kamerapaar für Objekt
               (*it)->set_ID_Cam_Links((*it)->get_ID_Cam_Links()+1);
               (*it)->sCameraManager::S_Payload *payloadet_ID_Cam_Rechts((*it)->get_ID_Cam_Rechts()+1);
               //Set ROI für nächstes Kamerapaar
               //this->camera_vector[(*it)->get_ID_Cam_Links()]->
               //thisCameraManager::S_Payload *payload->camera_vector[(*it)->get_ID_Cam_Rechts()]->
               }
            break;
            }
         }
      }
  }
  )&

  tbb::make_filter<S_Payload*,void>(tbb::filter::serial_in_order, [&] (S_Payload *pData)
    {
    pData->gray.copyTo(pData->final);
    // TBB NOTE: pipeline end point. dispatch to GUI
    if (! pipelineDone)
      {
      try
        {
        que.push(pData);
        }
      catch (...)
        {
        std::cout << "Pipeline caught an exception on the queue" << std::endl;
        pipelineDone = true;
        }//catch
      }//if (!done)
    }//STEP 5
    )//tbb::makefilter
  );//tbb pipeline

}
void C_CameraManager::smTracking (S_Payload* payload)

void *C_CameraManager::pipelineHelper(void* This)
  {
  static_cast<CameraManager::C_CameraManager*>(This)->pipelineTracking(static_cast<CameraManager::C_CameraManager*>(This)->vecCameras,
                                                                      *static_cast<CameraManager::C_CameraManager*>(This)->Que);
  }
std::vector<cv::Mat *> C_CameraManager::getVecImgShow() const
  {
  return vecImgShow;
  }

void C_CameraManager::setVecImgShow(const std::vector<cv::Mat *> &value)
  {
  vecImgShow = value;
  }
bool C_CameraManager::pollPipeline               (CameraManager::S_Payload* payload)
  {
  if(Que->try_pop(payload))
      {
      return true;
      }
  return false;
  }

