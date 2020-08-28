/********************************************************************************************************************************************/
/*                                                                                                                                          */
/* Source-Datei: UM_CSV_Datei.cpp                                                                                                           */
/*                                                                                                                                          */
/*  Klassen-Member-Definition des Moduls UM_CSV_Datei                                                                                       */
/*                                                                                                                                          */
/*  Marcel Bänfer 07.09.2019                                                                                                                */
/*                                                                                                                                          */
/********************************************************************************************************************************************/

/************************************************************* System-Includes **************************************************************/

/************************************************************ Anwender-Includes *************************************************************/
#include "headers/CSV_Datei.h"
#include <stdlib.h>

/************************************************************ Anwender-Namespace ************************************************************/
using namespace UM_CSV_Datei;

/************************************************************** Konstruktoren ***************************************************************/
C_CSV_Parameter_Datei::C_CSV_Parameter_Datei         ()
  {
  this->Dateistrom = nullptr;
  }

/*************************************************************** Destruktor *****************************************************************/
C_CSV_Parameter_Datei::~C_CSV_Parameter_Datei        ()
  {
  this->Dateistrom = nullptr;
  }

/********************************************** Nicht Öffentliche private Anwender-Methoden *************************************************/
void    C_CSV_Parameter_Datei::Separate              (string            Zeile,               string            (&Datenzelle)[3])
  {
  stringstream  Zeile_ss;

  // Zeilenwerte separieren
  Zeile_ss.str(Zeile);
  for (int i = 0; i < 3; i++)
    {
    getline(Zeile_ss, Datenzelle[i], ';');
    }
  }
bool    C_CSV_Parameter_Datei::To_bool               (string            Datenzelle)
  {
  if      (Datenzelle == "true"  || Datenzelle == "True"  || Datenzelle == "TRUE"  || Datenzelle == "1")
    {
    return (true);
    }
  else if (Datenzelle == "false" || Datenzelle == "False" || Datenzelle == "FALSE" || Datenzelle == "0")
    {
    return (false);
    }
  else
    {
    return (false);
    }
  }
void    C_CSV_Parameter_Datei::New_Line              (int               Streamposition,      string&           NewLine)
  {
  if (Streamposition == 0)
    {
    NewLine = "";
    }
  else if (Streamposition > 0)
    {
    NewLine = "\n";
    }
  }
/****************************************************** Öffentliche Anwender-Methoden *******************************************************/
void    C_CSV_Parameter_Datei::Oeffnen               (string            ParameterDateiName,  Enum_CSV_Access   Access)
  {

  if       (Access == Enum_CSV_Access::Read)
    {
    try
      {
      this->Dateistrom                = new fstream (ParameterDateiName, ios::in);
      }
    catch(exception* e)
      {
      this->Dateistrom                = nullptr;
      }
    }
  else if  (Access == Enum_CSV_Access::Write)
    {
    try
      {
      this->Dateistrom                = new fstream (ParameterDateiName, ios::out);
      }
    catch (exception* e)
      {
      this->Dateistrom                = nullptr;
      }
    }
  else
    {
    this->Dateistrom                  = nullptr;
    }
  }
void    C_CSV_Parameter_Datei::Schliessen            (void)
  {
  if (this->Dateistrom->is_open())
    {
    this->Dateistrom->close();
    delete( this->Dateistrom);
    }
  else
    {
    // tue nichts
    }
  }
bool    C_CSV_Parameter_Datei::IsOpen                (void)
  {
  return (this->Dateistrom->is_open());
  }
/********************************************************************************************************************************************/
void    C_CSV_Parameter_Datei::Lesen                 (double&           ParameterWert)
  {
  string        ParameterName;
  string        ParameterEinheit;
  string        Zeile;
  string        Datenzelle[3];

  // Zeile aus csv-Datei lesen
  getline(*this->Dateistrom, Zeile);

  // Zeilenwerte separieren
  this->Separate(Zeile, Datenzelle);

  // Zeilenwerte aus Datenzellen ausgeben
  ParameterName     = Datenzelle[0];
  ParameterWert     = stod(Datenzelle[1]);
  ParameterEinheit  = Datenzelle[2];
  }
void    C_CSV_Parameter_Datei::Lesen                 (float&            ParameterWert)
  {
  string        ParameterName;
  string        ParameterEinheit;
  string        Zeile;
  string        Datenzelle[3];

  // Zeile aus csv-Datei lesen
  getline(*this->Dateistrom, Zeile);

  // Zeilenwerte separieren
  this->Separate(Zeile, Datenzelle);

  // Zeilenwerte aus Datenzellen ausgeben
  ParameterName     = Datenzelle[0];
  ParameterWert     = stof(Datenzelle[1]);
  ParameterEinheit  = Datenzelle[2];
  }
