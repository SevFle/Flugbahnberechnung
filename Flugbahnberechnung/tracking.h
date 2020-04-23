#pragma once
#include "posen.h"
#include <vector>

using namespace nmsp_posen;



namespace nmsp_tracking
  {
  struct s_tracking_data
    {
    S_Positionsvektor positionsvektor;
    bool              found_0;
    bool              found_1;
    S_Positionsvektor Richtungsvektor_0;
    S_Positionsvektor Richtungsvektor_1;
    };

  class c_tracking
    {
      public:
      c_tracking();
      ~c_tracking();

      private:
      S_Positionsvektor*                       Positionsvektor_alt;

      public:
      //void                                    Get_Position_ObjectTracking                       (S_Positionsvektor&        Positionsvektor);

      void                                    Get_Position_ObjectTracking                       (s_tracking_data&        StructofTrackingData);
      void                                    Calc_Position_ObjectTracking                      (S_Positionsvektor&        Positionsvektor, std::vector<S_Positionsvektor>  vec_Richtungsvektoren_World, std::vector<C_AbsolutePose> vec_WorldToTCP_Poses);
      void                                    Calc_RichtungsvektorenToWorld                     (std::vector<S_Positionsvektor> vec_Richtungsvektoren, std::vector<S_Positionsvektor>& vec_Richtungsvektoren_World, std::vector<C_AbsolutePose> vec_TCP_Poses);

    };
  }

