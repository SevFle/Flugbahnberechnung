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
typedef std::chrono::steady_clock Clock;
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


    std::vector<C_AbsolutePose>*         vecWorldtoCamPose;
    vector<C_AbsolutePose>*              vecEinheitsVektor;

    std::vector<int>*                    vecIstX;
    std::vector<int>*                    vecIstY;
    std::vector<float>*                   vecPixelVelocityX;
    std::vector<float>*                   vecPixelVelocityY;
    std::vector<float>*                   vecPixelVelocityZ;

    /****************** Positionsbuffer T-1 *******************/
    S_Positionsvektor*                  objektVektorTm1;
    float                               objectVelocityTm1 [3];
    float                               objectVelocity [3];
    float                               objectAcceleration [3];


    public:
    void init_posen                     ();
    void load_posen                     (C_AbsolutePose& cameraPose);

    void Get_Position_ObjectTracking    (S_Positionsvektor&             objektVektor, S_Positionsvektor Richtungsvektoren[payloadSize]);
    void Calc_Position_ObjectTracking   (S_Positionsvektor&             objektVektor, vector<S_Positionsvektor>  vec_Richtungsvektoren_World);
    void Calc_RichtungsvektorenToWorld  (S_Positionsvektor              Richtungsvektoren[payloadSize], std::vector<S_Positionsvektor>& vec_Richtungsvektoren_World, std::vector<C_AbsolutePose> vecEinheitsMatrix);
    void calcPixelVeloctiy              (int dTimestamp, int ist_X, int ist_Y, int camID, int& pred_X, int& pred_Y);
    void calcObjectVeloctiy             (int dTimestamp, S_Positionsvektor&             objektVektor);

    void calcPixelAcceleration          (int dTimestamp);
    void calcObjectAcceleration         (int dTimestamp);

    void predictPixelMovement                         (int dTimestamp,int& predX, int& predY, int pixelVelocityX, int pixelVelocityY, int ist_X, int ist_Y);

    bool getAlive                                     () const;
    void setAlive                                     (bool value);

    S_Positionsvektor *getPositionsvektor_alt         () const;
    void setPositionsvektor_alt                       (S_Positionsvektor *value);

    void smTracking                                   ();
    int getSmState                                    () const;
    void setSmState                                   (int value);
    bool getInitZoneAlive                             () const;
    void setInitZoneAlive                             (bool value);
    };
  }
#endif
