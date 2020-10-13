#ifndef C_ROBOT_H
#define C_ROBOT_H

#include <franka/robot.h>
#include <franka/gripper.h>
#include <franka/exception.h>
#include <franka/model.h>

#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>

#include "headers/Roboter/posen.h"
#include "headers/Roboter/pidregler.h"

namespace robot
  {


  class C_robot
    {
    public:
    C_robot             ();
    ~C_robot            ();


  public:
    C_AbsolutePose*     WorldToRobot;
    C_AbsolutePose*     RobotToWorld;

    pidRegler::C_PID_Regler*                     PID_Regler_X_CamCalib;
    pidRegler::C_PID_Regler*                     PID_Regler_Y_CamCalib;
    pidRegler::C_PID_Regler*                     PID_Regler_Z_CamCalib;
    pidRegler::C_PID_Regler*                     PID_Regler_RX_CamCalib;
    pidRegler::C_PID_Regler*                     PID_Regler_RY_CamCalib;
    pidRegler::C_PID_Regler*                     PID_Regler_RZ_CamCalib;
    pidRegler::C_PID_Regler*                     PID_Regler_X_OT;
    pidRegler::C_PID_Regler*                     PID_Regler_Y_OT;
    pidRegler::C_PID_Regler*                     PID_Regler_Z_OT;
    pidRegler::C_PID_Regler*                     PID_Regler_RX_OT;
    pidRegler::C_PID_Regler*                     PID_Regler_RY_OT;
    pidRegler::C_PID_Regler*                     PID_Regler_RZ_OT;

    double                            Panda_Vel_max;
    double                            Panda_Acc_max;
    double                            Panda_Omega_max;
    double                            Panda_Alpha_max;


  private:

    franka::Robot*      robot;
    franka::RobotState* robotstate;
    franka::Duration*   robotDuration;
    franka::Model*      robotModel;
    double                            Richtungsvektor[3];
    double                            Rotationsachse[3];
    double                            Rotationsachse_K0[3];
    double                            Sollweg_Translation;
    double                            Sollwinkel_Rotation;
    double                            Sollvel_Translation;
    double                            Sollomega_Rotation;
    double                            Wegdifferenz;
    double                            Winkeldifferenz;
    franka::CartesianPose*            Abs_Callback_Start_Pose;
    Eigen::Quaternion<double>         Quat_Callback_Start_Orientation;
    franka::CartesianPose*            Abs_Callback_Target_Pose;
    Eigen::Quaternion<double>         Quat_Callback_Target_Orientation;
    int                               dq_Filterposition;
    int                               dq_Filtergroesse;
    std::vector<double>                    dq_Buffer;
    bool                              Object_Found;
    S_Positionsvektor                 WorldToObject_Pos;
    S_Positionsvektor                 CamToObject_Pos;
    S_Positionsvektor                 RobotToControlFrame_Pos;
    bool                              Stop_ObjectTracking;
    double                            ControlFrameToObject_Pos_Abs;
    double                            ControlFrameToTCP_Pos_Abs;
    S_Positionsvektor                 Lichtstrahl_Einheitsvektor;
    S_Positionsvektor                 ControlFrameToTCP_Pos;


  private:

    franka::CartesianPose       CartesianPose_Callback_Function_abs_Weg_Trapez          (double&                time,                   const franka::RobotState&      Robot_State,               franka::Duration& Duration);  // Erstellt die Callback-Funktion fr die Bewegung des Panda
    franka::CartesianVelocities CartesianPose_Callback_Function_abs_Vel_Trapez          (double&                time,                   const franka::RobotState&      Robot_State,               franka::Duration& Duration);  // Erstellt die Callback-Funktion fr die Bewegung des Panda
    franka::CartesianVelocities CartesianVel_Callback_Function_ObjectTracking           (double&                time,                   const franka::RobotState&      Robot_State,               franka::Duration& Duration);  // Erstellt die Callback-Funktion fr die Bewegung des Panda
    franka::CartesianPose       CartesianPose_Callback_Function_Inkrementell_Weg_Trapez (double&                time,                   const franka::RobotState&      Robot_State,               franka::Duration& Duration);  // Erstellt die Callback-Funktion fr die Bewegung des Panda
    franka::Torques             Torque_Callback_Motion_Controller                       (double&                time,                   const franka::RobotState&      Robot_State,               franka::Duration& Duration);  // Erstellt die Callback-Funktion fr die Bewegung des Panda
    franka::Torques             CartesianImpedance_Callback_Function                    (double&                time,                   const franka::RobotState&      Robot_State,               franka::Duration& Duration);  // Erstellt die Callback-Funktion fr die Bewegung des Panda

    bool                        Pose_Reached                                            (double                 Ist,                    double                 Soll,                      double    Epsilon);
    bool                        Pose_Reached                                            (franka::CartesianPose          Ist_Pose,               franka::CartesianPose          Soll_Pose,                 double    Epsilon_T,                   double    Epsilon_R);
    bool                        Pose_Reached                                            (std::array<double, 16>      Ist_Pose,               C_AbsolutePose         Soll_Pose,                 double    Epsilon_T,                   double    Epsilon_R);

    void                        HomogenousOrientationToQuaternion                       (Eigen::Quaternion<double>&    Quat,                   C_AbsolutePose         AbsolutePose);
    void                        HomogenousOrientationToQuaternion                       (Eigen::Quaternion<double>&    Quat,                   C_RelativePose         RelativePose);
    void                        HomogenousPoseToFrankaPose                              (franka::CartesianPose&         FrankaPose,             C_AbsolutePose         AbsolutePose);
    void                        HomogenousPoseToFrankaPose                              (franka::CartesianPose&         FrankaPose,             C_RelativePose         RelativePose);

    void                        QuaternionToHomogenousOrientation                       (Eigen::Quaternion<double>     Quat,                   C_AbsolutePose&        AbsolutePose);
    void                        QuaternionToHomogenousOrientation                       (Eigen::Quaternion<double>     Quat,                   C_RelativePose&        RelativePose);
    void                        QuaternionToFrankaOrientation                           (Eigen::Quaternion<double>     Quat,                   franka::CartesianPose&         FrankaPose);
    void                        FrankaPoseToHomogenousPose                              (franka::CartesianPose          FrankaPose,             C_AbsolutePose&        AbsolutePose);
    void                        FrankaPoseToHomogenousPose                              (franka::CartesianPose          FrankaPose,             C_RelativePose&        RelativePose);
    void                        FrankaOrientationToQuaternion                           (franka::CartesianPose          FrankaPose,             Eigen::Quaternion<double>&    Quat);
    void                        Get_RotationAngle                                       (Eigen::Quaternion<double>     Quat,                   double&                Rotationswinkel);
    void                        Get_UnitRotationAxis                                    (Eigen::Quaternion<double>     Quat,                   double                 (&Rotationsachse)[3]);
    void                        Get_UnitTranslationVektor                               (C_AbsolutePose         StartPose,              C_AbsolutePose         TargetPose,                double    (&Richtungsvektor)[3]);
    void                        Get_TranslationDistance                                 (C_AbsolutePose         StartPose,              C_AbsolutePose         TargetPose,                double&   Distance);
    void                        Get_Inverse_Franka_Pose                                 (franka::CartesianPose          Input_Pose,             franka::CartesianPose&         Output_Pose);
    S_Positionsvektor           Calc_Vector_Produkt                                     (S_Positionsvektor      Erster_Vektor,          S_Positionsvektor      Zweiter_Vektor);
    double                      Calc_Vector_Betrag                                      (S_Positionsvektor      Vektor);




  public:
    bool createRobot    (std::string ipAdress);
    bool startRobot     ();
    bool stopRobot      ();
    bool abortRobot     ();

    void setTCP         (double (&tcp)[4][4]);

    bool                              Is_MotionDone                                           (void);                                                                                                                                                               // Prft, ob die Bewegung des aktuellen Bewegungs-Thread komplett abgeschlossen ist
    void                              Set_Panda_Vel_Acc_max                                   (double                 Panda_Vel_max,          double                  Panda_Acc_max,            double    Panda_Omega_max,             double    Panda_Alpha_max);  // Setzen der maximalen Geschwindigkeit und Beschleunigung

    franka::RobotState  *getRobotstate() const;
    C_AbsolutePose      *getRobotToWorld() const;
    };
  }

#endif // C_ROBOT_H
