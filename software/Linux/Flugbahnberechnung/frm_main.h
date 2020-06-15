#ifndef FRM_MAIN_H
#define FRM_MAIN_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class frm_main; }
QT_END_NAMESPACE

class frm_main : public QMainWindow
{
    Q_OBJECT

public:
    frm_main(QWidget *parent = nullptr);
    ~frm_main();

private:
    Ui::frm_main *ui;
};
#endif // FRM_MAIN_H
