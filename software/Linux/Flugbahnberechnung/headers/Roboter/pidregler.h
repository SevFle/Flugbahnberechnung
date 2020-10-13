#ifndef PIDREGLER_H
#define PIDREGLER_H

#endif // PIDREGLER_H
namespace pidRegler
  {
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
  }