void    C_CSV_Parameter_Datei::Lesen                 (unsigned char&    ParameterWert)
  {
  string        ParameterName;
  string        ParameterEinheit;
  string        Zeile;
  string        Datenzelle[3];

  // Zeile aus csv-Datei lesen
  getline(*this->Dateistrom, Zeile);

  // Zeilenwerte separieren
  this->Separate(Zeile, Datenzelle);

  // Zeilenwerte aus Datenzellen ausgeben
  ParameterName     = Datenzelle[0];
  ParameterWert     = *Datenzelle[1].c_str();
  ParameterEinheit  = Datenzelle[2];
  }
void    C_CSV_Parameter_Datei::Lesen                 (unsigned short&   ParameterWert)
  {
  string        ParameterName;
  string        ParameterEinheit;
  string        Zeile;
  string        Datenzelle[3];

  // Zeile aus csv-Datei lesen
  getline(*this->Dateistrom, Zeile);

  // Zeilenwerte separieren
  this->Separate(Zeile, Datenzelle);

  // Zeilenwerte aus Datenzellen ausgeben
  ParameterName     = Datenzelle[0];
  ParameterWert     = (unsigned short)stoul(Datenzelle[1]);
  ParameterEinheit  = Datenzelle[2];
  }
void    C_CSV_Parameter_Datei::Lesen                 (unsigned int&     ParameterWert)
  {
  string        ParameterName;
  string        ParameterEinheit;
  string        Zeile;
  string        Datenzelle[3];

  // Zeile aus csv-Datei lesen
  getline(*this->Dateistrom, Zeile);

  // Zeilenwerte separieren
  this->Separate(Zeile, Datenzelle);

  // Zeilenwerte aus Datenzellen ausgeben
  ParameterName     = Datenzelle[0];
  ParameterWert     = (unsigned int)stoul(Datenzelle[1]);
  ParameterEinheit  = Datenzelle[2];
  }
void    C_CSV_Parameter_Datei::Lesen                 (unsigned long&    ParameterWert)
  {
  string        ParameterName;
  string        ParameterEinheit;
  string        Zeile;
  string        Datenzelle[3];

  // Zeile aus csv-Datei lesen
  getline(*this->Dateistrom, Zeile);

  // Zeilenwerte separieren
  this->Separate(Zeile, Datenzelle);

  // Zeilenwerte aus Datenzellen ausgeben
  ParameterName     = Datenzelle[0];
  ParameterWert     = stoul(Datenzelle[1]);
  ParameterEinheit  = Datenzelle[2];
  }
void    C_CSV_Parameter_Datei::Lesen                 (short&            ParameterWert)
  {
  string        ParameterName;
  string        ParameterEinheit;
  string        Zeile;
  string        Datenzelle[3];

  // Zeile aus csv-Datei lesen
  getline(*this->Dateistrom, Zeile);

  // Zeilenwerte separieren
  this->Separate(Zeile, Datenzelle);

  // Zeilenwerte aus Datenzellen ausgeben
  ParameterName     = Datenzelle[0];
  ParameterWert     = (short)stol(Datenzelle[1]);
  ParameterEinheit  = Datenzelle[2];
  }
void    C_CSV_Parameter_Datei::Lesen                 (int&              ParameterWert)
  {
  string        ParameterName;
  string        ParameterEinheit;
  string        Zeile;
  string        Datenzelle[3];

  // Zeile aus csv-Datei lesen
  getline(*this->Dateistrom, Zeile);

  // Zeilenwerte separieren
  this->Separate(Zeile, Datenzelle);

  // Zeilenwerte aus Datenzellen ausgeben
  ParameterName     = Datenzelle[0];
  ParameterWert     = stoi(Datenzelle[1]);
  ParameterEinheit  = Datenzelle[2];
  }
void    C_CSV_Parameter_Datei::Lesen                 (long&             ParameterWert)
  {
  string        ParameterName;
  string        ParameterEinheit;
  string        Zeile;
  string        Datenzelle[3];

  // Zeile aus csv-Datei lesen
  getline(*this->Dateistrom, Zeile);

  // Zeilenwerte separieren
  this->Separate(Zeile, Datenzelle);

  // Zeilenwerte aus Datenzellen ausgeben
  ParameterName     = Datenzelle[0];
  ParameterWert     = stol(Datenzelle[1]);
  ParameterEinheit  = Datenzelle[2];
  }
