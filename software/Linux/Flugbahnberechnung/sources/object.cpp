#include "headers/object.h"

using namespace object;


C_object::C_object()
  {
  this->objekt_id = 0;
  this->state = 0;
  this->translation[0] = 0;
  this->translation[1] = 0;
  this->translation[2] = 0;
  this->velocity[0] = 0;
  this->velocity[1] = 0;
  this->velocity[2] = 0;
  this->pixel_coordinates[0] = 0;
  this->pixel_coordinates[1] = 0;
  this->pixel_coordinates[2] = 0;
  this->active = false;


  }


C_object::~C_object()
  {
  }

void C_object::get_pixel_coordinates()
{

}
void C_object::calculate_pose()
{

}
void C_object::calculate_px_speed()
{

}
void C_object::calculate_ms_speed()
{

}


void C_object::save_trajectory()
{

}

void C_object::set_ID_Cam_Links(int ID_Cam_Links)
{
}
void C_object::set_ID_Cam_Rechts(int ID_Cam_Rechts)
{
}


int C_object::get_ID_Cam_Links()
{
}
int C_object::get_ID_Cam_Rechts()
{
}

double C_object::get_pose_x(int vec_position)
{
return this->vec_pose_x[vec_position];
}
double C_object::get_pose_y(int vec_position)
{
    return this->vec_pose_y[vec_position];
}
double C_object::get_pose_z(int vec_position)
{
    return this->vec_pose_z[vec_position];
}
double C_object::get_timestamp(int vec_position)
{
 return this->vec_timestamp[vec_position];
}


void C_object::set_pose_x(double pose_x)
  {
  this->vec_pose_x.push_back(pose_x);
  }
void C_object::set_pose_y(double pose_y)
  {
  this->vec_pose_y.push_back(pose_y);
  }
void C_object::set_pose_z(double pose_z)
  {
  this->vec_pose_z.push_back(pose_z);
  }
void C_object::set_timestamp(double timestamp)
  {
  this->vec_timestamp.push_back(timestamp);
  }


