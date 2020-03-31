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
  }
/**************************************************************** Destruktor ****************************************************************/
c_camera_unmanaged::~c_camera_unmanaged                                 ()
  {
  GlobalObjects = nullptr;
  stop_statemachine = false;
  cameras_in_use  = 0;
  }

/*************************************************** Nicht öffentliche private Methoden *****************************************************/

void c_camera_unmanaged::start_camera_thread                            ()
  {
  camera_vector[current_camera_id]->camera_thread();
  }
/******************************************************* Öffentliche Anwender-Methoden ******************************************************/

void c_camera_unmanaged::save_camera_settings                           (int camera_id)
  {
  string  Dateiname;
  string  Dateityp;
  Dateiname   = "Camera_setting"+to_string(camera_id)+".csv";
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

  Dateiname   = "Camera_setting"+to_string(camera_id)+".csv";
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
  }

void c_camera_unmanaged::save_camera_calibration                        ()
  {
  for (int i = 0; i< cameras_in_use; i++)
    {

    }
  }
void c_camera_unmanaged::load_camera_calibration                        ()
  {
  for (int i = 0; i< cameras_in_use; i++)
    {

    }
  }

void c_camera_unmanaged::save_camera_positioning                        (std::vector<int> camera_list)
  {
  string  Dateiname;
  string  Dateityp;
  Dateiname   = "Camera_Positioning.csv";
  Dateityp    = "Correct Camera position in vector corresponding to their ID";

  GlobalObjects->csv_parameter_datei->Oeffnen(Dateiname, Enum_CSV_Access::Write);

  GlobalObjects->csv_parameter_datei->Schreiben("Dateityp", Dateityp, "[1]");
  GlobalObjects->csv_parameter_datei->Schreiben("Anzahl Kameras", to_string(GlobalObjects->cameras_in_use), "[1]");


  for (int i = 0; i < GlobalObjects->cameras_in_use; i++)
    {
    GlobalObjects->csv_parameter_datei->Schreiben("Cameravector[" + to_string(i) +"]", to_string(camera_list[i]), "[1]");
    }


  GlobalObjects->csv_parameter_datei->Schliessen();

  }
void c_camera_unmanaged::load_camera_positioning                        ()
  {
  string  Dateiname;
  string  Dateityp;
  int id;
  int Camera_count;

  Dateiname   = "Camera_Positioning.csv";

  GlobalObjects->csv_parameter_datei->Oeffnen(Dateiname, Enum_CSV_Access::Read);
  if(GlobalObjects->csv_parameter_datei->IsOpen())
    {

    GlobalObjects->csv_parameter_datei->Lesen(Dateityp);
    GlobalObjects->csv_parameter_datei->Lesen(Camera_count);
    if(GlobalObjects->cameras_in_use == Camera_count)
      {

      for (int i = 0; i < GlobalObjects->cameras_in_use; i++)
        {
        GlobalObjects->csv_parameter_datei->Lesen(id);
        GlobalObjects->camera_order->push_back(id);
        move_camera_vector2temp(i, id);
        }

      move_camera_temp2vector(GlobalObjects->cameras_in_use);

      }

    }
  }

void c_camera_unmanaged::create_camera_vectors                          (int cameras_in_use)
{
  for (int i = 0; i < cameras_in_use; i++)
    {
    nmsp_opencv_unmanaged::c_opencv_unmanaged *opencv_unmanaged = new nmsp_opencv_unmanaged::c_opencv_unmanaged (i);
    camera_vector.push_back                          (opencv_unmanaged);
    //camera_vector_referrences.push_back                       (camera_referrence);
    std::cout << "Created " << i+1 << " Camera Objects with according pointers"<< std::endl;
    current_camera_id = i;
    camera_thread   = new std::thread(&c_camera_unmanaged::start_camera_thread, this);
    camera_vector_temp.resize(cameras_in_use);
    //delete (opencv_unmanaged);
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

