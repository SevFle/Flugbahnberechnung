/********************************************************************************************************************************************/
/*                                                                                                                                          */
/*  Header-Datei: UM_CSV_Datei.h                                                                                                            */
/*                                                                                                                                          */
/*  Klassen-Member-Deklaration der Moduls UM_CSV_Datei                                                                                      */
/*                                                                                                                                          */
/*  Marcel Bänfer 07.09.2019                                                                                                                */
/*                                                                                                                                          */
/********************************************************************************************************************************************/
//#pragma once
#ifndef __CSV_Datei_H
#define __CSV_Datei_H

/************************************************************ Anwender-Includes *************************************************************/
#include <fstream>
#include <sstream>

/************************************************************** using namespaces **************************************************************/
using namespace std;

/************************************************************* Klassendeklaration ***********************************************************/
namespace UM_CSV_Datei
  {
  /**************************************************************** Konstanten ****************************************************************/
  enum class Enum_CSV_Access
    {
    Read,
    Write,
    };

  class C_CSV_Parameter_Datei
    {
    /*************************************************************** Konstruktoren **************************************************************/
    public:
    C_CSV_Parameter_Datei ();

    /***************************************************************** Destruktor ***************************************************************/
    public:
    ~C_CSV_Parameter_Datei ();

    /********************************************** Nicht öffentliche private Anwender-Attribute ************************************************/
    private:
    fstream* Dateistrom;

    /**************************************************** Öffentliche Anwender-Attribute ********************************************************/
    public:

    /********************************************** Nicht Öffentliche private Anwender-Methoden *************************************************/
    private:
    void Separate (string Zeile, string (&Datenzelle)[3]);
    bool To_bool (string Datenzelle);
    void New_Line (int Streamposition, string& NewLine);

    /****************************************************** Öffentliche Anwender-Methoden *******************************************************/
    public:
    void Oeffnen (string ParameterDateiName, Enum_CSV_Access Access);
    void Schliessen (void);
    bool IsOpen (void);
    /********************************************************************************************************************************************/
    void Lesen (double& ParameterWert);
    void Lesen (float& ParameterWert);
    void Lesen (unsigned char& ParameterWert);
    void Lesen (unsigned short& ParameterWert);
    void Lesen (unsigned int& ParameterWert);
    void Lesen (unsigned long& ParameterWert);
    void Lesen (short& ParameterWert);
    void Lesen (int& ParameterWert);
    void Lesen (long& ParameterWert);
    void Lesen (long long& ParameterWert);
    void Lesen (bool& ParameterWert);
    void Lesen (string& ParameterWert);
    /********************************************************************************************************************************************/
    void Lesen (double& ParameterWert, double ScaleWert);
    void Lesen (float& ParameterWert, float ScaleWert);
    void Lesen (unsigned char& ParameterWert, unsigned char ScaleWert);
    void Lesen (unsigned short& ParameterWert, unsigned short ScaleWert);
    void Lesen (unsigned int& ParameterWert, unsigned int ScaleWert);
    void Lesen (unsigned long& ParameterWert, unsigned long ScaleWert);
    void Lesen (short& ParameterWert, short ScaleWert);
    void Lesen (int& ParameterWert, int ScaleWert);
    void Lesen (long& ParameterWert, long ScaleWert);
    void Lesen (long long& ParameterWert, long long ScaleWert);
    /********************************************************************************************************************************************/
    void Lesen (string& ParameterName, double& ParameterWert, string& ParameterEinheit);
    void Lesen (string& ParameterName, float& ParameterWert, string& ParameterEinheit);
    void Lesen (string& ParameterName, unsigned char& ParameterWert, string& ParameterEinheit);
    void Lesen (string& ParameterName, unsigned short& ParameterWert, string& ParameterEinheit);
    void Lesen (string& ParameterName, unsigned int& ParameterWert, string& ParameterEinheit);
    void Lesen (string& ParameterName, unsigned long& ParameterWert, string& ParameterEinheit);
    void Lesen (string& ParameterName, short& ParameterWert, string& ParameterEinheit);
    void Lesen (string& ParameterName, int& ParameterWert, string& ParameterEinheit);
    void Lesen (string& ParameterName, long& ParameterWert, string& ParameterEinheit);
    void Lesen (string& ParameterName, long long& ParameterWert, string& ParameterEinheit);
    void Lesen (string& ParameterName, bool& ParameterWert, string& ParameterEinheit);
    void Lesen (string& ParameterName, string& ParameterWert, string& ParameterEinheit);
    /********************************************************************************************************************************************/
    void Schreiben (string ParameterName, double ParameterWert, string ParameterEinheit);
    void Schreiben (string ParameterName, float ParameterWert, string ParameterEinheit);
    void Schreiben (string ParameterName, unsigned char ParameterWert, string ParameterEinheit);
    void Schreiben (string ParameterName, unsigned short ParameterWert, string ParameterEinheit);
    void Schreiben (string ParameterName, unsigned int ParameterWert, string ParameterEinheit);
    void Schreiben (string ParameterName, unsigned long ParameterWert, string ParameterEinheit);
    void Schreiben (string ParameterName, short ParameterWert, string ParameterEinheit);
    void Schreiben (string ParameterName, int ParameterWert, string ParameterEinheit);
    void Schreiben (string ParameterName, long ParameterWert, string ParameterEinheit);
    void Schreiben (string ParameterName, long long ParameterWert, string ParameterEinheit);
    void Schreiben (string ParameterName, bool ParameterWert, string ParameterEinheit);
    void Schreiben (string ParameterName, string ParameterWert, string ParameterEinheit);
    /********************************************************************************************************************************************/
    void Schreiben (string ParameterName, double ParameterWert, double ScaleWert, string ParameterEinheit);
    void Schreiben (string ParameterName, float ParameterWert, float ScaleWert, string ParameterEinheit);
    void Schreiben (string ParameterName, unsigned char ParameterWert, unsigned char ScaleWert, string ParameterEinheit);
    void Schreiben (string ParameterName, unsigned short ParameterWert, unsigned short ScaleWert, string ParameterEinheit);
    void Schreiben (string ParameterName, unsigned int ParameterWert, unsigned int ScaleWert, string ParameterEinheit);
    void Schreiben (string ParameterName, unsigned long ParameterWert, unsigned long ScaleWert, string ParameterEinheit);
    void Schreiben (string ParameterName, short ParameterWert, short ScaleWert, string ParameterEinheit);
    void Schreiben (string ParameterName, int ParameterWert, int ScaleWert, string ParameterEinheit);
    void Schreiben (string ParameterName, long ParameterWert, long ScaleWert, string ParameterEinheit);
    void Schreiben (string ParameterName, long long ParameterWert, long long ScaleWert, string ParameterEinheit);
    }; // public ref class C_CSV_Parameter_Datei
  } // namespace Schoeller
#endif
