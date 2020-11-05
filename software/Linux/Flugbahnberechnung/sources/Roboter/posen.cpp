/********************************************************************************************************************************************/
/*                                                                                                                                          */
/*  Source-Datei: UM_Posen.cpp                                                                                                              */
/*                                                                                                                                          */
/*                                                                                                                                          */
/*                                                                                                                                          */
/*  Marcel Bänfer      11.09.2019                                                                                                           */
/*                                                                                                                                          */
/********************************************************************************************************************************************/

/************************************************************ Anwender-Includes *************************************************************/
#include "headers/Roboter/posen.h"
#include <math.h>
#include <cmath>
/************************************************************* using namespaces *************************************************************/
using namespace posen;


/*********************************************** Klasse C_AbsolutePose ***********************************************/
/**************************************************** Kontruktoren ***************************************************/
C_AbsolutePose::C_AbsolutePose ()
  {
  for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
      {
      if (i == j)
        {
        this->Nullpose[i][j]            = 1.0;
        this->HomogenePosenMatrix[i][j] = 1.0;
        }
      else
        {
        this->Nullpose[i][j]            = 0.0;
        this->HomogenePosenMatrix[i][j] = 0.0;
        }
      }
    }

  for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
      {
      this->HomogenePosenMatrixTempPuffer_1[i][j] = 0.0;
      this->HomogenePosenMatrixTempPuffer_2[i][j] = 0.0;
      this->HomogenePosenMatrixTempPuffer_3[i][j] = 0.0;
      }
    }

  for (int i = 0; i < 6; i++)
    {
    for (int j = 0; j < 1; j++)
      {
      this->URPose_Puffer[i][j] = 0.0;
      }
    }

  this->RX_normiert = 0.0;
  this->RY_normiert = 0.0;
  this->RZ_normiert = 0.0;
  this->Epsilon     = 0.01;
  }
C_AbsolutePose::C_AbsolutePose (const C_AbsolutePose& AbsolutePose)
  {
  for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
      {
      this->HomogenePosenMatrix[i][j] = AbsolutePose.HomogenePosenMatrix[i][j];
      }
    }
  }
/***************************************************** Destruktor* ***************************************************/
C_AbsolutePose::~C_AbsolutePose ()
  {
  this->Epsilon     = 0.0;
  this->RZ_normiert = 0.0;
  this->RY_normiert = 0.0;
  this->RX_normiert = 0.0;

  for (int i = 0; i < 6; i++)
    {
    for (int j = 0; j < 1; j++)
      {
      this->URPose_Puffer[i][j] = 0.0;
      }
    }

  for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
      {
      this->HomogenePosenMatrixTempPuffer_3[i][j] = 0.0;
      this->HomogenePosenMatrixTempPuffer_2[i][j] = 0.0;
      this->HomogenePosenMatrixTempPuffer_1[i][j] = 0.0;
      this->HomogenePosenMatrix[i][j]             = 0.0;
      this->Nullpose[i][j]                        = 0.0;
      }
    }
  }

/*********************************************Öffentliche Methoden*********************************************/
void C_AbsolutePose::operator= (C_AbsolutePose AbsolutePose)
  {
  // Zuweisen der einzelnen Elemente der homogenen Pose
  for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
      {
      this->HomogenePosenMatrix[i][j] = AbsolutePose.HomogenePosenMatrix[i][j];
      }
    }
  }
void C_AbsolutePose::operator= (S_PoseWerte& URPose)
  {
  // Aufruf der Umwandlungsmethode bei Nutzung des überladenen Operators
  this->URPoseToHomogenousPose (URPose,this->HomogenePosenMatrix);
  }
void C_AbsolutePose::operator= (C_URPose URPose)
  {
  // Aufruf der Umwandlungsmethode bei Nutzung des überladenen Operators
  this->URPoseToHomogenousPose (URPose,this->HomogenePosenMatrix);
  }
void C_AbsolutePose::operator= (double (&NullposeMatrix)[4][4])
  {
  // Zuweisen der Matrixelemente der Nullpose = Einheitsmatrix
  for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
      {
      this->HomogenePosenMatrix[i][j] = NullposeMatrix[i][j];
      }
    }
  }
C_AbsolutePose C_AbsolutePose::operator* (C_RelativePose& RelativePose)
  {
  // Erzeugung eines neuen Objektes, welches als Return zurückgegeben wird.
  C_AbsolutePose HomogenePoseAusgabe;

  // Die Diagonale des zuvor erzeugten Objektes muss genullt werden, da
  // diese bei Objekterzeugung im Konstruktor mit 1 besetzt wird (Nullpose = Einheitsmatrix).
  for (int i = 0; i < 4; i++)
    {
    HomogenePoseAusgabe.HomogenePosenMatrix[i][i] = 0;
    }

  // Matrixmultiplikation
  for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
      {
      for (int k = 0; k < 4; k++)
        {
        // this->HomogenePosenMatrix[i][k] ist die Pose des Objektes, dass bei der Multiplikation
        // links des Multiplikationsoperator steht. RelativePose.HomogenePosenMatrix[k][j] ist die Pose
        // des Objektes, dass rechts des Multiplikationsoperator steht und als Parameter 
        // "C_AbsolutePose HomogenePoseAusgabe" an den überladenen Operator übergeben wird.
        HomogenePoseAusgabe.HomogenePosenMatrix[i][j] += this->HomogenePosenMatrix[i][k] * RelativePose.HomogenePosenMatrix[k][j];
        }
      }
    }

  // Ausgabe der im Objekt "C_AbsolutePose HomogenePoseAusgabe" gefüllten nmsp_posen-Matrix.
  return (HomogenePoseAusgabe);
  }
void C_AbsolutePose::operator*= (C_RelativePose& RelativePose)
  {
  // Sicherstellen, dass in "this->HomogenePosenMatrixTempPuffer_1"
  // keine Werte enthalten sind.
  for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
      {
      this->HomogenePosenMatrixTempPuffer_1[i][j] = 0.0;
      }
    }


  // Matrixmultiplikation
  for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
      {
      for (int k = 0; k < 4; k++)
        {
        // this->HomogenePosenMatrix[i][k] ist die Pose des Objektes, dass bei der Multiplikation
        // links des Multiplikationsoperator steht. RelativePose.HomogenePosenMatrix[k][j] ist die Pose
        // des Objektes, dass rechts des Multiplikationsoperator steht und als Parameter 
        // "C_AbsolutePose HomogenePoseAusgabe" an den überladenen Operator übergeben wird.
        this->HomogenePosenMatrixTempPuffer_1[i][j] += this->HomogenePosenMatrix[i][k] * RelativePose.HomogenePosenMatrix[k][j];
        }
      }
    }

  // Das in "this->HomogenePosenMatrixTempPuffer_1" zwischengespeicherte Ergebnis
  // nun in die "this->HomogenePosenMatrix" schreiben.
  for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
      {
      this->HomogenePosenMatrix[i][j] = this->HomogenePosenMatrixTempPuffer_1[i][j];
      }
    }
  }
C_AbsolutePose C_AbsolutePose::operator/ (C_RelativePose& RelativePose)
  {
  // Erzeugung eines neuen Objektes, welches als Return zurückgegeben wird.
  C_AbsolutePose HomogenePoseAusgabe;

  // Temporäre Umwandlung der RelativePose (Objekt rechts des Operators) in eine inverse homogene Pose.
  HomogenePoseAusgabe.InversHomogenousPose (RelativePose,HomogenePoseAusgabe.HomogenePosenMatrixTempPuffer_1);

  // Die Diagonale des zuvor erzeugten Objektes muss genullt werden, da
  // diese bei Objekterzeugung im Konstruktor mit 1 besetzt wird (Nullpose).
  for (int i = 0; i < 4; i++)
    {
    HomogenePoseAusgabe.HomogenePosenMatrix[i][i] = 0;
    }

  // Matrixmultiplikation
  for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
      {
      for (int k = 0; k < 4; k++)
        {
        // HomogenePoseAusgabe.HomogenePosenMatrixTempPuffer_1[k][j] ist die temporär umgewandelte Pose des Objektes,
        // dass bei der Division rechts des Divisionsoperator steht. this->HomogenePosenMatrix[i][k] ist die 
        // Pose des Objektes, dass links des Divisionsoperator steht.
        // Diese Multiplikation entspricht: A = B / C = B * C^-1
        HomogenePoseAusgabe.HomogenePosenMatrix[i][j] += this->HomogenePosenMatrix[i][k] * HomogenePoseAusgabe.HomogenePosenMatrixTempPuffer_1[k][j];
        }
      }
    }

  // Ausgabe der im Objekt "HomogenePoseAusgabe.HomogenePosenMatrix[i][j]" gefüllten nmsp_posen-Matrix.
  return (HomogenePoseAusgabe);
  }
void C_AbsolutePose::operator/= (C_RelativePose& RelativePose)
  {
  // Sicherstellen, dass in "this->HomogenePosenMatrixTempPuffer_1"
  // keine Werte enthalten sind.
  for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
      {
      this->HomogenePosenMatrixTempPuffer_1[i][j] = 0.0;
      }
    }

  // Temporäre Umwandlung der RelativePose (Objekt rechts des Operators) in eine inverse homogene Pose.
  this->InversHomogenousPose (RelativePose,RelativePose.HomogenePosenMatrixTempPuffer_1);

  // Matrixmultiplikation
  for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
      {
      for (int k = 0; k < 4; k++)
        {
        // RelativePose.HomogenePosenMatrixTempPuffer_1[k][j] ist die temporär umgewandelte Pose des Objektes,
        // dass bei der Division rechts des Divisionsoperator steht. this->HomogenePosenMatrix[i][k] ist die 
        // Pose des Objektes, dass links des Divisionsoperator steht.
        // Diese Multiplikation entspricht: A = B / C = B * C^-1
        this->HomogenePosenMatrixTempPuffer_1[i][j] += this->HomogenePosenMatrix[i][k] * RelativePose.HomogenePosenMatrixTempPuffer_1[k][j];
        }
      }
    }

  // Das in "this->HomogenePosenMatrixTempPuffer_1" zwischengespeicherte Ergebnis
  // nun in die "this->HomogenePosenMatrix" schreiben.
  for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
      {
      this->HomogenePosenMatrix[i][j] = this->HomogenePosenMatrixTempPuffer_1[i][j];
      }
    }
  }
C_RelativePose C_AbsolutePose::operator| (C_URPose& URPose)
  {
  // Erzeugung eines neuen Objektes, welches als Return zurückgegeben wird.
  C_RelativePose HomogenePoseAusgabe;

  // Temporäre Umwandlung der URPose (Objekt rechts des Operators) in eine homogene Pose.
  HomogenePoseAusgabe.URPoseToHomogenousPose (URPose,HomogenePoseAusgabe.HomogenePosenMatrixTempPuffer_1);

  // Temporäre Umwandlung der homogenen Pose (Objekt links des Operators) in eine inverse homogene Pose.
  HomogenePoseAusgabe.InversHomogenousPose (*this,HomogenePoseAusgabe.HomogenePosenMatrixTempPuffer_2);

  // Die Ausgabe-Pose des zuvor erzeugten Objektes muss genullt werden, da
  // diese bei Umwandlung (1. Schritt) der URPose als Zwischenspeicher genutzt wurde.
  for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
      {
      HomogenePoseAusgabe.HomogenePosenMatrix[i][j] = 0;
      }
    }

  // Matrixmultiplikation
  for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
      {
      for (int k = 0; k < 4; k++)
        {
        // HomogenePoseAusgabe.HomogenePosenMatrixTempPuffer_1[k][j] ist die temporär umgewandelte Pose des Objektes,
        // dass bei der Division rechts des Divisionsoperator steht. HomogenePoseAusgabe.HomogenePosenMatrixTempPuffer_2[i][k] ist die 
        // Pose des Objektes, dass links des Divisionsoperator steht.
        // Diese Multiplikation entspricht: A = B \ C = B^-1 * C
        HomogenePoseAusgabe.HomogenePosenMatrix[i][j] += HomogenePoseAusgabe.HomogenePosenMatrixTempPuffer_2[i][k] * HomogenePoseAusgabe.HomogenePosenMatrixTempPuffer_1[k][j];
        }
      }
    }

  // Ausgabe der im Objekt "HomogenePoseAusgabe.HomogenePosenMatrix[i][j]" gefüllten nmsp_posen-Matrix.
  return (HomogenePoseAusgabe);
  }
C_RelativePose C_AbsolutePose::operator| (C_AbsolutePose& AbsolutePose)
  {
  // Erzeugung eines neuen Objektes, welches als Return zurückgegeben wird.
  C_RelativePose HomogenePoseAusgabe;

  // Temporäre Umwandlung der Homogenen Pose (Objekt links des Operators) in eine inverse homogene Pose.
  HomogenePoseAusgabe.InversHomogenousPose (*this,HomogenePoseAusgabe.HomogenePosenMatrixTempPuffer_1);

  // Die Diagonale des zuvor erzeugten Objektes muss genullt werden, da
  // diese bei Objekterzeugung im Konstruktor mit 1 besetzt wird (Nullpose).
  for (int i = 0; i < 4; i++)
    {
    HomogenePoseAusgabe.HomogenePosenMatrix[i][i] = 0;
    }

  // Matrixmultiplikation
  for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
      {
      for (int k = 0; k < 4; k++)
        {
        // HomogenePoseAusgabe.HomogenePosenMatrixTempPuffer_1[i][k] ist die temporär umgewandelte Pose des Objektes,
        // dass bei der Division links des Divisionsoperator steht. AbsolutePose.HomogenePosenMatrix[k][j] ist die 
        // Pose des Objektes, dass rechts des Divisionsoperator steht und als Parameter an den überladenen Operator übergeben wird.
        // Diese Multiplikation entspricht: A = B \ C = B^-1 * C
        HomogenePoseAusgabe.HomogenePosenMatrix[i][j] += HomogenePoseAusgabe.HomogenePosenMatrixTempPuffer_1[i][k] * AbsolutePose.HomogenePosenMatrix[k][j];
        }
      }
    }

  // Ausgabe der im Objekt "HomogenePoseAusgabe.HomogenePosenMatrix[i][j]" gefüllten nmsp_posen-Matrix.
  return (HomogenePoseAusgabe);
  }
