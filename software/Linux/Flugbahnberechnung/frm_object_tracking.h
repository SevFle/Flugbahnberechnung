#ifndef FRM_OBJECT_TRACKING_H
#define FRM_OBJECT_TRACKING_H

#include <QDialog>

namespace Ui {
class frm_object_tracking;
}

class frm_object_tracking : public QDialog
{
    Q_OBJECT

public:
    explicit frm_object_tracking(QWidget *parent = nullptr);
    ~frm_object_tracking();

private:
    Ui::frm_object_tracking *ui;
};

#endif // FRM_OBJECT_TRACKING_H
