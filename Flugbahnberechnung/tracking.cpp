#include "tracking.h"

using namespace nmsp_tracking;

c_tracking::c_tracking()
  {
  auto* Positionsvektor_alt = new S_Positionsvektor;
  }


c_tracking::~c_tracking()
  {
  delete(Positionsvektor_alt);
  }

void              c_tracking::Get_Position_ObjectTracking             (s_tracking_data&               StructofTrackingData)
{
  std::vector<C_AbsolutePose>    vec_TCP_Poses;
  std::vector<C_AbsolutePose>    vec_WorldToTCP_Poses;

  // Kameradaten abholen
  std:: vector<bool>              vec_Object_Found;
  std::vector<S_Positionsvektor>  vec_Richtungsvektoren;

  vec_Richtungsvektoren.push_back (StructofTrackingData.Richtungsvektor_0);
  vec_Richtungsvektoren.push_back (StructofTrackingData.Richtungsvektor_1);
  vec_Object_Found.push_back      (StructofTrackingData.found_0);
  vec_Object_Found.push_back      (StructofTrackingData.found_0);

  // Richtungsvektoren der Objekt-Lichtstrahlen auf das Welt-KS transformieren
  std::vector<S_Positionsvektor> vec_Richtungsvektoren_World;
  this->Calc_RichtungsvektorenToWorld(vec_Richtungsvektoren, vec_Richtungsvektoren_World, vec_TCP_Poses);

  // Berechnung der Objektposition
  //E_ObjectTracking enum_ObjectTracking_0;
  //E_ObjectTracking enum_ObjectTracking_1;

  if (vec_Object_Found[0] && vec_Object_Found[1])
    {
    this->Calc_Position_ObjectTracking(StructofTrackingData.positionsvektor, vec_Richtungsvektoren_World, vec_WorldToTCP_Poses);
    Positionsvektor_alt = &StructofTrackingData.positionsvektor;

  //  enum_ObjectTracking_0     = E_ObjectTracking::Stereo_Object;
  //  enum_ObjectTracking_1     = E_ObjectTracking::Stereo_Object;
    }
  else if (vec_Object_Found[0] && !vec_Object_Found[1])
    {
    StructofTrackingData.positionsvektor           = *Positionsvektor_alt;
  //  enum_ObjectTracking_0     = E_ObjectTracking::Mono_Object;
  //  enum_ObjectTracking_1     = E_ObjectTracking::Object_Not_Found;
    }
  else if (!vec_Object_Found[0] && vec_Object_Found[1])
    {
    StructofTrackingData.positionsvektor           = *Positionsvektor_alt;
  //  enum_ObjectTracking_0     = E_ObjectTracking::Object_Not_Found;
  //  enum_ObjectTracking_1     = E_ObjectTracking::Mono_Object;
    }
  else
    {
    StructofTrackingData.positionsvektor           = *Positionsvektor_alt;
  //  enum_ObjectTracking_0     = E_ObjectTracking::Object_Not_Found;
  //  enum_ObjectTracking_1     = E_ObjectTracking::Object_Not_Found;
    }

  }
