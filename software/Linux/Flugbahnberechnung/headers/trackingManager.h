#ifndef __Tracking_H
#define __Tracking_H


#include "posen.h"
#include "GlobalObjects.h"
#include "object.h"
#include <vector>

using namespace posen;
using namespace GlobalObjects;
/********************************************** DEFINE PAYLOAD SIZE ******************************************************/
const int payloadSize =  2;


namespace trackingManager
  {
  struct S_trackingPayload
    {
    int               ID_Cam_Links[2];
    int               ID_Cam_Rechts[2];
    double            timestamp;

    //GET_OBJECTPOSITION_FROM_CAMERA()
    bool              found[4];
    S_Positionsvektor vecRichtung[4];

    };

  class C_trackingManager
    {
    public:
    C_trackingManager                   (C_GlobalObjects* GlobalObject);
    ~C_trackingManager                  ();

    private:
    C_GlobalObjects*                    globalObjects;
    S_trackingPayload*                  trackingPayload;
    S_Positionsvektor*                  Positionsvektor_alt;

    bool                                alive;
    object::C_object*                   trackedObject;
    std::vector<C_AbsolutePose>         vecWorldtoCamPose;
    std::vector<S_Positionsvektor>*     vecPositions;
    vector<C_AbsolutePose>              vecEinheitsVektor;

    /****************** Positionsbuffer T-1 *******************/
  private:
    S_Positionsvektor*                  RichtungsvektorenTm1   [payloadSize];
    S_Positionsvektor*                  objektVektorTm1;
    float                               pixelVelocityTm1 [3];
    float                               objectVelocityTm1 [3];
  public:
    float                               pixelVelocity [payloadSize][3];
    float                               pixelAcceleration [payloadSize][3];
    float                               objectVelocity [3];
    float                               objectAcceleration [3];
  private:

    int                                 smState;
    int                                 camIDLeft;
    int                                 camIDRight;
    bool                                initZoneAlive;


    public:
    void init_posen                     ();
    void load_posen                     (C_AbsolutePose& cameraPose);

    void Get_Position_ObjectTracking                  (S_Positionsvektor&             objektVektor, S_Positionsvektor* Richtungsvektoren   [payloadSize]);
    void Calc_Position_ObjectTracking                 (S_Positionsvektor&             objektVektor, vector<S_Positionsvektor>  vec_Richtungsvektoren_World);
    void Calc_RichtungsvektorenToWorld (S_Positionsvektor* vec_Richtungsvektoren[payloadSize], std::vector<S_Positionsvektor>& vec_Richtungsvektoren_World, std::vector<C_AbsolutePose> vecEinheitsMatrix);

    void calcPixelVeloctiy(int dTimestamp, S_Positionsvektor* Richtungsvektoren   [payloadSize], int camID);
    void calcObjectVeloctiy(int dTimestamp, S_Positionsvektor&             objektVektor);

    void calcPixelAcceleration(int dTimestamp);
    void calcObjectAcceleration(int dTimestamp);


    bool getAlive                                     () const;
    void setAlive                                     (bool value);
    S_Positionsvektor *getPositionsvektor_alt         () const;
    void setPositionsvektor_alt                       (S_Positionsvektor *value);

    void smTracking                                   ();
    S_trackingPayload getTrackingPayload() const;
    void setTrackingPayload(const S_trackingPayload &value);
    int getSmState() const;
    void setSmState(int value);
    bool getInitZoneAlive() const;
    void setInitZoneAlive(bool value);
    };
  }
#endif