void C_AbsolutePose::URPoseToHomogenousPose (S_PoseWerte& URPose, double (&HomogenePoseMatrix)[4][4])
  {
  // Betrag des Rotationsvektor = Drehwinkel um beliebige Achse [rad]
  double Drehwinkel = sqrt (URPose.RX * URPose.RX + URPose.RY * URPose.RY + URPose.RZ * URPose.RZ);

  // Einheitsrichtungsvektor des Rotationsvektor, welcher für die Umrechnung
  // in homogene Koordinaten benötigt wird.
  this->RX_normiert = URPose.RX / Drehwinkel;
  this->RY_normiert = URPose.RY / Drehwinkel;
  this->RZ_normiert = URPose.RZ / Drehwinkel;

  // Zuweisung der Zeile 3 der Posenmatrix
  HomogenePoseMatrix[3][0] = 0;
  HomogenePoseMatrix[3][1] = 0;
  HomogenePoseMatrix[3][2] = 0;
  HomogenePoseMatrix[3][3] = 1;

  // Zuweisung des Positionsvektors der Posenmatrix
  HomogenePoseMatrix[0][3] = URPose.X;
  HomogenePoseMatrix[1][3] = URPose.Y;
  HomogenePoseMatrix[2][3] = URPose.Z;

  // Beschreibung Rotationsmatrix siehe: Lothar Zunker - 
  // Transputerbasierter Lichtschnittsensor als Baustein eines
  // Multisensor-Steuerungskonzepts zur Echtzeit-Schweißprozessführung
  // und seine Integration in ein Roboterschweißsystem
  HomogenePoseMatrix[0][0] = pow (this->RX_normiert,2)
    * (1 - cos (Drehwinkel))
    + cos (Drehwinkel);
  HomogenePoseMatrix[0][1] = this->RX_normiert
    * this->RY_normiert
    * (1 - cos (Drehwinkel))
    - this->RZ_normiert
    * sin (Drehwinkel);
  HomogenePoseMatrix[0][2] = this->RX_normiert
    * this->RZ_normiert
    * (1 - cos (Drehwinkel))
    + this->RY_normiert
    * sin (Drehwinkel);
  HomogenePoseMatrix[1][0] = this->RX_normiert
    * this->RY_normiert
    * (1 - cos (Drehwinkel))
    + this->RZ_normiert
    * sin (Drehwinkel);
  HomogenePoseMatrix[1][1] = pow (this->RY_normiert,2)
    * (1 - cos (Drehwinkel))
    + cos (Drehwinkel);
  HomogenePoseMatrix[1][2] = this->RY_normiert
    * this->RZ_normiert
    * (1 - cos (Drehwinkel))
    - this->RX_normiert
    * sin (Drehwinkel);
  HomogenePoseMatrix[2][0] = this->RX_normiert
    * this->RZ_normiert
    * (1 - cos (Drehwinkel))
    - this->RY_normiert
    * sin (Drehwinkel);
  HomogenePoseMatrix[2][1] = this->RY_normiert
    * this->RZ_normiert
    * (1 - cos (Drehwinkel))
    + this->RX_normiert
    * sin (Drehwinkel);
  HomogenePoseMatrix[2][2] = pow (this->RZ_normiert,2)
    * (1 - cos (Drehwinkel))
    + cos (Drehwinkel);
  }
void C_AbsolutePose::URPoseToHomogenousPose (C_URPose& URPose, double (&HomogenePoseMatrix)[4][4])
  {
  // Betrag des Rotationsvektor = Drehwinkel um beliebige Achse [rad]
  double Drehwinkel = sqrt (pow (URPose.RX,2) + pow (URPose.RY,2) + pow (URPose.RZ,2));

  // Einheitsrichtungsvektor des Rotationsvektor, welcher für die Umrechnung
  // in homogene Koordinaten benötigt wird.
  this->RX_normiert = URPose.RX / Drehwinkel;
  this->RY_normiert = URPose.RY / Drehwinkel;
  this->RZ_normiert = URPose.RZ / Drehwinkel;

  // Zuweisung der Zeile 3 der Posenmatrix
  HomogenePoseMatrix[3][0] = 0;
  HomogenePoseMatrix[3][1] = 0;
  HomogenePoseMatrix[3][2] = 0;
  HomogenePoseMatrix[3][3] = 1;

  // Zuweisung des Positionsvektors der Posenmatrix
  HomogenePoseMatrix[0][3] = URPose.X;
  HomogenePoseMatrix[1][3] = URPose.Y;
  HomogenePoseMatrix[2][3] = URPose.Z;

  // Beschreibung Rotationsmatrix siehe: Lothar Zunker - 
  // Transputerbasierter Lichtschnittsensor als Baustein eines
  // Multisensor-Steuerungskonzepts zur Echtzeit-Schweißprozessführung
  // und seine Integration in ein Roboterschweißsystem
  HomogenePoseMatrix[0][0] = pow (this->RX_normiert,2)
    * (1 - cos (Drehwinkel))
    + cos (Drehwinkel);
  HomogenePoseMatrix[0][1] = this->RX_normiert
    * this->RY_normiert
    * (1 - cos (Drehwinkel))
    - this->RZ_normiert
    * sin (Drehwinkel);
  HomogenePoseMatrix[0][2] = this->RX_normiert
    * this->RZ_normiert
    * (1 - cos (Drehwinkel))
    + this->RY_normiert
    * sin (Drehwinkel);
  HomogenePoseMatrix[1][0] = this->RX_normiert
    * this->RY_normiert
    * (1 - cos (Drehwinkel))
    + this->RZ_normiert
    * sin (Drehwinkel);
  HomogenePoseMatrix[1][1] = pow (this->RY_normiert,2)
    * (1 - cos (Drehwinkel))
    + cos (Drehwinkel);
  HomogenePoseMatrix[1][2] = this->RY_normiert
    * this->RZ_normiert
    * (1 - cos (Drehwinkel))
    - this->RX_normiert
    * sin (Drehwinkel);
  HomogenePoseMatrix[2][0] = this->RX_normiert
    * this->RZ_normiert
    * (1 - cos (Drehwinkel))
    - this->RY_normiert
    * sin (Drehwinkel);
  HomogenePoseMatrix[2][1] = this->RY_normiert
    * this->RZ_normiert
    * (1 - cos (Drehwinkel))
    + this->RX_normiert
    * sin (Drehwinkel);
  HomogenePoseMatrix[2][2] = pow (this->RZ_normiert,2)
    * (1 - cos (Drehwinkel))
    + cos (Drehwinkel);
  }
void C_AbsolutePose::URPoseToHomogenousPose (double (&URPoseMatrix)[6][1], double (&HomogenePoseMatrix)[4][4])
  {
  // Betrag des Rotationsvektor = Drehwinkel um beliebige Achse [rad]
  double Drehwinkel = sqrt (pow (URPoseMatrix[3][0],2) + pow (URPoseMatrix[4][0],2) + pow (URPoseMatrix[5][0],2));

  // Einheitsrichtungsvektor des Rotationsvektor, welcher für die Umrechnung
  // in homogene Koordinaten benötigt wird.
  this->RX_normiert = URPoseMatrix[3][0] / Drehwinkel;
  this->RY_normiert = URPoseMatrix[4][0] / Drehwinkel;
  this->RZ_normiert = URPoseMatrix[5][0] / Drehwinkel;

  // Zuweisung der Zeile 3 der Posenmatrix
  HomogenePoseMatrix[3][0] = 0;
  HomogenePoseMatrix[3][1] = 0;
  HomogenePoseMatrix[3][2] = 0;
  HomogenePoseMatrix[3][3] = 1;

  // Zuweisung des Positionsvektors der Posenmatrix
  HomogenePoseMatrix[0][3] = URPoseMatrix[0][0];
  HomogenePoseMatrix[1][3] = URPoseMatrix[1][0];
  HomogenePoseMatrix[2][3] = URPoseMatrix[2][0];

  // Beschreibung Rotationsmatrix siehe: Lothar Zunker - 
  // Transputerbasierter Lichtschnittsensor als Baustein eines
  // Multisensor-Steuerungskonzepts zur Echtzeit-Schweißprozessführung
  // und seine Integration in ein Roboterschweißsystem
  HomogenePoseMatrix[0][0] = pow (this->RX_normiert,2)
    * (1 - cos (Drehwinkel))
    + cos (Drehwinkel);
  HomogenePoseMatrix[0][1] = this->RX_normiert
    * this->RY_normiert
    * (1 - cos (Drehwinkel))
    - this->RZ_normiert
    * sin (Drehwinkel);
  HomogenePoseMatrix[0][2] = this->RX_normiert
    * this->RZ_normiert
    * (1 - cos (Drehwinkel))
    + this->RY_normiert
    * sin (Drehwinkel);
  HomogenePoseMatrix[1][0] = this->RX_normiert
    * this->RY_normiert
    * (1 - cos (Drehwinkel))
    + this->RZ_normiert
    * sin (Drehwinkel);
  HomogenePoseMatrix[1][1] = pow (this->RY_normiert,2)
    * (1 - cos (Drehwinkel))
    + cos (Drehwinkel);
  HomogenePoseMatrix[1][2] = this->RY_normiert
    * this->RZ_normiert
    * (1 - cos (Drehwinkel))
    - this->RX_normiert
    * sin (Drehwinkel);
  HomogenePoseMatrix[2][0] = this->RX_normiert
    * this->RZ_normiert
    * (1 - cos (Drehwinkel))
    - this->RY_normiert
    * sin (Drehwinkel);
  HomogenePoseMatrix[2][1] = this->RY_normiert
    * this->RZ_normiert
    * (1 - cos (Drehwinkel))
    + this->RX_normiert
    * sin (Drehwinkel);
  HomogenePoseMatrix[2][2] = pow (this->RZ_normiert,2)
    * (1 - cos (Drehwinkel))
    + cos (Drehwinkel);
  }
void C_AbsolutePose::InversHomogenousPose (C_AbsolutePose& HomogenePose_In, double (&HomogenePoseMatrix_Out)[4][4])
  {
  // Transpornieren des Anteils der Rotationsmatrix
  for (int i = 0; i < 3; i++)
    {
    for (int j = 0; j < 3; j++)
      {
      HomogenePoseMatrix_Out[i][j] = HomogenePose_In.HomogenePosenMatrix[j][i];
      }
    }

  // Zuweisung der Zeile 3 der Posenmatrix
  HomogenePoseMatrix_Out[3][0] = 0;
  HomogenePoseMatrix_Out[3][1] = 0;
  HomogenePoseMatrix_Out[3][2] = 0;
  HomogenePoseMatrix_Out[3][3] = 1;

  // Berechnung benötigter Determinanten aus der Posenmatrix zur Bestimmung des
  // translatorischen Anteils
  double det_A30;
  double det_A31;
  double det_A32;

  det_A30 = HomogenePose_In.HomogenePosenMatrix[0][1]
    * HomogenePose_In.HomogenePosenMatrix[1][2]
    * HomogenePose_In.HomogenePosenMatrix[2][3]
    + HomogenePose_In.HomogenePosenMatrix[0][2]
    * HomogenePose_In.HomogenePosenMatrix[1][3]
    * HomogenePose_In.HomogenePosenMatrix[2][1]
    + HomogenePose_In.HomogenePosenMatrix[0][3]
    * HomogenePose_In.HomogenePosenMatrix[1][1]
    * HomogenePose_In.HomogenePosenMatrix[2][2]
    - HomogenePose_In.HomogenePosenMatrix[2][1]
    * HomogenePose_In.HomogenePosenMatrix[1][2]
    * HomogenePose_In.HomogenePosenMatrix[0][3]
    - HomogenePose_In.HomogenePosenMatrix[2][2]
    * HomogenePose_In.HomogenePosenMatrix[1][3]
    * HomogenePose_In.HomogenePosenMatrix[0][1]
    - HomogenePose_In.HomogenePosenMatrix[2][3]
    * HomogenePose_In.HomogenePosenMatrix[1][1]
    * HomogenePose_In.HomogenePosenMatrix[0][2];

  det_A31 = HomogenePose_In.HomogenePosenMatrix[0][0]
    * HomogenePose_In.HomogenePosenMatrix[1][2]
    * HomogenePose_In.HomogenePosenMatrix[2][3]
    + HomogenePose_In.HomogenePosenMatrix[0][2]
    * HomogenePose_In.HomogenePosenMatrix[1][3]
    * HomogenePose_In.HomogenePosenMatrix[2][0]
    + HomogenePose_In.HomogenePosenMatrix[0][3]
    * HomogenePose_In.HomogenePosenMatrix[1][0]
    * HomogenePose_In.HomogenePosenMatrix[2][2]
    - HomogenePose_In.HomogenePosenMatrix[2][0]
    * HomogenePose_In.HomogenePosenMatrix[1][2]
    * HomogenePose_In.HomogenePosenMatrix[0][3]
    - HomogenePose_In.HomogenePosenMatrix[2][2]
    * HomogenePose_In.HomogenePosenMatrix[1][3]
    * HomogenePose_In.HomogenePosenMatrix[0][0]
    - HomogenePose_In.HomogenePosenMatrix[2][3]
    * HomogenePose_In.HomogenePosenMatrix[1][0]
    * HomogenePose_In.HomogenePosenMatrix[0][2];

  det_A32 = HomogenePose_In.HomogenePosenMatrix[0][0]
    * HomogenePose_In.HomogenePosenMatrix[1][1]
    * HomogenePose_In.HomogenePosenMatrix[2][3]
    + HomogenePose_In.HomogenePosenMatrix[0][1]
    * HomogenePose_In.HomogenePosenMatrix[1][3]
    * HomogenePose_In.HomogenePosenMatrix[2][0]
    + HomogenePose_In.HomogenePosenMatrix[0][3]
    * HomogenePose_In.HomogenePosenMatrix[1][0]
    * HomogenePose_In.HomogenePosenMatrix[2][1]
    - HomogenePose_In.HomogenePosenMatrix[2][0]
    * HomogenePose_In.HomogenePosenMatrix[1][1]
    * HomogenePose_In.HomogenePosenMatrix[0][3]
    - HomogenePose_In.HomogenePosenMatrix[2][1]
    * HomogenePose_In.HomogenePosenMatrix[1][3]
    * HomogenePose_In.HomogenePosenMatrix[0][0]
    - HomogenePose_In.HomogenePosenMatrix[2][3]
    * HomogenePose_In.HomogenePosenMatrix[1][0]
    * HomogenePose_In.HomogenePosenMatrix[0][1];

// Berechnung des translatorischen Anteils
  HomogenePoseMatrix_Out[0][3] = -det_A30;
  HomogenePoseMatrix_Out[1][3] = det_A31;
  HomogenePoseMatrix_Out[2][3] = -det_A32;
  }