void    C_CSV_Parameter_Datei::Lesen                 (long long&        ParameterWert)
  {
  string        ParameterName;
  string        ParameterEinheit;
  string        Zeile;
  string        Datenzelle[3];

  // Zeile aus csv-Datei lesen
  getline(*this->Dateistrom, Zeile);

  // Zeilenwerte separieren
  this->Separate(Zeile, Datenzelle);

  // Zeilenwerte aus Datenzellen ausgeben
  ParameterName     = Datenzelle[0];
  ParameterWert     = stoll(Datenzelle[1]);
  ParameterEinheit  = Datenzelle[2];
  }
void    C_CSV_Parameter_Datei::Lesen                 (bool&             ParameterWert)
  {
  string        ParameterName;
  string        ParameterEinheit;
  string        Zeile;
  string        Datenzelle[3];

  // Zeile aus csv-Datei lesen
  getline(*this->Dateistrom, Zeile);

  // Zeilenwerte separieren
  this->Separate(Zeile, Datenzelle);

  // Zeilenwerte aus Datenzellen ausgeben
  ParameterName     = Datenzelle[0];
  ParameterWert     = this->To_bool(Datenzelle[1]);
  ParameterEinheit  = Datenzelle[2];
  }
void    C_CSV_Parameter_Datei::Lesen                 (string&           ParameterWert)
  {
  string        ParameterName;
  string        ParameterEinheit;
  string        Zeile;
  string        Datenzelle[3];

  // Zeile aus csv-Datei lesen
  getline(*this->Dateistrom, Zeile);

  // Zeilenwerte separieren
  this->Separate(Zeile, Datenzelle);

  // Zeilenwerte aus Datenzellen ausgeben
  ParameterName     = Datenzelle[0];
  ParameterWert     = Datenzelle[1];
  ParameterEinheit  = Datenzelle[2];
  }
/********************************************************************************************************************************************/
void    C_CSV_Parameter_Datei::Lesen                 (double&           ParameterWert,       double            ScaleWert)
  {
  string        ParameterName;
  string        ParameterEinheit;
  string        Zeile;
  string        Datenzelle[3];

  // Zeile aus csv-Datei lesen
  getline(*this->Dateistrom, Zeile);

  // Zeilenwerte separieren
  this->Separate(Zeile, Datenzelle);

  // Zeilenwerte aus Datenzellen ausgeben
  ParameterName     = Datenzelle[0];
  ParameterWert     = stod(Datenzelle[1]) / ScaleWert;
  ParameterEinheit  = Datenzelle[2];
  }
void    C_CSV_Parameter_Datei::Lesen                 (float&            ParameterWert,       float             ScaleWert)
  {
  string        ParameterName;
  string        ParameterEinheit;
  string        Zeile;
  string        Datenzelle[3];

  // Zeile aus csv-Datei lesen
  getline(*this->Dateistrom, Zeile);

  // Zeilenwerte separieren
  this->Separate(Zeile, Datenzelle);

  // Zeilenwerte aus Datenzellen ausgeben
  ParameterName     = Datenzelle[0];
  ParameterWert     = stof(Datenzelle[1]) / ScaleWert;
  ParameterEinheit  = Datenzelle[2];
  }
void    C_CSV_Parameter_Datei::Lesen                 (unsigned char&    ParameterWert,       unsigned char     ScaleWert)
  {
  string        ParameterName;
  string        ParameterEinheit;
  string        Zeile;
  string        Datenzelle[3];

  // Zeile aus csv-Datei lesen
  getline(*this->Dateistrom, Zeile);

  // Zeilenwerte separieren
  this->Separate(Zeile, Datenzelle);

  // Zeilenwerte aus Datenzellen ausgeben
  ParameterName     = Datenzelle[0];
  ParameterWert     = *Datenzelle[1].c_str() / ScaleWert;
  ParameterEinheit  = Datenzelle[2];
  }
void    C_CSV_Parameter_Datei::Lesen                 (unsigned short&   ParameterWert,       unsigned short    ScaleWert)
  {
  string        ParameterName;
  string        ParameterEinheit;
  string        Zeile;
  string        Datenzelle[3];

  // Zeile aus csv-Datei lesen
  getline(*this->Dateistrom, Zeile);

  // Zeilenwerte separieren
  this->Separate(Zeile, Datenzelle);

  // Zeilenwerte aus Datenzellen ausgeben
  ParameterName     = Datenzelle[0];
  ParameterWert     = (unsigned short)stoul(Datenzelle[1]) / ScaleWert;
  ParameterEinheit  = Datenzelle[2];
  }
void    C_CSV_Parameter_Datei::Lesen                 (unsigned int&     ParameterWert,       unsigned int      ScaleWert)
  {
  string        ParameterName;
  string        ParameterEinheit;
  string        Zeile;
  string        Datenzelle[3];

  // Zeile aus csv-Datei lesen
  getline(*this->Dateistrom, Zeile);

  // Zeilenwerte separieren
  this->Separate(Zeile, Datenzelle);

  // Zeilenwerte aus Datenzellen ausgeben
  ParameterName     = Datenzelle[0];
  ParameterWert     = (unsigned int)stoul(Datenzelle[1]) / ScaleWert;
  ParameterEinheit  = Datenzelle[2];
  }