void              c_tracking::Calc_Position_ObjectTracking            (S_Positionsvektor&             Positionsvektor, std::vector<S_Positionsvektor>  vec_Richtungsvektoren_World, std::vector<C_AbsolutePose> vec_WorldToTCP_Poses)
  {
  // Berechnung der aktuellen Objecktposition bezogen auf das Welt-koordinatensystem in Abhngigkeit aller TCP- / Kameraposen. Hierbei wird ber
  // Matrizen die Position bestimmt, bei der die Summe aller Abstandsquadrate der optischen Achsen zum Objekt am geringsten ist (Minimierungsproblem).
  // Siehe Ausarbeitung.

  // Anzahl der gefundenen TCP- / Kameraposen ermitteln
  int Anzahl_Posen = (int)vec_Richtungsvektoren_World.size(); // = (Int32)vec_WorldToTCP_Poses.size()

  // Aufstellen der Matrix "A".
  double Matrix_A[3][3];
  for (int i = 0; i < 3; i++)
    {
    for (int j = 0; j < 3; j++)
      {
      Matrix_A[i][j] = 0.0;
      }
    }

  for (int i = 0; i < Anzahl_Posen; i++)
    {
    // Berechnung a_00 = Sum(r_y + r_z)
    Matrix_A[0][0] +=  vec_Richtungsvektoren_World[i].Y * vec_Richtungsvektoren_World[i].Y + vec_Richtungsvektoren_World[i].Z * vec_Richtungsvektoren_World[i].Z;

    // Berechnung a_01 = Sum(-r_x * r_y)
    Matrix_A[0][1] += -vec_Richtungsvektoren_World[i].X * vec_Richtungsvektoren_World[i].Y;

    // Berechnung a_02 = Sum(-r_x * r_z)
    Matrix_A[0][2] += -vec_Richtungsvektoren_World[i].X * vec_Richtungsvektoren_World[i].Z;

    // Berechnung a_10 = Sum(-r_y * r_x)
    Matrix_A[1][0]  =  Matrix_A[0][1];

    // Berechnung a_11 = Sum(r_x + r_z)
    Matrix_A[1][1] +=  vec_Richtungsvektoren_World[i].X * vec_Richtungsvektoren_World[i].X + vec_Richtungsvektoren_World[i].Z * vec_Richtungsvektoren_World[i].Z;

    // Berechnung a_12 = Sum(-r_y * r_z)
    Matrix_A[1][2] += -vec_Richtungsvektoren_World[i].Y * vec_Richtungsvektoren_World[i].Z;

    // Berechnung a_20 = Sum(-r_z * r_x)
    Matrix_A[2][0]  =  Matrix_A[0][2];

    // Berechnung a_21 = Sum(-r_z * r_y)
    Matrix_A[2][1]  =  Matrix_A[1][2];

    // Berechnung a_22 = Sum(r_x + r_y)
    Matrix_A[2][2] +=  vec_Richtungsvektoren_World[i].X * vec_Richtungsvektoren_World[i].X + vec_Richtungsvektoren_World[i].Y * vec_Richtungsvektoren_World[i].Y;
    }

  // Bestimmen der Cholesky-Matrix L und L^T
  double Matrix_L[3][3];
  double Matrix_L_T[3][3];

  Matrix_L_T[0][0] = sqrt(Matrix_A[0][0]);
  Matrix_L_T[0][1] = Matrix_A[0][1] / Matrix_L_T[0][0];
  Matrix_L_T[0][2] = Matrix_A[0][2] / Matrix_L_T[0][0];
  Matrix_L_T[1][0] = 0.0;
  Matrix_L_T[1][1] = sqrt(Matrix_A[1][1] - Matrix_L_T[0][1] * Matrix_L_T[0][1]);
  Matrix_L_T[1][2] = (Matrix_A[1][2] - Matrix_L_T[0][1] * Matrix_L_T[0][2]) / Matrix_L_T[1][1];
  Matrix_L_T[2][0] = 0.0;
  Matrix_L_T[2][1] = 0.0;
  Matrix_L_T[2][2] = sqrt(Matrix_A[2][2] - Matrix_L_T[0][2] * Matrix_L_T[0][2] - Matrix_L_T[1][2] * Matrix_L_T[1][2]);

  for (int i = 0; i < 3; i++)
    {
    for (int j = 0; j < 3; j++)
      {
      Matrix_L[i][j] = Matrix_L_T[j][i];
      }
    }

  // Bestimmung der Matrix "b"
  double Matrix_b[3][1];
  for (int i = 0; i < 3; i++)
    {
    Matrix_b[i][0] = 0.0;
    }

  for (int i = 0; i < Anzahl_Posen; i++)
    {
    Matrix_b[0][0] += (-vec_WorldToTCP_Poses[i].pz() * vec_Richtungsvektoren_World[i].X + vec_WorldToTCP_Poses[i].px() * vec_Richtungsvektoren_World[i].Z) *   vec_Richtungsvektoren_World[i].Z +
      (-vec_WorldToTCP_Poses[i].px() * vec_Richtungsvektoren_World[i].Y + vec_WorldToTCP_Poses[i].py() * vec_Richtungsvektoren_World[i].X) * (-vec_Richtungsvektoren_World[i].Y);
    Matrix_b[1][0] += (-vec_WorldToTCP_Poses[i].px() * vec_Richtungsvektoren_World[i].Y + vec_WorldToTCP_Poses[i].py() * vec_Richtungsvektoren_World[i].X) *   vec_Richtungsvektoren_World[i].X +
      (-vec_WorldToTCP_Poses[i].py() * vec_Richtungsvektoren_World[i].Z + vec_WorldToTCP_Poses[i].pz() * vec_Richtungsvektoren_World[i].Y) * (-vec_Richtungsvektoren_World[i].Z);
    Matrix_b[2][0] += (-vec_WorldToTCP_Poses[i].py() * vec_Richtungsvektoren_World[i].Z + vec_WorldToTCP_Poses[i].pz() * vec_Richtungsvektoren_World[i].Y) *   vec_Richtungsvektoren_World[i].Y +
      (-vec_WorldToTCP_Poses[i].pz() * vec_Richtungsvektoren_World[i].X + vec_WorldToTCP_Poses[i].px() * vec_Richtungsvektoren_World[i].Z) * (-vec_Richtungsvektoren_World[i].X);
    }

  // Bestimmung der Hilfsmatrix "y" -> L*y=b
  double Matrix_y[3][1];
  Matrix_y[0][0] =  Matrix_b[0][0]                                                                      / Matrix_L[0][0];
  Matrix_y[1][0] = (Matrix_b[1][0] - Matrix_L[1][0] * Matrix_y[0][0])                                   / Matrix_L[1][1];
  Matrix_y[2][0] = (Matrix_b[2][0] - Matrix_L[2][0] * Matrix_y[0][0] - Matrix_L[2][1] * Matrix_y[1][0]) / Matrix_L[2][2];

  // Bestimmung der Position "x" -> L_T * x = y
  Positionsvektor.Z =  Matrix_y[2][0]                                                                                / Matrix_L_T[2][2];
  Positionsvektor.Y = (Matrix_y[1][0] - Matrix_L_T[1][2] * Positionsvektor.Z)                                        / Matrix_L_T[1][1];
  Positionsvektor.X = (Matrix_y[0][0] - Matrix_L_T[0][1] * Positionsvektor.Y - Matrix_L_T[0][2] * Positionsvektor.Z) / Matrix_L_T[0][0];
  }
