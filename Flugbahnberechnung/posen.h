/********************************************************************************************************************************************/
/*                                                                                                                                          */
/*  Header-Datei: UM_Posen.h                                                                                                                */
/*                                                                                                                                          */
/*                                                                                                                                          */
/*                                                                                                                                          */
/*  Marcel Bänfer      11.09.2019                                                                                                           */
/*                                                                                                                                          */
/********************************************************************************************************************************************/
//#pragma once

/************************************************************ Anwender-Defines **************************************************************/
#define  PI 3.14159265358979323846

/************************************************************ Anwender-Includes *************************************************************/
#include <math.h>

/************************************************************** using namespaces **************************************************************/

/*********************************************************** Vorwärtsdeklarationen ************************************************************/
namespace nmsp_posen
  {
  class  C_RelativePose;
  class  C_URPose;
  }using namespace nmsp_posen;


namespace nmsp_posen
  {
  struct S_EllbogenWerte
    {
    double Ellbogen_Z;
    double Ellbogen_Y;
    double Ellbogen_X;
    };
  struct S_EllbogenGeschwindigkeit
    {
    double Ellbogen_Z_v;
    double Ellbogen_Y_v;
    double Ellbogen_X_v;
    };
  struct S_PoseWerte
    {
    double RZ;
    double RY;
    double RX;
    double Z;
    double Y;
    double X;
    };
  struct S_PoseGeschwindigkeit
    {
    double RZ_v;
    double RY_v;
    double RX_v;
    double Z_v;
    double Y_v;
    double X_v;
    };
  struct S_PoseBeschleunigung
    {
    double Z_a;
    double Y_a;
    double X_a;
    };
  struct S_GelenkWerte
    {
    double Handgelenk3_Winkel;
    double Handgelenk2_Winkel;
    double Handgelenk1_Winkel;
    double Ellbogen_Winkel;
    double Schulter_Winkel;
    double Fuss_Winkel;
    };
  struct S_GelenkGeschwindigkeit
    {
    double Handgelenk3_Winkel_v;
    double Handgelenk2_Winkel_v;
    double Handgelenk1_Winkel_v;
    double Ellbogen_Winkel_v;
    double Schulter_Winkel_v;
    double Fuss_Winkel_v;
    };
  struct S_GelenkBeschleunigung
    {
    double Handgelenk3_Winkel_a;
    double Handgelenk2_Winkel_a;
    double Handgelenk1_Winkel_a;
    double Ellbogen_Winkel_a;
    double Schulter_Winkel_a;
    double Fuss_Winkel_a;
    };
  struct S_GelenkStrom
    {
    double Handgelenk3_Strom;
    double Handgelenk2_Strom;
    double Handgelenk1_Strom;
    double Ellbogen_Strom;
    double Schulter_Strom;
    double Fuss_Strom;
    };
  struct S_GelenkSpannung
    {
    double Handgelenk3_Spannung;
    double Handgelenk2_Spannung;
    double Handgelenk1_Spannung;
    double Ellbogen_Spannung;
    double Schulter_Spannung;
    double Fuss_Spannung;
    };
  struct S_GelenkMoment
    {
    double Handgelenk3_Moment;
    double Handgelenk2_Moment;
    double Handgelenk1_Moment;
    double Ellbogen_Moment;
    double Schulter_Moment;
    double Fuss_Moment;
    };
  struct S_GelenkTemperatur
    {
    double Handgelenk3_Temperatur;
    double Handgelenk2_Temperatur;
    double Handgelenk1_Temperatur;
    double Ellbogen_Temperatur;
    double Schulter_Temperatur;
    double Fuss_Temperatur;
    };
  struct S_GelenkKontrollModus
    {
    double Handgelenk3_KontrollModus;
    double Handgelenk2_KontrollModus;
    double Handgelenk1_KontrollModus;
    double Ellbogen_KontrollModus;
    double Schulter_KontrollModus;
    double Fuss_KontrollModus;
    };
  struct S_TCPKraft
    {
    double TCP_TZ;
    double TCP_TY;
    double TCP_TX;
    double TCP_FZ;
    double TCP_FY;
    double TCP_FX;
    };
  struct S_URSoftwareOnly
    {
    double URSoftwareOnly6;
    double URSoftwareOnly5;
    double URSoftwareOnly4;
    double URSoftwareOnly3;
    double URSoftwareOnly2;
    double URSoftwareOnly1;
    };
  struct S_BewegungJoint
    {
    double Geschwindigkeit;
    double Beschleunigung;
    double Zeit;
    double Radius;
    };
  struct S_BewegungLinear
    {
    double Geschwindigkeit;
    double Beschleunigung;
    double Zeit;
    double Radius;
    };
  struct S_BewegungZirkular
    {
    double Geschwindigkeit;
    double Beschleunigung;
    double Radius;
    int    Modus;
    };
  struct S_BewegungProcessServoC
    {
    double Geschwindigkeit;
    double Beschleunigung;
    double Radius;
    };
  struct S_BewegungServoJ
    {
    double Geschwindigkeit;
    double Beschleunigung;
    double Zeit;
    double Lookahead_Time;
    int    Gain;
    };
  struct S_VektorErdbeschleunigung
    {
    double g_X;
    double g_Y;
    double g_Z;
    };
  struct S_VektorSchwerkraftZentrum
    {
    double X;
    double Y;
    double Z;
    };
  struct S_PositionAbfrage
    {
    bool Pos1;
    bool Pos2;
    bool Pos3;
    bool Pos4;
    bool Pos5;
    bool Pos6;
    };

  /**************************************** Posenvektoren ****************************************/
  struct S_Positionsvektor
    {
    double                    X;
    double                    Y;
    double                    Z;
    };

  struct S_Orientierungsvektor
    {
    double                    RX;
    double                    RY;
    double                    RZ;
    };

  struct S_Posenvektor
    {
    double                    X;
    double                    Y;
    double                    Z;
    double                    RX;
    double                    RY;
    double                    RZ;
    };




  /*********************************************** Klasse C_AbsolutePose ***********************************************/
  class C_AbsolutePose
    {
    /********************************************* Kontruktoren / Destruktor *********************************************/
      public:
      C_AbsolutePose                                                  ();
      C_AbsolutePose                                                  (const C_AbsolutePose&                  AbsolutePose);
      ~C_AbsolutePose                                                 ();


      /********************************************* Öffentliche Methoden *********************************************/
      public:
      // Überladener Operator "="
      void                    operator=                               (C_AbsolutePose                         AbsolutePose);
      void                    operator=                               (S_PoseWerte&                           URPose);
      void                    operator=                               (C_URPose                               URPose);
      void                    operator=                               (double                                 (&NullposeMatrix)[4][4]);

      // Überladener Operator "*"
      C_AbsolutePose          operator*                               (C_RelativePose&                        RelativePose);

      // Überladener Operator "*="
      void                    operator*=                              (C_RelativePose&                        RelativePose);

      // Überladener Operator "/" (Rechtsmultiplikation)
      C_AbsolutePose          operator/                               (C_RelativePose&                        RelativePose);

      // Überladener Operator "/=" (Rechtsmultiplikation)
      void                    operator/=                              (C_RelativePose&                        RelativePose);

      // Überladener Operator "|" statt "\" (Linksmultiplikation)
      C_RelativePose          operator|                               (C_URPose&                              URPose);
      C_RelativePose          operator|                               (C_AbsolutePose&                        AbsolutePose);

      // Methoden zur Umwandlung von UR-nmsp_posen in homogene Koordinaten
      void                    URPoseToHomogenousPose                  (S_PoseWerte&                           URPose, double   (&HomogenePoseMatrix)[4][4]);
      void                    URPoseToHomogenousPose                  (C_URPose&                              URPose, double   (&HomogenePoseMatrix)[4][4]);
      void                    URPoseToHomogenousPose                  (double                                 (&URPoseMatrix)[6][1], double   (&HomogenePoseMatrix)[4][4]);

      // Methode zur Berechnung einer inversen homogenen Posenmatrix
      void                    InversHomogenousPose                    (C_AbsolutePose&                        HomogenePose_In, double   (&HomogenePoseMatrix_Out)[4][4]);
      void                    InversHomogenousPose                    (C_RelativePose&                        HomogenePose_In, double   (&HomogenePoseMatrix_Out)[4][4]);
      void                    InversHomogenousPose                    (double                                 (&HomogenePoseMatrix_In)[4][4], double   (&HomogenePoseMatrix_Out)[4][4]);

      // Get und Set- Methoden zum befllen der Posenmatrix
      double nx         (void)
        {
        return(this->HomogenePosenMatrix[0][0]);
        }
      void   nx         (double nx)
        {
        this->HomogenePosenMatrix[0][0] = nx;
        }
      double ny         (void)
        {
        return(this->HomogenePosenMatrix[1][0]);
        }
      void   ny         (double ny)
        {
        this->HomogenePosenMatrix[1][0] = ny;
        }
      double nz         (void)
        {
        return(this->HomogenePosenMatrix[2][0]);
        }
      void   nz         (double nz)
        {
        this->HomogenePosenMatrix[2][0] = nz;
        }
      double ox         (void)
        {
        return(this->HomogenePosenMatrix[0][1]);
        }
      void   ox         (double ox)
        {
        this->HomogenePosenMatrix[0][1] = ox;
        }
      double oy         (void)
        {
        return(this->HomogenePosenMatrix[1][1]);
        }
      void   oy         (double oy)
        {
        this->HomogenePosenMatrix[1][1] = oy;
        }
      double oz         (void)
        {
        return(this->HomogenePosenMatrix[2][1]);
        }
      void   oz         (double oz)
        {
        this->HomogenePosenMatrix[2][1] = oz;
        }
      double ax         (void)
        {
        return(this->HomogenePosenMatrix[0][2]);
        }
      void   ax         (double ax)
        {
        this->HomogenePosenMatrix[0][2] = ax;
        }
      double ay         (void)
        {
        return(this->HomogenePosenMatrix[1][2]);
        }
      void   ay         (double ay)
        {
        this->HomogenePosenMatrix[1][2] = ay;
        }
      double az         (void)
        {
        return(this->HomogenePosenMatrix[2][2]);
        }
      void   az         (double az)
        {
        this->HomogenePosenMatrix[2][2] = az;
        }
      double px         (void)
        {
        return(this->HomogenePosenMatrix[0][3]);
        }
      void   px         (double px)
        {
        this->HomogenePosenMatrix[0][3] = px;
        }
      double py         (void)
        {
        return(this->HomogenePosenMatrix[1][3]);
        }
      void   py         (double py)
        {
        this->HomogenePosenMatrix[1][3] = py;
        }
      double pz         (void)
        {
        return(this->HomogenePosenMatrix[2][3]);
        }
      void   pz         (double pz)
        {
        this->HomogenePosenMatrix[2][3] = pz;
        }

      double Euler_Psi  (void)
        {
        return(atan2 (this->HomogenePosenMatrix[2][1], this->HomogenePosenMatrix[2][2]));
        }
      void   Euler_Psi  (double Euler_Psi)
        {
        this->BerechneExtrinsischRPY(Euler_Psi, this->Euler_Phi(), this->Euler_Chi());
        }
      double Euler_Phi  (void)
        {
        return(atan2 (-HomogenePosenMatrix[2][0], sqrt(1 - pow(HomogenePosenMatrix[2][0], 2))));
        }
      void   Euler_Phi  (double Euler_Phi)
        {
        this->BerechneExtrinsischRPY(this->Euler_Psi(), Euler_Phi, this->Euler_Chi());
        }
      double Euler_Chi  (void)
        {
        return(atan2 (this->HomogenePosenMatrix[1][0], this->HomogenePosenMatrix[0][0]));
        }
      void   Euler_Chi  (double Euler_Chi)
        {
        this->BerechneExtrinsischRPY(this->Euler_Psi(), this->Euler_Phi(), Euler_Chi);
        }

      /************************************************Private Methoden************************************************/
      private:
      void                    BerechneExtrinsischRPY                  (double Euler_Psi, double Euler_Phi, double Euler_Chi);

      /*********************************************ffentliche Attribute*********************************************/
      public:
      // Variablen, welche der Ausgabe dienen
      double                                       Nullpose[4][4];
      double                                       HomogenePosenMatrix[4][4];
      // Variablen fr interne Berechnungen, mssen public aufgrund von externen Zugriff sein
      double                                       HomogenePosenMatrixTempPuffer_1[4][4];
      double                                       HomogenePosenMatrixTempPuffer_2[4][4];
      double                                       HomogenePosenMatrixTempPuffer_3[4][4];

      /*********************************************Private Attribute*********************************************/
      private:
      // Hilfsvariablen fr mathematische Operationen
      double                                       URPose_Puffer[6][1];
      double                                       RX_normiert;
      double                                       RY_normiert;
      double                                       RZ_normiert;
      double                                       Epsilon;
    };
  /*********************************************** Klasse C_AbsolutePose ***********************************************/


  /*********************************************** Klasse C_RelativePose ***********************************************/
  class C_RelativePose
    {
    /*********************************************Konstruktoren / Destruktor*********************************************/
      public:
      C_RelativePose                                                  ();
      C_RelativePose                                                  (const C_RelativePose&                  RelativePose);
      ~C_RelativePose                                                 ();


  //    /*********************************************ffentliche Methoden*********************************************/
      public:
      // berladener Operator "="
      void                    operator=                               (C_RelativePose                         RelativePose);
      void                    operator=                               (double                                 (&NullposeMatrix)[4][4]);
      void                    operator=                               (C_URPose                               URPose);

      // berladener Operator "*"
      C_RelativePose          operator*                               (C_RelativePose&                        RelativePose);

      // berladener Operator "*="
      void                    operator*=                              (C_RelativePose&                        RelativePose);

      // berladener Operator "/" (Rechtsmultiplikation)
      C_RelativePose          operator/                               (C_RelativePose&                        RelativePose);

      // berladener Operator "/=" (Rechtsmultiplikation)
      void                    operator/=                              (C_RelativePose&                        RelativePose);

      // berladener Operator "|" statt "\" (Linksmultiplikation)
      C_RelativePose          operator|                               (C_RelativePose&                        RelativePose);

      // berladener Operator "|=" statt "\=" (Linksmultiplikation)
      void                    operator|=                              (C_RelativePose&                        RelativePose);

      // Methoden zur Umwandlung von UR-nmsp_posen in homogene Koordinaten
      void            URPoseToHomogenousPose                          (C_URPose&                              URPose, double   (&HomogenePoseMatrix)[4][4]);
      void            URPoseToHomogenousPose                          (double                                 (&URPoseMatrix)[6][1], double   (&HomogenePoseMatrix)[4][4]);

      // Methode zur Berechnung einer inversen homogenen Posenmatrix
      void            InversHomogenousPose                            (C_AbsolutePose&                        HomogenePose_In, double   (&HomogenePoseMatrix_Out)[4][4]);
      void            InversHomogenousPose                            (C_RelativePose&                        HomogenePose_In, double   (&HomogenePoseMatrix_Out)[4][4]);
      void            InversHomogenousPose                            (double                                 (&HomogenePoseMatrix_In)[4][4], double   (&HomogenePoseMatrix_Out)[4][4]);

      // Get und Set- Methoden zum befllen der Posenmatrix
      double nx         (void)
        {
        return(this->HomogenePosenMatrix[0][0]);
        }
      void   nx         (double nx)
        {
        this->HomogenePosenMatrix[0][0] = nx;
        }
      double ny         (void)
        {
        return(this->HomogenePosenMatrix[1][0]);
        }
      void   ny         (double ny)
        {
        this->HomogenePosenMatrix[1][0] = ny;
        }
      double nz         (void)
        {
        return(this->HomogenePosenMatrix[2][0]);
        }
      void   nz         (double nz)
        {
        this->HomogenePosenMatrix[2][0] = nz;
        }
      double ox         (void)
        {
        return(this->HomogenePosenMatrix[0][1]);
        }
      void   ox         (double ox)
        {
        this->HomogenePosenMatrix[0][1] = ox;
        }
      double oy         (void)
        {
        return(this->HomogenePosenMatrix[1][1]);
        }
      void   oy         (double oy)
        {
        this->HomogenePosenMatrix[1][1] = oy;
        }
      double oz         (void)
        {
        return(this->HomogenePosenMatrix[2][1]);
        }
      void   oz         (double oz)
        {
        this->HomogenePosenMatrix[2][1] = oz;
        }
      double ax         (void)
        {
        return(this->HomogenePosenMatrix[0][2]);
        }
      void   ax         (double ax)
        {
        this->HomogenePosenMatrix[0][2] = ax;
        }
      double ay         (void)
        {
        return(this->HomogenePosenMatrix[1][2]);
        }
      void   ay         (double ay)
        {
        this->HomogenePosenMatrix[1][2] = ay;
        }
      double az         (void)
        {
        return(this->HomogenePosenMatrix[2][2]);
        }
      void   az         (double az)
        {
        this->HomogenePosenMatrix[2][2] = az;
        }
      double px         (void)
        {
        return(this->HomogenePosenMatrix[0][3]);
        }
      void   px         (double px)
        {
        this->HomogenePosenMatrix[0][3] = px;
        }
      double py         (void)
        {
        return(this->HomogenePosenMatrix[1][3]);
        }
      void   py         (double py)
        {
        this->HomogenePosenMatrix[1][3] = py;
        }
      double pz         (void)
        {
        return(this->HomogenePosenMatrix[2][3]);
        }
      void   pz         (double pz)
        {
        this->HomogenePosenMatrix[2][3] = pz;
        }

      double Euler_Psi  (void)
        {
        return(atan2 (this->HomogenePosenMatrix[2][1], this->HomogenePosenMatrix[2][2]));
        }
      void   Euler_Psi  (double Euler_Psi)
        {
        this->BerechneExtrinsischRPY(Euler_Psi, this->Euler_Phi(), this->Euler_Chi());
        }
      double Euler_Phi  (void)
        {
        return(atan2 (-HomogenePosenMatrix[2][0], sqrt(1 - pow(HomogenePosenMatrix[2][0], 2))));
        }
      void   Euler_Phi  (double Euler_Phi)
        {
        this->BerechneExtrinsischRPY(this->Euler_Psi(), Euler_Phi, this->Euler_Chi());
        }
      double Euler_Chi  (void)
        {
        return(atan2 (this->HomogenePosenMatrix[1][0], this->HomogenePosenMatrix[0][0]));
        }
      void   Euler_Chi  (double Euler_Chi)
        {
        this->BerechneExtrinsischRPY(this->Euler_Psi(), this->Euler_Phi(), Euler_Chi);
        }

  //    /************************************************Private Methoden************************************************/
      private:
      void                    BerechneExtrinsischRPY                  (double Euler_Psi, double Euler_Phi, double Euler_Chi);

  //    /*********************************************ffentliche Attribute*********************************************/
      public:
      // Variablen, welche der Ausgabe dienen
      double                                       Nullpose[4][4];
      double                                      HomogenePosenMatrix[4][4];
      // Variablen fr interne Berechnungen, mssen public aufgrund von externen Zugriff sein
      double                                       HomogenePosenMatrixTempPuffer_1[4][4];
      double                                       HomogenePosenMatrixTempPuffer_2[4][4];
      double                                       HomogenePosenMatrixTempPuffer_3[4][4];


  //    /*********************************************Private Attribute*********************************************/
      private:
      // Hilfsvariablen fr mathematische Operationen
      double                                       URPose_Puffer[6][1];
      double                                       RX_normiert;
      double                                       RY_normiert;
      double                                       RZ_normiert;
      double                                       Epsilon;
    };
  /*********************************************** Klasse C_RelativePose ***********************************************/


  /************************************************** Klasse C_URPose **************************************************/
  // Eine URPose wird immer als absolute Pose betrachtet!!!
      class C_URPose
        {
        /*********************************************Konstruktoren / Destruktor*********************************************/
          public:
          C_URPose                                                        ();
          C_URPose                                                        (const C_URPose& URPose);
          ~C_URPose                                                       ();


          /*********************************************ffentliche Methoden*********************************************/
          public:
          // berladener Operator "="
          void                    operator=                               (C_URPose                                 URPose);
          void                    operator=                               (S_PoseWerte&                             URPose);
          void                    operator=                               (C_AbsolutePose                           AbsolutePose);
          void                    operator=                               (C_RelativePose                           RelativePose);
          void                    operator=                               (double                                   (&NullposeMatrix)[6][1]);

          // berladener Operator "*"
          C_AbsolutePose          operator*                               (C_RelativePose&                          RelativePose);

          // berladener Operator "/" (Rechtsmultiplikation)
          C_AbsolutePose          operator/                               (C_RelativePose&                          RelativePose);

          // berladener Operator "|" statt "\" (Linksmultiplikation)
          C_RelativePose          operator|                               (C_AbsolutePose&                          AbsolutePose);
          C_RelativePose          operator|                               (C_URPose&                                URPose);

      //    property double Drehwinkel
      //      {
      //      double        get  ()
      //        {
      //        return(Math::Sqrt(this->RX*this->RX + this->RY*this->RY + this->RZ*this->RZ));
      //        }
      //      void  set  (double Dummy)
      //        {
      //        // Hier soll nichts geschehen!
      //        }
      //      }

          /*********************************************Private Methoden*********************************************/
          private:
          // Methoden zur Umwandlung von homogenen Koordinaten in UR-nmsp_posen
          void          HomogenousPoseToURPose                            (C_AbsolutePose&                          AbsolutePose);
          void          HomogenousPoseToURPose                            (C_RelativePose&                          RelativePose);
          void          HomogenousPoseToURPose                            (double                                   (&HomogenePoseMatrix)[4][4]);


          /*********************************************ffentliche Attribute*********************************************/
          public:
          // Variable, welche der Ausgabe dienen
          double                                    Nullpose[6][1];
          double                                    X;
          double                                    Y;
          double                                    Z;
          double                                    RX;
          double                                    RY;
          double                                    RZ;

          /*********************************************Private Attribute*********************************************/
          private:
          // Hilfsvariablen fr mathematische Operationen
          double                                    URPose_Puffer[6][1];
          double                                    HomogenePosenMatrixTempPuffer[4][4];
        };
      /************************************************** Klasse C_URPose **************************************************/
    };


