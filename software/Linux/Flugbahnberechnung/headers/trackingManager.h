#ifndef __Tracking_H
#define __Tracking_H


#include "posen.h"
#include "GlobalObjects.h"
#include "plotter.h"
#include <chrono>
#include <ctime>

#include <vector>
#include "libCuda.h"

using namespace posen;
using namespace GlobalObjects;
/********************************************** DEFINE PAYLOAD SIZE ******************************************************/
const int payloadSize =  2;
typedef std::chrono::system_clock Clock;
typedef std::chrono::nanoseconds nanoseconds;
typedef std::chrono::milliseconds milliseconds;


namespace trackingManager
  {
  class C_trackingManager
    {
    public:
    C_trackingManager                   (C_GlobalObjects* GlobalObject);
    ~C_trackingManager                  ();

    plotter::C_plotter*                 dataPlotter;

    private:
    C_GlobalObjects*                    globalObjects;
    S_Positionsvektor*                  Positionsvektor_alt;
    //onCuda::KalmanFilter2::C_kalman*    kalmanfilter;

    S_Positionsvektor*                   Richtungsvektoren[payloadSize];
    std::vector<C_AbsolutePose>*         vecWorldtoCamPose;
    std::vector<C_AbsolutePose>*         vecCamToWorldPose;

    vector<C_AbsolutePose>*              vecEinheitsVektor;

    std::vector<int>*                    vecIstX;
    std::vector<int>*                    vecIstY;
    std::vector<float>*                   vecPixelVelocityX;
    std::vector<float>*                   vecPixelVelocityY;
    std::vector<float>*                   vecPixelVelocityZ;

    /****************** Positionsbuffer T-1 *******************/
    S_Positionsvektor*                  objektVektorTm1;
    double                              objectVelocityTm1 [3];
    double                              objectVelocity [3];
    double                              objectAcceleration [3];
    double                              dTime;

    nanoseconds*                        dTimestamp;
    Clock*                              timer;
    Clock::time_point*                  timestamp_ms;
    Clock::time_point*                  timestamp_ms_old;





    public:
    void init_posen                                   ();
    void load_posen                                   (C_AbsolutePose& cameraPose);

    void Get_Position_ObjectTracking                  (S_Positionsvektor&             objektVektor, vector<int> WorldToCamPose_active);
    void Calc_Position_ObjectTracking                 (S_Positionsvektor&             objektVektor, vector<S_Positionsvektor>&  vec_Richtungsvektoren_World, vector<int> WorldToCamPose_active);
    void Calc_RichtungsvektorenToWorld                (std::vector<S_Positionsvektor>& vec_Richtungsvektoren_World, vector<int> WorldToCamPose_active);
    void calcPixelVeloctiy                            (int ist_X, int ist_Y, int camID, int& pred_X, int& pred_Y);
    void calcObjectVeloctiy                           (S_Positionsvektor&             objektVektor);

    void calcPixelAcceleration                        ();
    void calcObjectAcceleration                       ();

    void predictPixelMovement                         (int& predX, int& predY, int pixelVelocityX, int pixelVelocityY, int ist_X, int ist_Y);

    bool getAlive                                     () const;
    void setAlive                                     (bool value);

    const float& getObjectVelocity();
    const float& getObjectAcceleration();


    S_Positionsvektor *getPositionsvektor_alt         () const;
    void setPositionsvektor_alt                       (S_Positionsvektor *value);

    void setRichtungsvektor(S_Positionsvektor *value, int pos);

    void smTracking                                   ();
    int getSmState                                    () const;
    void setSmState                                   (int value);
    bool getInitZoneAlive                             () const;
    void setInitZoneAlive                             (bool value);
    void setTime                                      ();
    double getDTime() const;
    };
  }
#endif
