#include "headers/Roboter/robot.h"

using namespace robot;
using namespace franka;
using namespace Eigen;

C_robot::C_robot()
  {
  this->robot = nullptr;
  this->robotstate = new franka::RobotState;
  }
C_robot::~C_robot()
  {
  delete (this->robotstate);
  if(this->robot != nullptr)
    {
    delete (this->robot);
    }
  else
    {
    this->robot = nullptr;
    }
  }

C_AbsolutePose *C_robot::getRobotToWorld() const
  {
  return RobotToWorld;
  }

franka::RobotState *C_robot::getRobotstate() const
  {
  *this->robotstate = this->robot->readOnce();
  return robotstate;
  }

bool C_robot::createRobot(std::string ipAdress)
  {
  this->robot = new franka::Robot(ipAdress, franka::RealtimeConfig::kIgnore);
  return true;
  }
bool C_robot::startRobot()
  {

  }
bool C_robot::stopRobot()
  {

  }
bool C_robot::abortRobot()
  {

  }
void C_robot::setTCP(double (&tcp)[4][4])
  {
  std::array<double, 16> New_TCP_Frame;
  int k = 0;

  for(int i = 0; i < 4; i++)
    for(int j = 0; j < 4; j++)
      {
      New_TCP_Frame[k] = tcp[j][i];
      k++;
      }
  // Orientierungsanteil vorher (zur Sicherheit) normieren. Wenn die Orientierungsvektoren leicht vom Betrag 1 abweichen
  // werden diese nicht von der Robotersteuerung angenommen!
  double abs_n = sqrt(New_TCP_Frame[0] * New_TCP_Frame[0] + New_TCP_Frame[1] * New_TCP_Frame[1] + New_TCP_Frame[2]  * New_TCP_Frame[2]);
  double abs_o = sqrt(New_TCP_Frame[4] * New_TCP_Frame[4] + New_TCP_Frame[5] * New_TCP_Frame[5] + New_TCP_Frame[6]  * New_TCP_Frame[6]);
  double abs_a = sqrt(New_TCP_Frame[8] * New_TCP_Frame[8] + New_TCP_Frame[9] * New_TCP_Frame[9] + New_TCP_Frame[10] * New_TCP_Frame[10]);
  New_TCP_Frame[0]  /= abs_n;
  New_TCP_Frame[1]  /= abs_n;
  New_TCP_Frame[2]  /= abs_n;
  New_TCP_Frame[4]  /= abs_o;
  New_TCP_Frame[5]  /= abs_o;
  New_TCP_Frame[6]  /= abs_o;
  New_TCP_Frame[8]  /= abs_a;
  New_TCP_Frame[9]  /= abs_a;
  New_TCP_Frame[10] /= abs_a;

  this->robot->setEE(New_TCP_Frame);
  }

/*************************************************** Nicht ffentliche private Methoden *****************************************************/
franka::CartesianPose       C_robot::CartesianPose_Callback_Function_abs_Weg_Trapez               (double&                time,              const RobotState&    Robot_State,            Duration&           Duration)
  {
  *this->robotstate = Robot_State;

  time += Duration.toSec();

  // Startpose bei t = 0.0 initialisieren
  if (time == 0.0)
    {
    this->Sollweg_Translation = 0.0;
    this->Sollwinkel_Rotation = 0.0;

    *this->Abs_Callback_Start_Pose = Robot_State.O_T_EE;
    this->FrankaOrientationToQuaternion(*this->Abs_Callback_Start_Pose, this->Quat_Callback_Start_Orientation);

    return (*this->Abs_Callback_Start_Pose);
    }

  // Sollweg und Sollwinkel berechnen
  bool Translation = this->Sollweg_Vorgabe->SM_Sollweg_Vorgabe_Translation_abs_Weg_Trapez (this->Sollweg_Translation, time);
  bool Rotation    = this->Sollweg_Vorgabe->SM_Sollweg_Vorgabe_Rotation_abs_Weg_Trapez    (this->Sollwinkel_Rotation, time);

  // Sollpose initialisieren mit Startpose
  CartesianPose abs_Soll_Pose (*this->Abs_Callback_Start_Pose);

  // Sollposition der Sollpose berechnen
  abs_Soll_Pose.O_T_EE[12] = this->Abs_Callback_Start_Pose->O_T_EE[12] + this->Sollweg_Translation * this->Richtungsvektor[0]; // Soll_x
  abs_Soll_Pose.O_T_EE[13] = this->Abs_Callback_Start_Pose->O_T_EE[13] + this->Sollweg_Translation * this->Richtungsvektor[1]; // Soll_y
  abs_Soll_Pose.O_T_EE[14] = this->Abs_Callback_Start_Pose->O_T_EE[14] + this->Sollweg_Translation * this->Richtungsvektor[2]; // Soll_z

  // Sollorientierung der Sollpose berechnen
  Quaternion<double> rel_Soll_Quaternion;
  Quaternion<double> abs_Soll_Quaternion;
  rel_Soll_Quaternion.w() = cos(this->Sollwinkel_Rotation / 2.0);
  rel_Soll_Quaternion.x() = sin(this->Sollwinkel_Rotation / 2.0) * this->Rotationsachse[0];
  rel_Soll_Quaternion.y() = sin(this->Sollwinkel_Rotation / 2.0) * this->Rotationsachse[1];
  rel_Soll_Quaternion.z() = sin(this->Sollwinkel_Rotation / 2.0) * this->Rotationsachse[2];
  abs_Soll_Quaternion     = this->Quat_Callback_Start_Orientation * rel_Soll_Quaternion;
  this->QuaternionToFrankaOrientation(abs_Soll_Quaternion, abs_Soll_Pose);

  // Ausstiegsbedingung festlegen
  bool Ok = this->Pose_Reached(Robot_State.O_T_EE_d, this->Abs_TargetPose, 0.001, 0.01);
  if (!Translation || !Rotation || !Ok)
    {
    return (abs_Soll_Pose);
    }
  else
    {
    return (MotionFinished(abs_Soll_Pose));
    }
  }
franka::CartesianVelocities C_robot::CartesianPose_Callback_Function_abs_Vel_Trapez               (double&                time,              const RobotState&    Robot_State,            Duration&           Duration)
  {
  *this->Panda_RobotState = Robot_State;

  // Startpose und Startquaternion bei t = 0.0 initialisieren
  if (time == 0.0)
    {
    this->PID_Regler_X_CamCalib->Reset_PID_Regler  ();
    this->PID_Regler_Y_CamCalib->Reset_PID_Regler  ();
    this->PID_Regler_Z_CamCalib->Reset_PID_Regler  ();
    this->PID_Regler_RX_CamCalib->Reset_PID_Regler ();
    this->PID_Regler_RY_CamCalib->Reset_PID_Regler ();
    this->PID_Regler_RZ_CamCalib->Reset_PID_Regler ();

    this->Sollvel_Translation = 0.0;
    this->Sollomega_Rotation  = 0.0;
    this->Sollweg_Translation = 0.0;
    this->Sollwinkel_Rotation = 0.0;

    *this->Abs_Callback_Start_Pose = Robot_State.O_T_EE;
    this->FrankaOrientationToQuaternion(*this->Abs_Callback_Start_Pose, this->Quat_Callback_Start_Orientation);

    time += 0.001;
    return (Robot_State.O_dP_EE_c);
    }

  // Sollgeschwindigkeit und Sollwinkelgeschwindigkeit aus Sollwertvorgabe für Berechnung der Vorsteuerwerte bestimmen
  bool Translation = this->Sollweg_Vorgabe->SM_Sollweg_Vorgabe_Translation_abs_Vel_Trapez (this->Sollvel_Translation, this->Sollweg_Translation, time);
  bool Rotation    = this->Sollweg_Vorgabe->SM_Sollweg_Vorgabe_Rotation_abs_Vel_Trapez    (this->Sollomega_Rotation,  this->Sollwinkel_Rotation, time);

  // Soll- und Istposition bestimmen
  CartesianPose   Ist_Pose (Robot_State.O_T_EE);
  double Ist_x  = Ist_Pose.O_T_EE[12];
  double Ist_y  = Ist_Pose.O_T_EE[13];
  double Ist_z  = Ist_Pose.O_T_EE[14];
  double Soll_x = this->Abs_Callback_Start_Pose->O_T_EE[12] + this->Sollweg_Translation * this->Richtungsvektor[0];
  double Soll_y = this->Abs_Callback_Start_Pose->O_T_EE[13] + this->Sollweg_Translation * this->Richtungsvektor[1];
  double Soll_z = this->Abs_Callback_Start_Pose->O_T_EE[14] + this->Sollweg_Translation * this->Richtungsvektor[2];

  // Soll- und Istrotation bestimmen
  Quaternion<double> Ist_Orientierung;
  Quaternion<double> Trans_Orientierung;
  this->FrankaOrientationToQuaternion(Ist_Pose, Ist_Orientierung);
  double Istwinkel   = 0.0;
  Trans_Orientierung = this->Quat_Callback_Start_Orientation.inverse() * Ist_Orientierung;
  this->Get_RotationAngle(Trans_Orientierung, Istwinkel);
  double Ist_phi_x  = Istwinkel * this->Rotationsachse_K0[0];
  double Ist_phi_y  = Istwinkel * this->Rotationsachse_K0[1];
  double Ist_phi_z  = Istwinkel * this->Rotationsachse_K0[2];
  double Soll_phi_x = this->Sollwinkel_Rotation * this->Rotationsachse_K0[0];
  double Soll_phi_y = this->Sollwinkel_Rotation * this->Rotationsachse_K0[1];
  double Soll_phi_z = this->Sollwinkel_Rotation * this->Rotationsachse_K0[2];

  // Translatorische Geschwindigkeiten bestimmen (Vorsteuerwert)
//  double vx = this->Sollvel_Translation * this->Richtungsvektor[0];
//  double vy = this->Sollvel_Translation * this->Richtungsvektor[1];
//  double vz = this->Sollvel_Translation * this->Richtungsvektor[2];

  // Rotatorische Geschwindigkeit bestimmen (Vorsteuerwert)
//  double wx = this->Sollomega_Rotation * this->Rotationsachse_K0[0];
//  double wy = this->Sollomega_Rotation * this->Rotationsachse_K0[1];
//  double wz = this->Sollomega_Rotation * this->Rotationsachse_K0[2];

  // Stellwerte ermitteln
  double Ist_Werte[6]       = {Ist_x,     Ist_y,      Ist_z,           Ist_phi_x,     Ist_phi_y,  Ist_phi_z};
  double Soll_Werte[6]      = {Soll_x,    Soll_y,     Soll_z,          Soll_phi_x,    Soll_phi_y, Soll_phi_z};
  double Vorsteuer_Werte[6] = {0.0,       0.0,        0.0,             0.0,           0.0,        0.0};
  double Stell_Werte[6]     = {0.0,       0.0,        0.0,             0.0,           0.0,        0.0};
  this->PID_Regler_X_CamCalib->PID_Regler    (Ist_Werte[0], Soll_Werte[0], Vorsteuer_Werte[0], Stell_Werte[0]);
  this->PID_Regler_Y_CamCalib->PID_Regler    (Ist_Werte[1], Soll_Werte[1], Vorsteuer_Werte[1], Stell_Werte[1]);
  this->PID_Regler_Z_CamCalib->PID_Regler    (Ist_Werte[2], Soll_Werte[2], Vorsteuer_Werte[2], Stell_Werte[2]);
  this->PID_Regler_RX_CamCalib->PID_Regler   (Ist_Werte[3], Soll_Werte[3], Vorsteuer_Werte[3], Stell_Werte[3]);
  this->PID_Regler_RY_CamCalib->PID_Regler   (Ist_Werte[4], Soll_Werte[4], Vorsteuer_Werte[4], Stell_Werte[4]);
  this->PID_Regler_RZ_CamCalib->PID_Regler   (Ist_Werte[5], Soll_Werte[5], Vorsteuer_Werte[5], Stell_Werte[5]);

  // Ausgabegeschwindigkeit festlegen
  CartesianVelocities Vel_Output = {{Stell_Werte[0], Stell_Werte[1], Stell_Werte[2], Stell_Werte[3], Stell_Werte[4], Stell_Werte[5]}};

  // Ausstiegsbedingung festlegen
  double Epsilon_T_vel   = 0.001;
  double Epsilon_R_Vel   = 0.001;
  double Epsilon_T_pos   = 0.001;
  double Epsilon_R_pos   = 0.01;
  double vx_d            = Robot_State.O_dP_EE_d[0];
  double vy_d            = Robot_State.O_dP_EE_d[1];
  double vz_d            = Robot_State.O_dP_EE_d[2];
  double wx_d            = Robot_State.O_dP_EE_d[3];
  double wy_d            = Robot_State.O_dP_EE_d[4];
  double wz_d            = Robot_State.O_dP_EE_d[5];
  bool   Ok_vel          = (abs(vx_d) <= Epsilon_T_vel) && (abs(vy_d) <= Epsilon_T_vel) && (abs(vz_d) <= Epsilon_T_vel) &&
                           (abs(wx_d) <= Epsilon_R_Vel) && (abs(wy_d) <= Epsilon_R_Vel) && (abs(wz_d) <= Epsilon_R_Vel);
  bool   Ok_Pose         = this->Pose_Reached(Robot_State.O_T_EE, this->Abs_TargetPose, Epsilon_T_pos, Epsilon_R_pos);

  if (!Translation || !Rotation || !Ok_vel || !Ok_Pose)
    {
    time += 0.001;

    return (Vel_Output);
    }
  else
    {
    return (MotionFinished(Vel_Output));
    }
  }
