#pragma once
/****************************************************************** Includes ****************************************************************/
#include "Camera_unmanaged.h"

#include <thread>

/****************************************************************** Namespaces***************************************************************/
using namespace nmsp_camera_unmanaged;
using namespace nmsp_GlobalObjects;
/*************************************************************** Konstruktoren **************************************************************/
c_camera_unmanaged::c_camera_unmanaged                                  (int cameras_in_use, C_GlobalObjects* GlobalObjects)
  {
  this->cameras_in_use        = cameras_in_use;
  stop_statemachine           = false;
  this->GlobalObjects         = GlobalObjects;

  load_positioning            = false;

  numCornersWidth             = 0;
  numCornersHeight            = 0;
  SquareSize                  = 0;
  numBoards_imgs              = 0;
  Photo_ID                    = 0;


  }
/**************************************************************** Destruktor ****************************************************************/
c_camera_unmanaged::~c_camera_unmanaged                                 ()
  {
  load_positioning            = false;



  GlobalObjects               = nullptr;
  stop_statemachine           = false;
  cameras_in_use              = 0;
  }

/*************************************************** Nicht öffentliche private Methoden *****************************************************/

void c_camera_unmanaged::start_camera_thread                            ()
  {
  camera_vector[current_camera_id]->idle = true;
  camera_vector[current_camera_id]->camera_thread();
  }
/******************************************************* Öffentliche Anwender-Methoden ******************************************************/

void c_camera_unmanaged::save_camera_settings                           (int camera_id)
  {
  string  Dateiname;
  string  Dateityp;
  Dateiname   = "../Parameter/Camera_setting"+to_string(camera_id)+".csv";
  Dateityp    = "Value of the individual setting";


  GlobalObjects->csv_parameter_datei->Oeffnen  (Dateiname, Enum_CSV_Access::Write);


  if (GlobalObjects->csv_parameter_datei->IsOpen())
    {
    GlobalObjects->csv_parameter_datei->Schreiben("Dateityp", Dateityp, "[1]");


    GlobalObjects->csv_parameter_datei->Schreiben("hue_min", to_string(camera_vector[camera_id]->hue_min), "[1]");
    GlobalObjects->csv_parameter_datei->Schreiben("hue_max", to_string(camera_vector[camera_id]->hue_max), "[1]");
    GlobalObjects->csv_parameter_datei->Schreiben("saturation_min", to_string(camera_vector[camera_id]->saturation_min), "[1]");
    GlobalObjects->csv_parameter_datei->Schreiben("saturation_max", to_string(camera_vector[camera_id]->saturation_max), "[1]");
    GlobalObjects->csv_parameter_datei->Schreiben("value_min", to_string(camera_vector[camera_id]->value_min), "[1]");
    GlobalObjects->csv_parameter_datei->Schreiben("value_max", to_string(camera_vector[camera_id]->value_max), "[1]");

    GlobalObjects->csv_parameter_datei->Schreiben("erosion_iterations", to_string(camera_vector[camera_id]->erosion_iterations), "[1]");
    GlobalObjects->csv_parameter_datei->Schreiben("dilation_iterations", to_string(camera_vector[camera_id]->dilation_iterations), "[1]");
    GlobalObjects->csv_parameter_datei->Schreiben("opening_iteration", to_string(camera_vector[camera_id]->opening_iterations), "[1]");
    GlobalObjects->csv_parameter_datei->Schreiben("closing_iteration", to_string(camera_vector[camera_id]->closing_iterations), "[1]");
    GlobalObjects->csv_parameter_datei->Schreiben("morph_iteration", to_string(camera_vector[camera_id]->morph_iterations), "[1]");

    GlobalObjects->csv_parameter_datei->Schreiben("erosion_kernel_size", to_string(camera_vector[camera_id]->erosion_kernel_size), "[1]");
    GlobalObjects->csv_parameter_datei->Schreiben("dilation_kernel_size", to_string(camera_vector[camera_id]->dilation_kernel_size), "[1]");
    GlobalObjects->csv_parameter_datei->Schreiben("opening_kernel_size", to_string(camera_vector[camera_id]->opening_kernel_size), "[1]");
    GlobalObjects->csv_parameter_datei->Schreiben("closing_kernel_size", to_string(camera_vector[camera_id]->closing_kernel_size), "[1]");
    GlobalObjects->csv_parameter_datei->Schreiben("morph_kernel_size", to_string(camera_vector[camera_id]->morph_kernel_size), "[1]");
    GlobalObjects->csv_parameter_datei->Schreiben("gaussian_kernel_size", to_string(camera_vector[camera_id]->gaussian_kernel_size), "[1]");

    GlobalObjects->csv_parameter_datei->Schreiben("gaussian_sigma", to_string(camera_vector[camera_id]->gaussian_sigma), "[1]");

    GlobalObjects->csv_parameter_datei->Schreiben("bilateral_sigma_color", to_string(camera_vector[camera_id]->bilateral_sigma_color), "[1]");
    GlobalObjects->csv_parameter_datei->Schreiben("bilateral_sigma_spatial", to_string(camera_vector[camera_id]->bilateral_sigma_spatial), "[1]");
    }
  }
