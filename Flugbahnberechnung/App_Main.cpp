/********************************************************************************************************************************************/
/*                                                                                                                                          */
/*  Source-Datei: App_Main.cpp                                                                                                              */
/*                                                                                                                                          */
/*                                                                                                                                          */
/*                                                                                                                                          */
/*  Marcel Bänfer      12.08.2019                                                                                                           */
/*                                                                                                                                          */
/********************************************************************************************************************************************/
#pragma once

/************************************************************ Anwender-Includes *************************************************************/
#include "GlobalObjects.h"
#include "Main.h"
#include <locale>

/************************************************************** using namespaces **************************************************************/
using namespace nmsp_GlobalObjects;
using namespace nmsp_Main;
using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main (void)
  {
  Application::EnableVisualStyles();
  Application::SetCompatibleTextRenderingDefault (false);

  C_GlobalObjects* GlobalObjects = new C_GlobalObjects();
  C_Main^          Main          = gcnew C_Main (GlobalObjects);

  Application::Run (Main->frm_Main);

  delete (Main);
  delete (GlobalObjects);

  return (0);
  } // int main (void)