void    C_CSV_Parameter_Datei::Lesen                 (unsigned long&    ParameterWert,       unsigned long     ScaleWert)
  {
  string        ParameterName;
  string        ParameterEinheit;
  string        Zeile;
  string        Datenzelle[3];

  // Zeile aus csv-Datei lesen
  getline(*this->Dateistrom, Zeile);

  // Zeilenwerte separieren
  this->Separate(Zeile, Datenzelle);

  // Zeilenwerte aus Datenzellen ausgeben
  ParameterName     = Datenzelle[0];
  ParameterWert     = stoul(Datenzelle[1]) / ScaleWert;
  ParameterEinheit  = Datenzelle[2];
  }
void    C_CSV_Parameter_Datei::Lesen                 (short&            ParameterWert,       short             ScaleWert)
  {
  string        ParameterName;
  string        ParameterEinheit;
  string        Zeile;
  string        Datenzelle[3];

  // Zeile aus csv-Datei lesen
  getline(*this->Dateistrom, Zeile);

  // Zeilenwerte separieren
  this->Separate(Zeile, Datenzelle);

  // Zeilenwerte aus Datenzellen ausgeben
  ParameterName     = Datenzelle[0];
  ParameterWert     = (short)stol(Datenzelle[1]) / ScaleWert;
  ParameterEinheit  = Datenzelle[2];
  }
void    C_CSV_Parameter_Datei::Lesen                 (int&              ParameterWert,       int               ScaleWert)
  {
  string        ParameterName;
  string        ParameterEinheit;
  string        Zeile;
  string        Datenzelle[3];

  // Zeile aus csv-Datei lesen
  getline(*this->Dateistrom, Zeile);

  // Zeilenwerte separieren
  this->Separate(Zeile, Datenzelle);

  // Zeilenwerte aus Datenzellen ausgeben
  ParameterName     = Datenzelle[0];
  ParameterWert     = (int)stol(Datenzelle[1]) / ScaleWert;
  ParameterEinheit  = Datenzelle[2];
  }
void    C_CSV_Parameter_Datei::Lesen                 (long&             ParameterWert,       long              ScaleWert)
  {
  string        ParameterName;
  string        ParameterEinheit;
  string        Zeile;
  string        Datenzelle[3];

  // Zeile aus csv-Datei lesen
  getline(*this->Dateistrom, Zeile);

  // Zeilenwerte separieren
  this->Separate(Zeile, Datenzelle);

  // Zeilenwerte aus Datenzellen ausgeben
  ParameterName     = Datenzelle[0];
  ParameterWert     = stol(Datenzelle[1]) / ScaleWert;
  ParameterEinheit  = Datenzelle[2];
  }
void    C_CSV_Parameter_Datei::Lesen                 (long long&        ParameterWert,       long long         ScaleWert)
  {
  string        ParameterName;
  string        ParameterEinheit;
  string        Zeile;
  string        Datenzelle[3];

  // Zeile aus csv-Datei lesen
  getline(*this->Dateistrom, Zeile);

  // Zeilenwerte separieren
  this->Separate(Zeile, Datenzelle);

  // Zeilenwerte aus Datenzellen ausgeben
  ParameterName     = Datenzelle[0];
  ParameterWert     = stoll(Datenzelle[1]) / ScaleWert;
  ParameterEinheit  = Datenzelle[2];
  }
/********************************************************************************************************************************************/
void    C_CSV_Parameter_Datei::Lesen                 (string&           ParameterName,      double&            ParameterWert,   string&          ParameterEinheit)
  {
  string        Zeile;
  string        Datenzelle[3];

  // Zeile aus csv-Datei lesen
  getline(*this->Dateistrom, Zeile);

  // Zeilenwerte separieren
  this->Separate(Zeile, Datenzelle);

  // Zeilenwerte aus Datenzellen ausgeben
  ParameterName     = Datenzelle[0];
  ParameterWert     = stod(Datenzelle[1]);
  ParameterEinheit  = Datenzelle[2];
  }
void    C_CSV_Parameter_Datei::Lesen                 (string&           ParameterName,      float&             ParameterWert,   string&          ParameterEinheit)
  {
  string        Zeile;
  string        Datenzelle[3];

  // Zeile aus csv-Datei lesen
  getline(*this->Dateistrom, Zeile);

  // Zeilenwerte separieren
  this->Separate(Zeile, Datenzelle);

  // Zeilenwerte aus Datenzellen ausgeben
  ParameterName     = Datenzelle[0];
  ParameterWert     = stof(Datenzelle[1]);
  ParameterEinheit  = Datenzelle[2];
  }