void C_AbsolutePose::InversHomogenousPose (C_RelativePose& HomogenePose_In, double (&HomogenePoseMatrix_Out)[4][4])
  {
  // Transpornieren des Anteils der Rotationsmatrix
  for (int i = 0; i < 3; i++)
    {
    for (int j = 0; j < 3; j++)
      {
      HomogenePoseMatrix_Out[i][j] = HomogenePose_In.HomogenePosenMatrix[j][i];
      }
    }

  // Zuweisung der Zeile 3 der Posenmatrix
  HomogenePoseMatrix_Out[3][0] = 0;
  HomogenePoseMatrix_Out[3][1] = 0;
  HomogenePoseMatrix_Out[3][2] = 0;
  HomogenePoseMatrix_Out[3][3] = 1;

  // Berechnung benötigter Determinanten aus der Posenmatrix zur Bestimmung des
  // translatorischen Anteils
  double det_A30;
  double det_A31;
  double det_A32;

  det_A30 = HomogenePose_In.HomogenePosenMatrix[0][1]
    * HomogenePose_In.HomogenePosenMatrix[1][2]
    * HomogenePose_In.HomogenePosenMatrix[2][3]
    + HomogenePose_In.HomogenePosenMatrix[0][2]
    * HomogenePose_In.HomogenePosenMatrix[1][3]
    * HomogenePose_In.HomogenePosenMatrix[2][1]
    + HomogenePose_In.HomogenePosenMatrix[0][3]
    * HomogenePose_In.HomogenePosenMatrix[1][1]
    * HomogenePose_In.HomogenePosenMatrix[2][2]
    - HomogenePose_In.HomogenePosenMatrix[2][1]
    * HomogenePose_In.HomogenePosenMatrix[1][2]
    * HomogenePose_In.HomogenePosenMatrix[0][3]
    - HomogenePose_In.HomogenePosenMatrix[2][2]
    * HomogenePose_In.HomogenePosenMatrix[1][3]
    * HomogenePose_In.HomogenePosenMatrix[0][1]
    - HomogenePose_In.HomogenePosenMatrix[2][3]
    * HomogenePose_In.HomogenePosenMatrix[1][1]
    * HomogenePose_In.HomogenePosenMatrix[0][2];

  det_A31 = HomogenePose_In.HomogenePosenMatrix[0][0]
    * HomogenePose_In.HomogenePosenMatrix[1][2]
    * HomogenePose_In.HomogenePosenMatrix[2][3]
    + HomogenePose_In.HomogenePosenMatrix[0][2]
    * HomogenePose_In.HomogenePosenMatrix[1][3]
    * HomogenePose_In.HomogenePosenMatrix[2][0]
    + HomogenePose_In.HomogenePosenMatrix[0][3]
    * HomogenePose_In.HomogenePosenMatrix[1][0]
    * HomogenePose_In.HomogenePosenMatrix[2][2]
    - HomogenePose_In.HomogenePosenMatrix[2][0]
    * HomogenePose_In.HomogenePosenMatrix[1][2]
    * HomogenePose_In.HomogenePosenMatrix[0][3]
    - HomogenePose_In.HomogenePosenMatrix[2][2]
    * HomogenePose_In.HomogenePosenMatrix[1][3]
    * HomogenePose_In.HomogenePosenMatrix[0][0]
    - HomogenePose_In.HomogenePosenMatrix[2][3]
    * HomogenePose_In.HomogenePosenMatrix[1][0]
    * HomogenePose_In.HomogenePosenMatrix[0][2];

  det_A32 = HomogenePose_In.HomogenePosenMatrix[0][0]
    * HomogenePose_In.HomogenePosenMatrix[1][1]
    * HomogenePose_In.HomogenePosenMatrix[2][3]
    + HomogenePose_In.HomogenePosenMatrix[0][1]
    * HomogenePose_In.HomogenePosenMatrix[1][3]
    * HomogenePose_In.HomogenePosenMatrix[2][0]
    + HomogenePose_In.HomogenePosenMatrix[0][3]
    * HomogenePose_In.HomogenePosenMatrix[1][0]
    * HomogenePose_In.HomogenePosenMatrix[2][1]
    - HomogenePose_In.HomogenePosenMatrix[2][0]
    * HomogenePose_In.HomogenePosenMatrix[1][1]
    * HomogenePose_In.HomogenePosenMatrix[0][3]
    - HomogenePose_In.HomogenePosenMatrix[2][1]
    * HomogenePose_In.HomogenePosenMatrix[1][3]
    * HomogenePose_In.HomogenePosenMatrix[0][0]
    - HomogenePose_In.HomogenePosenMatrix[2][3]
    * HomogenePose_In.HomogenePosenMatrix[1][0]
    * HomogenePose_In.HomogenePosenMatrix[0][1];

// Berechnung des translatorischen Anteils
  HomogenePoseMatrix_Out[0][3] = -det_A30;
  HomogenePoseMatrix_Out[1][3] = det_A31;
  HomogenePoseMatrix_Out[2][3] = -det_A32;
  }
void C_AbsolutePose::InversHomogenousPose (double (&HomogenePoseMatrix_In)[4][4], double (&HomogenePoseMatrix_Out)[4][4])
  {
  // Transpornieren des Anteils der Rotationsmatrix
  for (int i = 0; i < 3; i++)
    {
    for (int j = 0; j < 3; j++)
      {
      HomogenePoseMatrix_Out[i][j] = HomogenePoseMatrix_In[j][i];
      }
    }

  // Zuweisung der Zeile 3 der Posenmatrix
  HomogenePoseMatrix_Out[3][0] = 0;
  HomogenePoseMatrix_Out[3][1] = 0;
  HomogenePoseMatrix_Out[3][2] = 0;
  HomogenePoseMatrix_Out[3][3] = 1;

  // Berechnung benötigter Determinanten aus der Posenmatrix zur Bestimmung des
  // translatorischen Anteils
  double det_A30;
  double det_A31;
  double det_A32;

  det_A30 = HomogenePoseMatrix_In[0][1]
    * HomogenePoseMatrix_In[1][2]
    * HomogenePoseMatrix_In[2][3]
    + HomogenePoseMatrix_In[0][2]
    * HomogenePoseMatrix_In[1][3]
    * HomogenePoseMatrix_In[2][1]
    + HomogenePoseMatrix_In[0][3]
    * HomogenePoseMatrix_In[1][1]
    * HomogenePoseMatrix_In[2][2]
    - HomogenePoseMatrix_In[2][1]
    * HomogenePoseMatrix_In[1][2]
    * HomogenePoseMatrix_In[0][3]
    - HomogenePoseMatrix_In[2][2]
    * HomogenePoseMatrix_In[1][3]
    * HomogenePoseMatrix_In[0][1]
    - HomogenePoseMatrix_In[2][3]
    * HomogenePoseMatrix_In[1][1]
    * HomogenePoseMatrix_In[0][2];

  det_A31 = HomogenePoseMatrix_In[0][0]
    * HomogenePoseMatrix_In[1][2]
    * HomogenePoseMatrix_In[2][3]
    + HomogenePoseMatrix_In[0][2]
    * HomogenePoseMatrix_In[1][3]
    * HomogenePoseMatrix_In[2][0]
    + HomogenePoseMatrix_In[0][3]
    * HomogenePoseMatrix_In[1][0]
    * HomogenePoseMatrix_In[2][2]
    - HomogenePoseMatrix_In[2][0]
    * HomogenePoseMatrix_In[1][2]
    * HomogenePoseMatrix_In[0][3]
    - HomogenePoseMatrix_In[2][2]
    * HomogenePoseMatrix_In[1][3]
    * HomogenePoseMatrix_In[0][0]
    - HomogenePoseMatrix_In[2][3]
    * HomogenePoseMatrix_In[1][0]
    * HomogenePoseMatrix_In[0][2];

  det_A32 = HomogenePoseMatrix_In[0][0]
    * HomogenePoseMatrix_In[1][1]
    * HomogenePoseMatrix_In[2][3]
    + HomogenePoseMatrix_In[0][1]
    * HomogenePoseMatrix_In[1][3]
    * HomogenePoseMatrix_In[2][0]
    + HomogenePoseMatrix_In[0][3]
    * HomogenePoseMatrix_In[1][0]
    * HomogenePoseMatrix_In[2][1]
    - HomogenePoseMatrix_In[2][0]
    * HomogenePoseMatrix_In[1][1]
    * HomogenePoseMatrix_In[0][3]
    - HomogenePoseMatrix_In[2][1]
    * HomogenePoseMatrix_In[1][3]
    * HomogenePoseMatrix_In[0][0]
    - HomogenePoseMatrix_In[2][3]
    * HomogenePoseMatrix_In[1][0]
    * HomogenePoseMatrix_In[0][1];

// Berechnung des translatorischen Anteils
  HomogenePoseMatrix_Out[0][3] = -det_A30;
  HomogenePoseMatrix_Out[1][3] = det_A31;
  HomogenePoseMatrix_Out[2][3] = -det_A32;
  }
void C_AbsolutePose::clear()
  {
  for(int i=0; i< 4; i++)
    {
    for(int j=0; j< 4; j++)
      {
      this->HomogenePosenMatrix[i][j] = 0.0;
      this->HomogenePosenMatrixTempPuffer_1[i][j] = 0.0;
      this->HomogenePosenMatrixTempPuffer_2[i][j] = 0.0;
      this->HomogenePosenMatrixTempPuffer_3[i][j] = 0.0;
      }
    }

  this->HomogenePosenMatrix[3][3] = 1;
  this->HomogenePosenMatrixTempPuffer_1[3][3] = 1;
  this->HomogenePosenMatrixTempPuffer_2[3][3] = 1;
  this->HomogenePosenMatrixTempPuffer_3[3][3] = 1;

  }
/*********************************************Private Methoden*********************************************/
void C_AbsolutePose::BerechneExtrinsischRPY (double Euler_Psi, double Euler_Phi, double Euler_Chi)
  {
  this->nx (cos (Euler_Chi) * cos (Euler_Phi));
  this->ny (cos (Euler_Phi) * sin (Euler_Chi));
  this->nz (-sin (Euler_Phi));
  this->ox (cos (Euler_Chi) * sin (Euler_Phi) * sin (Euler_Psi) - cos (Euler_Psi) * sin (Euler_Chi));
  this->oy (sin (Euler_Chi) * sin (Euler_Phi) * sin (Euler_Psi) + cos (Euler_Chi) * cos (Euler_Psi));
  this->oz (cos (Euler_Phi) * sin (Euler_Psi));
  this->ax (cos (Euler_Chi) * cos (Euler_Psi) * sin (Euler_Phi) + sin (Euler_Chi) * sin (Euler_Psi));
  this->ay (cos (Euler_Psi) * sin (Euler_Chi) * sin (Euler_Phi) - cos (Euler_Chi) * sin (Euler_Psi));
  this->az (cos (Euler_Phi) * cos (Euler_Psi));
  }
/*********************************************** Klasse C_AbsolutePose ***********************************************/