void c_camera_unmanaged::load_camera_settings                           (int camera_id)
  {
  string  Dateiname;
  string  Dateityp;
  uchar   hue_min;
  uchar   hue_max;
  uchar   saturation_min;
  uchar   saturation_max;
  uchar   value_min;
  uchar   value_max;

  int     erosion_iterations;
  int     dilation_iterations;
  int     opening_iterations;
  int     closing_iterations;
  int     morph_iterations;

  int     erosion_kernel_size;
  int     dilation_kernel_size;
  int     opening_kernel_size;
  int     closing_kernel_size;
  int     morph_kernel_size;
  int     gaussian_kernel_size;

  double  gaussian_sigma;


  float   bilateral_sigma_color;
  float   bilateral_sigma_spatial;

  Dateiname   = "../Parameter/Camera_setting"+to_string(camera_id)+".csv";
  Dateityp    = "Value of the individual setting";

  GlobalObjects->csv_parameter_datei->Oeffnen(Dateiname, Enum_CSV_Access::Read);

  if (GlobalObjects->csv_parameter_datei->IsOpen())
    {
    GlobalObjects->csv_parameter_datei->Lesen(Dateityp);

    GlobalObjects->csv_parameter_datei->Lesen(hue_min);
    GlobalObjects->csv_parameter_datei->Lesen(hue_max);
    GlobalObjects->csv_parameter_datei->Lesen(saturation_min);
    GlobalObjects->csv_parameter_datei->Lesen(saturation_max);
    GlobalObjects->csv_parameter_datei->Lesen(value_min);
    GlobalObjects->csv_parameter_datei->Lesen(value_max);

    GlobalObjects->csv_parameter_datei->Lesen(erosion_iterations);
    GlobalObjects->csv_parameter_datei->Lesen(dilation_iterations);
    GlobalObjects->csv_parameter_datei->Lesen(opening_iterations);
    GlobalObjects->csv_parameter_datei->Lesen(closing_iterations);
    GlobalObjects->csv_parameter_datei->Lesen(morph_iterations);

    GlobalObjects->csv_parameter_datei->Lesen(erosion_kernel_size);
    GlobalObjects->csv_parameter_datei->Lesen(dilation_kernel_size);
    GlobalObjects->csv_parameter_datei->Lesen(opening_kernel_size);
    GlobalObjects->csv_parameter_datei->Lesen(closing_kernel_size);
    GlobalObjects->csv_parameter_datei->Lesen(morph_kernel_size);
    GlobalObjects->csv_parameter_datei->Lesen(gaussian_kernel_size);

    GlobalObjects->csv_parameter_datei->Lesen(gaussian_sigma);

    GlobalObjects->csv_parameter_datei->Lesen(bilateral_sigma_color);
    GlobalObjects->csv_parameter_datei->Lesen(bilateral_sigma_spatial);

    camera_vector[camera_id]->hue_min                 = hue_min;
    camera_vector[camera_id]->hue_max                 = hue_max;
    camera_vector[camera_id]->saturation_min          = saturation_min;
    camera_vector[camera_id]->saturation_max          = saturation_max;
    camera_vector[camera_id]->value_min               = value_min;
    camera_vector[camera_id]->value_max               = value_max;

    camera_vector[camera_id]->erosion_iterations      = erosion_iterations;
    camera_vector[camera_id]->dilation_iterations     = dilation_iterations;
    camera_vector[camera_id]->opening_iterations      = opening_iterations;
    camera_vector[camera_id]->closing_iterations      = closing_iterations;
    camera_vector[camera_id]->morph_iterations        = morph_iterations;

    camera_vector[camera_id]->erosion_kernel_size     = erosion_kernel_size;
    camera_vector[camera_id]->dilation_kernel_size    = dilation_kernel_size;
    camera_vector[camera_id]->opening_kernel_size     = opening_kernel_size;
    camera_vector[camera_id]->closing_kernel_size     = closing_kernel_size;
    camera_vector[camera_id]->morph_kernel_size       = morph_kernel_size;
    camera_vector[camera_id]->gaussian_kernel_size    = gaussian_kernel_size;

    camera_vector[camera_id]->gaussian_sigma          = gaussian_sigma;

    camera_vector[camera_id]->bilateral_sigma_color   = bilateral_sigma_color;
    camera_vector[camera_id]->bilateral_sigma_spatial = bilateral_sigma_spatial;


    }
  std::cout << "Loaded Settings for Camera " << camera_id <<"." <<endl;
  }