franka::CartesianVelocities C_robot::CartesianVel_Callback_Function_ObjectTracking                (double&                time,              const RobotState&    Robot_State,            Duration&           Duration)
  {
  *this->Panda_RobotState = Robot_State;
  time += Duration.toSec();

  // Startpose, Startquaternion und Abstand zwischen TCP / Kamera und Regel-KS  bei t = 0.0 initialisieren.
  if (time == 0.0)
    {
    this->PID_Regler_X_OT->Reset_PID_Regler  ();
    this->PID_Regler_Y_OT->Reset_PID_Regler  ();
    this->PID_Regler_Z_OT->Reset_PID_Regler  ();
    this->PID_Regler_X_OT->Reset_PID_Regler  ();
    this->PID_Regler_Y_OT->Reset_PID_Regler  ();
    this->PID_Regler_Z_OT->Reset_PID_Regler  ();

    CartesianVelocities TCP_Velocity = {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}};

    return (TCP_Velocity);
    }

  /****************************************************************************************/
  /* Vorinitialisierung des TCP-Geschwindigkeitsvektors und der Stellwerte                */
  /****************************************************************************************/
  CartesianVelocities TCP_Velocity = {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}};
  double Stellwert_Pos_VX          = 0.0;
  double Stellwert_Pos_VY          = 0.0;
  double Stellwert_Pos_VZ          = 0.0;
  double Stellwert_Orient_VRX      = 0.0;
  double Stellwert_Orient_VRY      = 0.0;
  double Stellwert_Orient_VRZ      = 0.0;

  /****************************************************************************************/
  /* Bewegung des Roboters Anhand von Fallunterscheidung festlegen:                       */
  /* Fall 1 - E_ObjectTracking::Object_Not_Found: Die Kamera des Roboters hat das Objekt  */
  /*                                              nicht erfasst. Der Roboter richtet sich */
  /*                                              nach der ihm letzten bekannten Objekt-  */
  /*                                              position aus.                           */
  /* Fall 2 - E_ObjectTracking::Mono_Object:    : Nur die Kamera des eigenen Roboters hat */
  /*                                              das Objekt erkannt. Der Roboter ver-    */
  /*                                              folgt das Objekt nur in xy-Ebene und    */
  /*                                              kennt keine Tiefeninformation des Ob-   */
  /*                                              jektes. Der Abstand zwischen Regel-KS   */
  /*                                              und TCP / Kamera bleibt identisch.      */
  /* Fall 3 - E_ObjectTracking::Stereo_Object:  : Beide Roboter-Kameras haben das Objekt  */
  /*                                              erfasst. Tiefeninformationen liegen vor */
  /*                                              und beide Roboter können dem Objekt in  */
  /*                                              xyz-Ebene folgen.                       */
  /****************************************************************************************/

  // Vorinitialisierung
  S_Positionsvektor ControlFrameToObject_Pos;
  bool              Error                     = false;

  // Bestimmung der Ist-Pose und des Ist-Quaternion bezogen auf das Roboter-KS
  CartesianPose Ist_Pose (Robot_State.O_T_EE);
  Quaternion<double> Ist_Orientierung;
  this->FrankaOrientationToQuaternion(Ist_Pose, Ist_Orientierung);

  if (this->enum_ObjectTracking == E_ObjectTracking::Mono_Object)
    {
    // Transformation des Lichtstrahlvektors im Kamera-KS auf das Regel-KS [Px]
    S_Positionsvektor CamToObject_Pos_CF;
    CamToObject_Pos_CF.X = Ist_Pose.O_T_EE[0]  * this->Lichtstrahl_Einheitsvektor.X +
                           Ist_Pose.O_T_EE[4]  * this->Lichtstrahl_Einheitsvektor.Y +
                           Ist_Pose.O_T_EE[8]  * this->Lichtstrahl_Einheitsvektor.Z;
    CamToObject_Pos_CF.Y = Ist_Pose.O_T_EE[1]  * this->Lichtstrahl_Einheitsvektor.X +
                           Ist_Pose.O_T_EE[5]  * this->Lichtstrahl_Einheitsvektor.Y +
                           Ist_Pose.O_T_EE[9]  * this->Lichtstrahl_Einheitsvektor.Z;
    CamToObject_Pos_CF.Z = Ist_Pose.O_T_EE[2]  * this->Lichtstrahl_Einheitsvektor.X +
                           Ist_Pose.O_T_EE[6]  * this->Lichtstrahl_Einheitsvektor.Y +
                           Ist_Pose.O_T_EE[10] * this->Lichtstrahl_Einheitsvektor.Z;

    // Berechne der geschätzten Ballposition
    double CamToObject_Pos_Abs = this->ControlFrameToObject_Pos_Abs - this->ControlFrameToTCP_Pos_Abs;
    ControlFrameToObject_Pos.X = this->ControlFrameToTCP_Pos.X + CamToObject_Pos_CF.X * CamToObject_Pos_Abs;
    ControlFrameToObject_Pos.Y = this->ControlFrameToTCP_Pos.Y + CamToObject_Pos_CF.Y * CamToObject_Pos_Abs;
    ControlFrameToObject_Pos.Z = this->ControlFrameToTCP_Pos.Z + CamToObject_Pos_CF.Z * CamToObject_Pos_Abs;
    }
  else if ((this->enum_ObjectTracking == E_ObjectTracking::Object_Not_Found) || (this->enum_ObjectTracking == E_ObjectTracking::Stereo_Object))
    {
    /****************************************************************************************/
    /* Bestimmung der Soll-Pose des TCP / Kamera bezogen auf das Roboter-KS                 */
    /* Das Welt-KS, Roboter-Basis-KS und Regel-KS (Kugel-KS) haben identische Orientierung! */
    /****************************************************************************************/
    // Objektposition bezogen auf das Roboter-KS bestimmen
    S_Positionsvektor RobotToObject_Vector;
    RobotToObject_Vector.X = this->WorldToObject_Pos.X - this->Abs_WorldToRobot_Pose.px();
    RobotToObject_Vector.Y = this->WorldToObject_Pos.Y - this->Abs_WorldToRobot_Pose.py();
    RobotToObject_Vector.Z = this->WorldToObject_Pos.Z - this->Abs_WorldToRobot_Pose.pz();

    // Objektposition bezogen auf das Regel-KS bestimmen
    ControlFrameToObject_Pos.X = RobotToObject_Vector.X - this->RobotToControlFrame_Pos.X;
    ControlFrameToObject_Pos.Y = RobotToObject_Vector.Y - this->RobotToControlFrame_Pos.Y;
    ControlFrameToObject_Pos.Z = RobotToObject_Vector.Z - this->RobotToControlFrame_Pos.Z;
    }
  else
    {
    // Hier werden im Fehlerfall Dummywerte gesetzt, um Abstürze bei weiterer Berechnung (Division durch 0) zu vermeiden.
    // Die Error-Abfrage erfolgt nochmals bei setzten der kartesischen Geschwindigkeiten am Ende der Funktion.
    Error                    = true;
    ControlFrameToObject_Pos = {1.0, 1.0, 1.0};
    }

  // Bestimmung des Annäherungsvektors des TCP / Kamera bezogen auf das Regel-KS
  this->ControlFrameToObject_Pos_Abs  = sqrt(ControlFrameToObject_Pos.X * ControlFrameToObject_Pos.X +
                                             ControlFrameToObject_Pos.Y * ControlFrameToObject_Pos.Y +
                                             ControlFrameToObject_Pos.Z * ControlFrameToObject_Pos.Z);
  S_Positionsvektor Vector_a;
  Vector_a.X                          = ControlFrameToObject_Pos.X / this->ControlFrameToObject_Pos_Abs;
  Vector_a.Y                          = ControlFrameToObject_Pos.Y / this->ControlFrameToObject_Pos_Abs;
  Vector_a.Z                          = ControlFrameToObject_Pos.Z / this->ControlFrameToObject_Pos_Abs;

  // Bestimmung des Normalenvektor des TCP / Kamera bezogen auf das Regel-KS (Vektor n immer parallel zur xy-Ebene des Regel-Basis-KS)
  double            Vector_n_Abs;        // (Betrag des Vektor-Kreuzproduktes |a x e|)
  S_Positionsvektor Vector_ez;           // Pseudovektor (nur z-Richtung)
  S_Positionsvektor Vector_n;            // n = (a x ez) / (|a x ez|)
  Vector_ez.X  = 0.0;
  Vector_ez.Y  = 0.0;
  Vector_ez.Z  = 1.0;
  Vector_n     = this->Calc_Vector_Produkt(Vector_a, Vector_ez);
  Vector_n_Abs = this->Calc_Vector_Betrag(Vector_n);
  Vector_n.X  /= Vector_n_Abs;
  Vector_n.Y  /= Vector_n_Abs;
  Vector_n.Z  /= Vector_n_Abs;

  // Bestimmung des Orientierungsvektors des TCP / Kamera bezogen auf das Regel-KS
  S_Positionsvektor Vector_o; // o = a x n
  double            Vector_o_Abs;
  Vector_o     = this->Calc_Vector_Produkt(Vector_a, Vector_n);
  Vector_o_Abs = this->Calc_Vector_Betrag(Vector_o);
  Vector_o.X  /= Vector_o_Abs;
  Vector_o.Y  /= Vector_o_Abs;
  Vector_o.Z  /= Vector_o_Abs;

  // Bestimmung der TCP- / Kameraposition bezogen auf das Regel-KS
  double Positionsfaktor  = 1.0 / 2.0; // Beliebiger Wert
  this->ControlFrameToTCP_Pos.X = ControlFrameToObject_Pos.X * Positionsfaktor;
  this->ControlFrameToTCP_Pos.Y = ControlFrameToObject_Pos.Y * Positionsfaktor;
  this->ControlFrameToTCP_Pos.Z = ControlFrameToObject_Pos.Z * Positionsfaktor;

  // Einschränkung der TCP- / Kameraposition bezogen auf das Regel-KS durch festgelegte Grenze /
  // Kugel um das Regel-KS herum. Die TCP- / Kameraposition soll sich immer innerhalb
  // des Kugelschale befinden.
  double Innenradius               = 0.1;
  double Aussenradius              = 0.75;
  this->ControlFrameToTCP_Pos_Abs  = sqrt(this->ControlFrameToTCP_Pos.X * this->ControlFrameToTCP_Pos.X +
                                          this->ControlFrameToTCP_Pos.Y * this->ControlFrameToTCP_Pos.Y +
                                          this->ControlFrameToTCP_Pos.Z * this->ControlFrameToTCP_Pos.Z);
  if (this->ControlFrameToTCP_Pos_Abs < Innenradius)
    {
    this->ControlFrameToTCP_Pos.X *= Innenradius  / this->ControlFrameToTCP_Pos_Abs;
    this->ControlFrameToTCP_Pos.Y *= Innenradius  / this->ControlFrameToTCP_Pos_Abs;
    this->ControlFrameToTCP_Pos.Z *= Innenradius  / this->ControlFrameToTCP_Pos_Abs;
    }
  else if (this->ControlFrameToTCP_Pos_Abs > Aussenradius)
    {
    this->ControlFrameToTCP_Pos.X *= Aussenradius / this->ControlFrameToTCP_Pos_Abs;
    this->ControlFrameToTCP_Pos.Y *= Aussenradius / this->ControlFrameToTCP_Pos_Abs;
    this->ControlFrameToTCP_Pos.Z *= Aussenradius / this->ControlFrameToTCP_Pos_Abs;
    }

  // Bestimmung der TCP- / Kameraposition bezogen auf das Roboter-KS
  S_Positionsvektor RobotToTCP_Pos;
  RobotToTCP_Pos.X = this->RobotToControlFrame_Pos.X + ControlFrameToTCP_Pos.X;
  RobotToTCP_Pos.Y = this->RobotToControlFrame_Pos.Y + ControlFrameToTCP_Pos.Y;
  RobotToTCP_Pos.Z = this->RobotToControlFrame_Pos.Z + ControlFrameToTCP_Pos.Z;

  // Bestimmung der Sollpose und Sollorientierung
  CartesianPose      Soll_Pose = {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0}};
  Quaternion<double> Soll_Orientierung;
  Soll_Pose.O_T_EE[0]  = Vector_n.X;
  Soll_Pose.O_T_EE[1]  = Vector_n.Y;
  Soll_Pose.O_T_EE[2]  = Vector_n.Z;
  Soll_Pose.O_T_EE[4]  = Vector_o.X;
  Soll_Pose.O_T_EE[5]  = Vector_o.Y;
  Soll_Pose.O_T_EE[6]  = Vector_o.Z;
  Soll_Pose.O_T_EE[8]  = Vector_a.X;
  Soll_Pose.O_T_EE[9]  = Vector_a.Y;
  Soll_Pose.O_T_EE[10] = Vector_a.Z;
  Soll_Pose.O_T_EE[12] = RobotToTCP_Pos.X;
  Soll_Pose.O_T_EE[13] = RobotToTCP_Pos.Y;
  Soll_Pose.O_T_EE[14] = RobotToTCP_Pos.Z;
  this->FrankaOrientationToQuaternion(Soll_Pose, Soll_Orientierung);

  /****************************************************************************************/
  /* Bestimmung der Parameter für translatorische Positionsregelung                       */
  /****************************************************************************************/
  double Ist_X                    = Ist_Pose.O_T_EE   [12];
  double Ist_Y                    = Ist_Pose.O_T_EE   [13];
  double Ist_Z                    = Ist_Pose.O_T_EE   [14];
  double Soll_X                   = Soll_Pose.O_T_EE  [12];
  double Soll_Y                   = Soll_Pose.O_T_EE  [13];
  double Soll_Z                   = Soll_Pose.O_T_EE  [14];
  double Regelabweichung_Pos_X    = Soll_X - Ist_X; // Regelabweichung durch Differentbildung von Positionen
  double Regelabweichung_Pos_Y    = Soll_Y - Ist_Y; // Regelabweichung durch Differentbildung von Positionen
  double Regelabweichung_Pos_Z    = Soll_Z - Ist_Z; // Regelabweichung durch Differentbildung von Positionen

  /****************************************************************************************/
  /* Bestimmung der Parameter für rotatorische Orientierungsregelung                      */
  /****************************************************************************************/
  double             Delta_Winkel;
  Quaternion<double> Delta_Orientierung;
  double             Rotation_Axis_TCPFrame   [3];
  double             Rotation_Axis_RobotFrame [3];
  Delta_Orientierung               = Ist_Orientierung.inverse() * Soll_Orientierung;
  this->Get_RotationAngle            (Delta_Orientierung, Delta_Winkel);
  this->Get_UnitRotationAxis         (Delta_Orientierung, Rotation_Axis_TCPFrame);
  Rotation_Axis_RobotFrame[0]      = Ist_Pose.O_T_EE[0]  * Rotation_Axis_TCPFrame[0] +
                                     Ist_Pose.O_T_EE[4]  * Rotation_Axis_TCPFrame[1] +
                                     Ist_Pose.O_T_EE[8]  * Rotation_Axis_TCPFrame[2];
  Rotation_Axis_RobotFrame[1]      = Ist_Pose.O_T_EE[1]  * Rotation_Axis_TCPFrame[0] +
                                     Ist_Pose.O_T_EE[5]  * Rotation_Axis_TCPFrame[1] +
                                     Ist_Pose.O_T_EE[9]  * Rotation_Axis_TCPFrame[2];
  Rotation_Axis_RobotFrame[2]      = Ist_Pose.O_T_EE[2]  * Rotation_Axis_TCPFrame[0] +
                                     Ist_Pose.O_T_EE[6]  * Rotation_Axis_TCPFrame[1] +
                                     Ist_Pose.O_T_EE[10] * Rotation_Axis_TCPFrame[2];

  double Regelabweichung_Orient_RX = Rotation_Axis_RobotFrame[0] * Delta_Winkel; // Regelabweichung durch Division von Orientierungs-Quaternionen
  double Regelabweichung_Orient_RY = Rotation_Axis_RobotFrame[1] * Delta_Winkel; // Regelabweichung durch Division von Orientierungs-Quaternionen
  double Regelabweichung_Orient_RZ = Rotation_Axis_RobotFrame[2] * Delta_Winkel; // Regelabweichung durch Division von Orientierungs-Quaternionen

  /****************************************************************************************/
  /* Bestimmung der Stellwerte der Positonsregelung                                       */
  /****************************************************************************************/
  this->PID_Regler_X_OT->PID_Regler    (Regelabweichung_Pos_X,     Stellwert_Pos_VX);
  this->PID_Regler_Y_OT->PID_Regler    (Regelabweichung_Pos_Y,     Stellwert_Pos_VY);
  this->PID_Regler_Z_OT->PID_Regler    (Regelabweichung_Pos_Z,     Stellwert_Pos_VZ);
  this->PID_Regler_RX_OT->PID_Regler   (Regelabweichung_Orient_RX, Stellwert_Orient_VRX);
  this->PID_Regler_RY_OT->PID_Regler   (Regelabweichung_Orient_RY, Stellwert_Orient_VRY);
  this->PID_Regler_RZ_OT->PID_Regler   (Regelabweichung_Orient_RZ, Stellwert_Orient_VRZ);


  /****************************************************************************************/
  /* Bestimmung des Geschwindigkeitsvektors und Festlegung von maximalen Geschwindig-     */
  /* keitswerten bzw. Stellwerten. Die maximalen resultierenden Geschwindigkeitswerte     */
  /* sind laut offizieller Doku für kartesische Bewegung:                                 */
  /* Translation = 1.7   [m/s]                                                            */
  /* Rotation    = 2.5   [rad/s]                                                          */
  /* Ellbogen    = 2.175 [rad/s]                                                          */
  /* Für den Anwendungsfall werden die Maximalwerte wie folgt festgelegt:                 */
  /* Translation = 1.2   [m/s]                                                            */
  /* Rotation    = 2.0   [rad/s]                                                          */
  /* Ellbogen    = nicht berücksichtigt                                                   */
  /****************************************************************************************/
  double Stellwert_Pos_max    = 1.2;
  double Stellwert_Orient_max = 2.0;
  double Stellwert_Pos_Abs    = sqrt(Stellwert_Pos_VX     * Stellwert_Pos_VX     + Stellwert_Pos_VY     * Stellwert_Pos_VY     + Stellwert_Pos_VZ     * Stellwert_Pos_VZ);
  double Stellwert_Orient_Abs = sqrt(Stellwert_Orient_VRX * Stellwert_Orient_VRX + Stellwert_Orient_VRY * Stellwert_Orient_VRY + Stellwert_Orient_VRZ * Stellwert_Orient_VRZ);

  if (Stellwert_Pos_Abs > Stellwert_Pos_max)
    {
    Stellwert_Pos_VX     *= Stellwert_Pos_max    / Stellwert_Pos_Abs;
    Stellwert_Pos_VY     *= Stellwert_Pos_max    / Stellwert_Pos_Abs;
    Stellwert_Pos_VZ     *= Stellwert_Pos_max    / Stellwert_Pos_Abs;
    }
  if (Stellwert_Orient_Abs > Stellwert_Orient_max)
    {
    Stellwert_Orient_VRX *= Stellwert_Orient_max / Stellwert_Orient_Abs;
    Stellwert_Orient_VRY *= Stellwert_Orient_max / Stellwert_Orient_Abs;
    Stellwert_Orient_VRZ *= Stellwert_Orient_max / Stellwert_Orient_Abs;
    }

  if (!Error)
    {
    TCP_Velocity = {{Stellwert_Pos_VX, Stellwert_Pos_VY, Stellwert_Pos_VZ, Stellwert_Orient_VRX, Stellwert_Orient_VRY, Stellwert_Orient_VRZ}};
    }
  else
    {
    TCP_Velocity = {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0,}};
    }

  if (!this->Stop_ObjectTracking)
    {
    return (TCP_Velocity);
    }
  else
    {
    return (MotionFinished(TCP_Velocity));
    }
  }
