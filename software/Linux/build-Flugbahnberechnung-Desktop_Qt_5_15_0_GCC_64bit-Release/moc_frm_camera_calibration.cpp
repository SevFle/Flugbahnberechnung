/****************************************************************************
** Meta object code from reading C++ file 'frm_camera_calibration.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Flugbahnberechnung/headers/frm_camera_calibration.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frm_camera_calibration.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_frm_Camera_Calibration__C_frm_Camera_Calibration_t {
    QByteArrayData data[20];
    char stringdata0[363];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_frm_Camera_Calibration__C_frm_Camera_Calibration_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_frm_Camera_Calibration__C_frm_Camera_Calibration_t qt_meta_stringdata_frm_Camera_Calibration__C_frm_Camera_Calibration = {
    {
QT_MOC_LITERAL(0, 0, 48), // "frm_Camera_Calibration::C_frm..."
QT_MOC_LITERAL(1, 49, 14), // "Taktgeber_Tick"
QT_MOC_LITERAL(2, 64, 0), // ""
QT_MOC_LITERAL(3, 65, 11), // "FillMat2Lbl"
QT_MOC_LITERAL(4, 77, 8), // "cv::Mat&"
QT_MOC_LITERAL(5, 86, 3), // "img"
QT_MOC_LITERAL(6, 90, 7), // "QLabel*"
QT_MOC_LITERAL(7, 98, 5), // "label"
QT_MOC_LITERAL(8, 104, 25), // "camera_calibration_thread"
QT_MOC_LITERAL(9, 130, 4), // "This"
QT_MOC_LITERAL(10, 135, 28), // "sm_Single_camera_calibration"
QT_MOC_LITERAL(11, 164, 28), // "sm_Stereo_camera_calibration"
QT_MOC_LITERAL(12, 193, 19), // "on_bt_start_clicked"
QT_MOC_LITERAL(13, 213, 18), // "on_bt_exit_clicked"
QT_MOC_LITERAL(14, 232, 29), // "on_num_camera_id_valueChanged"
QT_MOC_LITERAL(15, 262, 4), // "arg1"
QT_MOC_LITERAL(16, 267, 32), // "on_rb_single_calibration_clicked"
QT_MOC_LITERAL(17, 300, 32), // "on_rb_stereo_calibration_clicked"
QT_MOC_LITERAL(18, 333, 19), // "on_bt_photo_clicked"
QT_MOC_LITERAL(19, 353, 9) // "ShowTable"

    },
    "frm_Camera_Calibration::C_frm_Camera_Calibration\0"
    "Taktgeber_Tick\0\0FillMat2Lbl\0cv::Mat&\0"
    "img\0QLabel*\0label\0camera_calibration_thread\0"
    "This\0sm_Single_camera_calibration\0"
    "sm_Stereo_camera_calibration\0"
    "on_bt_start_clicked\0on_bt_exit_clicked\0"
    "on_num_camera_id_valueChanged\0arg1\0"
    "on_rb_single_calibration_clicked\0"
    "on_rb_stereo_calibration_clicked\0"
    "on_bt_photo_clicked\0ShowTable"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_frm_Camera_Calibration__C_frm_Camera_Calibration[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    2,   75,    2, 0x08 /* Private */,
       8,    1,   80,    2, 0x08 /* Private */,
      10,    0,   83,    2, 0x08 /* Private */,
      11,    0,   84,    2, 0x08 /* Private */,
      12,    0,   85,    2, 0x08 /* Private */,
      13,    0,   86,    2, 0x08 /* Private */,
      14,    1,   87,    2, 0x08 /* Private */,
      16,    0,   90,    2, 0x08 /* Private */,
      17,    0,   91,    2, 0x08 /* Private */,
      18,    0,   92,    2, 0x08 /* Private */,
      19,    0,   93,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 6,    5,    7,
    QMetaType::Void, QMetaType::VoidStar,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void frm_Camera_Calibration::C_frm_Camera_Calibration::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<C_frm_Camera_Calibration *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Taktgeber_Tick(); break;
        case 1: _t->FillMat2Lbl((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< QLabel*(*)>(_a[2]))); break;
        case 2: _t->camera_calibration_thread((*reinterpret_cast< void*(*)>(_a[1]))); break;
        case 3: _t->sm_Single_camera_calibration(); break;
        case 4: _t->sm_Stereo_camera_calibration(); break;
        case 5: _t->on_bt_start_clicked(); break;
        case 6: _t->on_bt_exit_clicked(); break;
        case 7: _t->on_num_camera_id_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_rb_single_calibration_clicked(); break;
        case 9: _t->on_rb_stereo_calibration_clicked(); break;
        case 10: _t->on_bt_photo_clicked(); break;
        case 11: _t->ShowTable(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QLabel* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject frm_Camera_Calibration::C_frm_Camera_Calibration::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_frm_Camera_Calibration__C_frm_Camera_Calibration.data,
    qt_meta_data_frm_Camera_Calibration__C_frm_Camera_Calibration,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *frm_Camera_Calibration::C_frm_Camera_Calibration::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *frm_Camera_Calibration::C_frm_Camera_Calibration::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_frm_Camera_Calibration__C_frm_Camera_Calibration.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int frm_Camera_Calibration::C_frm_Camera_Calibration::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
