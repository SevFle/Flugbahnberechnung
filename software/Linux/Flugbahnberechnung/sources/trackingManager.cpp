#include "headers/trackingManager.h"

using namespace trackingManager;
using namespace GlobalObjects;

C_trackingManager::C_trackingManager (C_GlobalObjects* GlobalObjects)
  {
  this->globalObjects       = GlobalObjects;
  this->dataPlotter         = new plotter::C_plotter;

  this->Positionsvektor_alt = new S_Positionsvektor;
  //onCuda::KalmanFilter2::C_kalman*    kalmanfilter;

  this->vecWorldtoCamPose = new std::vector<C_AbsolutePose>;
  this->vecEinheitsVektor = new std::vector<C_AbsolutePose>;
  this->vecIstX = new std::vector<int>;
  this->vecIstY = new std::vector<int>;
  this->vecPixelVelocityX = new std::vector<float>;
  this->vecPixelVelocityY = new std::vector<float>;
  this->vecPixelVelocityZ = new std::vector<float>;
  this->objektVektorTm1 = new S_Positionsvektor;
  /****************** Positionsbuffer T-1 *******************/
  for(int i = 0; i < 3; i++)
    {
    this->objectVelocityTm1[i] = 0.0f;
    this->objectVelocity[i] = 0.0f;
    this->objectAcceleration[i] = 0.0f;
    }
  }
C_trackingManager::~C_trackingManager ()
  {
  for(int i = 0; i < 3; i++)
    {
    this->objectAcceleration[i] = 0.0f;
    this->objectVelocity[i] = 0.0f;
    this->objectVelocityTm1[i] = 0.0f;
    }
  delete (objektVektorTm1);
  delete (vecPixelVelocityZ);
  delete (vecPixelVelocityY);
  delete (vecPixelVelocityX);

  delete (vecIstY);
  delete (vecIstX);

  delete (vecEinheitsVektor);
  delete (vecWorldtoCamPose);

  delete (vecWorldtoCamPose);

  delete (dataPlotter);
  this->globalObjects = nullptr;
  }

void C_trackingManager::init_posen                     ()
  {
  // REMOVE LATER
  for(int i = 0; i < payloadSize; i++)
    {
      C_AbsolutePose            absEinheitsVektor;
      vecEinheitsVektor->push_back(absEinheitsVektor);
    }
  this->vecIstX->resize(globalObjects->absCameras);
  this->vecIstY->resize(globalObjects->absCameras);

  this->vecPixelVelocityX->resize(globalObjects->absCameras);
  this->vecPixelVelocityY->resize(globalObjects->absCameras);
  this->vecPixelVelocityZ->resize(globalObjects->absCameras);

  }
void C_trackingManager::load_posen                     (C_AbsolutePose& cameraPose)
  {
  this->vecWorldtoCamPose->push_back(cameraPose);
  }

S_Positionsvektor *C_trackingManager::getPositionsvektor_alt() const
  {
  return Positionsvektor_alt;
  }

void C_trackingManager::setPositionsvektor_alt(S_Positionsvektor *value)
  {
  Positionsvektor_alt = value;
    }

void C_trackingManager::Get_Position_ObjectTracking (S_Positionsvektor& objektVektor, S_Positionsvektor Richtungsvektoren   [payloadSize])
  {
  //objektVektor = aktuelle Position des objektes - Beinhaltet bei Übergabe keine Position [0],
  //Richtungsvektoren[payloadsize] = Objektrichttungsvektoren aufgenommen durch die Bilder der Kameras

  // Richtungsvektoren der Objekt-Lichtstrahlen auf das Welt-KS transformieren
  vector<S_Positionsvektor> vec_Richtungsvektoren_World;
  //
  this->Calc_RichtungsvektorenToWorld(Richtungsvektoren, vec_Richtungsvektoren_World, *vecEinheitsVektor);

  this->Calc_Position_ObjectTracking(objektVektor, vec_Richtungsvektoren_World);

  *this->Positionsvektor_alt = objektVektor;

  //Mappe die aktuellen Objektpositionen auf einen QVector um diesen plotten zu können
  QVector3D vec3d;
  vec3d.setX(objektVektor.X);
  vec3d.setY(objektVektor.Y);
  vec3d.setZ(objektVektor.Z);

  this->dataPlotter->addSingleData(vec3d, plotter::series::realValue);
  }