franka::CartesianPose      C_robot::CartesianPose_Callback_Function_Inkrementell_Weg_Trapez      (double&                time,              const RobotState&    Robot_State,            Duration&           Duration)
  {
  *this->Panda_RobotState = Robot_State;

  time += Duration.toSec();

  // Startpose bei t = 0.0 initialisieren
  if (time == 0.0)
    {
    this->Sollweg_Translation = 0.0;
    this->Sollwinkel_Rotation = 0.0;

    *this->Abs_Callback_Start_Pose = Robot_State.O_T_EE;
    this->FrankaOrientationToQuaternion(*this->Abs_Callback_Start_Pose, this->Quat_Callback_Start_Orientation);

    return (*this->Abs_Callback_Start_Pose);
    }

  // Sollweg und Sollwinkel berechnen
  bool Translation = this->Sollweg_Vorgabe->SM_Sollweg_Vorgabe_Translation_Inkrementell_Weg_Trapez (this->Sollweg_Translation);
  bool Rotation    = this->Sollweg_Vorgabe->SM_Sollweg_Vorgabe_Rotation_Inkrementell_Weg_Trapez    (this->Sollwinkel_Rotation);

  // Sollpose initialisieren mit Startpose
  CartesianPose abs_Soll_Pose (*this->Abs_Callback_Start_Pose);

  // Sollposition der Sollpose berechnen
  abs_Soll_Pose.O_T_EE[12] = this->Abs_Callback_Start_Pose->O_T_EE[12] + this->Sollweg_Translation * this->Richtungsvektor[0]; // Soll_x
  abs_Soll_Pose.O_T_EE[13] = this->Abs_Callback_Start_Pose->O_T_EE[13] + this->Sollweg_Translation * this->Richtungsvektor[1]; // Soll_y
  abs_Soll_Pose.O_T_EE[14] = this->Abs_Callback_Start_Pose->O_T_EE[14] + this->Sollweg_Translation * this->Richtungsvektor[2]; // Soll_z

  // Sollorientierung der Sollpose berechnen
  Quaternion<double> rel_Soll_Quaternion;
  Quaternion<double> abs_Soll_Quaternion;
  rel_Soll_Quaternion.w() = cos(this->Sollwinkel_Rotation / 2.0);
  rel_Soll_Quaternion.x() = sin(this->Sollwinkel_Rotation / 2.0) * this->Rotationsachse[0];
  rel_Soll_Quaternion.y() = sin(this->Sollwinkel_Rotation / 2.0) * this->Rotationsachse[1];
  rel_Soll_Quaternion.z() = sin(this->Sollwinkel_Rotation / 2.0) * this->Rotationsachse[2];
  abs_Soll_Quaternion     = this->Quat_Callback_Start_Orientation * rel_Soll_Quaternion;
  this->QuaternionToFrankaOrientation(abs_Soll_Quaternion, abs_Soll_Pose);

  // Ausstiegsbedingung festlegen
  bool Ok = this->Pose_Reached(Robot_State.O_T_EE_d, this->Abs_TargetPose, 0.001, 0.01);
  if (!Translation || !Rotation || !Ok)
    {
    return (abs_Soll_Pose);
    }
  else
    {
    return (MotionFinished(abs_Soll_Pose));
    }
  }