void c_camera_unmanaged::save_camera_calibration                        (int camera_id)
  {
  string  Dateiname;
  string  Dateityp;
  int     numBoards;
  double  DistCoeffs[1][5];
  double  Intrinsic[3][3];
  numBoards = this->numBoards_imgs;

  this->camera_vector[camera_id]->get_calibration_parameter(DistCoeffs, Intrinsic);

  Dateiname   = "../Parameter/Camera_Calibration_Parameter_CameraID_" + to_string(camera_id) + ".csv";
  Dateityp    = "Intrinisic and distortion parameters of camera-single-calibration";

  this->GlobalObjects->csv_parameter_datei->Oeffnen(Dateiname, Enum_CSV_Access::Write);

  this->GlobalObjects->csv_parameter_datei->Schreiben("Dateityp", Dateityp, "[1]");
  this->GlobalObjects->csv_parameter_datei->Schreiben("Anzahl Boards", numBoards, "[1]");
  this->GlobalObjects->csv_parameter_datei->Schreiben("Distortion k1", DistCoeffs[0][0], "[1]");
  this->GlobalObjects->csv_parameter_datei->Schreiben("Distortion k2", DistCoeffs[0][1], "[1]");
  this->GlobalObjects->csv_parameter_datei->Schreiben("Distortion p1", DistCoeffs[0][2], "[1]");
  this->GlobalObjects->csv_parameter_datei->Schreiben("Distortion p2", DistCoeffs[0][3], "[1]");
  this->GlobalObjects->csv_parameter_datei->Schreiben("Distortion k3", DistCoeffs[0][4], "[1]");
  this->GlobalObjects->csv_parameter_datei->Schreiben("Intrinsic fx", Intrinsic[0][0], "[Px]");
  this->GlobalObjects->csv_parameter_datei->Schreiben("Intrinsic 01", Intrinsic[0][1], "[Px]");
  this->GlobalObjects->csv_parameter_datei->Schreiben("Intrinsic cx", Intrinsic[0][2], "[Px]");
  this->GlobalObjects->csv_parameter_datei->Schreiben("Intrinsic 10", Intrinsic[1][0], "[Px]");
  this->GlobalObjects->csv_parameter_datei->Schreiben("Intrinsic fy", Intrinsic[1][1], "[Px]");
  this->GlobalObjects->csv_parameter_datei->Schreiben("Intrinsic cy", Intrinsic[1][2], "[Px]");
  this->GlobalObjects->csv_parameter_datei->Schreiben("Intrinsic 20", Intrinsic[2][0], "[Px]");
  this->GlobalObjects->csv_parameter_datei->Schreiben("Intrinsic 21", Intrinsic[2][1], "[Px]");
  this->GlobalObjects->csv_parameter_datei->Schreiben("Intrinsic 22", Intrinsic[2][2], "[Px]");

  std::cout <<"Camera " <<  camera_id << " Saved Distortion k1 " << to_string(DistCoeffs[0][0]) << endl;
  std::cout <<"Camera " <<  camera_id << " Saved Distortion k2 " << to_string(DistCoeffs[0][1]) << endl;
  std::cout <<"Camera " <<  camera_id << " Saved Distortion p1 " << to_string(DistCoeffs[0][2]) << endl;
  std::cout <<"Camera " <<  camera_id << " Saved Distortion p2 " << to_string(DistCoeffs[0][3]) << endl;
  std::cout <<"Camera " <<  camera_id << " Saved Distortion k3 " << to_string(DistCoeffs[0][4]) << endl;

  std::cout <<"Camera " <<  camera_id << " Saved Intrinsic fx " << to_string(Intrinsic[0][0]) << endl;
  std::cout <<"Camera " <<  camera_id << " Saved Intrinsic 01 " << to_string(Intrinsic[0][1]) << endl;
  std::cout <<"Camera " <<  camera_id << " Saved Intrinsic cx " << to_string(Intrinsic[0][2]) << endl;
  std::cout <<"Camera " <<  camera_id << " Saved Intrinsic 10 " << to_string(Intrinsic[1][0]) << endl;
  std::cout <<"Camera " <<  camera_id << " Saved Intrinsic fy " << to_string(Intrinsic[1][1]) << endl;
  std::cout <<"Camera " <<  camera_id << " Saved Intrinsic cy " << to_string(Intrinsic[1][2]) << endl;
  std::cout <<"Camera " <<  camera_id << " Saved Intrinsic 20 " << to_string(Intrinsic[2][0]) << endl;
  std::cout <<"Camera " <<  camera_id << " Saved Intrinsic 21 " << to_string(Intrinsic[2][1]) << endl;
  std::cout <<"Camera " <<  camera_id << " Saved Intrinsic 22 " << to_string(Intrinsic[2][2]) << endl;


  this->GlobalObjects->csv_parameter_datei->Schliessen();

  }