void C_trackingManager::Calc_Position_ObjectTracking (S_Positionsvektor& Positionsvektor, std::vector<S_Positionsvektor> vec_Richtungsvektoren_World)
  {
  // Berechnung der aktuellen Objecktposition bezogen auf das Welt-koordinatensystem in Abhngigkeit aller Kameraposen. Hierbei wird ber
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
    Matrix_A[0][0] += vec_Richtungsvektoren_World[i].Y * vec_Richtungsvektoren_World[i].Y + vec_Richtungsvektoren_World[i].Z * vec_Richtungsvektoren_World[i].Z;

    // Berechnung a_01 = Sum(-r_x * r_y)
    Matrix_A[0][1] += -vec_Richtungsvektoren_World[i].X * vec_Richtungsvektoren_World[i].Y;

    // Berechnung a_02 = Sum(-r_x * r_z)
    Matrix_A[0][2] += -vec_Richtungsvektoren_World[i].X * vec_Richtungsvektoren_World[i].Z;

    // Berechnung a_10 = Sum(-r_y * r_x)
    Matrix_A[1][0] = Matrix_A[0][1];

    // Berechnung a_11 = Sum(r_x + r_z)
    Matrix_A[1][1] += vec_Richtungsvektoren_World[i].X * vec_Richtungsvektoren_World[i].X + vec_Richtungsvektoren_World[i].Z * vec_Richtungsvektoren_World[i].Z;

    // Berechnung a_12 = Sum(-r_y * r_z)
    Matrix_A[1][2] += -vec_Richtungsvektoren_World[i].Y * vec_Richtungsvektoren_World[i].Z;

    // Berechnung a_20 = Sum(-r_z * r_x)
    Matrix_A[2][0] = Matrix_A[0][2];

    // Berechnung a_21 = Sum(-r_z * r_y)
    Matrix_A[2][1] = Matrix_A[1][2];

    // Berechnung a_22 = Sum(r_x + r_y)
    Matrix_A[2][2] += vec_Richtungsvektoren_World[i].X * vec_Richtungsvektoren_World[i].X + vec_Richtungsvektoren_World[i].Y * vec_Richtungsvektoren_World[i].Y;
    }

  // Bestimmen der Cholesky-Matrix L und L^T
  double Matrix_L[3][3];
  double Matrix_L_T[3][3];

  Matrix_L_T[0][0] = sqrt (Matrix_A[0][0]);
  Matrix_L_T[0][1] = Matrix_A[0][1] / Matrix_L_T[0][0];
  Matrix_L_T[0][2] = Matrix_A[0][2] / Matrix_L_T[0][0];
  Matrix_L_T[1][0] = 0.0;
  Matrix_L_T[1][1] = sqrt (Matrix_A[1][1] - Matrix_L_T[0][1] * Matrix_L_T[0][1]);
  Matrix_L_T[1][2] = (Matrix_A[1][2] - Matrix_L_T[0][1] * Matrix_L_T[0][2]) / Matrix_L_T[1][1];
  Matrix_L_T[2][0] = 0.0;
  Matrix_L_T[2][1] = 0.0;
  Matrix_L_T[2][2] = sqrt (Matrix_A[2][2] - Matrix_L_T[0][2] * Matrix_L_T[0][2] - Matrix_L_T[1][2] * Matrix_L_T[1][2]);

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
    Matrix_b[0][0] += (-this->vecWorldtoCamPose->at(i).pz() * vec_Richtungsvektoren_World[i].X + this->vecWorldtoCamPose->at(i).px() * vec_Richtungsvektoren_World[i].Z) * vec_Richtungsvektoren_World[i].Z +
      (-this->vecWorldtoCamPose->at(i).px() * vec_Richtungsvektoren_World[i].Y + this->vecWorldtoCamPose->at(i).py() * vec_Richtungsvektoren_World[i].X) * (-vec_Richtungsvektoren_World[i].Y);
    Matrix_b[1][0] += (-this->vecWorldtoCamPose->at(i).px() * vec_Richtungsvektoren_World[i].Y + this->vecWorldtoCamPose->at(i).py() * vec_Richtungsvektoren_World[i].X) * vec_Richtungsvektoren_World[i].X +
      (-this->vecWorldtoCamPose->at(i).py() * vec_Richtungsvektoren_World[i].Z + this->vecWorldtoCamPose->at(i).pz() * vec_Richtungsvektoren_World[i].Y) * (-vec_Richtungsvektoren_World[i].Z);
    Matrix_b[2][0] += (-this->vecWorldtoCamPose->at(i).py() * vec_Richtungsvektoren_World[i].Z + this->vecWorldtoCamPose->at(i).pz() * vec_Richtungsvektoren_World[i].Y) * vec_Richtungsvektoren_World[i].Y +
      (-this->vecWorldtoCamPose->at(i).pz() * vec_Richtungsvektoren_World[i].X + this->vecWorldtoCamPose->at(i).px() * vec_Richtungsvektoren_World[i].Z) * (-vec_Richtungsvektoren_World[i].X);
    }

  // Bestimmung der Hilfsmatrix "y" -> L*y=b
  double Matrix_y[3][1];
  Matrix_y[0][0] = Matrix_b[0][0] / Matrix_L[0][0];
  Matrix_y[1][0] = (Matrix_b[1][0] - Matrix_L[1][0] * Matrix_y[0][0]) / Matrix_L[1][1];
  Matrix_y[2][0] = (Matrix_b[2][0] - Matrix_L[2][0] * Matrix_y[0][0] - Matrix_L[2][1] * Matrix_y[1][0]) / Matrix_L[2][2];

  // Bestimmung der Position "x" -> L_T * x = y
  Positionsvektor.Z = Matrix_y[2][0] / Matrix_L_T[2][2];
  Positionsvektor.Y = (Matrix_y[1][0] - Matrix_L_T[1][2] * Positionsvektor.Z) / Matrix_L_T[1][1];
  Positionsvektor.X = (Matrix_y[0][0] - Matrix_L_T[0][1] * Positionsvektor.Y - Matrix_L_T[0][2] * Positionsvektor.Z) / Matrix_L_T[0][0];
  }