franka::Torques            C_robot::Torque_Callback_Motion_Controller                            (double&                time,              const RobotState&    Robot_State,            Duration& Duration)
  {
  *this->Panda_RobotState = Robot_State;

  time += Duration.toSec();

  // Vorbereiten der benötigten Variablen
  if (time == 0.0)
    {
    this->dq_Filterposition = 0;
    this->dq_Filtergroesse  = 5;

    for (int i = 0; i < (this->dq_Filtergroesse * 7); i++)
      {
      this->dq_Buffer.push_back(0.0);
      }

    return (Robot_State.tau_J_d);
    }

  // Update des Filters
  for (int i = 0; i < 7; i++)
    {
    this->dq_Buffer[this->dq_Filterposition * 7 + i] = Robot_State.dq[i];
    }
  this->dq_Filterposition = (this->dq_Filterposition + 1) % this->dq_Filtergroesse;

  // Ausgabemoment berechnen
  array<double, 7> Torque;
  for (size_t i = 0; i < 7; i++)
    {
    double dq_Gefiltert = 0.0;

    // dq-Wert Filtern
    for (int j = i; j < (this->dq_Filtergroesse * 7); j += 7)
      {
      dq_Gefiltert += this->dq_Buffer[i];
      }
    dq_Gefiltert   /= (double)this->dq_Filtergroesse;

    // Moment bestimmen
//    Torque[i] = this->Kp * (Robot_State.q_d[i] - Robot_State.q[i]) + this->Kp * this->Tv * (Robot_State.dq_d[i] - dq_Gefiltert);
    double Taktzeit        = 0.001;
    double Kp              = 1.5;
    double Tn              = 125.0;
    double Regelabweichung = Robot_State.dq_d[i] - Robot_State.dq[i];
    double P_StellWert     = Kp * Regelabweichung;
    double I_Stellwert     = Kp * Taktzeit * Regelabweichung / Tn;
    Torque[i]              = P_StellWert + I_Stellwert;
    }

  return (Torque);
  }
