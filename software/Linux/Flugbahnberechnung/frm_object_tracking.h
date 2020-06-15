#ifndef FRM_OBJECT_TRACKING_H
#define FRM_OBJECT_TRACKING_H

#include <QDialog>

#include "Main.h"

#include "ui_frm_object_tracking.h"

class C_frm_object_tracking : public QDialog
{
    Q_OBJECT

public:
    C_frm_object_tracking(C_GlobalObjects* GlobalObjects, C_Main* Main, QWidget *parent = nullptr);
    ~C_frm_object_tracking();

private:
  Ui::C_frm_object_tracking* Ui;



  C_GlobalObjects* GlobalObjects;
  C_Main*         Main;
  int Zaehler;
  QTimer*         Taktgeber;
  int             Taktgeber_Intervall;


private:
  void showEvent (QShowEvent* ShowEvent) override;
  void closeEvent (QCloseEvent* CloseEvent) override;
  bool eventFilter (QObject* Object, QEvent* Event) override;
};

#endif // FRM_OBJECT_TRACKING_H
