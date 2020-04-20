#pragma once
#include "posen.h"
#include <vector>

using namespace UM_Posen;

namespace nmsp_tracking
  {
  class c_tracking
    {
      public:
      c_tracking();
      ~c_tracking();

      private:
      S_Positionsvektor                       Positionsvektor_alt;

      void                                    Get_Position_ObjectTracking                       (S_Positionsvektor&        Positionsvektor);
      void                                    Calc_Position_ObjectTracking                      (S_Positionsvektor&        Positionsvektor, std::vector<S_Positionsvektor>  vec_Richtungsvektoren_World, std::vector<C_AbsolutePose> vec_WorldToTCP_Poses);
      void                                    Calc_RichtungsvektorenToWorld                     (std::vector<S_Positionsvektor> vec_Richtungsvektoren, std::vector<S_Positionsvektor>& vec_Richtungsvektoren_World, std::vector<C_AbsolutePose> vec_TCP_Poses);

    };
  }

