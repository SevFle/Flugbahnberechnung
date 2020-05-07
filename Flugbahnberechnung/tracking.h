#pragma once
#include "posen.h"
#include "GlobalObjects.h"
#include <vector>

using namespace nmsp_posen;
using namespace nmsp_GlobalObjects;


namespace nmsp_tracking
  {
  struct s_tracking_data
    {
    S_Positionsvektor positionsvektor;
    bool              found_0;
    bool              found_1;
    S_Positionsvektor Richtungsvektor_0;
    S_Positionsvektor Richtungsvektor_1;
    int               ID_Cam_Links;
    int               ID_Cam_Rechts;
    };

  class c_tracking
    {
    public:
    c_tracking (C_GlobalObjects* GlobalObject);
    ~c_tracking ();
    void               init_posen ();
    void               load_posen ();
    S_Positionsvektor* Positionsvektor_alt;
    private:
    C_GlobalObjects* GlobalObjects;

    public:
    //void                                    Get_Position_ObjectTracking                       (S_Positionsvektor&        Positionsvektor);

    void Get_Position_ObjectTracking (s_tracking_data& StructofTrackingData, std::vector<C_AbsolutePose>& vec_WorldToCam_Poses);
    void Calc_Position_ObjectTracking (S_Positionsvektor& Positionsvektor, std::vector<S_Positionsvektor> vec_Richtungsvektoren_World, std::vector<C_AbsolutePose> vec_WorldToTCP_Poses);
    void Calc_RichtungsvektorenToWorld (std::vector<S_Positionsvektor> vec_Richtungsvektoren, std::vector<S_Positionsvektor>& vec_Richtungsvektoren_World, std::vector<C_AbsolutePose> vec_TCP_Poses);
    };
  }