void c_camera_unmanaged::load_camera_calibration                        (int camera_id)
  {
  string  Dateiname;
  string  Dateityp;
  int     numBoards;
  double  DistCoeffs[1][5];
  double  Intrinsic[3][3];

  Dateiname   = "../Parameter/Camera_Calibration_Parameter_CameraID_" + to_string(camera_id) + ".csv";
  Dateityp    = "Intrinisic and distortion parameters of camera-single-calibration";

  this->GlobalObjects->csv_parameter_datei->Oeffnen(Dateiname, Enum_CSV_Access::Read);

  if (this->GlobalObjects->csv_parameter_datei->IsOpen())
    {
    this->GlobalObjects->csv_parameter_datei->Lesen(Dateityp);
    this->GlobalObjects->csv_parameter_datei->Lesen(numBoards);
    this->GlobalObjects->csv_parameter_datei->Lesen(DistCoeffs[0][0]);
    this->GlobalObjects->csv_parameter_datei->Lesen(DistCoeffs[0][1]);
    this->GlobalObjects->csv_parameter_datei->Lesen(DistCoeffs[0][2]);
    this->GlobalObjects->csv_parameter_datei->Lesen(DistCoeffs[0][3]);
    this->GlobalObjects->csv_parameter_datei->Lesen(DistCoeffs[0][4]);
    this->GlobalObjects->csv_parameter_datei->Lesen(Intrinsic[0][0]);
    this->GlobalObjects->csv_parameter_datei->Lesen(Intrinsic[0][1]);
    this->GlobalObjects->csv_parameter_datei->Lesen(Intrinsic[0][2]);
    this->GlobalObjects->csv_parameter_datei->Lesen(Intrinsic[1][0]);
    this->GlobalObjects->csv_parameter_datei->Lesen(Intrinsic[1][1]);
    this->GlobalObjects->csv_parameter_datei->Lesen(Intrinsic[1][2]);
    this->GlobalObjects->csv_parameter_datei->Lesen(Intrinsic[2][0]);
    this->GlobalObjects->csv_parameter_datei->Lesen(Intrinsic[2][1]);
    this->GlobalObjects->csv_parameter_datei->Lesen(Intrinsic[2][2]);

    this->GlobalObjects->csv_parameter_datei->Schliessen();

    }

  this->camera_vector[camera_id]->set_calibration_parameter(DistCoeffs, Intrinsic);

  std::cout << "Loaded Calibration for Camera " << camera_id <<"." <<endl;

  }