/*********************************************** Klasse C_RelativePose ***********************************************/
/**************************************************** Kontruktoren ***************************************************/
C_RelativePose::C_RelativePose ()
  {
  for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
      {
      if (i == j)
        {
        this->Nullpose[i][j]            = 1.0;
        this->HomogenePosenMatrix[i][j] = 1.0;
        }
      else
        {
        this->Nullpose[i][j]            = 0.0;
        this->HomogenePosenMatrix[i][j] = 0.0;
        }
      }
    }

  for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
      {
      this->HomogenePosenMatrixTempPuffer_1[i][j] = 0.0;
      this->HomogenePosenMatrixTempPuffer_2[i][j] = 0.0;
      this->HomogenePosenMatrixTempPuffer_3[i][j] = 0.0;
      }
    }

  for (int i = 0; i < 6; i++)
    {
    for (int j = 0; j < 1; j++)
      {
      this->URPose_Puffer[i][j] = 0.0;
      }
    }

  this->RX_normiert = 0.0;
  this->RY_normiert = 0.0;
  this->RZ_normiert = 0.0;
  this->Epsilon     = 0.01;
  }
C_RelativePose::C_RelativePose (const C_RelativePose& RelativePose)
  {
  for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
      {
      this->HomogenePosenMatrix[i][j] = RelativePose.HomogenePosenMatrix[i][j];
      }
    }
  }
/***************************************************** Destruktor* ***************************************************/
C_RelativePose::~C_RelativePose ()
  {
  this->Epsilon     = 0.0;
  this->RZ_normiert = 0.0;
  this->RY_normiert = 0.0;
  this->RX_normiert = 0.0;

  for (int i = 0; i < 6; i++)
    {
    for (int j = 0; j < 1; j++)
      {
      this->URPose_Puffer[i][j] = 0.0;
      }
    }
  for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
      {
      this->HomogenePosenMatrixTempPuffer_3[i][j] = 0.0;
      this->HomogenePosenMatrixTempPuffer_2[i][j] = 0.0;
      this->HomogenePosenMatrixTempPuffer_1[i][j] = 0.0;
      this->HomogenePosenMatrix[i][j]             = 0.0;
      this->Nullpose[i][j]                        = 0.0;
      }
    }
  }

/*********************************************Öffentliche Methoden*********************************************/
void C_RelativePose::operator= (C_RelativePose RelativePose)
  {
  // Zuweisen der einzelnen Elemente der homogenen Pose
  for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
      {
      this->HomogenePosenMatrix[i][j] = RelativePose.HomogenePosenMatrix[i][j];
      }
    }
  }
void C_RelativePose::operator= (double (&NullposeMatrix)[4][4])
  {
  // Zuweisen der Matrixelemente der Nullpose = Einheitsmatrix
  for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
      {
      this->HomogenePosenMatrix[i][j] = NullposeMatrix[i][j];
      }
    }
  }
void C_RelativePose::operator= (C_URPose URPose)
  {
  // Aufruf der Umwandlungsmethode bei Nutzung des überladenen Operators
  this->URPoseToHomogenousPose (URPose,this->HomogenePosenMatrix);
  }
C_RelativePose C_RelativePose::operator* (C_RelativePose& RelativePose)
  {
  // Erzeugung eines neuen Objektes, welches als Return zurückgegeben wird.
  C_RelativePose HomogenePoseAusgabe;

  // Die Diagonale des zuvor erzeugten Objektes muss genullt werden, da
  // diese bei Objekterzeugung im Konstruktor mit 1 besetzt wird (Nullpose = Einheitsmatrix).
  for (int i = 0; i < 4; i++)
    {
    HomogenePoseAusgabe.HomogenePosenMatrix[i][i] = 0;
    }

  // Matrixmultiplikation
  for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
      {
      for (int k = 0; k < 4; k++)
        {
        // this->HomogenePosenMatrix[i][k] ist die Pose des Objektes, dass bei der Multiplikation
        // links des Multiplikationsoperator steht. RelativePose.HomogenePosenMatrix[k][j] ist die Pose
        // des Objektes, dass rechts des Multiplikationsoperator steht und als Parameter 
        // "C_RelativePose HomogenePoseAusgabe" an den überladenen Operator übergeben wird.
        HomogenePoseAusgabe.HomogenePosenMatrix[i][j] += this->HomogenePosenMatrix[i][k] * RelativePose.HomogenePosenMatrix[k][j];
        }
      }
    }

  // Ausgabe der im Objekt "C_RelativePose HomogenePoseAusgabe" gefüllten nmsp_posen-Matrix.
  return (HomogenePoseAusgabe);
  }
void C_RelativePose::operator*= (C_RelativePose& RelativePose)
  {
  // Sicherstellen, dass in "this->HomogenePosenMatrixTempPuffer_1"
  // keine Werte enthalten sind.
  for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
      {
      this->HomogenePosenMatrixTempPuffer_1[i][j] = 0.0;
      }
    }


  // Matrixmultiplikation
  for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
      {
      for (int k = 0; k < 4; k++)
        {
        // this->HomogenePosenMatrix[i][k] ist die Pose des Objektes, dass bei der Multiplikation
        // links des Multiplikationsoperator steht. RelativePose.HomogenePosenMatrix[k][j] ist die Pose
        // des Objektes, dass rechts des Multiplikationsoperator steht und als Parameter 
        // "C_RelativePose HomogenePoseAusgabe" an den überladenen Operator übergeben wird.
        this->HomogenePosenMatrixTempPuffer_1[i][j] += this->HomogenePosenMatrix[i][k] * RelativePose.HomogenePosenMatrix[k][j];
        }
      }
    }

  // Das in "this->HomogenePosenMatrixTempPuffer_1" zwischengespeicherte Ergebnis
  // nun in die "this->HomogenePosenMatrix" schreiben.
  for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
      {
      this->HomogenePosenMatrix[i][j] = this->HomogenePosenMatrixTempPuffer_1[i][j];
      }
    }
  }
C_RelativePose C_RelativePose::operator/ (C_RelativePose& RelativePose)
  {
  // Erzeugung eines neuen Objektes, welches als Return zurückgegeben wird.
  C_RelativePose HomogenePoseAusgabe;

  // Temporäre Umwandlung der RelativePose (Objekt rechts des Operators) in eine inverse homogene Pose.
  HomogenePoseAusgabe.InversHomogenousPose (RelativePose,HomogenePoseAusgabe.HomogenePosenMatrixTempPuffer_1);

  // Die Diagonale des zuvor erzeugten Objektes muss genullt werden, da
  // diese bei Objekterzeugung im Konstruktor mit 1 besetzt wird (Nullpose).
  for (int i = 0; i < 4; i++)
    {
    HomogenePoseAusgabe.HomogenePosenMatrix[i][i] = 0;
    }

  // Matrixmultiplikation
  for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
      {
      for (int k = 0; k < 4; k++)
        {
        // HomogenePoseAusgabe.HomogenePosenMatrixTempPuffer_1[k][j] ist die temporär umgewandelte Pose des Objektes,
        // dass bei der Division rechts des Divisionsoperator steht. this->HomogenePosenMatrix[i][k] ist die 
        // Pose des Objektes, dass links des Divisionsoperator steht.
        // Diese Multiplikation entspricht: A = B / C = B * C^-1
        HomogenePoseAusgabe.HomogenePosenMatrix[i][j] += this->HomogenePosenMatrix[i][k] * HomogenePoseAusgabe.HomogenePosenMatrixTempPuffer_1[k][j];
        }
      }
    }

  // Ausgabe der im Objekt "HomogenePoseAusgabe.HomogenePosenMatrix[i][j]" gefüllten nmsp_posen-Matrix.
  return (HomogenePoseAusgabe);
  }
void C_RelativePose::operator/= (C_RelativePose& RelativePose)
  {
  // Sicherstellen, dass in "this->HomogenePosenMatrixTempPuffer_1"
  // keine Werte enthalten sind.
  for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
      {
      this->HomogenePosenMatrixTempPuffer_1[i][j] = 0.0;
      }
    }

  // Temporäre Umwandlung der RelativePose (Objekt rechts des Operators) in eine inverse homogene Pose.
  this->InversHomogenousPose (RelativePose,RelativePose.HomogenePosenMatrixTempPuffer_1);

  // Matrixmultiplikation
  for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
      {
      for (int k = 0; k < 4; k++)
        {
        // RelativePose.HomogenePosenMatrixTempPuffer_1[k][j] ist die temporär umgewandelte Pose des Objektes,
        // dass bei der Division rechts des Divisionsoperator steht. this->HomogenePosenMatrix[i][k] ist die 
        // Pose des Objektes, dass links des Divisionsoperator steht.
        // Diese Multiplikation entspricht: A = B / C = B * C^-1
        this->HomogenePosenMatrixTempPuffer_1[i][j] += this->HomogenePosenMatrix[i][k] * RelativePose.HomogenePosenMatrixTempPuffer_1[k][j];
        }
      }
    }

  // Das in "this->HomogenePosenMatrixTempPuffer_1" zwischengespeicherte Ergebnis
  // nun in die "this->HomogenePosenMatrix" schreiben.
  for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
      {
      this->HomogenePosenMatrix[i][j] = this->HomogenePosenMatrixTempPuffer_1[i][j];
      }
    }
  }
C_RelativePose C_RelativePose::operator| (C_RelativePose& RelativePose)
  {
  // Erzeugung eines neuen Objektes, welches als Return zurückgegeben wird.
  C_RelativePose HomogenePoseAusgabe;

  // Temporäre Umwandlung der Homogenen Pose (Objekt links des Operators) in eine inverse homogene Pose.
  HomogenePoseAusgabe.InversHomogenousPose (*this,HomogenePoseAusgabe.HomogenePosenMatrixTempPuffer_1);

  // Die Diagonale des zuvor erzeugten Objektes muss genullt werden, da
  // diese bei Objekterzeugung im Konstruktor mit 1 besetzt wird (Nullpose).
  for (int i = 0; i < 4; i++)
    {
    HomogenePoseAusgabe.HomogenePosenMatrix[i][i] = 0;
    }

  // Matrixmultiplikation
  for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
      {
      for (int k = 0; k < 4; k++)
        {
        // HomogenePoseAusgabe.HomogenePosenMatrixTempPuffer_1[i][k] ist die temporär umgewandelte Pose des Objektes,
        // dass bei der Division links des Divisionsoperator steht. RelativePose.HomogenePosenMatrix[k][j] ist die 
        // Pose des Objektes, dass rechts des Divisionsoperator steht und als Parameter an den überladenen Operator übergeben wird.
        // Diese Multiplikation entspricht: A = B \ C = B^-1 * C
        HomogenePoseAusgabe.HomogenePosenMatrix[i][j] += HomogenePoseAusgabe.HomogenePosenMatrixTempPuffer_1[i][k] * RelativePose.HomogenePosenMatrix[k][j];
        }
      }
    }

  // Ausgabe der im Objekt "HomogenePoseAusgabe.HomogenePosenMatrix[i][j]" gefüllten nmsp_posen-Matrix.
  return (HomogenePoseAusgabe);
  }
void C_RelativePose::operator|= (C_RelativePose& RelativePose)
  {
  // Temporäre Umwandlung der Homogenen Pose (Objekt links des Operators) in eine inverse homogene Pose.
  this->InversHomogenousPose (*this,this->HomogenePosenMatrixTempPuffer_1);

  // Sicherstellen, dass in "this->HomogenePosenMatrixTempPuffer_1"
  // keine Werte enthalten sind.
  for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
      {
      this->HomogenePosenMatrixTempPuffer_2[i][j] = 0.0;
      }
    }

  // Matrixmultiplikation
  for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
      {
      for (int k = 0; k < 4; k++)
        {
        // this->HomogenePosenMatrixTempPuffer_1[i][k] ist die temporär umgewandelte Pose des Objektes,
        // dass bei der Division links des Divisionsoperator steht. RelativePose.HomogenePosenMatrix[k][j] ist die 
        // Pose des Objektes, dass rechts des Divisionsoperator steht und als Parameter an den überladenen Operator übergeben wird.
        // Diese Multiplikation entspricht: A = B \ C = B^-1 * C
        this->HomogenePosenMatrixTempPuffer_2[i][j] += this->HomogenePosenMatrixTempPuffer_1[i][k] * RelativePose.HomogenePosenMatrix[k][j];
        }
      }
    }

  // Das in "this->HomogenePosenMatrixTempPuffer_2" zwischengespeicherte Ergebnis
  // nun in die "this->HomogenePosenMatrix" schreiben.
  for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
      {
      this->HomogenePosenMatrix[i][j] = this->HomogenePosenMatrixTempPuffer_1[i][j];
      }
    }
  }