franka::Torques             C_robot::CartesianImpedance_Callback_Function                         (double&                time,              const RobotState&    Robot_State,            Duration&           Duration)
  {
  *this->Panda_RobotState = Robot_State;

  time = Duration.toSec();

  if (time == 0.0)
    {
    // Zielpose bestimmen
    this->HomogenousPoseToFrankaPose         (*this->Abs_Callback_Target_Pose,        this->Abs_TargetPose);
    this->HomogenousOrientationToQuaternion  (this->Quat_Callback_Target_Orientation, this->Abs_TargetPose);
    }

  // Positionsvektor und Quaternion der Zielpose bestimmen
//  Affine3d                         Target_Transform    (Matrix4d::Map(this->Abs_Callback_Target_Pose->O_T_EE.data()));
  Vector3d                         Target_Position    (this->Abs_Callback_Target_Pose->O_T_EE[12],
                                                       this->Abs_Callback_Target_Pose->O_T_EE[13],
                                                       this->Abs_Callback_Target_Pose->O_T_EE[14]); //(Target_Transform.translation());
  Quaterniond                      Target_Orientation (this->Quat_Callback_Target_Orientation.w(),
                                                       this->Quat_Callback_Target_Orientation.x(),
                                                       this->Quat_Callback_Target_Orientation.y(),
                                                       this->Quat_Callback_Target_Orientation.z());  //(Target_Transform.linear());

  // Aktuelle Statuswerte abfragen und nach Eigen-Format konvertieren
  std::array<double, 7>  Arr_Coriolis = this->robotModel->coriolis(Robot_State);
  std::array<double, 42> Arr_Jacobian = this->robotModel->zeroJacobian(franka::Frame::kEndEffector, Robot_State);

  Map<const Matrix<double, 7, 1> > Coriolis            (Arr_Coriolis.data());
  Map<const Matrix<double, 6, 7> > Jacobian            (Arr_Jacobian.data());
//  Map<const Matrix<double, 7, 1> > q                   (Robot_State.q.data());
  Map<const Matrix<double, 7, 1> > dq                  (Robot_State.dq.data());
  Affine3d                         Transform           (Matrix4d::Map(Robot_State.O_T_EE.data()));
  Vector3d                         Position            (Transform.translation());
  Quaterniond                      Orientation         (Transform.linear());

  // Positionsfehler / -differenz berechnen
  Matrix<double, 6, 1> Error;
  Error.head(3) << Position - Target_Position;

  // Orientierunfsfehler / -different berechnen und in das Basiskoordinatensystem transformieren
  // Das Skalarprodukt zweier Einheitsvektoren ergibt den Cosinus der halben Winkeldifferenz zwischen beiden Orientierungen. Die Winkeldifferenz ist identisch mit dem Winkel,
  // welcher über q12 = q01^-1 * q02 aus q12 berechnet werden kann.
  // cos(phi/2) = q1 'dot' q2
  if (Target_Orientation.coeffs().dot(Orientation.coeffs()) < 0.0)
    {
    // Wenn cos(phi/2) = q1 'dot' q2 < 0 ist, dann tausche alle Vorzeichen des aktuellen Quaternions. Dadurch wird die Winkeldifferenz nicht größer als +-180° bzw. +-Pi.
    Orientation.coeffs() << -Orientation.coeffs();
    }
  // Berechne das Transformationsquaternion q12 = q01^-1 * q02
  Quaterniond Quat_Error (Orientation.inverse() * Target_Orientation);
  Error.tail(3) << Quat_Error.x(), Quat_Error.y(), Quat_Error.z();
  Error.tail(3) << -Transform.linear() * Error.tail(3);

  // Steifheit und Dämpfung festlegen
  const double    Steifheit_Translation   {150.0};
  const double    Steifheit_Rotation      {10.0};
  MatrixXd        Steifheit               (6, 6);
  MatrixXd        Daempfung               (6, 6);
  Steifheit.setZero          ();
  Daempfung.setZero          ();
  Steifheit.topLeftCorner    (3, 3)     << Steifheit_Translation       * MatrixXd::Identity(3, 3) * 1.0;
  Steifheit.bottomRightCorner(3, 3)     << Steifheit_Rotation          * MatrixXd::Identity(3, 3) * 1.0;
  Daempfung.topLeftCorner    (3, 3)     << sqrt(Steifheit_Translation) * MatrixXd::Identity(3, 3) * 2.0;
  Daempfung.bottomRightCorner(3, 3)     << sqrt(Steifheit_Rotation)    * MatrixXd::Identity(3, 3) * 2.0;

  // Berechne das Ausgabemoment
  VectorXd         Torque_Vec(7);
  array<double, 7> Torque_Out{};

  Torque_Vec << Jacobian.transpose() * (-Steifheit * Error - Daempfung * (Jacobian * dq)) + Coriolis;
  VectorXd::Map(&Torque_Out[0], 7) = Torque_Vec;

  // Ausstiegsbedingung festlegen
  double Epsilon_T = 0.01;
  double Epsilon_R = 0.1;
  bool   Ok        = (Error(0,0) <= Epsilon_T) && (Error(1,0) <= Epsilon_T) && (Error(2,0) <= Epsilon_T) &&
                     (Error(3,0) <= Epsilon_R) && (Error(4,0) <= Epsilon_R) && (Error(5,0) <= Epsilon_R);

  if (!Ok)
    {
    Torques Output (Torque_Out);
    return (Output);
    }
  else
    {
    Torques Output (Torque_Out);
    return (MotionFinished(Output));
    }
  }
bool                         C_robot::Pose_Reached                                                 (double                 Ist,               double               Soll,                   double              Epsilon)
  {
  bool ok = ((Soll - Ist) * (Soll - Ist)) <= (Epsilon * Epsilon);
  return (ok);
  }
bool                         C_robot::Pose_Reached                                                 (franka::CartesianPose          Ist_Pose,          CartesianPose        Soll_Pose,              double              Epsilon_T,                double     Epsilon_R)
  {
  bool nx = ((Soll_Pose.O_T_EE[0]  - Ist_Pose.O_T_EE[0])  * (Soll_Pose.O_T_EE[0]  - Ist_Pose.O_T_EE[0])  <= (Epsilon_R * Epsilon_R));
  bool ny = ((Soll_Pose.O_T_EE[1]  - Ist_Pose.O_T_EE[1])  * (Soll_Pose.O_T_EE[1]  - Ist_Pose.O_T_EE[1])  <= (Epsilon_R * Epsilon_R));
  bool nz = ((Soll_Pose.O_T_EE[2]  - Ist_Pose.O_T_EE[2])  * (Soll_Pose.O_T_EE[2]  - Ist_Pose.O_T_EE[2])  <= (Epsilon_R * Epsilon_R));
  bool ox = ((Soll_Pose.O_T_EE[4]  - Ist_Pose.O_T_EE[4])  * (Soll_Pose.O_T_EE[4]  - Ist_Pose.O_T_EE[4])  <= (Epsilon_R * Epsilon_R));
  bool oy = ((Soll_Pose.O_T_EE[5]  - Ist_Pose.O_T_EE[5])  * (Soll_Pose.O_T_EE[5]  - Ist_Pose.O_T_EE[5])  <= (Epsilon_R * Epsilon_R));
  bool oz = ((Soll_Pose.O_T_EE[6]  - Ist_Pose.O_T_EE[6])  * (Soll_Pose.O_T_EE[6]  - Ist_Pose.O_T_EE[6])  <= (Epsilon_R * Epsilon_R));
  bool ax = ((Soll_Pose.O_T_EE[8]  - Ist_Pose.O_T_EE[8])  * (Soll_Pose.O_T_EE[8]  - Ist_Pose.O_T_EE[8])  <= (Epsilon_R * Epsilon_R));
  bool ay = ((Soll_Pose.O_T_EE[9]  - Ist_Pose.O_T_EE[9])  * (Soll_Pose.O_T_EE[9]  - Ist_Pose.O_T_EE[9])  <= (Epsilon_R * Epsilon_R));
  bool az = ((Soll_Pose.O_T_EE[10] - Ist_Pose.O_T_EE[10]) * (Soll_Pose.O_T_EE[10] - Ist_Pose.O_T_EE[10]) <= (Epsilon_R * Epsilon_R));
  bool px = ((Soll_Pose.O_T_EE[12] - Ist_Pose.O_T_EE[12]) * (Soll_Pose.O_T_EE[12] - Ist_Pose.O_T_EE[12]) <= (Epsilon_T * Epsilon_T));
  bool py = ((Soll_Pose.O_T_EE[13] - Ist_Pose.O_T_EE[13]) * (Soll_Pose.O_T_EE[13] - Ist_Pose.O_T_EE[13]) <= (Epsilon_T * Epsilon_T));
  bool pz = ((Soll_Pose.O_T_EE[14] - Ist_Pose.O_T_EE[14]) * (Soll_Pose.O_T_EE[14] - Ist_Pose.O_T_EE[14]) <= (Epsilon_T * Epsilon_T));

  return (nx && ny && nz && ox && oy && oz && ax && ay && az && px && py && pz);
  }
bool                         C_robot::Pose_Reached                                                 (std::array<double, 16>      Ist_Pose,          C_AbsolutePose       Soll_Pose,              double              Epsilon_T,                double     Epsilon_R)
  {
  bool nx = ((Soll_Pose.nx() - Ist_Pose[0])  * (Soll_Pose.nx() - Ist_Pose[0])  <= (Epsilon_R * Epsilon_R));
  bool ny = ((Soll_Pose.ny() - Ist_Pose[1])  * (Soll_Pose.ny() - Ist_Pose[1])  <= (Epsilon_R * Epsilon_R));
  bool nz = ((Soll_Pose.nz() - Ist_Pose[2])  * (Soll_Pose.nz() - Ist_Pose[2])  <= (Epsilon_R * Epsilon_R));
  bool ox = ((Soll_Pose.ox() - Ist_Pose[4])  * (Soll_Pose.ox() - Ist_Pose[4])  <= (Epsilon_R * Epsilon_R));
  bool oy = ((Soll_Pose.oy() - Ist_Pose[5])  * (Soll_Pose.oy() - Ist_Pose[5])  <= (Epsilon_R * Epsilon_R));
  bool oz = ((Soll_Pose.oz() - Ist_Pose[6])  * (Soll_Pose.oz() - Ist_Pose[6])  <= (Epsilon_R * Epsilon_R));
  bool ax = ((Soll_Pose.ax() - Ist_Pose[8])  * (Soll_Pose.ax() - Ist_Pose[8])  <= (Epsilon_R * Epsilon_R));
  bool ay = ((Soll_Pose.ay() - Ist_Pose[9])  * (Soll_Pose.ay() - Ist_Pose[9])  <= (Epsilon_R * Epsilon_R));
  bool az = ((Soll_Pose.az() - Ist_Pose[10]) * (Soll_Pose.az() - Ist_Pose[10]) <= (Epsilon_R * Epsilon_R));
  bool px = ((Soll_Pose.px() - Ist_Pose[12]) * (Soll_Pose.px() - Ist_Pose[12]) <= (Epsilon_T * Epsilon_T));
  bool py = ((Soll_Pose.py() - Ist_Pose[13]) * (Soll_Pose.py() - Ist_Pose[13]) <= (Epsilon_T * Epsilon_T));
  bool pz = ((Soll_Pose.pz() - Ist_Pose[14]) * (Soll_Pose.pz() - Ist_Pose[14]) <= (Epsilon_T * Epsilon_T));

  return (nx && ny && nz && ox && oy && oz && ax && ay && az && px && py && pz);
  }