void              c_tracking::Calc_RichtungsvektorenToWorld           (std::vector<S_Positionsvektor> vec_Richtungsvektoren, std::vector<S_Positionsvektor>& vec_Richtungsvektoren_World, std::vector<C_AbsolutePose> vec_TCP_Poses)
  {
  // Die Orientierung von Welt- und Roboter-KS sind identisch. Es gilt:
  // w_r_R = Einheitsmatrix
  // w_o_P = w_r_R * r_c_R * c_o_P = r_c_R * c_o_P

  int Anzahl_Posen = (int)vec_TCP_Poses.size();

  for (int i = 0; i < Anzahl_Posen; i++)
    {
    S_Positionsvektor Richtungsvektor;
    vec_Richtungsvektoren_World.push_back(Richtungsvektor);

    vec_Richtungsvektoren_World[i].X  = vec_TCP_Poses[i].nx() * vec_Richtungsvektoren[i].X
      + vec_TCP_Poses[i].ox() * vec_Richtungsvektoren[i].Y
      + vec_TCP_Poses[i].ax() * vec_Richtungsvektoren[i].Z;

    vec_Richtungsvektoren_World[i].Y  = vec_TCP_Poses[i].ny() * vec_Richtungsvektoren[i].X
      + vec_TCP_Poses[i].oy() * vec_Richtungsvektoren[i].Y
      + vec_TCP_Poses[i].ay() * vec_Richtungsvektoren[i].Z;

    vec_Richtungsvektoren_World[i].Z  = vec_TCP_Poses[i].nz() * vec_Richtungsvektoren[i].X
      + vec_TCP_Poses[i].oz() * vec_Richtungsvektoren[i].Y
      + vec_TCP_Poses[i].az() * vec_Richtungsvektoren[i].Z;
    }
  }