void    C_CSV_Parameter_Datei::Lesen                 (string&           ParameterName,      unsigned char&     ParameterWert,   string&          ParameterEinheit)
  {
  string        Zeile;
  string        Datenzelle[3];

  // Zeile aus csv-Datei lesen
  getline(*this->Dateistrom, Zeile);

  // Zeilenwerte separieren
  this->Separate(Zeile, Datenzelle);

  // Zeilenwerte aus Datenzellen ausgeben
  ParameterName     = Datenzelle[0];
  ParameterWert     = *Datenzelle[1].c_str();
  ParameterEinheit  = Datenzelle[2];
  }
void    C_CSV_Parameter_Datei::Lesen                 (string&           ParameterName,      unsigned short&    ParameterWert,   string&          ParameterEinheit)
  {
  string        Zeile;
  string        Datenzelle[3];

  // Zeile aus csv-Datei lesen
  getline(*this->Dateistrom, Zeile);

  // Zeilenwerte separieren
  this->Separate(Zeile, Datenzelle);

  // Zeilenwerte aus Datenzellen ausgeben
  ParameterName     = Datenzelle[0];
  ParameterWert     = (unsigned short)stoul(Datenzelle[1]);
  ParameterEinheit  = Datenzelle[2];
  }
void    C_CSV_Parameter_Datei::Lesen                 (string&           ParameterName,      unsigned int&      ParameterWert,   string&          ParameterEinheit)
  {
  string        Zeile;
  string        Datenzelle[3];

  // Zeile aus csv-Datei lesen
  getline(*this->Dateistrom, Zeile);

  // Zeilenwerte separieren
  this->Separate(Zeile, Datenzelle);

  // Zeilenwerte aus Datenzellen ausgeben
  ParameterName     = Datenzelle[0];
  ParameterWert     = (unsigned int)stoul(Datenzelle[1]);
  ParameterEinheit  = Datenzelle[2];
  }
void    C_CSV_Parameter_Datei::Lesen                 (string&           ParameterName,      unsigned long&     ParameterWert,   string&          ParameterEinheit)
  {
  string        Zeile;
  string        Datenzelle[3];

  // Zeile aus csv-Datei lesen
  getline(*this->Dateistrom, Zeile);

  // Zeilenwerte separieren
  this->Separate(Zeile, Datenzelle);

  // Zeilenwerte aus Datenzellen ausgeben
  ParameterName     = Datenzelle[0];
  ParameterWert     = stoul(Datenzelle[1]);
  ParameterEinheit  = Datenzelle[2];
  }
void    C_CSV_Parameter_Datei::Lesen                 (string&           ParameterName,      short&             ParameterWert,   string&          ParameterEinheit)
  {
  string        Zeile;
  string        Datenzelle[3];

  // Zeile aus csv-Datei lesen
  getline(*this->Dateistrom, Zeile);

  // Zeilenwerte separieren
  this->Separate(Zeile, Datenzelle);

  // Zeilenwerte aus Datenzellen ausgeben
  ParameterName     = Datenzelle[0];
  ParameterWert     = (short)stol(Datenzelle[1]);
  ParameterEinheit  = Datenzelle[2];
  }
void    C_CSV_Parameter_Datei::Lesen                 (string&           ParameterName,      int&               ParameterWert,   string&          ParameterEinheit)
  {
  string        Zeile;
  string        Datenzelle[3];

  // Zeile aus csv-Datei lesen
  getline(*this->Dateistrom, Zeile);

  // Zeilenwerte separieren
  this->Separate(Zeile, Datenzelle);

  // Zeilenwerte aus Datenzellen ausgeben
  ParameterName     = Datenzelle[0];
  ParameterWert     = (int)stol(Datenzelle[1]);
  ParameterEinheit  = Datenzelle[2];
  }
void    C_CSV_Parameter_Datei::Lesen                 (string&           ParameterName,      long&              ParameterWert,   string&          ParameterEinheit)
  {
  string        Zeile;
  string        Datenzelle[3];

  // Zeile aus csv-Datei lesen
  getline(*this->Dateistrom, Zeile);

  // Zeilenwerte separieren
  this->Separate(Zeile, Datenzelle);

  // Zeilenwerte aus Datenzellen ausgeben
  ParameterName     = Datenzelle[0];
  ParameterWert     = stol(Datenzelle[1]);
  ParameterEinheit  = Datenzelle[2];
  }