void C_RelativePose::URPoseToHomogenousPose (C_URPose& URPose, double (&HomogenePoseMatrix)[4][4])
  {
  // Betrag des Rotationsvektor = Drehwinkel um beliebige Achse [rad]
  double Drehwinkel = sqrt (pow (URPose.RX,2) + pow (URPose.RY,2) + pow (URPose.RZ,2));

  // Einheitsrichtungsvektor des Rotationsvektor, welcher für die Umrechnung
  // in homogene Koordinaten benötigt wird.
  this->RX_normiert = URPose.RX / Drehwinkel;
  this->RY_normiert = URPose.RY / Drehwinkel;
  this->RZ_normiert = URPose.RZ / Drehwinkel;

  // Zuweisung der Zeile 3 der Posenmatrix
  HomogenePoseMatrix[3][0] = 0;
  HomogenePoseMatrix[3][1] = 0;
  HomogenePoseMatrix[3][2] = 0;
  HomogenePoseMatrix[3][3] = 1;

  // Zuweisung des Positionsvektors der Posenmatrix
  HomogenePoseMatrix[0][3] = URPose.X;
  HomogenePoseMatrix[1][3] = URPose.Y;
  HomogenePoseMatrix[2][3] = URPose.Z;

  // Beschreibung Rotationsmatrix siehe: Lothar Zunker - 
  // Transputerbasierter Lichtschnittsensor als Baustein eines
  // Multisensor-Steuerungskonzepts zur Echtzeit-Schweißprozessführung
  // und seine Integration in ein Roboterschweißsystem
  HomogenePoseMatrix[0][0] = pow (this->RX_normiert,2)
    * (1 - cos (Drehwinkel))
    + cos (Drehwinkel);
  HomogenePoseMatrix[0][1] = this->RX_normiert
    * this->RY_normiert
    * (1 - cos (Drehwinkel))
    - this->RZ_normiert
    * sin (Drehwinkel);
  HomogenePoseMatrix[0][2] = this->RX_normiert
    * this->RZ_normiert
    * (1 - cos (Drehwinkel))
    + this->RY_normiert
    * sin (Drehwinkel);
  HomogenePoseMatrix[1][0] = this->RX_normiert
    * this->RY_normiert
    * (1 - cos (Drehwinkel))
    + this->RZ_normiert
    * sin (Drehwinkel);
  HomogenePoseMatrix[1][1] = pow (this->RY_normiert,2)
    * (1 - cos (Drehwinkel))
    + cos (Drehwinkel);
  HomogenePoseMatrix[1][2] = this->RY_normiert
    * this->RZ_normiert
    * (1 - cos (Drehwinkel))
    - this->RX_normiert
    * sin (Drehwinkel);
  HomogenePoseMatrix[2][0] = this->RX_normiert
    * this->RZ_normiert
    * (1 - cos (Drehwinkel))
    - this->RY_normiert
    * sin (Drehwinkel);
  HomogenePoseMatrix[2][1] = this->RY_normiert
    * this->RZ_normiert
    * (1 - cos (Drehwinkel))
    + this->RX_normiert
    * sin (Drehwinkel);
  HomogenePoseMatrix[2][2] = pow (this->RZ_normiert,2)
    * (1 - cos (Drehwinkel))
    + cos (Drehwinkel);
  }
void C_RelativePose::URPoseToHomogenousPose (double (&URPoseMatrix)[6][1], double (&HomogenePoseMatrix)[4][4])
  {
  // Betrag des Rotationsvektor = Drehwinkel um beliebige Achse [rad]
  double Drehwinkel = sqrt (pow (URPoseMatrix[3][0],2) + pow (URPoseMatrix[4][0],2) + pow (URPoseMatrix[5][0],2));

  // Einheitsrichtungsvektor des Rotationsvektor, welcher für die Umrechnung
  // in homogene Koordinaten benötigt wird.
  this->RX_normiert = URPoseMatrix[3][0] / Drehwinkel;
  this->RY_normiert = URPoseMatrix[4][0] / Drehwinkel;
  this->RZ_normiert = URPoseMatrix[5][0] / Drehwinkel;

  // Zuweisung der Zeile 3 der Posenmatrix
  HomogenePoseMatrix[3][0] = 0;
  HomogenePoseMatrix[3][1] = 0;
  HomogenePoseMatrix[3][2] = 0;
  HomogenePoseMatrix[3][3] = 1;

  // Zuweisung des Positionsvektors der Posenmatrix
  HomogenePoseMatrix[0][3] = URPoseMatrix[0][0];
  HomogenePoseMatrix[1][3] = URPoseMatrix[1][0];
  HomogenePoseMatrix[2][3] = URPoseMatrix[2][0];

  // Beschreibung Rotationsmatrix siehe: Lothar Zunker -
  // Transputerbasierter Lichtschnittsensor als Baustein eines
  // Multisensor-Steuerungskonzepts zur Echtzeit-Schweißprozessführung
  // und seine Integration in ein Roboterschweißsystem
  HomogenePoseMatrix[0][0] = pow (this->RX_normiert,2)
    * (1 - cos (Drehwinkel))
    + cos (Drehwinkel);
  HomogenePoseMatrix[0][1] = this->RX_normiert
    * this->RY_normiert
    * (1 - cos (Drehwinkel))
    - this->RZ_normiert
    * sin (Drehwinkel);
  HomogenePoseMatrix[0][2] = this->RX_normiert
    * this->RZ_normiert
    * (1 - cos (Drehwinkel))
    + this->RY_normiert
    * sin (Drehwinkel);
  HomogenePoseMatrix[1][0] = this->RX_normiert
    * this->RY_normiert
    * (1 - cos (Drehwinkel))
    + this->RZ_normiert
    * sin (Drehwinkel);
  HomogenePoseMatrix[1][1] = pow (this->RY_normiert,2)
    * (1 - cos (Drehwinkel))
    + cos (Drehwinkel);
  HomogenePoseMatrix[1][2] = this->RY_normiert
    * this->RZ_normiert
    * (1 - cos (Drehwinkel))
    - this->RX_normiert
    * sin (Drehwinkel);
  HomogenePoseMatrix[2][0] = this->RX_normiert
    * this->RZ_normiert
    * (1 - cos (Drehwinkel))
    - this->RY_normiert
    * sin (Drehwinkel);
  HomogenePoseMatrix[2][1] = this->RY_normiert
    * this->RZ_normiert
    * (1 - cos (Drehwinkel))
    + this->RX_normiert
    * sin (Drehwinkel);
  HomogenePoseMatrix[2][2] = pow (this->RZ_normiert,2)
    * (1 - cos (Drehwinkel))
    + cos (Drehwinkel);
  }
void C_RelativePose::InversHomogenousPose (C_AbsolutePose& HomogenePose_In, double (&HomogenePoseMatrix_Out)[4][4])
  {
  // Transpornieren des Anteils der Rotationsmatrix
  for (int i = 0; i < 3; i++)
    {
    for (int j = 0; j < 3; j++)
      {
      HomogenePoseMatrix_Out[i][j] = HomogenePose_In.HomogenePosenMatrix[j][i];
      }
    }

  // Zuweisung der Zeile 3 der Posenmatrix
  HomogenePoseMatrix_Out[3][0] = 0;
  HomogenePoseMatrix_Out[3][1] = 0;
  HomogenePoseMatrix_Out[3][2] = 0;
  HomogenePoseMatrix_Out[3][3] = 1;

  // Berechnung benötigter Determinanten aus der Posenmatrix zur Bestimmung des
  // translatorischen Anteils
  double det_A30;
  double det_A31;
  double det_A32;

  det_A30 = HomogenePose_In.HomogenePosenMatrix[0][1]
    * HomogenePose_In.HomogenePosenMatrix[1][2]
    * HomogenePose_In.HomogenePosenMatrix[2][3]
    + HomogenePose_In.HomogenePosenMatrix[0][2]
    * HomogenePose_In.HomogenePosenMatrix[1][3]
    * HomogenePose_In.HomogenePosenMatrix[2][1]
    + HomogenePose_In.HomogenePosenMatrix[0][3]
    * HomogenePose_In.HomogenePosenMatrix[1][1]
    * HomogenePose_In.HomogenePosenMatrix[2][2]
    - HomogenePose_In.HomogenePosenMatrix[2][1]
    * HomogenePose_In.HomogenePosenMatrix[1][2]
    * HomogenePose_In.HomogenePosenMatrix[0][3]
    - HomogenePose_In.HomogenePosenMatrix[2][2]
    * HomogenePose_In.HomogenePosenMatrix[1][3]
    * HomogenePose_In.HomogenePosenMatrix[0][1]
    - HomogenePose_In.HomogenePosenMatrix[2][3]
    * HomogenePose_In.HomogenePosenMatrix[1][1]
    * HomogenePose_In.HomogenePosenMatrix[0][2];

  det_A31 = HomogenePose_In.HomogenePosenMatrix[0][0]
    * HomogenePose_In.HomogenePosenMatrix[1][2]
    * HomogenePose_In.HomogenePosenMatrix[2][3]
    + HomogenePose_In.HomogenePosenMatrix[0][2]
    * HomogenePose_In.HomogenePosenMatrix[1][3]
    * HomogenePose_In.HomogenePosenMatrix[2][0]
    + HomogenePose_In.HomogenePosenMatrix[0][3]
    * HomogenePose_In.HomogenePosenMatrix[1][0]
    * HomogenePose_In.HomogenePosenMatrix[2][2]
    - HomogenePose_In.HomogenePosenMatrix[2][0]
    * HomogenePose_In.HomogenePosenMatrix[1][2]
    * HomogenePose_In.HomogenePosenMatrix[0][3]
    - HomogenePose_In.HomogenePosenMatrix[2][2]
    * HomogenePose_In.HomogenePosenMatrix[1][3]
    * HomogenePose_In.HomogenePosenMatrix[0][0]
    - HomogenePose_In.HomogenePosenMatrix[2][3]
    * HomogenePose_In.HomogenePosenMatrix[1][0]
    * HomogenePose_In.HomogenePosenMatrix[0][2];

  det_A32 = HomogenePose_In.HomogenePosenMatrix[0][0]
    * HomogenePose_In.HomogenePosenMatrix[1][1]
    * HomogenePose_In.HomogenePosenMatrix[2][3]
    + HomogenePose_In.HomogenePosenMatrix[0][1]
    * HomogenePose_In.HomogenePosenMatrix[1][3]
    * HomogenePose_In.HomogenePosenMatrix[2][0]
    + HomogenePose_In.HomogenePosenMatrix[0][3]
    * HomogenePose_In.HomogenePosenMatrix[1][0]
    * HomogenePose_In.HomogenePosenMatrix[2][1]
    - HomogenePose_In.HomogenePosenMatrix[2][0]
    * HomogenePose_In.HomogenePosenMatrix[1][1]
    * HomogenePose_In.HomogenePosenMatrix[0][3]
    - HomogenePose_In.HomogenePosenMatrix[2][1]
    * HomogenePose_In.HomogenePosenMatrix[1][3]
    * HomogenePose_In.HomogenePosenMatrix[0][0]
    - HomogenePose_In.HomogenePosenMatrix[2][3]
    * HomogenePose_In.HomogenePosenMatrix[1][0]
    * HomogenePose_In.HomogenePosenMatrix[0][1];

// Berechnung des translatorischen Anteils
  HomogenePoseMatrix_Out[0][3] = -det_A30;
  HomogenePoseMatrix_Out[1][3] = det_A31;
  HomogenePoseMatrix_Out[2][3] = -det_A32;
  }
void C_RelativePose::InversHomogenousPose (C_RelativePose& HomogenePose_In, double (&HomogenePoseMatrix_Out)[4][4])
  {
  // Transpornieren des Anteils der Rotationsmatrix
  for (int i = 0; i < 3; i++)
    {
    for (int j = 0; j < 3; j++)
      {
      HomogenePoseMatrix_Out[i][j] = HomogenePose_In.HomogenePosenMatrix[j][i];
      }
    }

  // Zuweisung der Zeile 3 der Posenmatrix
  HomogenePoseMatrix_Out[3][0] = 0;
  HomogenePoseMatrix_Out[3][1] = 0;
  HomogenePoseMatrix_Out[3][2] = 0;
  HomogenePoseMatrix_Out[3][3] = 1;

  // Berechnung benötigter Determinanten aus der Posenmatrix zur Bestimmung des
  // translatorischen Anteils
  double det_A30;
  double det_A31;
  double det_A32;

  det_A30 = HomogenePose_In.HomogenePosenMatrix[0][1]
    * HomogenePose_In.HomogenePosenMatrix[1][2]
    * HomogenePose_In.HomogenePosenMatrix[2][3]
    + HomogenePose_In.HomogenePosenMatrix[0][2]
    * HomogenePose_In.HomogenePosenMatrix[1][3]
    * HomogenePose_In.HomogenePosenMatrix[2][1]
    + HomogenePose_In.HomogenePosenMatrix[0][3]
    * HomogenePose_In.HomogenePosenMatrix[1][1]
    * HomogenePose_In.HomogenePosenMatrix[2][2]
    - HomogenePose_In.HomogenePosenMatrix[2][1]
    * HomogenePose_In.HomogenePosenMatrix[1][2]
    * HomogenePose_In.HomogenePosenMatrix[0][3]
    - HomogenePose_In.HomogenePosenMatrix[2][2]
    * HomogenePose_In.HomogenePosenMatrix[1][3]
    * HomogenePose_In.HomogenePosenMatrix[0][1]
    - HomogenePose_In.HomogenePosenMatrix[2][3]
    * HomogenePose_In.HomogenePosenMatrix[1][1]
    * HomogenePose_In.HomogenePosenMatrix[0][2];

  det_A31 = HomogenePose_In.HomogenePosenMatrix[0][0]
    * HomogenePose_In.HomogenePosenMatrix[1][2]
    * HomogenePose_In.HomogenePosenMatrix[2][3]
    + HomogenePose_In.HomogenePosenMatrix[0][2]
    * HomogenePose_In.HomogenePosenMatrix[1][3]
    * HomogenePose_In.HomogenePosenMatrix[2][0]
    + HomogenePose_In.HomogenePosenMatrix[0][3]
    * HomogenePose_In.HomogenePosenMatrix[1][0]
    * HomogenePose_In.HomogenePosenMatrix[2][2]
    - HomogenePose_In.HomogenePosenMatrix[2][0]
    * HomogenePose_In.HomogenePosenMatrix[1][2]
    * HomogenePose_In.HomogenePosenMatrix[0][3]
    - HomogenePose_In.HomogenePosenMatrix[2][2]
    * HomogenePose_In.HomogenePosenMatrix[1][3]
    * HomogenePose_In.HomogenePosenMatrix[0][0]
    - HomogenePose_In.HomogenePosenMatrix[2][3]
    * HomogenePose_In.HomogenePosenMatrix[1][0]
    * HomogenePose_In.HomogenePosenMatrix[0][2];

  det_A32 = HomogenePose_In.HomogenePosenMatrix[0][0]
    * HomogenePose_In.HomogenePosenMatrix[1][1]
    * HomogenePose_In.HomogenePosenMatrix[2][3]
    + HomogenePose_In.HomogenePosenMatrix[0][1]
    * HomogenePose_In.HomogenePosenMatrix[1][3]
    * HomogenePose_In.HomogenePosenMatrix[2][0]
    + HomogenePose_In.HomogenePosenMatrix[0][3]
    * HomogenePose_In.HomogenePosenMatrix[1][0]
    * HomogenePose_In.HomogenePosenMatrix[2][1]
    - HomogenePose_In.HomogenePosenMatrix[2][0]
    * HomogenePose_In.HomogenePosenMatrix[1][1]
    * HomogenePose_In.HomogenePosenMatrix[0][3]
    - HomogenePose_In.HomogenePosenMatrix[2][1]
    * HomogenePose_In.HomogenePosenMatrix[1][3]
    * HomogenePose_In.HomogenePosenMatrix[0][0]
    - HomogenePose_In.HomogenePosenMatrix[2][3]
    * HomogenePose_In.HomogenePosenMatrix[1][0]
    * HomogenePose_In.HomogenePosenMatrix[0][1];

// Berechnung des translatorischen Anteils
  HomogenePoseMatrix_Out[0][3] = -det_A30;
  HomogenePoseMatrix_Out[1][3] = det_A31;
  HomogenePoseMatrix_Out[2][3] = -det_A32;
  }
