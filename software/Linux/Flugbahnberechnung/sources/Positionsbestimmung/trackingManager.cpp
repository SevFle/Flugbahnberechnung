#include "headers/Positionsbestimmung/trackingManager.h"

using namespace trackingManager;
using namespace GlobalObjects;

C_trackingManager::C_trackingManager                    (C_GlobalObjects* GlobalObjects)
  {
  this->globalObjects       = GlobalObjects;
  this->dataPlotter         = new plotter::C_plotter;

  this->Positionsvektor_alt = new S_Positionsvektor;
  this->kalmanfilter        = new kalmanFilter::C_kalmanFilter;

  this->vecWorldtoCamPose   = new std::vector<C_AbsolutePose>;
  this->vecEinheitsVektor   = new std::vector<C_AbsolutePose>;
  this->vecCamToWorldPose   = new std::vector<C_AbsolutePose>;
  this->vecIstX             = new std::vector<int>;
  this->vecIstY             = new std::vector<int>;
  this->vecPixelVelocityX   = new std::vector<float>;
  this->vecPixelVelocityY   = new std::vector<float>;
  this->vecPixelVelocityZ   = new std::vector<float>;
  this->objektVektorTm1     = new S_Positionsvektor;

  this->dTime               = 0;

  for (int i = 0; i < payloadSize; i++)
    {
    this->Richtungsvektoren[i] = new S_Positionsvektor;
    }
  /****************** Positionsbuffer T-1 *******************/
  for(int i = 0; i < 3; i++)
    {
    this->objectVelocityTm1[i]  = 0.0f;
    this->objectVelocity[i]     = 0.0f;
    this->objectAcceleration[i] = 0.0f;
    this->PredVelocity[i]       = 0.0;
    }
  this->dTimestamp        = new milliseconds;
  this->timestamp_ms      = new Clock::time_point;
  this->timestamp_ms_old  = new Clock::time_point;

  this->kalman_dTimestamp        = new milliseconds;
  this->kalman_timestamp_ms      = new Clock::time_point;
  this->kalman_timestamp_ms_old  = new Clock::time_point;

  this->timer             = new Clock;
  this->consecutive_found = 0;
  this->kalmanAlive       = false;

  this->PredPosition = new S_Positionsvektor;
  this->positionPayload = nullptr;

  }
C_trackingManager::~C_trackingManager                   ()
  {
  if(this->positionPayload != nullptr)
    {
    delete (this->positionPayload);
    }
  delete                  (PredPosition);
  this->kalmanAlive       = false;
  this->consecutive_found = 0;



  delete                  (timer);

  delete                  (kalman_dTimestamp);
  delete                  (kalman_timestamp_ms_old);
  delete                  (kalman_timestamp_ms);

  delete                  (dTimestamp);
  delete                  (timestamp_ms_old);
  delete                  (timestamp_ms);

  for(int i = 0; i < 3; i++)
    {
    this->PredVelocity[i]       = 0.0;
    this->objectAcceleration[i] = 0.0f;
    this->objectVelocity[i]     = 0.0f;
    this->objectVelocityTm1[i]  = 0.0f;
    }
  for (int i = 0; i < payloadSize; i++)
    {
    delete (this->Richtungsvektoren[i]);
    this->Richtungsvektoren[i] = nullptr;
    }
  this->dTime              = 0;

  delete (objektVektorTm1);
  delete (vecPixelVelocityZ);
  delete (vecPixelVelocityY);
  delete (vecPixelVelocityX);

  delete (vecIstY);
  delete (vecIstX);

  delete (vecCamToWorldPose);
  delete (vecEinheitsVektor);
  delete (vecWorldtoCamPose);
  delete (dataPlotter);
  this->globalObjects = nullptr;
  }

void C_trackingManager::init_posen                      ()
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
void C_trackingManager::load_posen                      (C_AbsolutePose& cameraToWorld, C_AbsolutePose& worldToCamera)
  {

  this->vecWorldtoCamPose->push_back(worldToCamera);
  this->vecCamToWorldPose->push_back(cameraToWorld);
  }
void C_trackingManager::setTime                         ()
  {
  *this->timestamp_ms     = timer->now();
  *this->dTimestamp       = std::chrono::duration_cast<milliseconds>(*this->timestamp_ms - *this->timestamp_ms_old);
  this->dTime             = this->dTimestamp->count();

  *this->timestamp_ms_old = timer->now();
  if(this->dTime < 0)
    this->dTime = 1;
  }
