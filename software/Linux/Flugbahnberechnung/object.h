#pragma once
#include <vector>

namespace object
  {
  class C_object
    {
    public:
    C_object();
    ~C_object();
	public:
	int objekt_id;
    int state;

    double translation[3];
    double velocity[3];

    double pixel_coordinates[3];

    bool active;

	S_Positionsvektor positionsvektor;
	bool              found_0;
	bool              found_1;
	S_Positionsvektor Richtungsvektor_0;
	S_Positionsvektor Richtungsvektor_1;
	int               ID_Cam_Links;
	int               ID_Cam_Rechts;
	double			  timestamp;


    std::vector<double> pose_x;
    std::vector<double> pose_y;
    std::vector<double> pose_z;

    void get_pixel_coordinates();
    void calculate_pose();

    void save_trajectory();
    void statemachine();




    };
  }