void c_camera_unmanaged::save_camera_positioning                        (std::vector<int> camera_list)
  {
  string  Dateiname;
  string  Dateityp;
  Dateiname   = "../Parameter/Camera_Positioning.csv";
  Dateityp    = "Correct Camera position in vector corresponding to their ID";

  GlobalObjects->csv_parameter_datei->Oeffnen(Dateiname, Enum_CSV_Access::Write);

  GlobalObjects->csv_parameter_datei->Schreiben("Dateityp", Dateityp, "[1]");
  GlobalObjects->csv_parameter_datei->Schreiben("Anzahl Kameras", to_string(GlobalObjects->cameras_in_use), "[1]");


  for (int i = 0; i < GlobalObjects->cameras_in_use; i++)
    {
    GlobalObjects->csv_parameter_datei->Schreiben("Cameravector[" + to_string(i) +"]", to_string(camera_list[i]), "[1]");
    std::cout << "Saving Camera " << i << " to position " << camera_list[i];
    }


  GlobalObjects->csv_parameter_datei->Schliessen();

  }
void c_camera_unmanaged::load_camera_positioning                        ()
  {
  string  Dateiname;
  string  Dateityp;
  int id;
  int Camera_count;

  Dateiname   = "../Parameter/Camera_Positioning.csv";

  GlobalObjects->csv_parameter_datei->Oeffnen(Dateiname, Enum_CSV_Access::Read);
  if(GlobalObjects->csv_parameter_datei->IsOpen())
    {

    GlobalObjects->csv_parameter_datei->Lesen(Dateityp);
    GlobalObjects->csv_parameter_datei->Lesen(Camera_count);
    if(GlobalObjects->cameras_in_use == Camera_count)
      {
      for (int i = 0; i < Camera_count; i++)
        {
        GlobalObjects->csv_parameter_datei->Lesen(id);
        GlobalObjects->camera_order->push_back(id);
        move_camera_vector2temp(i, id);
        }

      move_camera_temp2vector(Camera_count);
      load_positioning = true;
      }

    }
  std::cout << "Loaded Positioning."  <<endl;

  }

void c_camera_unmanaged::init_camera_vectors                            (int cameras_in_use)
{
  //Create a camera object and start its according thread. The amount of objects equals the amount of cameras in use 
  for                                                       (int i = 0; i < cameras_in_use; i++)
    {
    nmsp_opencv_unmanaged::c_opencv_unmanaged *opencv_unmanaged = new nmsp_opencv_unmanaged::c_opencv_unmanaged (i);
    opencv_unmanaged->idle                                      = true;
    camera_vector.push_back                                 (opencv_unmanaged);

    std::cout << "Created " << i+1 << " Camera Objects with according pointers"<< std::endl;


    current_camera_id                                           = i;
    camera_thread   = new std::thread                       (&c_camera_unmanaged::start_camera_thread, this);
    camera_vector_temp.resize                               (cameras_in_use);
    }

  //Reorder recently created Cameras
  this->load_camera_positioning                             ();

  //Load Settings and Calibration for each camera created earlier
  for                                                       (int i = 0; i < cameras_in_use; i++)
    {
    this->load_camera_calibration                           (i);
    this->load_camera_settings                              (i);
    }
  }
