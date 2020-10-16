/********************************************************************************************************************************************/
/*                                                                                                                                          */
/*  Header-Datei: UM_Robot_Panda.h                                                                                                          */
/*                                                                                                                                          */
/*  Implementierung der libfranka-Bibliothek und der Panda-Klasse                                                                           */
/*                                                                                                                                          */
/*  Marcel Bnfer      08.09.2019                                                                                                            */
/*                                                                                                                                          */
/********************************************************************************************************************************************/
//#pragma once
#ifndef __UM_Robot_Panda_H
#define __UM_Robot_Panda_H

/************************************************************ Anwender-Includes *************************************************************/
#include <franka/robot.h>
#include <franka/gripper.h>
#include <franka/exception.h>
#include <franka/model.h>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include "headers/Roboter/posen.h"
#include <mutex>
#include <thread>
#include <iostream>

/************************************************************** using namespaces **************************************************************/
using namespace franka;
using namespace Eigen;
using namespace posen;


namespace Robot_Panda
  {
  /************************************************************ Enum ObjectTracking *************************************************************/
  enum E_ObjectTracking
    {
    Object_Not_Found, // Objekt durch eigene Kamera nicht erfasst
    Mono_Object,      // Objekt nur durch eigene Kamera erfasst
    Stereo_Object,    // Objekt durch beide Kameras erfasst
    };

  /*********************************************************** Vorwärtsdeklarationen ************************************************************/
  class C_Robot_Panda;



  /*************************************************************** C_Sollweg_Vorgabe ***************************************************************/
  class C_Sollweg_Vorgabe
    {
    /*************************************************************** Konstruktoren **************************************************************/
    public:
    C_Sollweg_Vorgabe                                                                            (C_Robot_Panda* UM_Robot_Panda);

    /**************************************************************** Destruktor ****************************************************************/
    public:
    ~C_Sollweg_Vorgabe                                                                          ();

    /**************************************************** ffentliche Anwender-Attribute ********************************************************/
    public:
    double                              Gesamtzeit;

    /********************************************** Nicht ffentliche private Anwender-Attribute ************************************************/
    private:
    C_Robot_Panda*                   UM_Robot_Panda;
    double                              Taktzeit;
    double                              Panda_acc;
    double                              Panda_vel;
    double                              Panda_weg_1;
    double                              Panda_weg_2;
    double                              Panda_omega;
    double                              Panda_alpha;
    double                              Panda_winkel_1;
    double                              Panda_winkel_2;
    double                              Zeit1_T;
    double                              Zeit2_T;
    double                              Zeit3_T;
    double                              Zeit1_Ist_T;
    double                              Zeit2_Ist_T;
    double                              Zeit3_Ist_T;
    double                              Zeit1_R;
    double                              Zeit2_R;
    double                              Zeit3_R;
    double                              Zeit1_Ist_R;
    double                              Zeit2_Ist_R;
    double                              Zeit3_Ist_R;
    double                              Stuetzwert_Anz1_T;
    double                              Stuetzwert_Anz2_T;
    double                              Stuetzwert_Anz3_T;
    double                              Stuetzwert_Anz1_R;
    double                              Stuetzwert_Anz2_R;
    double                              Stuetzwert_Anz3_R;
    double                              Stuetzwert_Nr_T;
    double                              Stuetzwert_Nr_R;
    double                              Wegaenderung1;
    double                              Wegaenderung2;
    double                              Wegaenderung3;
    double                              Winkelaenderung1;
    double                              Winkelaenderung2;
    double                              Winkelaenderung3;
    int                                 SM_Sollweg_Vorgabe_Schritt_Translation_abs_Weg_Trapez;
    int                                 SM_Sollweg_Vorgabe_Schritt_Translation_abs_Vel_Trapez;
    int                                 SM_Sollweg_Vorgabe_Schritt_Translation_Inkrementell_Weg_Trapez;
    int                                 SM_Sollweg_Vorgabe_Schritt_Rotation_abs_Weg_Trapez;
    int                                 SM_Sollweg_Vorgabe_Schritt_Rotation_abs_Vel_Trapez;
    int                                 SM_Sollweg_Vorgabe_Schritt_Rotation_Inkrementell_Weg_Trapez;

    /****************************************************** ffentliche Anwender-Methoden *******************************************************/
    public:
    bool                                Initialize_Sollweg_Vorgabe_Trapez                       (double  Delta_Pos,  double  Delta_Rad);                   // Initialisiert die Sollwert-Vorgabe
    bool                                SM_Sollweg_Vorgabe_Translation_abs_Weg_Trapez           (double& Sollweg,    double  time);                        // Gibt den Sollwert fr einen Fahrbefehl vor
    bool                                SM_Sollweg_Vorgabe_Translation_abs_Vel_Trapez           (double& Sollvel,    double& Sollweg,    double time);     // Gibt den Sollwert fr einen Fahrbefehl vor
    bool                                SM_Sollweg_Vorgabe_Translation_Inkrementell_Weg_Trapez  (double& Sollweg);                                         // Gibt den Sollwert fr einen Fahrbefehl vor
    bool                                SM_Sollweg_Vorgabe_Rotation_abs_Weg_Trapez              (double& Sollwinkel, double  time);                        // Gibt den Sollwert fr einen Fahrbefehl vor
    bool                                SM_Sollweg_Vorgabe_Rotation_abs_Vel_Trapez              (double& Sollomega,  double& Sollwinkel, double time);     // Gibt den Sollwert fr einen Fahrbefehl vor
    bool                                SM_Sollweg_Vorgabe_Rotation_Inkrementell_Weg_Trapez     (double& Sollwinkel);                                      // Gibt den Sollwert fr einen Fahrbefehl vor
    };



  /*************************************************************** C_Sollweg_Vorgabe ***************************************************************/
  class C_PID_Regler
    {
    /*************************************************************** Konstruktoren **************************************************************/
    public:
    C_PID_Regler                                                                                (void);

    /**************************************************************** Destruktor ****************************************************************/
    public:
    ~C_PID_Regler                                                                               ();

    /**************************************************** ffentliche Variablen ********************************************************/
    public:

    /********************************************** Nicht ffentliche Variablen ************************************************/
    private:
    double                              Regelabweichung_0;
    double                              Regelabweichung_1;
    double                              Kp;
    double                              Tn;
    double                              Tv;
    double                              P_Stellwert;
    double                              I_Stellwert;
    double                              D_Stellwert;
    bool                                P_Regler_Enabled;
    bool                                I_Regler_Enabled;
    bool                                D_Regler_Enabled;
    double                              Taktzeit;

    /****************************************************** ffentliche Funktionen *******************************************************/
    public:
    void                                PID_Regler                                             (double   Istwert,          double   Sollwert,      double   Vorsteuerwert, double&    Stellwert);
    void                                PID_Regler                                             (double   Regelabweichung,  double&  Stellwert);
    void                                Set_PID_Parameter                                      (bool     P_Enabled,        bool     I_Enabled,     bool     D_Enabled,     double     Kp,        double   Tn, double   Tv, double  Taktzeit);
    void                                Get_PID_Parameter                                      (bool&    P_Enabled,        bool&    I_Enabled,     bool&    D_Enabled,     double&    Kp,        double&  Tn, double&  Tv, double& Taktzeit);
    void                                Reset_PID_Regler                                       (void);

    /****************************************************** Nicht ffentliche Funktionen *******************************************************/
    private:
    };

  /*************************************************************** C_UM_Panda_unmanaged ***************************************************************/
  class C_Robot_Panda
    {
    /*************************************************************** Konstruktoren **************************************************************/
    public:
    C_Robot_Panda                                                                          (const char* Panda_IP, bool Franka_Gripper_Enabled);

    /**************************************************************** Destruktor ****************************************************************/
    public:
    ~C_Robot_Panda                                                                         ();

    /******************************************** Nicht öffentliche private Klassenobjekte **************************************************/
    private:
    C_Sollweg_Vorgabe*                Sollweg_Vorgabe;

    /**************************************************** Öffentliche Klassenobjekte ********************************************************/
    public:
    Robot*                            Panda_Robot;
    Gripper*                          Panda_Gripper;
    RobotState*                       Panda_RobotState;
    Duration*                         Panda_Duration;
    Model*                            Panda_Model;
    C_PID_Regler*                     PID_Regler_X_CamCalib;
    C_PID_Regler*                     PID_Regler_Y_CamCalib;
    C_PID_Regler*                     PID_Regler_Z_CamCalib;
    C_PID_Regler*                     PID_Regler_RX_CamCalib;
    C_PID_Regler*                     PID_Regler_RY_CamCalib;
    C_PID_Regler*                     PID_Regler_RZ_CamCalib;
    C_PID_Regler*                     PID_Regler_X_OT;
    C_PID_Regler*                     PID_Regler_Y_OT;
    C_PID_Regler*                     PID_Regler_Z_OT;
    C_PID_Regler*                     PID_Regler_RX_OT;
    C_PID_Regler*                     PID_Regler_RY_OT;
    C_PID_Regler*                     PID_Regler_RZ_OT;

    /******************************************** Nicht öffentliche private Anwender-Attribute **************************************************/
    private:
    bool                              Franka_Gripper_Enabled;
    bool                              MotionDone;
    int                               SM_Panda_Processor_Calibrate_Camera_Schritt;
    int                               SM_Panda_Processor_Move_Slow_Schritt;
    C_AbsolutePose                    Abs_TargetPose;
    double                            Richtungsvektor[3];
    double                            Rotationsachse[3];
    double                            Rotationsachse_K0[3];
    double                            Sollweg_Translation;
    double                            Sollwinkel_Rotation;
    double                            Sollvel_Translation;
    double                            Sollomega_Rotation;
    double                            Wegdifferenz;
    double                            Winkeldifferenz;
    CartesianPose*                    Abs_Callback_Start_Pose;
    Quaternion<double>                Quat_Callback_Start_Orientation;
    CartesianPose*                    Abs_Callback_Target_Pose;
    Quaternion<double>                Quat_Callback_Target_Orientation;
    int                               dq_Filterposition;
    int                               dq_Filtergroesse;
    std::vector<double>               dq_Buffer;
    bool                              Object_Found;
    S_Positionsvektor                 WorldToObject_Pos;
    S_Positionsvektor                 CamToObject_Pos;
    S_Positionsvektor                 RobotToControlFrame_Pos;
    bool                              Stop_ObjectTracking;
    E_ObjectTracking                  enum_ObjectTracking;
    E_ObjectTracking                  enum_ObjectTracking_alt;
    double                            ControlFrameToObject_Pos_Abs;
    double                            ControlFrameToTCP_Pos_Abs;
    S_Positionsvektor                 Lichtstrahl_Einheitsvektor;
    S_Positionsvektor                 ControlFrameToTCP_Pos;

    /**************************************************** ffentliche Anwender-Attribute ********************************************************/
    public:
    C_AbsolutePose                    Abs_WorldToRobot_Pose;
    C_AbsolutePose                    Abs_RobotToWorld_Pose;
    C_AbsolutePose                    Abs_Home_Pose;
    std::vector<C_AbsolutePose>       vectorOf_Abs_Camera_Calibration_Poses;
    int                               Camera_Calibration_PoseID;
    double                            Panda_Vel_max;
    double                            Panda_Acc_max;
    double                            Panda_Omega_max;
    double                            Panda_Alpha_max;
    bool                              SM_Panda_Processor_Calibrate_Camera_Enabled;
    bool                              SM_Panda_Processor_Move_Robot_Slow_Enabled;
    /*************************************************** Nicht ffentliche private Methoden *****************************************************/
    private:
    CartesianPose                     CartesianPose_Callback_Function_abs_Weg_Trapez          (double&                time,                   const RobotState&      Robot_State,               Duration& Duration);  // Erstellt die Callback-Funktion fr die Bewegung des Panda
    CartesianVelocities               CartesianPose_Callback_Function_abs_Vel_Trapez          (double&                time,                   const RobotState&      Robot_State,               Duration& Duration);  // Erstellt die Callback-Funktion fr die Bewegung des Panda
    CartesianVelocities               CartesianVel_Callback_Function_ObjectTracking           (double&                time,                   const RobotState&      Robot_State,               Duration& Duration);  // Erstellt die Callback-Funktion fr die Bewegung des Panda
    CartesianPose                     CartesianPose_Callback_Function_Inkrementell_Weg_Trapez (double&                time,                   const RobotState&      Robot_State,               Duration& Duration);  // Erstellt die Callback-Funktion fr die Bewegung des Panda
    Torques                           Torque_Callback_Motion_Controller                       (double&                time,                   const RobotState&      Robot_State,               Duration& Duration);  // Erstellt die Callback-Funktion fr die Bewegung des Panda
    Torques                           CartesianImpedance_Callback_Function                    (double&                time,                   const RobotState&      Robot_State,               Duration& Duration);  // Erstellt die Callback-Funktion fr die Bewegung des Panda
    bool                              Pose_Reached                                            (double                 Ist,                    double                 Soll,                      double    Epsilon);
    bool                              Pose_Reached                                            (CartesianPose          Ist_Pose,               CartesianPose          Soll_Pose,                 double    Epsilon_T,                   double    Epsilon_R);
    bool                              Pose_Reached                                            (std::array<double, 16>      Ist_Pose,               C_AbsolutePose         Soll_Pose,                 double    Epsilon_T,                   double    Epsilon_R);
    void                              HomogenousOrientationToQuaternion                       (Quaternion<double>&    Quat,                   C_AbsolutePose         AbsolutePose);
    void                              HomogenousOrientationToQuaternion                       (Quaternion<double>&    Quat,                   C_RelativePose         RelativePose);
    void                              HomogenousPoseToFrankaPose                              (CartesianPose&         FrankaPose,             C_AbsolutePose         AbsolutePose);
    void                              HomogenousPoseToFrankaPose                              (CartesianPose&         FrankaPose,             C_RelativePose         RelativePose);
    void                              QuaternionToHomogenousOrientation                       (Quaternion<double>     Quat,                   C_AbsolutePose&        AbsolutePose);
    void                              QuaternionToHomogenousOrientation                       (Quaternion<double>     Quat,                   C_RelativePose&        RelativePose);
    void                              QuaternionToFrankaOrientation                           (Quaternion<double>     Quat,                   CartesianPose&         FrankaPose);
    void                              FrankaPoseToHomogenousPose                              (CartesianPose          FrankaPose,             C_AbsolutePose&        AbsolutePose);
    void                              FrankaPoseToHomogenousPose                              (CartesianPose          FrankaPose,             C_RelativePose&        RelativePose);
    void                              FrankaOrientationToQuaternion                           (CartesianPose          FrankaPose,             Quaternion<double>&    Quat);
    void                              Get_RotationAngle                                       (Quaternion<double>     Quat,                   double&                Rotationswinkel);
    void                              Get_UnitRotationAxis                                    (Quaternion<double>     Quat,                   double                 (&Rotationsachse)[3]);
    void                              Get_UnitTranslationVektor                               (C_AbsolutePose         StartPose,              C_AbsolutePose         TargetPose,                double    (&Richtungsvektor)[3]);
    void                              Get_TranslationDistance                                 (C_AbsolutePose         StartPose,              C_AbsolutePose         TargetPose,                double&   Distance);
    void                              Get_Inverse_Franka_Pose                                 (CartesianPose          Input_Pose,             CartesianPose&         Output_Pose);
    S_Positionsvektor                 Calc_Vector_Produkt                                     (S_Positionsvektor      Erster_Vektor,          S_Positionsvektor      Zweiter_Vektor);
    double                            Calc_Vector_Betrag                                      (S_Positionsvektor      Vektor);

    /******************************************************* ffentliche Anwender-Methoden ******************************************************/
    public:
    void                              Panda_Processor_MoveToPose_Slow                         (void);
    void                              Panda_Processor_Calibrate_Camera                        (void);                                                                                                                                                               // Funktion, welche im Thread ausgefhrt werden kann
    void                              Panda_Processor_ObjectTracking                          (void);
    void                              Get_TCP_Frame                                           (double                 (&TCP_Frame)[4][4]);                                                                                                                          // Ldt den aktuellen TCP-Frame aus der Steuerung und schreibt diesen direkt in den bergebenen Parameter
    void                              Set_TCP_Frame                                           (double                 (&TCP_Frame)[4][4]);                                                                                                                          // Schreibt den TCP-Frame aus dem bergebenen Parameter direkt in die Steuerung
    void                              Get_EndEffector_Load                                    (double&                Mass,                   double                  (&Center_Of_Mass)[3],     double    (&Inertia_Tensor)[3][3]);                                 // Ldt die aktuellen End-Effektor-Massenwerte aus der Steuerung und schreibt diese direkt in die bergebenen Parameter
    void                              Set_EndEffector_DynamicLoad                             (double&                Mass,                   double                  (&Center_Of_Mass)[3],     double    (&Inertia_Tensor)[3][3]);                                 // Schreibt die End-Effektor-Massenwerte aus den bergebenen Parametern direkt in die Steuerung
    bool                              Is_MotionDone                                           (void);                                                                                                                                                               // Prft, ob die Bewegung des aktuellen Bewegungs-Thread komplett abgeschlossen ist
    void                              Set_Panda_Vel_Acc_max                                   (double                 Panda_Vel_max,          double                  Panda_Acc_max,            double    Panda_Omega_max,             double    Panda_Alpha_max);  // Setzen der maximalen Geschwindigkeit und Beschleunigung
    void                              Get_Current_TCP_Pose                                    (double                 (&TCP_Pose)[4][4]);
    void                              Get_Current_TCP_Pose                                    (C_AbsolutePose&        TCP_Pose);
    void                              Get_Current_TCP_Pose_Motion                             (C_AbsolutePose&        TCP_Pose);
    bool                              Create_Abs_Camera_Calibration_Poses                     (void);
    void                              Reset_Abs_Camera_Calibration_Poses                      (void);
    void                              Calculate_WorldToRobot_Pose                             (void);
    void                              Set_Parameter_ObjectTracking                            (S_Positionsvektor      Lichtstrahl_Einheitsvektor,     S_Positionsvektor       Positionsvektor,          E_ObjectTracking enum_ObjectTracking);
    void                              Set_Stop_ObjectTracking                                 (void);
    void                              Reset_Stop_ObjectTracking                               (void);
    void                              Get_WorldToTCP_Pose_ObjectTracking                      (C_AbsolutePose&        WorldToTCP_Pose);
    void                              Get_WorldToTCP_Pose_ObjectTracking                      (C_AbsolutePose         TCP_Pose,               C_AbsolutePose&         WorldToTCP_Pose);
    void                              Set_Target_Pose                                         (C_AbsolutePose&        targetPose);
    };
  }
#endif