void C_RelativePose::InversHomogenousPose (double (&HomogenePoseMatrix_In)[4][4], double (&HomogenePoseMatrix_Out)[4][4])
  {
  // Transpornieren des Anteils der Rotationsmatrix
  for (int i = 0; i < 3; i++)
    {
    for (int j = 0; j < 3; j++)
      {
      HomogenePoseMatrix_Out[i][j] = HomogenePoseMatrix_In[j][i];
      }
    }

  // Zuweisung der Zeile 3 der Posenmatrix
  HomogenePoseMatrix_Out[3][0] = 0;
  HomogenePoseMatrix_Out[3][1] = 0;
  HomogenePoseMatrix_Out[3][2] = 0;
  HomogenePoseMatrix_Out[3][3] = 1;

  // Berechnung benötigter Determinanten aus der Posenmatrix zur Bestimmung des
  // translatorischen Anteils
  double det_A30;
  double det_A31;
  double det_A32;

  det_A30 = HomogenePoseMatrix_In[0][1]
    * HomogenePoseMatrix_In[1][2]
    * HomogenePoseMatrix_In[2][3]
    + HomogenePoseMatrix_In[0][2]
    * HomogenePoseMatrix_In[1][3]
    * HomogenePoseMatrix_In[2][1]
    + HomogenePoseMatrix_In[0][3]
    * HomogenePoseMatrix_In[1][1]
    * HomogenePoseMatrix_In[2][2]
    - HomogenePoseMatrix_In[2][1]
    * HomogenePoseMatrix_In[1][2]
    * HomogenePoseMatrix_In[0][3]
    - HomogenePoseMatrix_In[2][2]
    * HomogenePoseMatrix_In[1][3]
    * HomogenePoseMatrix_In[0][1]
    - HomogenePoseMatrix_In[2][3]
    * HomogenePoseMatrix_In[1][1]
    * HomogenePoseMatrix_In[0][2];

  det_A31 = HomogenePoseMatrix_In[0][0]
    * HomogenePoseMatrix_In[1][2]
    * HomogenePoseMatrix_In[2][3]
    + HomogenePoseMatrix_In[0][2]
    * HomogenePoseMatrix_In[1][3]
    * HomogenePoseMatrix_In[2][0]
    + HomogenePoseMatrix_In[0][3]
    * HomogenePoseMatrix_In[1][0]
    * HomogenePoseMatrix_In[2][2]
    - HomogenePoseMatrix_In[2][0]
    * HomogenePoseMatrix_In[1][2]
    * HomogenePoseMatrix_In[0][3]
    - HomogenePoseMatrix_In[2][2]
    * HomogenePoseMatrix_In[1][3]
    * HomogenePoseMatrix_In[0][0]
    - HomogenePoseMatrix_In[2][3]
    * HomogenePoseMatrix_In[1][0]
    * HomogenePoseMatrix_In[0][2];

  det_A32 = HomogenePoseMatrix_In[0][0]
    * HomogenePoseMatrix_In[1][1]
    * HomogenePoseMatrix_In[2][3]
    + HomogenePoseMatrix_In[0][1]
    * HomogenePoseMatrix_In[1][3]
    * HomogenePoseMatrix_In[2][0]
    + HomogenePoseMatrix_In[0][3]
    * HomogenePoseMatrix_In[1][0]
    * HomogenePoseMatrix_In[2][1]
    - HomogenePoseMatrix_In[2][0]
    * HomogenePoseMatrix_In[1][1]
    * HomogenePoseMatrix_In[0][3]
    - HomogenePoseMatrix_In[2][1]
    * HomogenePoseMatrix_In[1][3]
    * HomogenePoseMatrix_In[0][0]
    - HomogenePoseMatrix_In[2][3]
    * HomogenePoseMatrix_In[1][0]
    * HomogenePoseMatrix_In[0][1];

// Berechnung des translatorischen Anteils
  HomogenePoseMatrix_Out[0][3] = -det_A30;
  HomogenePoseMatrix_Out[1][3] = det_A31;
  HomogenePoseMatrix_Out[2][3] = -det_A32;
  }
void C_RelativePose::clear()
  {
  for(int i=0; i< 4; i++)
    {
    for(int j=0; j< 4; j++)
      {
      this->HomogenePosenMatrix[i][j] = 0.0;
      this->HomogenePosenMatrixTempPuffer_1[i][j] = 0.0;
      this->HomogenePosenMatrixTempPuffer_2[i][j] = 0.0;
      this->HomogenePosenMatrixTempPuffer_3[i][j] = 0.0;
      }
    }

  this->HomogenePosenMatrix[3][3] = 1;
  this->HomogenePosenMatrixTempPuffer_1[3][3] = 1;
  this->HomogenePosenMatrixTempPuffer_2[3][3] = 1;
  this->HomogenePosenMatrixTempPuffer_3[3][3] = 1;
  }
/*********************************************Private Methoden*********************************************/
void C_RelativePose::BerechneExtrinsischRPY (double Euler_Psi, double Euler_Phi, double Euler_Chi)
  {
  this->nx (cos (Euler_Chi) * cos (Euler_Phi));
  this->ny (cos (Euler_Phi) * sin (Euler_Chi));
  this->nz (-sin (Euler_Phi));
  this->ox (cos (Euler_Chi) * sin (Euler_Phi) * sin (Euler_Psi) - cos (Euler_Psi) * sin (Euler_Chi));
  this->oy (sin (Euler_Chi) * sin (Euler_Phi) * sin (Euler_Psi) + cos (Euler_Chi) * cos (Euler_Psi));
  this->oz (cos (Euler_Phi) * sin (Euler_Psi));
  this->ax (cos (Euler_Chi) * cos (Euler_Psi) * sin (Euler_Phi) + sin (Euler_Chi) * sin (Euler_Psi));
  this->ay (cos (Euler_Psi) * sin (Euler_Chi) * sin (Euler_Phi) - cos (Euler_Chi) * sin (Euler_Psi));
  this->az (cos (Euler_Phi) * cos (Euler_Psi));
  }
/*********************************************** Klasse C_RelativePose ***********************************************/


/*********************************************** Klasse C_URPose ***********************************************/
/**************************************************** Kontruktoren ***************************************************/
C_URPose::C_URPose ()
  {
  for (int i = 0; i < 6; i++)
    {
    for (int j = 0; j < 1; j++)
      {
      this->Nullpose[i][j] = 0.0;
      }
    }

  this->X  = 0.0;
  this->Y  = 0.0;
  this->Z  = 0.0;
  this->RX = 0.0;
  this->RY = 0.0;
  this->RZ = 0.0;

  for (int i = 0; i < 6; i++)
    {
    for (int j = 0; j < 1; j++)
      {
      this->URPose_Puffer[i][j] = 0.0;
      }
    }

  for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
      {
      this->HomogenePosenMatrixTempPuffer[i][j] = 0.0;
      }
    }
  }
C_URPose::C_URPose (const C_URPose& URPose)
  {
  this->X  = URPose.X;
  this->Y  = URPose.Y;
  this->Z  = URPose.Z;
  this->RX = URPose.RX;
  this->RY = URPose.RY;
  this->RZ = URPose.RZ;
  }
/***************************************************** Destruktor* ***************************************************/
C_URPose::~C_URPose ()
  {
  for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
      {
      this->HomogenePosenMatrixTempPuffer[i][j] = 0.0;
      }
    }

  for (int i = 0; i < 6; i++)
    {
    for (int j = 0; j < 1; j++)
      {
      this->URPose_Puffer[i][j] = 0.0;
      this->Nullpose[i][j]      = 0.0;
      }
    }

  this->RZ = 0.0;
  this->RY = 0.0;
  this->RX = 0.0;
  this->Z  = 0.0;
  this->Y  = 0.0;
  this->X  = 0.0;
  }

/*********************************************Öffentliche Methoden*********************************************/
void C_URPose::operator= (C_URPose URPose)
  {
  // Zuweisen der Posenwerte der beiden UR-nmsp_posen
  this->X  = URPose.X;
  this->Y  = URPose.Y;
  this->Z  = URPose.Z;
  this->RX = URPose.RX;
  this->RY = URPose.RY;
  this->RZ = URPose.RZ;
  }
void C_URPose::operator= (S_PoseWerte& URPose)
  {
  // Zuweisen der Posenwerte der beiden UR-nmsp_posen
  this->X  = URPose.X;
  this->Y  = URPose.Y;
  this->Z  = URPose.Z;
  this->RX = URPose.RX;
  this->RY = URPose.RY;
  this->RZ = URPose.RZ;
  }
void C_URPose::operator= (C_AbsolutePose AbsolutePose)
  {
  // Aufruf der Umwandlungsmethode bei Nutzung des überladenen Operators
  //this->HomogenousPoseToURPose_Eigen(AbsolutePose);
  this->HomogenousPoseToURPose (AbsolutePose);
  }
void C_URPose::operator= (C_RelativePose RelativePose)
  {
  // Aufruf der Umwandlungsmethode bei Nutzung des überladenen Operators
  //this->HomogenousPoseToURPose_Eigen(AbsolutePose);
  this->HomogenousPoseToURPose (RelativePose);
  }
void C_URPose::operator= (double (&NullposeMatrix)[6][1])
  {
  // Zuweisen der Nullpose
  this->X  = NullposeMatrix[0][0];
  this->Y  = NullposeMatrix[1][0];
  this->Z  = NullposeMatrix[2][0];
  this->RX = NullposeMatrix[3][0];
  this->RY = NullposeMatrix[4][0];
  this->RZ = NullposeMatrix[5][0];
  }
C_AbsolutePose C_URPose::operator* (C_RelativePose& RelativePose)
  {
  // Erzeugung eines neuen Objektes, welches als Return zurückgegeben wird.
  C_AbsolutePose HomogenePoseAusgabe;

  // Temporäre Umwandlung der URPose (Objekt links des Operators) in eine homogene Pose.
  HomogenePoseAusgabe.URPoseToHomogenousPose (*this,HomogenePoseAusgabe.HomogenePosenMatrixTempPuffer_1);

  // Die Diagonale des zuvor erzeugten Objektes muss genullt werden, da
  // diese bei Objekterzeugung im Konstruktor mit 1 besetzt wird (Nullpose).
  for (int i = 0; i < 4; i++)
    {
    HomogenePoseAusgabe.HomogenePosenMatrix[i][i] = 0;
    }

  // Matrixmultiplikation
  for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
      {
      for (int k = 0; k < 4; k++)
        {
        // HomogenePoseAusgabe.HomogenePosenMatrixTempPuffer_1[i][k] ist die temporär umgewandelte Pose des Objektes,
        // dass bei der Multiplikation links des Multiplikationsoperator steht. AbsolutePose.HomogenePosenMatrix[k][j] ist die 
        // Pose des Objektes, dass rechts des Multiplikationsoperator steht und als Parameter an den überladenen Operator übergeben wird.
        HomogenePoseAusgabe.HomogenePosenMatrix[i][j] += HomogenePoseAusgabe.HomogenePosenMatrixTempPuffer_1[i][k] * RelativePose.HomogenePosenMatrix[k][j];
        }
      }
    }

  // Ausgabe der im Objekt "HomogenePoseAusgabe.HomogenePosenMatrix[i][j]" gefüllten nmsp_posen-Matrix.
  return (HomogenePoseAusgabe);
  }