void                         C_robot::HomogenousOrientationToQuaternion                            (Quaternion<double>&    Quat,              C_AbsolutePose       AbsolutePose)
  {
  // Spur der Rotationsmatrix bestimmen
  double Spur_R = AbsolutePose.nx() + AbsolutePose.oy() + AbsolutePose.az();

  // Berechnen der Quaternionselemente in Abhängigkeit der Spur der Rotationsmatrix
  double q0     = 0.0;
  double q1     = 0.0;
  double q2     = 0.0;
  double q3     = 0.0;
  double S      = 0.0;

  if (Spur_R > 0.0)
    {
    S  = sqrt(Spur_R + 1.0) * 2.0;
    q0 = S / 4.0;
    q1 = (AbsolutePose.oz() - AbsolutePose.ay()) / S;
    q2 = (AbsolutePose.ax() - AbsolutePose.nz()) / S;
    q3 = (AbsolutePose.ny() - AbsolutePose.ox()) / S;
    }
  else if ((AbsolutePose.nx() > AbsolutePose.oy()) && (AbsolutePose.nx() > AbsolutePose.az()))
    {
    S  = sqrt(1.0 + AbsolutePose.nx() - AbsolutePose.oy() - AbsolutePose.az()) * 2.0;
    q0 = (AbsolutePose.oz() - AbsolutePose.ay()) / S;
    q1 = S / 4.0;
    q2 = (AbsolutePose.ox() + AbsolutePose.ny()) / S;
    q3 = (AbsolutePose.ax() + AbsolutePose.nz()) / S;
    }
  else if (AbsolutePose.oy() > AbsolutePose.az())
    {
    S  = sqrt(1.0 - AbsolutePose.nx() + AbsolutePose.oy() - AbsolutePose.az()) * 2.0;
    q0 = (AbsolutePose.ax() - AbsolutePose.nz()) / S;
    q1 = (AbsolutePose.ox() + AbsolutePose.ny()) / S;
    q2 = S / 4.0;
    q3 = (AbsolutePose.ay() + AbsolutePose.oz()) / S;
    }
  else
    {
    S  = sqrt(1.0 - AbsolutePose.nx() - AbsolutePose.oy() + AbsolutePose.az()) * 2.0;
    q0 = (AbsolutePose.ny() - AbsolutePose.ox()) / S;
    q1 = (AbsolutePose.ax() + AbsolutePose.nz()) / S;
    q2 = (AbsolutePose.ay() + AbsolutePose.oz()) / S;
    q3 = S / 4.0;
    }

  // Elemente normalisieren
  double abs_Quaternion = sqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);

  q0 /= abs_Quaternion;
  q1 /= abs_Quaternion;
  q2 /= abs_Quaternion;
  q3 /= abs_Quaternion;

  // Zuweisen der Elemente
  Quat = {q0, q1, q2, q3};
  }
void                         C_robot::HomogenousOrientationToQuaternion                            (Quaternion<double>&    Quat,              C_RelativePose       RelativePose)
  {
  // Spur der Rotationsmatrix bestimmen
  double Spur_R = RelativePose.nx() + RelativePose.oy() + RelativePose.az();

  // Berechnen der Quaternionselemente in Abhängigkeit der Spur der Rotationsmatrix
  double q0     = 0.0;
  double q1     = 0.0;
  double q2     = 0.0;
  double q3     = 0.0;
  double S      = 0.0;

  if (Spur_R > 0.0)
    {
    S  = sqrt(Spur_R + 1.0) * 2.0;
    q0 = S / 4.0;
    q1 = (RelativePose.oz() - RelativePose.ay()) / S;
    q2 = (RelativePose.ax() - RelativePose.nz()) / S;
    q3 = (RelativePose.ny() - RelativePose.ox()) / S;
    }
  else if ((RelativePose.nx() > RelativePose.oy()) && (RelativePose.nx() > RelativePose.az()))
    {
    S  = sqrt(1.0 + RelativePose.nx() - RelativePose.oy() - RelativePose.az()) * 2.0;
    q0 = (RelativePose.oz() - RelativePose.ay()) / S;
    q1 = S / 4.0;
    q2 = (RelativePose.ox() + RelativePose.ny()) / S;
    q3 = (RelativePose.ax() + RelativePose.nz()) / S;
    }
  else if (RelativePose.oy() > RelativePose.az())
    {
    S  = sqrt(1.0 - RelativePose.nx() + RelativePose.oy() - RelativePose.az()) * 2.0;
    q0 = (RelativePose.ax() - RelativePose.nz()) / S;
    q1 = (RelativePose.ox() + RelativePose.ny()) / S;
    q2 = S / 4.0;
    q3 = (RelativePose.ay() + RelativePose.oz()) / S;
    }
  else
    {
    S  = sqrt(1.0 - RelativePose.nx() - RelativePose.oy() + RelativePose.az()) * 2.0;
    q0 = (RelativePose.ny() - RelativePose.ox()) / S;
    q1 = (RelativePose.ax() + RelativePose.nz()) / S;
    q2 = (RelativePose.ay() + RelativePose.oz()) / S;
    q3 = S / 4.0;
    }

  // Elemente normalisieren
  double abs_Quaternion = sqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);

  q0 /= abs_Quaternion;
  q1 /= abs_Quaternion;
  q2 /= abs_Quaternion;
  q3 /= abs_Quaternion;

  // Zuweisen der Elemente
  Quat = {q0, q1, q2, q3};
  }
void                         C_robot::HomogenousPoseToFrankaPose                                   (CartesianPose&         FrankaPose,        C_AbsolutePose       AbsolutePose)
  {
  // Elemente zuweisen
  FrankaPose.O_T_EE[0]  = AbsolutePose.nx();
  FrankaPose.O_T_EE[1]  = AbsolutePose.ny();
  FrankaPose.O_T_EE[2]  = AbsolutePose.nz();
  FrankaPose.O_T_EE[4]  = AbsolutePose.ox();
  FrankaPose.O_T_EE[5]  = AbsolutePose.oy();
  FrankaPose.O_T_EE[6]  = AbsolutePose.oz();
  FrankaPose.O_T_EE[8]  = AbsolutePose.ax();
  FrankaPose.O_T_EE[9]  = AbsolutePose.ay();
  FrankaPose.O_T_EE[10] = AbsolutePose.az();
  FrankaPose.O_T_EE[12] = AbsolutePose.px();
  FrankaPose.O_T_EE[13] = AbsolutePose.py();
  FrankaPose.O_T_EE[14] = AbsolutePose.pz();
  }
void                         C_robot::HomogenousPoseToFrankaPose                                   (CartesianPose&         FrankaPose,        C_RelativePose       RelativePose)
  {
  // Elemente zuweisen
  FrankaPose.O_T_EE[0]  = RelativePose.nx();
  FrankaPose.O_T_EE[1]  = RelativePose.ny();
  FrankaPose.O_T_EE[2]  = RelativePose.nz();
  FrankaPose.O_T_EE[4]  = RelativePose.ox();
  FrankaPose.O_T_EE[5]  = RelativePose.oy();
  FrankaPose.O_T_EE[6]  = RelativePose.oz();
  FrankaPose.O_T_EE[8]  = RelativePose.ax();
  FrankaPose.O_T_EE[9]  = RelativePose.ay();
  FrankaPose.O_T_EE[10] = RelativePose.az();
  FrankaPose.O_T_EE[12] = RelativePose.px();
  FrankaPose.O_T_EE[13] = RelativePose.py();
  FrankaPose.O_T_EE[14] = RelativePose.pz();
  }
void                         C_robot::QuaternionToHomogenousOrientation                            (Quaternion<double>     Quat,              C_AbsolutePose&      AbsolutePose)
  {
  // Berechnen der Matrixelemente
  double nx = Quat.w() * Quat.w() + Quat.x() * Quat.x() - Quat.y() * Quat.y() - Quat.z() * Quat.z();
  double ny = 2.0 * (Quat.w() * Quat.z() + Quat.x() * Quat.y());
  double nz = 2.0 * (Quat.x() * Quat.z() - Quat.w() * Quat.y());
  double ox = 2.0 * (Quat.x() * Quat.y() - Quat.w() * Quat.z());
  double oy = Quat.w() * Quat.w() - Quat.x() * Quat.x() + Quat.y() * Quat.y() - Quat.z() * Quat.z();
  double oz = 2.0 * (Quat.w() * Quat.x() + Quat.y() * Quat.z());
  double ax = 2.0 * (Quat.w() * Quat.y() + Quat.x() * Quat.z());
  double ay = 2.0 * (Quat.y() * Quat.z() - Quat.w() * Quat.x());
  double az = Quat.w() * Quat.w() - Quat.x() * Quat.x() - Quat.y() * Quat.y() + Quat.z() * Quat.z();

  // Matrixelemente nochmals normieren
  double abs_n = sqrt (nx * nx + ny * ny + nz * nz);
  double abs_o = sqrt (ox * ox + oy * oy + oz * oz);
  double abs_a = sqrt (ax * ax + ay * ay + az * az);

  nx /= abs_n;
  ny /= abs_n;
  nz /= abs_n;
  ox /= abs_o;
  oy /= abs_o;
  oz /= abs_o;
  ax /= abs_a;
  ay /= abs_a;
  az /= abs_a;

  // Matrixelemente der Absolut-Orientierung zuweisen
  AbsolutePose.nx(nx);
  AbsolutePose.ny(ny);
  AbsolutePose.nz(nz);
  AbsolutePose.ox(ox);
  AbsolutePose.oy(oy);
  AbsolutePose.oz(oz);
  AbsolutePose.ax(ax);
  AbsolutePose.ay(ay);
  AbsolutePose.az(az);
  }