void C_trackingManager::setRichtungsvektor              (S_Positionsvektor *value, int pos)
  {
  Richtungsvektoren[pos] = value;
  }
void C_trackingManager::Get_Position_ObjectTracking     (S_Positionsvektor& objektVektor, vector<int> WorldToCamPose_active)
  {
  //objektVektor = aktuelle Position des objektes - Beinhaltet bei Übergabe keine Position [0],
  //Richtungsvektoren[payloadsize] = Objektrichttungsvektoren aufgenommen durch die Bilder der Kameras

  // Richtungsvektoren der Objekt-Lichtstrahlen auf das Welt-KS transformieren
  vector<S_Positionsvektor> vec_Richtungsvektoren_World;
  //
  this->Calc_RichtungsvektorenToWorld(vec_Richtungsvektoren_World, WorldToCamPose_active);

  this->Calc_Position_ObjectTracking(objektVektor, vec_Richtungsvektoren_World, WorldToCamPose_active);

  *this->Positionsvektor_alt = objektVektor;

  }
void C_trackingManager::Calc_Position_ObjectTracking    (S_Positionsvektor &objektVektor, vector<S_Positionsvektor> &vec_Richtungsvektoren_World, vector<int> WorldToCamPose_active)
  {
  // Berechnung der aktuellen Objecktposition bezogen auf das Welt-koordinatensystem in Abhngigkeit aller TCP- / Kameraposen. Hierbei wird ber
  // Matrizen die Position bestimmt, bei der die Summe aller Abstandsquadrate der optischen Achsen zum Objekt am geringsten ist (Minimierungsproblem).
  // Siehe Ausarbeitung.

  // Anzahl der gefundenen TCP- / Kameraposen ermitteln
  int Anzahl_Posen = payloadSize;//(int)vec_Richtungsvektoren_World.size(); // = (Int32)vec_WorldToTCP_Poses.size()

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
  //CamPose = WorldToTCPPose
  for (int i = 0; i < Anzahl_Posen; i++)
    {
    Matrix_b[0][0] += (-this->vecWorldtoCamPose->at(WorldToCamPose_active.at(i)).pz() * vec_Richtungsvektoren_World[i].X + this->vecWorldtoCamPose->at(WorldToCamPose_active.at(i)).px() * vec_Richtungsvektoren_World[i].Z) *   vec_Richtungsvektoren_World[i].Z +
                      (-this->vecWorldtoCamPose->at(WorldToCamPose_active.at(i)).px() * vec_Richtungsvektoren_World[i].Y + this->vecWorldtoCamPose->at(WorldToCamPose_active.at(i)).py() * vec_Richtungsvektoren_World[i].X) * (-vec_Richtungsvektoren_World[i].Y);
    Matrix_b[1][0] += (-this->vecWorldtoCamPose->at(WorldToCamPose_active.at(i)).px() * vec_Richtungsvektoren_World[i].Y + this->vecWorldtoCamPose->at(WorldToCamPose_active.at(i)).py() * vec_Richtungsvektoren_World[i].X) *   vec_Richtungsvektoren_World[i].X +
                      (-this->vecWorldtoCamPose->at(WorldToCamPose_active.at(i)).py() * vec_Richtungsvektoren_World[i].Z + this->vecWorldtoCamPose->at(WorldToCamPose_active.at(i)).pz() * vec_Richtungsvektoren_World[i].Y) * (-vec_Richtungsvektoren_World[i].Z);
    Matrix_b[2][0] += (-this->vecWorldtoCamPose->at(WorldToCamPose_active.at(i)).py() * vec_Richtungsvektoren_World[i].Z + this->vecWorldtoCamPose->at(WorldToCamPose_active.at(i)).pz() * vec_Richtungsvektoren_World[i].Y) *   vec_Richtungsvektoren_World[i].Y +
                      (-this->vecWorldtoCamPose->at(WorldToCamPose_active.at(i)).pz() * vec_Richtungsvektoren_World[i].X + this->vecWorldtoCamPose->at(WorldToCamPose_active.at(i)).px() * vec_Richtungsvektoren_World[i].Z) * (-vec_Richtungsvektoren_World[i].X);
    }

  // Bestimmung der Hilfsmatrix "y" -> L*y=b
  double Matrix_y[3][1];
  Matrix_y[0][0] =  Matrix_b[0][0]                                                                      / Matrix_L[0][0];
  Matrix_y[1][0] = (Matrix_b[1][0] - Matrix_L[1][0] * Matrix_y[0][0])                                   / Matrix_L[1][1];
  Matrix_y[2][0] = (Matrix_b[2][0] - Matrix_L[2][0] * Matrix_y[0][0] - Matrix_L[2][1] * Matrix_y[1][0]) / Matrix_L[2][2];

  // Bestimmung der Position "x" -> L_T * x = y
  objektVektor.Z =  Matrix_y[2][0]                                                                                / Matrix_L_T[2][2];
  objektVektor.Y = (Matrix_y[1][0] - Matrix_L_T[1][2] * objektVektor.Z)                                        / Matrix_L_T[1][1];
  objektVektor.X = (Matrix_y[0][0] - Matrix_L_T[0][1] * objektVektor.Y - Matrix_L_T[0][2] * objektVektor.Z) / Matrix_L_T[0][0];
  }