C_AbsolutePose C_URPose::operator/ (C_RelativePose& RelativePose)
  {
  // Erzeugung eines neuen Objektes, welches als Return zurückgegeben wird.
  C_AbsolutePose HomogenePoseAusgabe;

  // Temporäre Umwandlung der URPose (Objekt links des Operators) in eine homogene Pose.
  HomogenePoseAusgabe.URPoseToHomogenousPose (*this,HomogenePoseAusgabe.HomogenePosenMatrixTempPuffer_1);

  // Temporäre Umwandlung der RelativePose (Objekt rechts des Operators) in eine inverse homogene Pose.
  HomogenePoseAusgabe.InversHomogenousPose (RelativePose,HomogenePoseAusgabe.HomogenePosenMatrixTempPuffer_2);

  // Die Diagonale des zuvor erzeugten Objektes muss genullt werden, da
  // diese bei Objekterzeugung im Konstruktor mit 1 besetzt wird (Nullpose).
  for (int i = 0; i < 4; i++)
    {
    HomogenePoseAusgabe.HomogenePosenMatrix[i][i] = 0;
    }

  // Matrixmultiplikation

  for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
      {
      for (int k = 0; k < 4; k++)
        {
        // HomogenePoseAusgabe.HomogenePosenMatrixTempPuffer_1[i][k] ist die temporär umgewandelte Pose des Objektes,
        // dass bei der Division links des Divisionsoperator steht. HomogenePoseAusgabe.HomogenePosenMatrixTempPuffer_2[k][j] ist die 
        // Pose des Objektes, dass rechts des Divisionsoperator steht.
        // Diese Multiplikation entspricht: A = B / C = B * C^-1
        HomogenePoseAusgabe.HomogenePosenMatrix[i][j] += HomogenePoseAusgabe.HomogenePosenMatrixTempPuffer_1[i][k] * HomogenePoseAusgabe.HomogenePosenMatrixTempPuffer_2[k][j];
        }
      }
    }

  // Ausgabe der im Objekt "HomogenePoseAusgabe.HomogenePosenMatrix[i][j]" gefüllten nmsp_posen-Matrix.
  return (HomogenePoseAusgabe);
  }
C_RelativePose C_URPose::operator| (C_AbsolutePose& AbsolutePose)
  {
  // Erzeugung eines neuen Objektes, welches als Return zurückgegeben wird.
  C_RelativePose HomogenePoseAusgabe;

  // Temporäre Umwandlung der URPose (Objekt links des Operators) in eine homogene
  // Pose und anschließend in eine inverse homogene Pose.
  HomogenePoseAusgabe.URPoseToHomogenousPose (*this,HomogenePoseAusgabe.HomogenePosenMatrixTempPuffer_1);
  HomogenePoseAusgabe.InversHomogenousPose (HomogenePoseAusgabe.HomogenePosenMatrixTempPuffer_1,HomogenePoseAusgabe.HomogenePosenMatrixTempPuffer_2);

  // Die Diagonale des zuvor erzeugten Objektes muss genullt werden, da
  // diese bei Objekterzeugung im Konstruktor mit 1 besetzt wird (Nullpose).
  for (int i = 0; i < 4; i++)
    {
    HomogenePoseAusgabe.HomogenePosenMatrix[i][i] = 0;
    }

  // Matrixmultiplikation

  for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
      {
      for (int k = 0; k < 4; k++)
        {
        // HomogenePoseAusgabe.HomogenePosenMatrixTempPuffer_2[i][k] ist die temporär umgewandelte Pose des Objektes,
        // dass bei der Division links des Divisionsoperator steht. AbsolutePose.HomogenePosenMatrix[k][j] ist die 
        // Pose des Objektes, dass rechts des Divisionsoperator steht.
        // Diese Multiplikation entspricht: A = B \ C = B^-1 * C
        HomogenePoseAusgabe.HomogenePosenMatrix[i][j] += HomogenePoseAusgabe.HomogenePosenMatrixTempPuffer_2[i][k] * AbsolutePose.HomogenePosenMatrix[k][j];
        }
      }
    }

  // Ausgabe der im Objekt "HomogenePoseAusgabe.HomogenePosenMatrix[i][j]" gefüllten nmsp_posen-Matrix.
  return (HomogenePoseAusgabe);
  }
C_RelativePose C_URPose::operator| (C_URPose& URPose)
  {
  // Erzeugung eines neuen Objektes, welches als Return zurückgegeben wird.
  C_RelativePose HomogenePoseAusgabe;

  // Temporäre Umwandlung der URPose (Objekt links des Operators) in eine homogene
  // Pose und anschließend in eine inverse homogene Pose.
  HomogenePoseAusgabe.URPoseToHomogenousPose (*this,HomogenePoseAusgabe.HomogenePosenMatrixTempPuffer_1);
  HomogenePoseAusgabe.InversHomogenousPose (HomogenePoseAusgabe.HomogenePosenMatrixTempPuffer_1,HomogenePoseAusgabe.HomogenePosenMatrixTempPuffer_2);

  // Temporäre Umwandlung der URPose (Objekt rechts des Operators) in eine homogene Pose
  HomogenePoseAusgabe.URPoseToHomogenousPose (URPose,HomogenePoseAusgabe.HomogenePosenMatrixTempPuffer_3);

  // Die Diagonale des zuvor erzeugten Objektes muss genullt werden, da
  // diese bei Objekterzeugung im Konstruktor mit 1 besetzt wird (Nullpose).
  for (int i = 0; i < 4; i++)
    {
    HomogenePoseAusgabe.HomogenePosenMatrix[i][i] = 0;
    }

  // Matrixmultiplikation
  for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
      {
      for (int k = 0; k < 4; k++)
        {
        // HomogenePoseAusgabe.HomogenePosenMatrixTempPuffer_2[i][k] ist die temporär umgewandelte Pose des Objektes,
        // dass bei der Division links des Divisionsoperator steht. HomogenePoseAusgabe.HomogenePosenMatrixTempPuffer_3[k][j] ist die 
        // Pose des Objektes, dass rechts des Divisionsoperator steht.
        // Diese Multiplikation entspricht: A = B \ C = B^-1 * C
        HomogenePoseAusgabe.HomogenePosenMatrix[i][j] += HomogenePoseAusgabe.HomogenePosenMatrixTempPuffer_2[i][k] * HomogenePoseAusgabe.HomogenePosenMatrixTempPuffer_3[k][j];
        }
      }
    }

  // Ausgabe der im Objekt "HomogenePoseAusgabe.HomogenePosenMatrix[i][j]" gefüllten nmsp_posen-Matrix.
  return (HomogenePoseAusgabe);
  }

/************************************************Private Methoden************************************************/
void C_URPose::HomogenousPoseToURPose (C_AbsolutePose& AbsolutePose)
  {
  // Zuweisung der Positionsangabe der UR-Pose
  this->X = AbsolutePose.HomogenePosenMatrix[0][3];
  this->Y = AbsolutePose.HomogenePosenMatrix[1][3];
  this->Z = AbsolutePose.HomogenePosenMatrix[2][3];

  // Berechnung des Betrages der Rotationsachse ergibt sich aus der Berechung
  // des Drehwinkels phi. Der Drehwinkel und der Betrag des Rotations-
  // vektors sind identisch.
  // Es gilt folgendes:
  // cos(phi)               = (Spur(Rot) - 1) / 2
  // sin(phi)               = sqrt(- pow((1 - Spur(Rot)) / 2, 2) + 1)
  // phi                    = atan(sin(phi) / cos(phi))
  // Drehwinkel             = phi
  double SpurRot = AbsolutePose.HomogenePosenMatrix[0][0] + AbsolutePose.HomogenePosenMatrix[1][1] + AbsolutePose.HomogenePosenMatrix[2][2];
  if (SpurRot <= -1.0)
    {
    SpurRot = -1.0;
    }
  else if (SpurRot >= 1.0)
    {
    SpurRot = 1.0;
    }
  double CosPhi     = (SpurRot - 1) / 2;
  double SinPhi     = sqrt (-pow ((1 - SpurRot) / 2,2) + 1);
  double Drehwinkel = atan2 (SinPhi,CosPhi);

  // Die Berechnung des Einheitsvektors der beliebigen Drehachse
  // erfolgt aus der Berechnung eines Eigenvektors der Rotationsmatrix.
  // Diese hat immer einen Wert von Lambda = 1 und ein konjungiert
  // komplexes Polstellenpaar als Eigenwerte. Aus dem zu Lambda = 1
  // zugehörigen Eigenvektor lässt sich der normierte Drehachsenvektor
  // errechnen:
  // Eigenvektor = normierter Drehachsenvektor
  // Die Formel zur Berechnung des Eigenvektors stammt aus:
  // "Mark W. Spong, Seth Hutchinson, M. Vidyasagar - Robot Dynamics
  // ans Control (Second Edition)"
  // Mit der Variablen Epsilon erfolgt eine Prüfung, ob der Nenner
  // gegen 0 geht.
  double Epsilon = 0.01;
  double Nenner  = 2 * sin (Drehwinkel);
  if (Nenner > Epsilon)
    {
    // Ist definiert
    this->RX = (AbsolutePose.HomogenePosenMatrix[2][1] - AbsolutePose.HomogenePosenMatrix[1][2]) / Nenner;
    this->RY = (AbsolutePose.HomogenePosenMatrix[0][2] - AbsolutePose.HomogenePosenMatrix[2][0]) / Nenner;
    this->RZ = (AbsolutePose.HomogenePosenMatrix[1][0] - AbsolutePose.HomogenePosenMatrix[0][1]) / Nenner;
    }
  else if (Nenner < Epsilon && abs (Drehwinkel) < Epsilon)
    {
    // Wenn sin(phi) gegen 0 geht und der Drehwinkel ebenfalls gegen 0 geht,
    // dann findet keine Rotations statt.
    this->RX = 0.0;
    this->RY = 0.0;
    this->RZ = 0.0;
    }
  else if (Nenner < Epsilon && abs (abs (Drehwinkel) - PI) < Epsilon)
    {
    // Wenn sin(phi) gegen 0 geht und Drehwinkel - Pi < Epsilon ist,
    // dann wurd um +-Pi gedreht.

    // Hier erfolgen nun einzelne Abfragen, wie genau um +-Pi gedreht wurde.
    if (abs (AbsolutePose.HomogenePosenMatrix[0][0] - 1.0) < Epsilon && abs (AbsolutePose.HomogenePosenMatrix[1][1] + 1.0) < Epsilon && abs (AbsolutePose.HomogenePosenMatrix[2][2] + 1.0) < Epsilon)
      {
      // R =  1  0  0
      //      0 -1  0
      //      0  0 -1
      this->RX = 1.0;
      this->RY = 0.0;
      this->RZ = 0.0;
      }

    if (abs (AbsolutePose.HomogenePosenMatrix[0][0] + 1.0) < Epsilon && abs (AbsolutePose.HomogenePosenMatrix[1][1] - 1.0) < Epsilon && abs (AbsolutePose.HomogenePosenMatrix[2][2] + 1.0) < Epsilon)
      {
      // R = -1  0  0
      //      0  1  0
      //      0  0 -1
      this->RX = 0.0;
      this->RY = 1.0;
      this->RZ = 0.0;
      }

    if (abs (AbsolutePose.HomogenePosenMatrix[0][0] + 1.0) < Epsilon && abs (AbsolutePose.HomogenePosenMatrix[1][1] + 1.0) < Epsilon && abs (AbsolutePose.HomogenePosenMatrix[2][2] - 1.0) < Epsilon)
      {
      // R = -1  0  0
      //      0 -1  0
      //      0  0  1
      this->RX = 0.0;
      this->RY = 0.0;
      this->RZ = 1.0;
      }

    if (abs (AbsolutePose.HomogenePosenMatrix[0][1] + 1.0) < Epsilon && abs (AbsolutePose.HomogenePosenMatrix[1][0] + 1.0) < Epsilon && abs (AbsolutePose.HomogenePosenMatrix[2][2] + 1.0) < Epsilon)
      {
      // R = 0 -1  0
      //    -1  0  0
      //     0  0 -1
      this->RX = -1.0 / sqrt (2.0);
      this->RY = -this->RX;
      this->RZ = 0.0;
      }

    if (abs (AbsolutePose.HomogenePosenMatrix[2][0] + 1.0) < Epsilon && abs (AbsolutePose.HomogenePosenMatrix[1][1] + 1.0) < Epsilon && abs (AbsolutePose.HomogenePosenMatrix[0][2] + 1.0) < Epsilon)
      {
      // R = 0  0 -1
      //     0 -1  0
      //    -1  0  0
      this->RX = 1.0 / sqrt (2.0);
      this->RY = 0.0;
      this->RZ = -this->RX;
      }

    if (abs (AbsolutePose.HomogenePosenMatrix[0][0] + 1.0) < Epsilon && abs (AbsolutePose.HomogenePosenMatrix[2][1] + 1.0) < Epsilon && abs (AbsolutePose.HomogenePosenMatrix[1][2] + 1.0) < Epsilon)
      {
      // R = -1  0  0
      //      0  0 -1
      //      0 -1  0
      this->RX = 0.0;
      this->RY = 1.0 / sqrt (2.0);
      this->RZ = -this->RY;
      }
    }

  // Weiterhin muss der berechnete Eigenvektor mit dem Drehwinkel
  // multipliziert werden, um den Drehachsenvektor zu erhalten. Da
  // RX, RY und RZ die Richtungen des Einheitsvektors der Drehachse sind,
  // müssen die Richtungen mit dem Betrag des Drehwinkel multipliziert
  // werden. Somit erhält man den Vektor der Drehachse.
  this->RX *= abs (Drehwinkel);
  this->RY *= abs (Drehwinkel);
  this->RZ *= abs (Drehwinkel);
  }
