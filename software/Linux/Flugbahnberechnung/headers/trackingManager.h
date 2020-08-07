#pragma once
#ifndef __Tracking_H
#define __Tracking_H

#include "posen.h"
#include "GlobalObjects.h"
#include "object.h"
#include <vector>

using namespace posen;
using namespace GlobalObjects;


namespace trackingManager
  {
  struct S_trackingPayload
    {
    S_Positionsvektor positionsvektor;
    bool              found_0;
    bool              found_1;
    S_Positionsvektor Richtungsvektor_0;
    S_Positionsvektor Richtungsvektor_1;
    int               ID_Cam_Links;
    int               ID_Cam_Rechts;
    double            timestamp;
    };

  class C_trackingManager
    {
    public:
    C_trackingManager                   (C_GlobalObjects* GlobalObject);
    ~C_trackingManager                  ();

    S_Positionsvektor*                  Positionsvektor_alt;
    private:
    C_GlobalObjects*                    globalObjects;
    S_trackingPayload*                  trackingPayload;

    bool                                alive;
    object::C_object*                   trackedObject;
    std::vector<C_AbsolutePose>*        vecWorldtoCamPose;
    std::vector<S_Positionsvektor>*     vecPositions;
    int                                 smState;
    int                                 camIDLeft;
    int                                 camIDRight;
    bool                                initZoneAlive;


    public:
    void init_posen                     ();
    void load_posen                     ();

    void Get_Position_ObjectTracking                  (S_trackingPayload&             StructofTrackingData,   std::vector<C_AbsolutePose>&    vec_WorldToCam_Poses);
    void Calc_Position_ObjectTracking                 (S_Positionsvektor&             Positionsvektor,        std::vector<S_Positionsvektor>  vec_Richtungsvektoren_World, std::vector<C_AbsolutePose> vec_WorldToTCP_Poses);
    void Calc_RichtungsvektorenToWorld                (std::vector<S_Positionsvektor> vec_Richtungsvektoren,  std::vector<S_Positionsvektor>& vec_Richtungsvektoren_World, std::vector<C_AbsolutePose> vec_TCP_Poses);

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