void    C_CSV_Parameter_Datei::Lesen                 (string&           ParameterName,      long long&         ParameterWert,   string&          ParameterEinheit)
  {
  string        Zeile;
  string        Datenzelle[3];

  // Zeile aus csv-Datei lesen
  getline(*this->Dateistrom, Zeile);

  // Zeilenwerte separieren
  this->Separate(Zeile, Datenzelle);

  // Zeilenwerte aus Datenzellen ausgeben
  ParameterName     = Datenzelle[0];
  ParameterWert     = stoll(Datenzelle[1]);
  ParameterEinheit  = Datenzelle[2];
  }
void    C_CSV_Parameter_Datei::Lesen                 (string&           ParameterName,      bool&              ParameterWert,   string&          ParameterEinheit)
  {
  string        Zeile;
  string        Datenzelle[3];

  // Zeile aus csv-Datei lesen
  getline(*this->Dateistrom, Zeile);

  // Zeilenwerte separieren
  this->Separate(Zeile, Datenzelle);

  // Zeilenwerte aus Datenzellen ausgeben
  ParameterName     = Datenzelle[0];
  ParameterWert     = this->To_bool(Datenzelle[1]);
  ParameterEinheit  = Datenzelle[2];
  }
void    C_CSV_Parameter_Datei::Lesen                 (string&           ParameterName,      string&            ParameterWert,   string&          ParameterEinheit)
  {
  string        Zeile;
  string        Datenzelle[3];

  // Zeile aus csv-Datei lesen
  getline(*this->Dateistrom, Zeile);

  // Zeilenwerte separieren
  this->Separate(Zeile, Datenzelle);

  // Zeilenwerte aus Datenzellen ausgeben
  ParameterName     = Datenzelle[0];
  ParameterWert     = Datenzelle[1];
  ParameterEinheit  = Datenzelle[2];
  }
/********************************************************************************************************************************************/
void    C_CSV_Parameter_Datei::Schreiben             (string            ParameterName,       double            ParameterWert,    string           ParameterEinheit)
  {
  string NewLine;
  string StreamMessage;

  // Prüfen, ob Zeilenvorschub nötig ist
  this->New_Line(this->Dateistrom->tellp(), NewLine);

  // Parameter in Datei schreiben
  StreamMessage = NewLine + ParameterName + ";" + to_string(ParameterWert) + ";" + ParameterEinheit;
  *this->Dateistrom << StreamMessage;
  }
void    C_CSV_Parameter_Datei::Schreiben             (string            ParameterName,       float             ParameterWert,    string           ParameterEinheit)
  {
  string NewLine;
  string StreamMessage;

  // Prüfen, ob Zeilenvorschub nötig ist
  this->New_Line(this->Dateistrom->tellp(), NewLine);

  // Parameter in Datei schreiben
  StreamMessage = NewLine + ParameterName + ";" + to_string(ParameterWert) + ";" + ParameterEinheit;
  *this->Dateistrom << StreamMessage;
  }
void    C_CSV_Parameter_Datei::Schreiben             (string            ParameterName,       unsigned char     ParameterWert,    string           ParameterEinheit)
  {
  string NewLine;
  string StreamMessage;

  // Prüfen, ob Zeilenvorschub nötig ist
  this->New_Line(this->Dateistrom->tellp(), NewLine);

  // Parameter in Datei schreiben
  StreamMessage = NewLine + ParameterName + ";" + to_string(ParameterWert) + ";" + ParameterEinheit;
  *this->Dateistrom << StreamMessage;
  }
void    C_CSV_Parameter_Datei::Schreiben             (string            ParameterName,       unsigned short    ParameterWert,    string           ParameterEinheit)
  {
  string NewLine;
  string StreamMessage;

  // Prüfen, ob Zeilenvorschub nötig ist
  this->New_Line(this->Dateistrom->tellp(), NewLine);

  // Parameter in Datei schreiben
  StreamMessage = NewLine + ParameterName + ";" + to_string(ParameterWert) + ";" + ParameterEinheit;
  *this->Dateistrom << StreamMessage;
  }
void    C_CSV_Parameter_Datei::Schreiben             (string            ParameterName,       unsigned int      ParameterWert,    string           ParameterEinheit)
  {
  string NewLine;
  string StreamMessage;

  // Prüfen, ob Zeilenvorschub nötig ist
  this->New_Line(this->Dateistrom->tellp(), NewLine);

  // Parameter in Datei schreiben
  StreamMessage = NewLine + ParameterName + ";" + to_string(ParameterWert) + ";" + ParameterEinheit;
  *this->Dateistrom << StreamMessage;
  }
void    C_CSV_Parameter_Datei::Schreiben             (string            ParameterName,       unsigned long     ParameterWert,    string           ParameterEinheit)
  {
  string NewLine;
  string StreamMessage;

  // Prüfen, ob Zeilenvorschub nötig ist
  this->New_Line(this->Dateistrom->tellp(), NewLine);

  // Parameter in Datei schreiben
  StreamMessage = NewLine + ParameterName + ";" + to_string(ParameterWert) + ";" + ParameterEinheit;
  *this->Dateistrom << StreamMessage;
  }