void C_URPose::HomogenousPoseToURPose (C_RelativePose& RelativePose)
  {
  // Zuweisung der Positionsangabe der UR-Pose
  this->X = RelativePose.HomogenePosenMatrix[0][3];
  this->Y = RelativePose.HomogenePosenMatrix[1][3];
  this->Z = RelativePose.HomogenePosenMatrix[2][3];

  // Berechnung des Betrages der Rotationsachse ergibt sich aus der Berechung
  // des Drehwinkels phi. Der Drehwinkel und der Betrag des Rotations-
  // vektors sind identisch.
  // Es gilt folgendes:
  // cos(phi)               = (Spur(Rot) - 1) / 2
  // sin(phi)               = sqrt(- pow((1 - Spur(Rot)) / 2, 2) + 1)
  // phi                    = atan(sin(phi) / cos(phi))
  // Drehwinkel             = phi
  double SpurRot = RelativePose.HomogenePosenMatrix[0][0] + RelativePose.HomogenePosenMatrix[1][1] + RelativePose.HomogenePosenMatrix[2][2];
  if (SpurRot <= -1.0)
    {
    SpurRot = -1.0;
    }
  else if (SpurRot >= 1.0)
    {
    SpurRot = 1.0;
    }
  double CosPhi     = (SpurRot - 1) / 2;
  double SinPhi     = sqrt (-pow ((1 - SpurRot) / 2,2) + 1);
  double Drehwinkel = atan2 (SinPhi,CosPhi);

  // Die Berechnung des Einheitsvektors der beliebigen Drehachse
  // erfolgt aus der Berechnung eines Eigenvektors der Rotationsmatrix.
  // Diese hat immer einen Wert von Lambda = 1 und ein konjungiert
  // komplexes Polstellenpaar als Eigenwerte. Aus dem zu Lambda = 1
  // zugehörigen Eigenvektor lässt sich der normierte Drehachsenvektor
  // errechnen:
  // Eigenvektor = normierter Drehachsenvektor
  // Die Formel zur Berechnung des Eigenvektors stammt aus:
  // "Mark W. Spong, Seth Hutchinson, M. Vidyasagar - Robot Dynamics
  // ans Control (Second Edition)"
  // Mit der Variablen Epsilon erfolgt eine Prüfung, ob der Nenner
  // gegen 0 geht.
  double Epsilon = 0.01;
  double Nenner  = 2 * sin (Drehwinkel);
  if (Nenner > Epsilon)
    {
    // Ist definiert
    this->RX = (RelativePose.HomogenePosenMatrix[2][1] - RelativePose.HomogenePosenMatrix[1][2]) / Nenner;
    this->RY = (RelativePose.HomogenePosenMatrix[0][2] - RelativePose.HomogenePosenMatrix[2][0]) / Nenner;
    this->RZ = (RelativePose.HomogenePosenMatrix[1][0] - RelativePose.HomogenePosenMatrix[0][1]) / Nenner;
    }
  else if (Nenner < Epsilon && abs (Drehwinkel) < Epsilon)
    {
    // Wenn sin(phi) gegen 0 geht und der Drehwinkel ebenfalls gegen 0 geht,
    // dann findet keine Rotations statt.
    this->RX = 0.0;
    this->RY = 0.0;
    this->RZ = 0.0;
    }
  else if (Nenner < Epsilon && abs (abs (Drehwinkel) - PI) < Epsilon)
    {
    // Wenn sin(phi) gegen 0 geht und Drehwinkel - Pi < Epsilon ist,
    // dann wurd um +-Pi gedreht.

    // Hier erfolgen nun einzelne Abfragen, wie genau um +-Pi gedreht wurde.
    if (abs (RelativePose.HomogenePosenMatrix[0][0] - 1.0) < Epsilon && abs (RelativePose.HomogenePosenMatrix[1][1] + 1.0) < Epsilon && abs (RelativePose.HomogenePosenMatrix[2][2] + 1.0) < Epsilon)
      {
      // R =  1  0  0
      //      0 -1  0
      //      0  0 -1
      this->RX = 1.0;
      this->RY = 0.0;
      this->RZ = 0.0;
      }

    if (abs (RelativePose.HomogenePosenMatrix[0][0] + 1.0) < Epsilon && abs (RelativePose.HomogenePosenMatrix[1][1] - 1.0) < Epsilon && abs (RelativePose.HomogenePosenMatrix[2][2] + 1.0) < Epsilon)
      {
      // R = -1  0  0
      //      0  1  0
      //      0  0 -1
      this->RX = 0.0;
      this->RY = 1.0;
      this->RZ = 0.0;
      }

    if (abs (RelativePose.HomogenePosenMatrix[0][0] + 1.0) < Epsilon && abs (RelativePose.HomogenePosenMatrix[1][1] + 1.0) < Epsilon && abs (RelativePose.HomogenePosenMatrix[2][2] - 1.0) < Epsilon)
      {
      // R = -1  0  0
      //      0 -1  0
      //      0  0  1
      this->RX = 0.0;
      this->RY = 0.0;
      this->RZ = 1.0;
      }

    if (abs (RelativePose.HomogenePosenMatrix[0][1] + 1.0) < Epsilon && abs (RelativePose.HomogenePosenMatrix[1][0] + 1.0) < Epsilon && abs (RelativePose.HomogenePosenMatrix[2][2] + 1.0) < Epsilon)
      {
      // R = 0 -1  0
      //    -1  0  0
      //     0  0 -1
      this->RX = -1.0 / sqrt (2.0);
      this->RY = -this->RX;
      this->RZ = 0.0;
      }

    if (abs (RelativePose.HomogenePosenMatrix[2][0] + 1.0) < Epsilon && abs (RelativePose.HomogenePosenMatrix[1][1] + 1.0) < Epsilon && abs (RelativePose.HomogenePosenMatrix[0][2] + 1.0) < Epsilon)
      {
      // R = 0  0 -1
      //     0 -1  0
      //    -1  0  0
      this->RX = 1.0 / sqrt (2.0);
      this->RY = 0.0;
      this->RZ = -this->RX;
      }

    if (abs (RelativePose.HomogenePosenMatrix[0][0] + 1.0) < Epsilon && abs (RelativePose.HomogenePosenMatrix[2][1] + 1.0) < Epsilon && abs (RelativePose.HomogenePosenMatrix[1][2] + 1.0) < Epsilon)
      {
      // R = -1  0  0
      //      0  0 -1
      //      0 -1  0
      this->RX = 0.0;
      this->RY = 1.0 / sqrt (2.0);
      this->RZ = -this->RY;
      }
    }

  // Weiterhin muss der berechnete Eigenvektor mit dem Drehwinkel
  // multipliziert werden, um den Drehachsenvektor zu erhalten. Da
  // RX, RY und RZ die Richtungen des Einheitsvektors der Drehachse sind,
  // müssen die Richtungen mit dem Betrag des Drehwinkel multipliziert
  // werden. Somit erhält man den Vektor der Drehachse.
  this->RX *= abs (Drehwinkel);
  this->RY *= abs (Drehwinkel);
  this->RZ *= abs (Drehwinkel);
  }
void C_URPose::HomogenousPoseToURPose (double (&HomogenePoseMatrix)[4][4])
  {
  // Zuweisung der Positionsangabe der UR-Pose
  this->X = HomogenePoseMatrix[0][3];
  this->Y = HomogenePoseMatrix[1][3];
  this->Z = HomogenePoseMatrix[2][3];

  // Berechnung des Betrages der Rotationsachse ergibt sich aus der Berechung
  // des Drehwinkels phi. Der Drehwinkel und der Betrag des Rotations-
  // vektors sind identisch.
  // Es gilt folgendes:
  // cos(phi)               = (Spur(Rot) - 1) / 2
  // sin(phi)               = sqrt(- pow((1 - Spur(Rot)) / 2, 2) + 1)
  // phi                    = atan(sin(phi) / cos(phi))
  // Drehwinkel             = phi
  double SpurRot = HomogenePoseMatrix[0][0] + HomogenePoseMatrix[1][1] + HomogenePoseMatrix[2][2];
  if (SpurRot <= -1.0)
    {
    SpurRot = -1.0;
    }
  else if (SpurRot >= 1.0)
    {
    SpurRot = 1.0;
    }
  double CosPhi     = (SpurRot - 1) / 2;
  double SinPhi     = sqrt (-pow ((1 - SpurRot) / 2,2) + 1);
  double Drehwinkel = atan2 (SinPhi,CosPhi);

  // Die Berechnung des Einheitsvektors der beliebigen Drehachse
  // erfolgt aus der Berechnung eines Eigenvektors der Rotationsmatrix.
  // Diese hat immer einen Wert von Lambda = 1 und ein konjungiert
  // komplexes Polstellenpaar als Eigenwerte. Aus dem zu Lambda = 1
  // zugehörigen Eigenvektor lässt sich der normierte Drehachsenvektor
  // errechnen:
  // Eigenvektor = normierter Drehachsenvektor
  // Die Formel zur Berechnung des Eigenvektors stammt aus:
  // "Mark W. Spong, Seth Hutchinson, M. Vidyasagar - Robot Dynamics
  // ans Control (Second Edition)"
  // Mit der Variablen Epsilon erfolgt eine Prüfung, ob der Nenner
  // gegen 0 geht.
  double Epsilon = 0.01;
  double Nenner  = 2 * sin (Drehwinkel);
  if (Nenner > Epsilon)
    {
    // Ist definiert
    this->RX = (HomogenePoseMatrix[2][1] - HomogenePoseMatrix[1][2]) / Nenner;
    this->RY = (HomogenePoseMatrix[0][2] - HomogenePoseMatrix[2][0]) / Nenner;
    this->RZ = (HomogenePoseMatrix[1][0] - HomogenePoseMatrix[0][1]) / Nenner;
    }
  else if (Nenner < Epsilon && abs (Drehwinkel) < Epsilon)
    {
    // Wenn sin(phi) gegen 0 geht und der Drehwinkel ebenfalls gegen 0 geht,
    // dann findet keine Rotations statt.
    this->RX = 0.0;
    this->RY = 0.0;
    this->RZ = 0.0;
    }
  else if (Nenner < Epsilon && abs (abs (Drehwinkel) - PI) < Epsilon)
    {
    // Wenn sin(phi) gegen 0 geht und Drehwinkel - Pi < Epsilon ist,
    // dann wurd um +-Pi gedreht.

    // Hier erfolgen nun einzelne Abfragen, wie genau um +-Pi gedreht wurde.
    if (abs (HomogenePoseMatrix[0][0] - 1.0) < Epsilon && abs (HomogenePoseMatrix[1][1] + 1.0) < Epsilon && abs (HomogenePoseMatrix[2][2] + 1.0) < Epsilon)
      {
      // R =  1  0  0
      //      0 -1  0
      //      0  0 -1
      this->RX = 1.0;
      this->RY = 0.0;
      this->RZ = 0.0;
      }

    if (abs (HomogenePoseMatrix[0][0] + 1.0) < Epsilon && abs (HomogenePoseMatrix[1][1] - 1.0) < Epsilon && abs (HomogenePoseMatrix[2][2] + 1.0) < Epsilon)
      {
      // R = -1  0  0
      //      0  1  0
      //      0  0 -1
      this->RX = 0.0;
      this->RY = 1.0;
      this->RZ = 0.0;
      }

    if (abs (HomogenePoseMatrix[0][0] + 1.0) < Epsilon && abs (HomogenePoseMatrix[1][1] + 1.0) < Epsilon && abs (HomogenePoseMatrix[2][2] - 1.0) < Epsilon)
      {
      // R = -1  0  0
      //      0 -1  0
      //      0  0  1
      this->RX = 0.0;
      this->RY = 0.0;
      this->RZ = 1.0;
      }

    if (abs (HomogenePoseMatrix[0][1] + 1.0) < Epsilon && abs (HomogenePoseMatrix[1][0] + 1.0) < Epsilon && abs (HomogenePoseMatrix[2][2] + 1.0) < Epsilon)
      {
      // R = 0 -1  0
      //    -1  0  0
      //     0  0 -1
      this->RX = -1.0 / sqrt (2.0);
      this->RY = -this->RX;
      this->RZ = 0.0;
      }

    if (abs (HomogenePoseMatrix[2][0] + 1.0) < Epsilon && abs (HomogenePoseMatrix[1][1] + 1.0) < Epsilon && abs (HomogenePoseMatrix[0][2] + 1.0) < Epsilon)
      {
      // R = 0  0 -1
      //     0 -1  0
      //    -1  0  0
      this->RX = 1.0 / sqrt (2.0);
      this->RY = 0.0;
      this->RZ = -this->RX;
      }


    if (abs (HomogenePoseMatrix[0][0] + 1.0) < Epsilon && abs (HomogenePoseMatrix[2][1] + 1.0) < Epsilon && abs (HomogenePoseMatrix[1][2] + 1.0) < Epsilon)
      {
      // R = -1  0  0
      //      0  0 -1
      //      0 -1  0
      this->RX = 0.0;
      this->RY = 1.0 / sqrt (2.0);
      this->RZ = -this->RY;
      }
    }

  // Weiterhin muss der berechnete Eigenvektor mit dem Drehwinkel
  // multipliziert werden, um den Drehachsenvektor zu erhalten. Da
  // RX, RY und RZ die Richtungen des Einheitsvektors der Drehachse sind,
  // müssen die Richtungen mit dem Betrag des Drehwinkel multipliziert
  // werden. Somit erhält man den Vektor der Drehachse.
  this->RX *= abs (Drehwinkel);
  this->RY *= abs (Drehwinkel);
  this->RZ *= abs (Drehwinkel);
  }
/*********************************************** Klasse C_URPose ***********************************************/
