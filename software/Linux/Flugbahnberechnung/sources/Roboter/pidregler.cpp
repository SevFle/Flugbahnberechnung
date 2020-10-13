#include "headers/Roboter/pidregler.h"

using namespace pidRegler;

/*************************************************************** C_PID_Regler ***************************************************************/
/*************************************************************** Konstruktoren **************************************************************/
C_PID_Regler::C_PID_Regler                                                                                  (void)
  {
  this->Regelabweichung_0    = 0.0;
  this->Regelabweichung_1    = 0.0;
  this->Kp                   = 0.0;
  this->Tn                   = 0.0;
  this->Tv                   = 0.0;
  this->P_Stellwert          = 0.0;
  this->I_Stellwert          = 0.0;
  this->D_Stellwert          = 0.0;
  this->P_Regler_Enabled     = false;
  this->I_Regler_Enabled     = false;
  this->D_Regler_Enabled     = false;
  }

/*************************************************************** Destruktoren **************************************************************/
C_PID_Regler::~C_PID_Regler                                                                                 (void)
  {
  this->D_Regler_Enabled     = false;
  this->I_Regler_Enabled     = false;
  this->P_Regler_Enabled     = false;
  this->D_Stellwert          = 0.0;
  this->I_Stellwert          = 0.0;
  this->P_Stellwert          = 0.0;
  this->Tv                   = 0.0;
  this->Tn                   = 0.0;
  this->Kp                   = 0.0;
  this->Regelabweichung_1    = 0.0;
  this->Regelabweichung_0    = 0.0;
  }

/****************************************************** ffentliche Funktionen *******************************************************/
void                         C_PID_Regler::PID_Regler                                                       (double                Istwert,           double                Sollwert,              double              Vorsteuerwert,             double&    Stellwert)
  {
  this->Regelabweichung_1  = this->Regelabweichung_0;
  this->Regelabweichung_0  = Sollwert - Istwert;

  if (this->P_Regler_Enabled)
    {
    this->P_Stellwert  = this->Kp * this->Regelabweichung_0;
    }
  else // if (!this->P_Regler_enabled)
    {
    this->P_Stellwert  = 0.0;
    }

  if (this->I_Regler_Enabled)
    {
    this->I_Stellwert += this->Kp * (this->Taktzeit / this->Tn) * this->Regelabweichung_0;
    }
  else  // if (!this->I_Regler_enabled)
    {
    this->I_Stellwert  = 0.0;
    }

  if (this->D_Regler_Enabled)
    {
    this->D_Stellwert  = this->Kp * (this->Tv / this->Taktzeit) * (this->Regelabweichung_0 - this->Regelabweichung_1);
    }
  else  // if (!this->D_Regler_enabled)
    {
    this->D_Stellwert  = 0.0;
    }

  Stellwert = Vorsteuerwert + this->P_Stellwert + this->I_Stellwert + this->D_Stellwert;
  }
void                         C_PID_Regler::PID_Regler                                                       (double                Regelabweichung,   double&               Stellwert)
  {
  this->Regelabweichung_1  = this->Regelabweichung_0;
  this->Regelabweichung_0  = Regelabweichung;

  if (this->P_Regler_Enabled)
    {
    this->P_Stellwert  = this->Kp * this->Regelabweichung_0;
    }
  else // if (!this->P_Regler_enabled)
    {
    this->P_Stellwert  = 0.0;
    }

  if (this->I_Regler_Enabled)
    {
    this->I_Stellwert += this->Kp * (this->Taktzeit / this->Tn) * this->Regelabweichung_0;
    }
  else  // if (!this->I_Regler_enabled)
    {
    this->I_Stellwert  = 0.0;
    }

  if (this->D_Regler_Enabled)
    {
    this->D_Stellwert  = this->Kp * (this->Tv / this->Taktzeit) * (this->Regelabweichung_0 - this->Regelabweichung_1);
    }
  else  // if (!this->D_Regler_enabled)
    {
    this->D_Stellwert  = 0.0;
    }

  Stellwert = this->P_Stellwert + this->I_Stellwert + this->D_Stellwert;
  }
void                         C_PID_Regler::Set_PID_Parameter                                                (bool                  P_Enabled,         bool                  I_Enabled,             bool                D_Enabled,                 double     Kp,         double   Tn, double   Tv, double  Taktzeit)
  {
  this->P_Regler_Enabled   = P_Enabled;
  this->I_Regler_Enabled   = I_Enabled;
  this->D_Regler_Enabled   = D_Enabled;

  this->Kp                 = Kp;
  this->Tn                 = Tn;
  this->Tv                 = Tv;

  this->Taktzeit           = Taktzeit;

  this->Reset_PID_Regler();
  }
void                         C_PID_Regler::Get_PID_Parameter                                                (bool&                 P_Enabled,         bool&                 I_Enabled,             bool&               D_Enabled,                 double&    Kp,         double&  Tn, double&  Tv, double& Taktzeit)
  {
  P_Enabled   = this->P_Regler_Enabled;
  I_Enabled   = this->I_Regler_Enabled;
  D_Enabled   = this->D_Regler_Enabled;

  Kp          = this->Kp;
  Tn          = this->Tn;
  Tv          = this->Tv;

  Taktzeit    = this->Taktzeit;
  }
void                         C_PID_Regler::Reset_PID_Regler                                                 (void)
  {
  this->Regelabweichung_0 = 0.0;
  this->Regelabweichung_1 = 0.0;

  this->P_Stellwert       = 0.0;
  this->I_Stellwert       = 0.0;
  this->D_Stellwert       = 0.0;
  }