void C_trackingManager::Calc_RichtungsvektorenToWorld   (std::vector<S_Positionsvektor>& vec_Richtungsvektoren_World, vector<int> WorldToCamPose_active)
  {
  // Die Orientierung von Welt- und Roboter-KS sind identisch. Es gilt:
  // w_r_R = Einheitsmatrix
  // w_o_P = w_r_R * r_c_R * c_o_P = r_c_R * c_o_P

  int Anzahl_Posen =  payloadSize;//(int)vecWorldtoCamPose->size();

  for (int i = 0; i < Anzahl_Posen; i++)
    {
    S_Positionsvektor Richtungsvektor;
    vec_Richtungsvektoren_World.push_back(Richtungsvektor);

    vec_Richtungsvektoren_World[i].X  = this->vecWorldtoCamPose->at(WorldToCamPose_active.at(i)).nx() * Richtungsvektoren[i]->X
                                      + this->vecWorldtoCamPose->at(WorldToCamPose_active.at(i)).ox() * Richtungsvektoren[i]->Y
                                      + this->vecWorldtoCamPose->at(WorldToCamPose_active.at(i)).ax() * Richtungsvektoren[i]->Z;

    vec_Richtungsvektoren_World[i].Y  = this->vecWorldtoCamPose->at(WorldToCamPose_active.at(i)).ny() * Richtungsvektoren[i]->X
                                      + this->vecWorldtoCamPose->at(WorldToCamPose_active.at(i)).oy() * Richtungsvektoren[i]->Y
                                      + this->vecWorldtoCamPose->at(WorldToCamPose_active.at(i)).ay() * Richtungsvektoren[i]->Z;

    vec_Richtungsvektoren_World[i].Z  = this->vecWorldtoCamPose->at(WorldToCamPose_active.at(i)).nz() * Richtungsvektoren[i]->X
                                      + this->vecWorldtoCamPose->at(WorldToCamPose_active.at(i)).oz() * Richtungsvektoren[i]->Y
                                      + this->vecWorldtoCamPose->at(WorldToCamPose_active.at(i)).az() * Richtungsvektoren[i]->Z;
    }
  }
void C_trackingManager::calcPixelVeloctiy               (int ist_X, int ist_Y, int camID, int& pred_X, int& pred_Y)
  {
  int dPixelX;
  int dPixelY;

  dPixelX = ist_X - this->vecIstX->at(camID);
  dPixelY = ist_Y - this->vecIstY->at(camID);

  int velX = dPixelX/this->dTime;
  int velY = dPixelY/this->dTime;

  this->vecPixelVelocityX->at(camID) = velX;
  this->vecPixelVelocityY->at(camID) = velY;
  this->predictPixelMovement(pred_X, pred_Y, this->vecPixelVelocityX->at(camID), this->vecPixelVelocityY->at(camID), ist_X, ist_Y);
  }