void    C_CSV_Parameter_Datei::Schreiben             (string            ParameterName,       short             ParameterWert,    string           ParameterEinheit)
  {
  string NewLine;
  string StreamMessage;

  // Prüfen, ob Zeilenvorschub nötig ist
  this->New_Line(this->Dateistrom->tellp(), NewLine);

  // Parameter in Datei schreiben
  StreamMessage = NewLine + ParameterName + ";" + to_string(ParameterWert) + ";" + ParameterEinheit;
  *this->Dateistrom << StreamMessage;
  }
void    C_CSV_Parameter_Datei::Schreiben             (string            ParameterName,       int               ParameterWert,    string           ParameterEinheit)
  {
  string NewLine;
  string StreamMessage;

  // Prüfen, ob Zeilenvorschub nötig ist
  this->New_Line(this->Dateistrom->tellp(), NewLine);

  // Parameter in Datei schreiben
  StreamMessage = NewLine + ParameterName + ";" + to_string(ParameterWert) + ";" + ParameterEinheit;
  *this->Dateistrom << StreamMessage;
  }
void    C_CSV_Parameter_Datei::Schreiben             (string            ParameterName,       long              ParameterWert,    string           ParameterEinheit)
  {
  string NewLine;
  string StreamMessage;

  // Prüfen, ob Zeilenvorschub nötig ist
  this->New_Line(this->Dateistrom->tellp(), NewLine);

  // Parameter in Datei schreiben
  StreamMessage = NewLine + ParameterName + ";" + to_string(ParameterWert) + ";" + ParameterEinheit;
  *this->Dateistrom << StreamMessage;
  }
void    C_CSV_Parameter_Datei::Schreiben             (string            ParameterName,       long long         ParameterWert,    string           ParameterEinheit)
  {
  string NewLine;
  string StreamMessage;

  // Prüfen, ob Zeilenvorschub nötig ist
  this->New_Line(this->Dateistrom->tellp(), NewLine);

  // Parameter in Datei schreiben
  StreamMessage = NewLine + ParameterName + ";" + to_string(ParameterWert) + ";" + ParameterEinheit;
  *this->Dateistrom << StreamMessage;
  }
void    C_CSV_Parameter_Datei::Schreiben             (string            ParameterName,       bool              ParameterWert,    string           ParameterEinheit)
  {
  string NewLine;
  string StreamMessage;

  // Prüfen, ob Zeilenvorschub nötig ist
  this->New_Line(this->Dateistrom->tellp(), NewLine);

  // Parameter in Datei schreiben
  StreamMessage = NewLine + ParameterName + ";" + to_string(ParameterWert) + ";" + ParameterEinheit;
  *this->Dateistrom << StreamMessage;
  }
void    C_CSV_Parameter_Datei::Schreiben             (string            ParameterName,       string            ParameterWert,    string           ParameterEinheit)
  {
  string NewLine;
  string StreamMessage;

  // Prüfen, ob Zeilenvorschub nötig ist
  this->New_Line(this->Dateistrom->tellp(), NewLine);

  // Parameter in Datei schreiben
  StreamMessage = NewLine + ParameterName + ";" + ParameterWert + ";" + ParameterEinheit;
  *this->Dateistrom << StreamMessage;
  }
/********************************************************************************************************************************************/
void    C_CSV_Parameter_Datei::Schreiben             (string            ParameterName,       double            ParameterWert,    double           ScaleWert,           string    ParameterEinheit)
  {
  string NewLine;
  string StreamMessage;

  // Prüfen, ob Zeilenvorschub nötig ist
  this->New_Line(this->Dateistrom->tellp(), NewLine);

  // Parameter in Datei schreiben
  StreamMessage = NewLine + ParameterName + ";" + to_string(ParameterWert * ScaleWert) + ";" + ParameterEinheit;
  *this->Dateistrom << StreamMessage;
  }
void    C_CSV_Parameter_Datei::Schreiben             (string            ParameterName,       float             ParameterWert,    float            ScaleWert,           string    ParameterEinheit)
  {
  string NewLine;
  string StreamMessage;

  // Prüfen, ob Zeilenvorschub nötig ist
  this->New_Line(this->Dateistrom->tellp(), NewLine);

  // Parameter in Datei schreiben
  StreamMessage = NewLine + ParameterName + ";" + to_string(ParameterWert * ScaleWert) + ";" + ParameterEinheit;
  *this->Dateistrom << StreamMessage;
  }