void                         C_robot::QuaternionToHomogenousOrientation                            (Quaternion<double>     Quat,              C_RelativePose&      RelativePose)
  {
  // Berechnen der Matrixelemente
  double nx = Quat.w() * Quat.w() + Quat.x() * Quat.x() - Quat.y() * Quat.y() - Quat.z() * Quat.z();
  double ny = 2.0 * (Quat.w() * Quat.z() + Quat.x() * Quat.y());
  double nz = 2.0 * (Quat.x() * Quat.z() - Quat.w() * Quat.y());
  double ox = 2.0 * (Quat.x() * Quat.y() - Quat.w() * Quat.z());
  double oy = Quat.w() * Quat.w() - Quat.x() * Quat.x() + Quat.y() * Quat.y() - Quat.z() * Quat.z();
  double oz = 2.0 * (Quat.w() * Quat.x() + Quat.y() * Quat.z());
  double ax = 2.0 * (Quat.w() * Quat.y() + Quat.x() * Quat.z());
  double ay = 2.0 * (Quat.y() * Quat.z() - Quat.w() * Quat.x());
  double az = Quat.w() * Quat.w() - Quat.x() * Quat.x() - Quat.y() * Quat.y() + Quat.z() * Quat.z();

  // Matrixelemente nochmals normieren
  double abs_n = sqrt (nx * nx + ny * ny + nz * nz);
  double abs_o = sqrt (ox * ox + oy * oy + oz * oz);
  double abs_a = sqrt (ax * ax + ay * ay + az * az);

  nx /= abs_n;
  ny /= abs_n;
  nz /= abs_n;
  ox /= abs_o;
  oy /= abs_o;
  oz /= abs_o;
  ax /= abs_a;
  ay /= abs_a;
  az /= abs_a;

  // Matrixelemente der Relativ-Orientierung zuweisen
  RelativePose.nx(nx);
  RelativePose.ny(ny);
  RelativePose.nz(nz);
  RelativePose.ox(ox);
  RelativePose.oy(oy);
  RelativePose.oz(oz);
  RelativePose.ax(ax);
  RelativePose.ay(ay);
  RelativePose.az(az);
  }
void                         C_robot::QuaternionToFrankaOrientation                                (Quaternion<double>     Quat,              CartesianPose&       FrankaPose)
  {
  // Berechnen der Matrixelemente
  double nx = Quat.w() * Quat.w() + Quat.x() * Quat.x() - Quat.y() * Quat.y() - Quat.z() * Quat.z();
  double ny = 2.0 * (Quat.w() * Quat.z() + Quat.x() * Quat.y());
  double nz = 2.0 * (Quat.x() * Quat.z() - Quat.w() * Quat.y());
  double ox = 2.0 * (Quat.x() * Quat.y() - Quat.w() * Quat.z());
  double oy = Quat.w() * Quat.w() - Quat.x() * Quat.x() + Quat.y() * Quat.y() - Quat.z() * Quat.z();
  double oz = 2.0 * (Quat.w() * Quat.x() + Quat.y() * Quat.z());
  double ax = 2.0 * (Quat.w() * Quat.y() + Quat.x() * Quat.z());
  double ay = 2.0 * (Quat.y() * Quat.z() - Quat.w() * Quat.x());
  double az = Quat.w() * Quat.w() - Quat.x() * Quat.x() - Quat.y() * Quat.y() + Quat.z() * Quat.z();

  // Matrixelemente nochmals normieren
  double abs_n = sqrt (nx * nx + ny * ny + nz * nz);
  double abs_o = sqrt (ox * ox + oy * oy + oz * oz);
  double abs_a = sqrt (ax * ax + ay * ay + az * az);

  nx /= abs_n;
  ny /= abs_n;
  nz /= abs_n;
  ox /= abs_o;
  oy /= abs_o;
  oz /= abs_o;
  ax /= abs_a;
  ay /= abs_a;
  az /= abs_a;

  // Matrixelemente der Franka-Orientierung zuweisen
  FrankaPose.O_T_EE[0]  = nx;
  FrankaPose.O_T_EE[1]  = ny;
  FrankaPose.O_T_EE[2]  = nz;
  FrankaPose.O_T_EE[4]  = ox;
  FrankaPose.O_T_EE[5]  = oy;
  FrankaPose.O_T_EE[6]  = oz;
  FrankaPose.O_T_EE[8]  = ax;
  FrankaPose.O_T_EE[9]  = ay;
  FrankaPose.O_T_EE[10] = az;
  }
void                         C_robot::FrankaPoseToHomogenousPose                                   (CartesianPose          FrankaPose,        C_AbsolutePose&      AbsolutePose)
  {
  // Elemente zuweisen
  AbsolutePose.nx(FrankaPose.O_T_EE[0]);
  AbsolutePose.ny(FrankaPose.O_T_EE[1]);
  AbsolutePose.nz(FrankaPose.O_T_EE[2]);
  AbsolutePose.ox(FrankaPose.O_T_EE[4]);
  AbsolutePose.oy(FrankaPose.O_T_EE[5]);
  AbsolutePose.oz(FrankaPose.O_T_EE[6]);
  AbsolutePose.ax(FrankaPose.O_T_EE[8]);
  AbsolutePose.ay(FrankaPose.O_T_EE[9]);
  AbsolutePose.az(FrankaPose.O_T_EE[10]);
  AbsolutePose.px(FrankaPose.O_T_EE[12]);
  AbsolutePose.py(FrankaPose.O_T_EE[13]);
  AbsolutePose.pz(FrankaPose.O_T_EE[14]);
  }
void                         C_robot::FrankaPoseToHomogenousPose                                   (CartesianPose          FrankaPose,        C_RelativePose&      RelativePose)
  {
  // Elemente zuweisen
  RelativePose.nx(FrankaPose.O_T_EE[0]);
  RelativePose.ny(FrankaPose.O_T_EE[1]);
  RelativePose.nz(FrankaPose.O_T_EE[2]);
  RelativePose.ox(FrankaPose.O_T_EE[4]);
  RelativePose.oy(FrankaPose.O_T_EE[5]);
  RelativePose.oz(FrankaPose.O_T_EE[6]);
  RelativePose.ax(FrankaPose.O_T_EE[8]);
  RelativePose.ay(FrankaPose.O_T_EE[9]);
  RelativePose.az(FrankaPose.O_T_EE[10]);
  RelativePose.px(FrankaPose.O_T_EE[12]);
  RelativePose.py(FrankaPose.O_T_EE[13]);
  RelativePose.pz(FrankaPose.O_T_EE[14]);
  }
void                         C_robot::FrankaOrientationToQuaternion                                (CartesianPose          FrankaPose,        Quaternion<double>&  Quat)
  {
  // Elemente der Rotationsmatrix zwischenspeichern
  double nx     = FrankaPose.O_T_EE[0];
  double ny     = FrankaPose.O_T_EE[1];
  double nz     = FrankaPose.O_T_EE[2];
  double ox     = FrankaPose.O_T_EE[4];
  double oy     = FrankaPose.O_T_EE[5];
  double oz     = FrankaPose.O_T_EE[6];
  double ax     = FrankaPose.O_T_EE[8];
  double ay     = FrankaPose.O_T_EE[9];
  double az     = FrankaPose.O_T_EE[10];

  // Berechnen der Spur der Rotationsmatrix
  double Spur_R = nx + oy + az;

  // Berechnen der Quaternionselemente in Abhängigkeit der Spur der Rotationsmatrix
  double q0     = 0.0;
  double q1     = 0.0;
  double q2     = 0.0;
  double q3     = 0.0;
  double S      = 0.0;

  if (Spur_R > 0.0)
    {
    S  = sqrt(Spur_R + 1.0) * 2.0;
    q0 = S / 4.0;
    q1 = (oz - ay) / S;
    q2 = (ax - nz) / S;
    q3 = (ny - ox) / S;
    }
  else if ((nx > oy) && (nx > az))
    {
    S  = sqrt(1.0 + nx - oy - az) * 2.0;
    q0 = (oz - ay) / S;
    q1 = S / 4.0;
    q2 = (ox + ny) / S;
    q3 = (ax + nz) / S;
    }
  else if (oy > az)
    {
    S  = sqrt(1.0 - nx + oy - az) * 2.0;
    q0 = (ax - nz) / S;
    q1 = (ox + ny) / S;
    q2 = S / 4.0;
    q3 = (ay + oz) / S;
    }
  else
    {
    S  = sqrt(1.0 - nx - oy + az) * 2.0;
    q0 = (ny - ox) / S;
    q1 = (ax + nz) / S;
    q2 = (ay + oz) / S;
    q3 = S / 4.0;
    }

  // Einheitsquaternion berechnen
  double abs_Quaternion = sqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);

  q0 /= abs_Quaternion;
  q1 /= abs_Quaternion;
  q2 /= abs_Quaternion;
  q3 /= abs_Quaternion;

  // Zuweisen der Elemente
  Quat = {q0, q1, q2, q3};
  }
