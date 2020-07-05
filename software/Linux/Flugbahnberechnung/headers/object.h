#pragma once
#ifndef __Object_H
#define __Object_H
#include <vector>
#include "headers/posen.h"

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

    //S_Positionsvektor positionsvektor;
	bool              found_0;
	bool              found_1;
    //S_Positionsvektor Richtungsvektor_0;
    //S_Positionsvektor Richtungsvektor_1;
	int               ID_Cam_Links;
	int               ID_Cam_Rechts;
	double			  timestamp;


    std::vector<double> pose_x;
    std::vector<double> pose_y;
    std::vector<double> pose_z;

    void get_pixel_coordinates();
    void calculate_pose();
    void calculate_px_speed();
    void calculate_ms_speed();


    void save_trajectory();
    void statemachine();

    void set_ID_Cam_Links(int ID_Cam_Links);
    void set_ID_Cam_Rechts(int ID_Cam_Rechts);


    int get_ID_Cam_Links();
    int get_ID_Cam_Rechts();

    };
  }

#endif


