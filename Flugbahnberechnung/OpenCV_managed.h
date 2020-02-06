#pragma once
#include "OpenCV_unmanaged.h"
#include "GlobalObjects.h"

using namespace nmsp_GlobalObjects;
using namespace nmsp_open_cv_unmanaged;

namespace nmsp_opencv_managed
  {
  ref class C_OpenCV_managed
    {
      public:
      C_OpenCV_managed            (C_GlobalObjects^ GlobalObjects);

      ~C_OpenCV_managed           ();

    private:
    
    public:
    C_opencv_unmanaged* opencv_unmanaged;


    private:
    C_GlobalObjects^    GlobalObjects;


    public:
    bool  open_cam_thread       (int& cam_id, int width, int height);
    bool  close_cam_thread      (int& cam_id);


    };
  }

