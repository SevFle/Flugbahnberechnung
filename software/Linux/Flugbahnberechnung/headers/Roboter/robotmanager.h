#ifndef C_ROBOTMANAGER_H
#define C_ROBOTMANAGER_H
#include "posen.h"
#include "robot.h"
#include "headers/Etc/GlobalObjects.h"
#include "headers/Etc/mathhelper.h"

using namespace GlobalObjects;

namespace robotManager
  {

  class C_robotManager
    {
    enum threadselector
      {
      singlePose,
      continousMovement
      };

  public:
    C_robotManager                      (C_GlobalObjects* globalObjects);
    ~C_robotManager                     ();

    Robot_Panda::C_Robot_Panda*         roboter;
    C_GlobalObjects*                    globalObjects;
    std::thread*                        robotThread;
    GlobalObjects::S_PositionPayload*   objectPayload;
    GlobalObjects::robotConstraints*    outerConstraints;
    GlobalObjects::robotConstraints*    innerConstraints;

    C_AbsolutePose*                     Pose_waiting;
    C_AbsolutePose*                     Pose_inter_waiting;

    posen::S_Positionsvektor*           objectEntry;
    posen::S_Positionsvektor*           objectExit;
    std::atomic<bool>*                  state_machine_running;
    std::thread*                        smThread;
    C_mathHelper*                       math;
    threadselector                      threadSelector;
    std::vector<C_AbsolutePose>         vec_AbsPosenBezier;

    bool                                threadActive;
    bool                                robotReady;
    int                                 smBallTrackingStep;


    void initTCP                              ();
    void initRobot                            (std::string IPAdresse);
    bool moveRobotToTarget                    (C_AbsolutePose* targetPose);
    void sm_BallTracking                      ();
    bool close_Panda_threading                ();

    void start_smTracking                     ();
    void stop_smTracking                      ();
    C_AbsolutePose calibrateRobotBaseToWorld  (C_AbsolutePose& worldToCam,  C_RelativePose& BoardToTCP);
  private:
    static void open_Panda_threading          (void *This);
    static void threadHelper                  (void* This);
    void boundingBoxToWorld                   ();
    float mix                                 (float a, float b, float t);
    float BezierQuadratic                     (float A, float B, float C, float t);
    float BezierCubic                         (float A, float B, float C, float D, float t);
    float BezierQuartic                       (float A, float B, float C, float D, float E, float t);
    float BezierQuintic                       (float A, float B, float C, float D, float E, float F, float t);
    float BezierSextic                        (float A, float B, float C, float D, float E, float F, float G, float t);
    C_AbsolutePose computeBezier              (C_AbsolutePose start, C_AbsolutePose mid, C_AbsolutePose end, float t);
    C_AbsolutePose computeBezier              (C_AbsolutePose start, C_AbsolutePose mid1, C_AbsolutePose mid2, C_AbsolutePose End, float t);
    C_AbsolutePose computePoseInWorld         (C_AbsolutePose Abs_pose);
    float computeBezierlength                 (std::vector<C_AbsolutePose>& vecOfBezierPoints);

    /************************************************* GETTER SETTER *******************************************************************/
  public:
    void getAbsoluteHomogenousBaseToTCP       (posen::C_RelativePose* TcpPose);
    void getAbsoluteHomogenousBaseToTCP       (posen::C_AbsolutePose* TcpPose);
    void getAbsoluteHomogenousBaseToWorld     (posen::C_AbsolutePose* BasePose);
    };
  }



#endif // C_ROBOTMANAGER_H
