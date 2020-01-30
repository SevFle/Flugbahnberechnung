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

/************************************************************** using namespaces **************************************************************/
using namespace NmSp_GlobalObjects;
using namespace NmSp_Main;
using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main (void)
  {
  Application::EnableVisualStyles                ();
  Application::SetCompatibleTextRenderingDefault (false);

  C_GlobalObjects^  GlobalObjects = gcnew C_GlobalObjects ();
  C_Main^           Main          = gcnew C_Main          (GlobalObjects);

  Application::Run                                                 (Main->frm_Main);

  delete (Main);
  delete (GlobalObjects);

  return (0);
  } // int main (void)

