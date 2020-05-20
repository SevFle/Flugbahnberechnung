#pragma once
#include <vector>

namespace object
  {
  class C_object
    {
      public:
      C_object(int objekt_id);
      ~C_object();

      int objekt_id;
      int state;

      double translation[3];
      double velocity[3];

      double pixel_coordinates[3];

      bool active;

      std::vector<double> pose_x;
      std::vector<double> pose_y;
      std::vector<double> pose_z;

      void get_pixel_coordinates();
      void calculate_pose();

      void save_trajectory();
      void statemachine();


    };
  }


