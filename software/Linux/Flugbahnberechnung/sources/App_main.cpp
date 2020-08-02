#include "headers/Main.h"
#include "headers/GlobalObjects.h"

#include <QApplication>

using namespace GlobalObjects;

int main(int argc, char *argv[])
{
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





//Finished Conversion:
//frm_Object_tracking
//frm_object_calibration
//frm_main
//