void                         C_robot::Get_RotationAngle                                            (Quaternion<double>     Quat,              double&              Rotationswinkel)
  {
  // Rotationswinkel berechnen
  Rotationswinkel = 2.0 * acos(Quat.w());

  // Winkel umrechnen, da nur im Bereich von -Pi <= phi <= +Pi gültig
  if (Rotationswinkel > M_PI)
    {
    Rotationswinkel -= 2.0 * M_PI;
    }
  else if (Rotationswinkel < (-M_PI))
    {
    Rotationswinkel += 2.0 * M_PI;
    }

  // Winkel als Betrag ausgeben! Sollwinkelvorgabe gibt auch nur Beträge aus. Die richtige Drehrichtung ergibt sich durch positive Drehung um die Drehachse
  Rotationswinkel = abs(Rotationswinkel);
  }
void                         C_robot::Get_UnitRotationAxis                                         (Quaternion<double>     Quat,              double               (&Rotationsachse)[3])
  {
  // Winkel berechnen
  double Rotationswinkel = 2.0 * acos(Quat.w());

  // Winkel nur im Bereich von -Pi <= phi <= +Pi gültig
  if (Rotationswinkel > M_PI)
    {
    Rotationswinkel -= 2.0 * M_PI;
    }
  else if (Rotationswinkel < (-M_PI))
    {
    Rotationswinkel += 2.0 * M_PI;
    }

  // Vorzeichen der Achsrichtungen bestimmen
  double Vorzeichen;
  if (Rotationswinkel >= 0.0)
    {
    Vorzeichen = +1.0;
    }
  else
    {
    Vorzeichen = -1.0;
    }

  // Rotationswinkel nur als Betrag ausgeben, da die Sollwertvorgabe auch nur Beträge ausgibt
  Rotationswinkel = abs(Rotationswinkel);

  // Berechnung der Drehachse. Diese ergibt immer eine Drehachse, bei der durch Sollwertvorgabe in positiver Richtung rotiert wird
  double S = sin(Rotationswinkel / 2.0);

  if (abs(S) > 0.0001) // Abfangen einer Division durch 0
    {
    // Berechnung der Elemente der Rotationsachse. Das Vorzeichen der Achselemente ergibt sich automatisch durch das Vorzeichen
    // des Rotationswinkels. Die Rotationsachse richtet sich immer automatisch so aus, dass bei Sollwertvorgabe IMMER ein positiver
    // Winkel bzw. der Betrag des Winkels übergeben wird.
    double x               = Vorzeichen * Quat.x() / S;
    double y               = Vorzeichen * Quat.y() / S;
    double z               = Vorzeichen * Quat.z() / S;

    // Bestimmung des Einheitsvektors
    double abs_Vector      = sqrt(x * x + y * y + z * z);

    Rotationsachse[0]      = x / abs_Vector;
    Rotationsachse[1]      = y / abs_Vector;
    Rotationsachse[2]      = z / abs_Vector;
    }
  else // (abs(S) <= 0.0001)
    {
    // In diesem Fall sind auch die Elemente x, y und z des Quaternions null.
    Rotationsachse[0]      = 0.0;
    Rotationsachse[1]      = 0.0;
    Rotationsachse[2]      = 0.0;
    }
  }
void                         C_robot::Get_UnitTranslationVektor                                    (C_AbsolutePose         StartPose,         C_AbsolutePose       TargetPose,             double              (&Richtungsvektor)[3])
  {
  // Berechnen der Elemente des Richtungsvektors
  double Delta_x     = TargetPose.px() - StartPose.px();
  double Delta_y     = TargetPose.py() - StartPose.py();
  double Delta_z     = TargetPose.pz() - StartPose.pz();

  // Einheitsvektor des Richtungsvektors berechnen uns ausgeben
  double abs_Vector  = sqrt(Delta_x * Delta_x + Delta_y * Delta_y + Delta_z * Delta_z);

  Richtungsvektor[0] = Delta_x / abs_Vector;
  Richtungsvektor[1] = Delta_y / abs_Vector;
  Richtungsvektor[2] = Delta_z / abs_Vector;
  }
void                         C_robot::Get_TranslationDistance                                      (C_AbsolutePose         StartPose,         C_AbsolutePose       TargetPose,             double&             Distance)
  {
  // Berechnen der Elemente des Richtungsvektors
  double Delta_x     = TargetPose.px() - StartPose.px();
  double Delta_y     = TargetPose.py() - StartPose.py();
  double Delta_z     = TargetPose.pz() - StartPose.pz();

  // Distanz als Betrag des Vektors ermitteln
  Distance           = sqrt(Delta_x * Delta_x + Delta_y * Delta_y + Delta_z * Delta_z);
  }
void                         C_robot::Get_Inverse_Franka_Pose                                      (CartesianPose          Input_Pose,        CartesianPose&       Output_Pose)
  {
  // Transpornieren des Anteils der Rotationsmatrix
  Output_Pose.O_T_EE[0] = Input_Pose.O_T_EE[0];
  Output_Pose.O_T_EE[1] = Input_Pose.O_T_EE[4];
  Output_Pose.O_T_EE[2] = Input_Pose.O_T_EE[8];
  Output_Pose.O_T_EE[4] = Input_Pose.O_T_EE[1];
  Output_Pose.O_T_EE[5] = Input_Pose.O_T_EE[5];
  Output_Pose.O_T_EE[6] = Input_Pose.O_T_EE[9];
  Output_Pose.O_T_EE[8] = Input_Pose.O_T_EE[2];
  Output_Pose.O_T_EE[9] = Input_Pose.O_T_EE[6];
  Output_Pose.O_T_EE[10] = Input_Pose.O_T_EE[10];

  // Zuweisung der Zeile 3 der Posenmatrix
  Output_Pose.O_T_EE[3]  = 0.0;
  Output_Pose.O_T_EE[7]  = 0.0;
  Output_Pose.O_T_EE[11] = 0.0;
  Output_Pose.O_T_EE[15] = 1.0;

  // Berechnung benötigter Determinanten aus der Posenmatrix zur Bestimmung des
  // translatorischen Anteils
  double det_A30;
  double det_A31;
  double det_A32;

  det_A30   = Input_Pose.O_T_EE[4]
            * Input_Pose.O_T_EE[9]
            * Input_Pose.O_T_EE[14]
            + Input_Pose.O_T_EE[8]
            * Input_Pose.O_T_EE[13]
            * Input_Pose.O_T_EE[6]
            + Input_Pose.O_T_EE[12]
            * Input_Pose.O_T_EE[5]
            * Input_Pose.O_T_EE[10]
            - Input_Pose.O_T_EE[6]
            * Input_Pose.O_T_EE[9]
            * Input_Pose.O_T_EE[12]
            - Input_Pose.O_T_EE[10]
            * Input_Pose.O_T_EE[13]
            * Input_Pose.O_T_EE[4]
            - Input_Pose.O_T_EE[14]
            * Input_Pose.O_T_EE[5]
            * Input_Pose.O_T_EE[8];

  det_A31   = Input_Pose.O_T_EE[0]
            * Input_Pose.O_T_EE[9]
            * Input_Pose.O_T_EE[14]
            + Input_Pose.O_T_EE[8]
            * Input_Pose.O_T_EE[13]
            * Input_Pose.O_T_EE[2]
            + Input_Pose.O_T_EE[12]
            * Input_Pose.O_T_EE[1]
            * Input_Pose.O_T_EE[10]
            - Input_Pose.O_T_EE[2]
            * Input_Pose.O_T_EE[9]
            * Input_Pose.O_T_EE[12]
            - Input_Pose.O_T_EE[10]
            * Input_Pose.O_T_EE[13]
            * Input_Pose.O_T_EE[0]
            - Input_Pose.O_T_EE[14]
            * Input_Pose.O_T_EE[1]
            * Input_Pose.O_T_EE[8];

  det_A32   = Input_Pose.O_T_EE[0]
            * Input_Pose.O_T_EE[5]
            * Input_Pose.O_T_EE[14]
            + Input_Pose.O_T_EE[4]
            * Input_Pose.O_T_EE[13]
            * Input_Pose.O_T_EE[2]
            + Input_Pose.O_T_EE[12]
            * Input_Pose.O_T_EE[1]
            * Input_Pose.O_T_EE[6]
            - Input_Pose.O_T_EE[2]
            * Input_Pose.O_T_EE[5]
            * Input_Pose.O_T_EE[12]
            - Input_Pose.O_T_EE[6]
            * Input_Pose.O_T_EE[13]
            * Input_Pose.O_T_EE[0]
            - Input_Pose.O_T_EE[14]
            * Input_Pose.O_T_EE[1]
            * Input_Pose.O_T_EE[4];

// Berechnung des translatorischen Anteils
  Output_Pose.O_T_EE[12] = - det_A30;
  Output_Pose.O_T_EE[13] =   det_A31;
  Output_Pose.O_T_EE[14] = - det_A32;
  }
S_Positionsvektor            C_robot::Calc_Vector_Produkt                                          (S_Positionsvektor      Erster_Vektor,     S_Positionsvektor    Zweiter_Vektor)
  {
  S_Positionsvektor Ergebnis_Vektor;
  Ergebnis_Vektor.X   = Erster_Vektor.Y * Zweiter_Vektor.Z - Zweiter_Vektor.Y * Erster_Vektor.Z;
  Ergebnis_Vektor.Y   = Erster_Vektor.Z * Zweiter_Vektor.X - Zweiter_Vektor.Z * Erster_Vektor.X;
  Ergebnis_Vektor.Z   = Erster_Vektor.X * Zweiter_Vektor.Y - Zweiter_Vektor.X * Erster_Vektor.Y;

  return (Ergebnis_Vektor);
  }
double                       C_robot::Calc_Vector_Betrag                                           (S_Positionsvektor      Vektor)
  {
  return (sqrt(Vektor.X * Vektor.X + Vektor.Y * Vektor.Y + Vektor.Z * Vektor.Z));
  }

