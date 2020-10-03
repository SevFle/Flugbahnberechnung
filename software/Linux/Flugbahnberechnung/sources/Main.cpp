#include "headers/Main.h"

using namespace Main;

C_Main::C_Main(C_GlobalObjects* GlobalObjects)
  {
//    cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);

//    cv::Ptr<cv::aruco::CharucoBoard> board = cv::aruco::CharucoBoard::create(9, 6, 0.40f, 0.25f, dictionary);
//    cv::Mat boardImage;
//    //DINA4 3508 x 2480 px
//    board->draw(cv::Size(3200, 2200), boardImage, 10, 1);
//    cv::imwrite("../Parameter/Charuco_BoardImage_5_7_0.04f_0.02f_Size(3200, 2200).jpg", boardImage);

  this->cameraManager = new C_CameraManager(GlobalObjects);

  this->frm_Main = new C_frm_Main(GlobalObjects, this);

  this->frm_Camera_Calibration          = new C_frm_Camera_Calibration(GlobalObjects, this);

  this->frm_Camera_Positioning          = new C_frm_Camera_Positioning(GlobalObjects, this);
  this->frm_Camera_Positioning_Pose     = new C_frm_Camera_Positioning_Pose(GlobalObjects, this);

  this->frm_Object_Calibration          = new C_frm_Object_Calibration(GlobalObjects, this);
  this->frm_Object_Tracking             = new C_frm_Object_Tracking(GlobalObjects, this);

  this->GlobalObjects                   = GlobalObjects;

  this->frm_Main->show();
}



C_Main::~C_Main()
{
    this->GlobalObjects = nullptr;

    delete  (frm_Object_Tracking);
    delete  (frm_Object_Calibration);

    delete  (frm_Camera_Positioning_Pose);
    delete  (frm_Camera_Positioning);


    delete  (frm_Camera_Calibration);

    delete  (frm_Main);
    delete  (cameraManager);

}


#include "frm_main.cpp"
#include "frm_object_calibration.cpp"
#include "frm_object_tracking.cpp"
#include "frm_camera_calibration.cpp"
#include "frm_camera_positioning.cpp"
#include "frm_camera_positioning_pose.cpp"