void C_trackingManager::calcObjectVeloctiy(S_Positionsvektor &objektVektor, float (&objectVelocity)[3])
  {
  //Aktualisere dt mit der aktuellen Zeit. dt ist die Zeitspanne zwischen jetzt und dem letzten Aufrufen der Funktion
  this->setTime(); //[ms]

  S_Positionsvektor dObjektVektor;
  dObjektVektor.X = objektVektor.X - this->objektVektorTm1->X; //[m]
  dObjektVektor.Y = objektVektor.Y - this->objektVektorTm1->Y; //[m]
  dObjektVektor.Z = objektVektor.Z - this->objektVektorTm1->Z; //[m]
  this->objectVelocity[0] = dObjektVektor.X/this->dTime; //[m/ms]
  this->objectVelocity[1] = dObjektVektor.Y/this->dTime; //[m/ms]
  this->objectVelocity[2] = dObjektVektor.Z/this->dTime; //[m/ms]
  objectVelocity[0] = this->objectVelocity[0];
  objectVelocity[1] = this->objectVelocity[1];
  objectVelocity[2] = this->objectVelocity[2];

  this->calcObjectAcceleration();
  this->objektVektorTm1->X = objektVektor.X;
  this->objektVektorTm1->Y = objektVektor.Y;
  this->objektVektorTm1->Z = objektVektor.Z;

  std::cout << std::endl << "Velocity X: " << objectVelocity[0] << std::endl;
  std::cout << std::endl << "Velocity Y: " << objectVelocity[1] << std::endl;
  std::cout << std::endl << "Velocity Z: " << objectVelocity[2] << std::endl;

  }
void C_trackingManager::calcPixelAcceleration           ()
  {

  }
void C_trackingManager::calcObjectAcceleration          ()
  {
  float dObjectVelocity [3];
  dObjectVelocity[0] = this->objectVelocityTm1[0]-this->objectVelocity[0];
  dObjectVelocity[1] = this->objectVelocityTm1[1]-this->objectVelocity[1];
  dObjectVelocity[2] = this->objectVelocityTm1[2]-this->objectVelocity[2];

  this->objectVelocityTm1[0] = this->objectVelocity[0];
  this->objectVelocityTm1[1] = this->objectVelocity[1];
  this->objectVelocityTm1[2] = this->objectVelocity[2];

  this->objectAcceleration[0] = dObjectVelocity[0]/this->dTime;
  this->objectAcceleration[1] = dObjectVelocity[1]/this->dTime;
  this->objectAcceleration[2] = dObjectVelocity[2]/this->dTime;
  }
void C_trackingManager::predictPixelMovement            (int& predX, int& predY, int pixelVelocityX, int pixelVelocityY, int ist_X, int ist_Y)
  {
  predX = ist_X +  this->dTime*pixelVelocityX;
  predY = ist_Y + this->dTime*pixelVelocityY;
  }
void C_trackingManager::predictKalman                   ()
  {
  this->kalmanfilter->predict(this->dTime);
  this->positionPayload = new GlobalObjects::S_PositionPayload;

  this->positionPayload->predPosition->X = this->kalmanfilter->predictedState->at<float>(0);
  this->positionPayload->predPosition->Y = this->kalmanfilter->predictedState->at<float>(1);
  this->positionPayload->predPosition->Z = this->kalmanfilter->predictedState->at<float>(2);

  this->positionPayload->predVelocity[0] = this->kalmanfilter->predictedState->at<float>(3);
  this->positionPayload->predVelocity[1] = this->kalmanfilter->predictedState->at<float>(4);
  this->positionPayload->predVelocity[2] = this->kalmanfilter->predictedState->at<float>(5);
  if(!this->globalObjects->objectPosenQue->try_push(positionPayload))
    {
    delete (this->positionPayload);
    this->positionPayload = nullptr;
    }


  }
void C_trackingManager::correctKalman                   (float x, float y, float z)
  {
  this->kalmanfilter->correct     (x,y,z);
  }
void C_trackingManager::processKalman                   (float x, float y, float z)
  {
  //Predict state
  std::cout << "############################# PROCESS KALMAN ##################################"<< std::endl;

  std::cout << "Timestamp ms" << this->dTime << std::endl;

  this->kalmanfilter->processKalman(this->dTime, x,y,z);
  this->positionPayload = new GlobalObjects::S_PositionPayload;

  this->positionPayload->predPosition->X = this->kalmanfilter->predictedState->at<float>(0);
  this->positionPayload->predPosition->Y = this->kalmanfilter->predictedState->at<float>(1);
  this->positionPayload->predPosition->Z = this->kalmanfilter->predictedState->at<float>(2);

  this->positionPayload->predVelocity[0] = this->kalmanfilter->predictedState->at<float>(3);
  this->positionPayload->predVelocity[1] = this->kalmanfilter->predictedState->at<float>(4);
  this->positionPayload->predVelocity[2] = this->kalmanfilter->predictedState->at<float>(5);
  if(!this->globalObjects->objectPosenQue->try_push(positionPayload))
    {
    delete (this->positionPayload);
    this->positionPayload = nullptr;
    }
  //Correct state
  //this->kalmanfilter->correct(x,y,z);


  }
double C_trackingManager::getDTime                      () const
  {
  return dTime;
  }