void c_camera_unmanaged::close_cameras                                  (int cameras_in_use)
  {
  for (int i = 0; i < cameras_in_use; i++)
    {
    camera_vector[i]->cap->release();
    }
  }

void c_camera_unmanaged::move_camera_vector2temp                        (int camera_desired_id, int camera_current_id)
  {
  std::vector<nmsp_opencv_unmanaged::c_opencv_unmanaged*>::iterator iterator = camera_vector_temp.begin();
  // Wo ist die feste Position der Kamera? -> Camera_Current_ID
  // Wo ist die Position der Kamera im unsorted Vector? ->Camera_desired_id
  // Zeige die fest installierte Position des Vektors "Referrences" auf die Adresse im Unsortierten Vektor
  camera_vector_temp[camera_desired_id] = std::move(camera_vector[camera_current_id]);
  //camera_vector_temp.insert(camera_vector_temp.begin()+camera_desired_id, camera_vector[camera_current_id]);
  std::cout << " Moved Pointer for Camera " << camera_current_id << " to Position " << camera_desired_id << " in temporary Vector" << std::endl;
  }
void c_camera_unmanaged::move_camera_temp2vector                        (int cameras_in_use)
  {
  for (int i = 0; i < cameras_in_use; i++)
    {
    camera_vector[i] = std::move(camera_vector_temp[i]);
    }
  }