void C_trackingManager::Calc_RichtungsvektorenToWorld (S_Positionsvektor vec_Richtungsvektoren[payloadSize], std::vector<S_Positionsvektor>& vec_Richtungsvektoren_World, std::vector<C_AbsolutePose> vecEinheitsMatrix)
  {
  // Die Orientierung von Welt- und Roboter-KS sind identisch. Es gilt:
  // w_r_R = Einheitsmatrix
  // w_o_P = w_r_R * r_c_R * c_o_P = r_c_R * c_o_P

  int Anzahl_Posen = (int)vecEinheitsMatrix.size();

  for (int i = 0; i < Anzahl_Posen; i++)
    {
    S_Positionsvektor Richtungsvektor;
    Richtungsvektor.X = 0.0;
    Richtungsvektor.Y = 0.0;
    Richtungsvektor.Z = 0.0;

    vec_Richtungsvektoren_World.push_back (Richtungsvektor);

    vec_Richtungsvektoren_World[i].X = vecEinheitsMatrix[i].nx() * vec_Richtungsvektoren[i].X
      + vecEinheitsMatrix[i].ox() * vec_Richtungsvektoren[i].Y
      + vecEinheitsMatrix[i].ax() * vec_Richtungsvektoren[i].Z;

    vec_Richtungsvektoren_World[i].Y = vecEinheitsMatrix[i].ny() * vec_Richtungsvektoren[i].X
      + vecEinheitsMatrix[i].oy() * vec_Richtungsvektoren[i].Y
      + vecEinheitsMatrix[i].ay() * vec_Richtungsvektoren[i].Z;

    vec_Richtungsvektoren_World[i].Z = vecEinheitsMatrix[i].nz() * vec_Richtungsvektoren[i].X
      + vecEinheitsMatrix[i].oz() * vec_Richtungsvektoren[i].Y
      + vecEinheitsMatrix[i].az() * vec_Richtungsvektoren[i].Z;
    }
  }

void C_trackingManager::calcPixelVeloctiy             (int dTimestamp, int ist_X, int ist_Y, int camID, int& pred_X, int& pred_Y)
  {
  int dPixelX;
  int dPixelY;

  dPixelX = ist_X - this->vecIstX->at(camID);
  dPixelY = ist_Y - this->vecIstY->at(camID);

  int velX = dPixelX/dTimestamp;
  int velY = dPixelY/dTimestamp;

  this->vecPixelVelocityX->at(camID) = velX;
  this->vecPixelVelocityY->at(camID) = velY;
  this->predictPixelMovement(dTimestamp, pred_X, pred_Y, this->vecPixelVelocityX->at(camID), this->vecPixelVelocityY->at(camID), ist_X, ist_Y);
  }

void C_trackingManager::calcObjectVeloctiy(int dTimestamp, S_Positionsvektor&             objektVektor)
  {
  S_Positionsvektor dObjektVektor;
  dObjektVektor.X = objektVektor.X - this->objektVektorTm1->X;
  dObjektVektor.Y = objektVektor.Y - this->objektVektorTm1->Y;
  dObjektVektor.Z = objektVektor.Z - this->objektVektorTm1->Z;
  this->objectVelocity[0] = dObjektVektor.X/dTimestamp;
  this->objectVelocity[1] = dObjektVektor.Y/dTimestamp;
  this->objectVelocity[2] = dObjektVektor.Z/dTimestamp;
  this->calcObjectAcceleration(dTimestamp);
  }

void C_trackingManager::calcPixelAcceleration(int dTimestamp)
  {

  }
void C_trackingManager::calcObjectAcceleration(int dTimestamp)
  {
  float dObjectVelocity [3];
  dObjectVelocity[0] = this->objectVelocityTm1[0]-this->objectVelocity[0];
  dObjectVelocity[1] = this->objectVelocityTm1[1]-this->objectVelocity[1];
  dObjectVelocity[2] = this->objectVelocityTm1[2]-this->objectVelocity[2];

  this->objectAcceleration[0] = dObjectVelocity[0]/dTimestamp;
  this->objectAcceleration[1] = dObjectVelocity[1]/dTimestamp;
  this->objectAcceleration[2] = dObjectVelocity[2]/dTimestamp;
  }

void C_trackingManager::predictPixelMovement           (int dTimestamp,int& predX, int& predY, int pixelVelocityX, int pixelVelocityY, int ist_X, int ist_Y)
  {
  predX = ist_X +  dTimestamp*pixelVelocityX;
  predY = ist_Y + dTimestamp*pixelVelocityY;
  }