void    C_CSV_Parameter_Datei::Schreiben             (string            ParameterName,       unsigned char     ParameterWert,    unsigned char    ScaleWert,           string    ParameterEinheit)
  {
  string NewLine;
  string StreamMessage;

  // Prüfen, ob Zeilenvorschub nötig ist
  this->New_Line(this->Dateistrom->tellp(), NewLine);

  // Parameter in Datei schreiben
  StreamMessage = NewLine + ParameterName + ";" + to_string(ParameterWert * ScaleWert) + ";" + ParameterEinheit;
  *this->Dateistrom << StreamMessage;
  }
void    C_CSV_Parameter_Datei::Schreiben             (string            ParameterName,       unsigned short    ParameterWert,    unsigned short   ScaleWert,           string    ParameterEinheit)
  {
  string NewLine;
  string StreamMessage;

  // Prüfen, ob Zeilenvorschub nötig ist
  this->New_Line(this->Dateistrom->tellp(), NewLine);

  // Parameter in Datei schreiben
  StreamMessage = NewLine + ParameterName + ";" + to_string(ParameterWert * ScaleWert) + ";" + ParameterEinheit;
  *this->Dateistrom << StreamMessage;
  }
void    C_CSV_Parameter_Datei::Schreiben             (string            ParameterName,       unsigned int      ParameterWert,    unsigned int     ScaleWert,           string    ParameterEinheit)
  {
  string NewLine;
  string StreamMessage;

  // Prüfen, ob Zeilenvorschub nötig ist
  this->New_Line(this->Dateistrom->tellp(), NewLine);

  // Parameter in Datei schreiben
  StreamMessage = NewLine + ParameterName + ";" + to_string(ParameterWert * ScaleWert) + ";" + ParameterEinheit;
  *this->Dateistrom << StreamMessage;
  }
void    C_CSV_Parameter_Datei::Schreiben             (string            ParameterName,       unsigned long     ParameterWert,    unsigned long    ScaleWert,           string    ParameterEinheit)
  {
  string NewLine;
  string StreamMessage;

  // Prüfen, ob Zeilenvorschub nötig ist
  this->New_Line(this->Dateistrom->tellp(), NewLine);

  // Parameter in Datei schreiben
  StreamMessage = NewLine + ParameterName + ";" + to_string(ParameterWert * ScaleWert) + ";" + ParameterEinheit;
  *this->Dateistrom << StreamMessage;
  }
void    C_CSV_Parameter_Datei::Schreiben             (string            ParameterName,       short             ParameterWert,    short            ScaleWert,           string    ParameterEinheit)
  {
  string NewLine;
  string StreamMessage;

  // Prüfen, ob Zeilenvorschub nötig ist
  this->New_Line(this->Dateistrom->tellp(), NewLine);

  // Parameter in Datei schreiben
  StreamMessage = NewLine + ParameterName + ";" + to_string(ParameterWert * ScaleWert) + ";" + ParameterEinheit;
  *this->Dateistrom << StreamMessage;
  }
void    C_CSV_Parameter_Datei::Schreiben             (string            ParameterName,       int               ParameterWert,    int              ScaleWert,           string    ParameterEinheit)
  {
  string NewLine;
  string StreamMessage;

  // Prüfen, ob Zeilenvorschub nötig ist
  this->New_Line(this->Dateistrom->tellp(), NewLine);

  // Parameter in Datei schreiben
  StreamMessage = NewLine + ParameterName + ";" + to_string(ParameterWert * ScaleWert) + ";" + ParameterEinheit;
  *this->Dateistrom << StreamMessage;
  }
void    C_CSV_Parameter_Datei::Schreiben             (string            ParameterName,       long              ParameterWert,    long             ScaleWert,           string    ParameterEinheit)
  {
  string NewLine;
  string StreamMessage;

  // Prüfen, ob Zeilenvorschub nötig ist
  this->New_Line(this->Dateistrom->tellp(), NewLine);

  // Parameter in Datei schreiben
  StreamMessage = NewLine + ParameterName + ";" + to_string(ParameterWert * ScaleWert) + ";" + ParameterEinheit;
  *this->Dateistrom << StreamMessage;
  }
void    C_CSV_Parameter_Datei::Schreiben             (string            ParameterName,       long long         ParameterWert,    long long        ScaleWert,           string    ParameterEinheit)
  {
  string NewLine;
  string StreamMessage;

  // Prüfen, ob Zeilenvorschub nötig ist
  this->New_Line(this->Dateistrom->tellp(), NewLine);

  // Parameter in Datei schreiben
  StreamMessage = NewLine + ParameterName + ";" + to_string(ParameterWert * ScaleWert) + ";" + ParameterEinheit;
  *this->Dateistrom << StreamMessage;
  }