void c_camera_unmanaged::calibrate_single_camera                        (int current_camera_id)
  {
  // Deklaration benötigter Variablen
  cv::Mat                     Originalbild;
  cv::Mat                     Grau_Bild;
  vector<cv::Point2f>         Corners;
  cv::Size                    Board_Sz         = cv::Size (this->numCornersWidth, this->numCornersHeight);
  cv::Mat                     intrinsic          (cv::Mat_<double>(3, 3));
  cv::Mat                     distCoeffs;
  vector<cv::Point3f>         Obj;
  vector<vector<cv::Point3f>> Object_Points;
  vector<vector<cv::Point2f>> Image_Points;
  vector<cv::Mat>             Rvecs;
  vector<cv::Mat>             Tvecs;
  vector<cv::Mat>             TCP_Orientation;
  vector<cv::Mat>             TCP_Position;
  cv::Mat                     R_TCP2Cam;
  cv::Mat                     T_TCP2Cam;
  vector<cv::Mat>             Rvecs_Rodrigues;

  this->Photo_ID = 0;

  // Füllen des "Obj"-Vektors mit 3D-Koordinaten der Schachbrett-Ecken. Die Koordinaten werden manuell vorgegeben und ergeben sich über Länge
  // und Breite der Schachbrett-Rechtecke über die gesamte Länge und Breite des Schachbrettes. Das Schachbrett-Rechteck hat eine Größe von
  // 24.23mm x 24.23mm. Damit ergeben sich die Koordinaten (x, y, z) wie folgt: (0, 0, 0), (24.23, 0, 0), (48.46, 0, 0), .... z ist immer null,
  // da die Rechtecke auf einer Ebene liegen und der Koordinatensystemursprung (Welt) auf dem Schachbrett liegt.
  for (int i = 0; i < this->numCornersHeight; i++)
    {
    for (int j = 0; j < this->numCornersWidth; j++)
      {
      Obj.push_back (cv::Point3f((float)j * this->SquareSize, (float)i * this->SquareSize, 0.0f));
      }
    }

  // Abarbeiten aller gespeicherten Bilder
  while (this->Photo_ID < this->numBoards_imgs)
    {
    std::cout << "Processing image " << Photo_ID << " out of " << numBoards_imgs << " images." << endl;
    // Laden des Bildes mit der angegebenen Photo_ID
    Originalbild = cv::imread ("../Parameter/Bilder/Camera_Single_Calibration_" + std::to_string(camera_id) + "_Snapshot_" + std::to_string(this->Photo_ID) + ".png", 1);

    // Umwandeln des geladenen Bildes in ein Grauwertbild und abspeichern dieses in einem anderen Bild-Array
    cvtColor (Originalbild, Grau_Bild, cv::COLOR_BGR2GRAY);

    // Das geladenene Originalbild nach Schachbrett-Ecken absuchen. Die Anzahl der inneren Ecken über Länge und Breite wird über "Board_Sz" vorgegeben und
    // die gefundenen Ecken werden in "Corners" abgespeichert. Es wird eine adaptive Schwellwertbildung genutzt und das Bild wird nach Rechtecken
    // gefiltert. "Found" wird nur true, wenn alle Ecken gefunden wurden. Die Ecken-Koordinaten aus "Corners" sind 2D-Koordinaten der Bildebene.
    bool Found = findChessboardCorners (Originalbild, Board_Sz, Corners, cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_FILTER_QUADS);

    if (Found) // Falls Rechtecke gefunden wurden
      {
      // Mit Hilfe der gefundenen Ecken in "Corners" werden im Graustufenbild nun die Ecken-Standorte verfeinert. Mit den beiden "Size"-Angaben
      // wird die Größe der abzusuchenden Bereiche in jedem Iterationsschritt angegeben. Der erste Wert legt die Fenstergröße auf (2*5+1) x (2*5+1) = 11x11
      // fest, der zweite Wert legt die Mindestgröße fest, wobei die Werte -1 angeben, dass es keine "Totzone" gibt. Mit "TermCriteria" werden die
      // Ausstiegbedingungen für den Iterationsvorgang angegeben. "EPS" legt eine gewünschte Genauigkeit bzw. Parameteränderung von 0.1 fest. "MAX_ITER"
      // legt die Anzahl der maximalen Iterationen von 30 fest. Die Ausstiegsbedingung ist eine ODER-Bedingung.
      cornerSubPix         (Grau_Bild, Corners, cv::Size(5, 5), cv::Size(-1, -1), cv::TermCriteria(cv::TermCriteria::EPS | cv::TermCriteria::MAX_ITER, 30, 0.1));

      // Mit dieser Funktion werden die gefundenen Ecken aus "Corners" im Graustufenbild eingezeichnet. Ist "Found" true, wurde das Schachbrett und die
      // Ecken erkannt und diese werden markiert und mit Linien verbunden. Ist "Found" false, werden nur die gefundenen Ecken mit einem roten Kreis markiert.
      drawChessboardCorners(Grau_Bild, Board_Sz, Corners, Found);

      // Die gefundenen Ecken-Koordinaten (2D, ohne z-Koordinate) im Vektor "Image-Points" abspeichern.
      Image_Points.push_back  (Corners);

      // Alle manuell vorgegebenen Ecken-Koordinaten aus "Obj" in Vektor "Object_Points" ablegen.
      Object_Points.push_back (Obj);

      // Die entsprechende Roboterpose zum aktuellen Bild in einem Vektor abspeichern. Dieser Vektor wird für
      // die Eye-In-Hand-Kalibrierung benötigt.
      cv::Mat Mat_Orientation (cv::Mat_<double>(3, 3));
      cv::Mat Mat_Position    (cv::Mat_<double>(3, 1));

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
      TCP_Orientation.push_back(Mat_Orientation);
      TCP_Position.push_back   (Mat_Position);
      }

    // Grauwertbild mit eingezeichneten Ecken abspeichern.
    imwrite ("../Parameter/Bilder/Camera_Single_Calibration_" + std::to_string(camera_id) + "_Gray_DrawCorners_" + std::to_string(this->Photo_ID) + ".png", Grau_Bild);

    // Photo-ID für nächsten Durchlauf erhöhen.
    this->Photo_ID++;
    }

  // Mit den gefundenen Ecken in 2D-Koordinaten und den vorgegebenen 3D-Koordinaten werden die intrinsischen Parameter (Camera-Matrix) und
  // die Koeffizienten der Verzerrung berechnet. Rvecs und Tvecs erhalten dabei die Orientierung und die Position der Transformationsmatrix
  // zwischen Kamerakoordinatensystem und Schachbrettkoordinatensystem.
  std::cout << endl << "Calculating Intrinsic and DistCoeffs. This may take a while, please wait." << endl;
  cv::calibrateCamera(Object_Points, Image_Points, Originalbild.size(), intrinsic, distCoeffs, Rvecs, Tvecs);

  std::cout << "Calculation finished. Saving data." << endl << endl;

  *camera_vector[camera_id]->Intrinsic  = intrinsic;
  *camera_vector[camera_id]->DistCoeffs = distCoeffs;

  this->save_camera_calibration(camera_id);

  //// Durchführen der HandEye-Kalibrierung zur Berechnung der Kamerapose relativ zum TCP-Koordinatensystem.
  //// Für die Funktion "calibrateHandEye" müssen die Orientierungen zwischen Kamera und Schachbrett als 3x3-Matrix
  //// vorliegen. Die Ausgabe aus der Kamerakalibrierung übergibt jedoch einen 3x1 Vektor (Rotation um eine Beliebige
  //// Achse mit einem beliebigen Drehwinkel). Die Funktion "Rodrigues" wandelt den 3x1-Vektor in eine 3x3-Matrix um
  //// (Rodrigues-Frank-Formeln). Die umgewandelten Vektoren werden als Matrix in einem Vektor abgelegt.
  //for (int i = 0; i < (int)Rvecs.size(); i++)
  //  {
  //  Mat Rvec_Rodrigues (Mat_<double>(3, 3));
  //  Rodrigues(Rvecs.at(i), Rvec_Rodrigues);
  //  Rvecs_Rodrigues.push_back(Rvec_Rodrigues);
  //  }

  //// Die Funktion "calibrateHandEye" berechnet die Transformationspose zwischen TCP / Gripper und der Kamera (T_g_c).
  //// Die ersten beiden Parameter sind jeweils die Orientierung und die Position des TCP bezogen auf das Roboter-Basis-
  //// Koordinatensystem und zwar bezogen auf jedes aufgenommene Foto. Die Roboterpose wird also jedes mal bei Foto-
  //// aufnahme während der Kalibrierung in einem Vektor abgespeichert. Diese Pose wird dann in Orientierung und Position
  //// getrennt ("TCP_Orientation" und "TCP_Position", for-Schleife oben). Die Parameter Rvecs_Rodrigues und Tvecs
  //// erhalten dabei die Orientierung und die Position der Transformationsmatrix zwischen Kamerakoordinatensystem
  //// und Schachbrettkoordinatensystem. Die Parameter "R_Cam2TCP" und "T_Cam2TCP" sind nun die Orientierung und Position der
  //// Transformationsmatrix (die Lösung der Gleichungssysteme) zwischen TCP und Kamera. Mit dem letzten Parameter kann die
  //// Berechnungmethode bestimmt werden.
  //calibrateHandEye(TCP_Orientation, TCP_Position, Rvecs_Rodrigues, Tvecs, R_TCP2Cam, T_TCP2Cam, cv::CALIB_HAND_EYE_ANDREFF);

  //*this->Translation_TCP2Cam = T_TCP2Cam;
  //*this->Orientation_TCP2Cam = R_TCP2Cam;

  }

void c_camera_unmanaged::save_picture                                   (int camera_id, int photo_id)
  {
  cv::imwrite("../Parameter/Bilder/Camera_Single_Calibration_" + std::to_string(camera_id) + "_Snapshot_" + std::to_string(photo_id) + ".png", *camera_vector[camera_id]->cpu_src_img);
  }
