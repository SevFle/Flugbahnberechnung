#include "headers/Main.h"
#include "headers/GlobalObjects.h"

#include <QApplication>

using namespace GlobalObjects;

int main(int argc, char *argv[])
{

//      cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);
//      cv::Ptr<cv::aruco::CharucoBoard> board = cv::aruco::CharucoBoard::create(7, 5, 0.1f, 0.07f, dictionary);
//      cv::Mat boardImage;
//      //DINA4 3508 x 2480 px
//      //DINA3 3508 x 4961 px
//      board->draw(cv::Size(4800, 3400), boardImage, 10, 1);
//      cv::imwrite("../Parameter/Charuco_BoardImage_5_7_0.04f_0.02f_Size(4700, 3200)_A3.jpg", boardImage);



    QApplication*     Projekt_ObjectTracking  = new QApplication        (argc, argv);
    gst_init                                                            (&argc, &argv);
    C_GlobalObjects*  GlobalObjects           = new C_GlobalObjects     ();
    C_Main*           Main                    = new C_Main              (GlobalObjects);

    Projekt_ObjectTracking->exec();

    delete (Main);
    delete (GlobalObjects);
    delete (Projekt_ObjectTracking);


    return(0);
}

//TODO

