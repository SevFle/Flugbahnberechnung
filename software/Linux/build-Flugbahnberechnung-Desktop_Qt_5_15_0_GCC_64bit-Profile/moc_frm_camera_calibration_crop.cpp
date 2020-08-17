/****************************************************************************
** Meta object code from reading C++ file 'frm_camera_calibration_crop.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Flugbahnberechnung/headers/frm_camera_calibration_crop.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frm_camera_calibration_crop.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_frm_Camera_Calibration_Crop__C_frm_Camera_Calibration_Crop_t {
    QByteArrayData data[8];
    char stringdata0[117];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_frm_Camera_Calibration_Crop__C_frm_Camera_Calibration_Crop_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_frm_Camera_Calibration_Crop__C_frm_Camera_Calibration_Crop_t qt_meta_stringdata_frm_Camera_Calibration_Crop__C_frm_Camera_Calibration_Crop = {
    {
QT_MOC_LITERAL(0, 0, 58), // "frm_Camera_Calibration_Crop::..."
QT_MOC_LITERAL(1, 59, 14), // "Taktgeber_Tick"
QT_MOC_LITERAL(2, 74, 0), // ""
QT_MOC_LITERAL(3, 75, 14), // "Fill_Mat_2_Lbl"
QT_MOC_LITERAL(4, 90, 8), // "cv::Mat&"
QT_MOC_LITERAL(5, 99, 3), // "img"
QT_MOC_LITERAL(6, 103, 7), // "QLabel*"
QT_MOC_LITERAL(7, 111, 5) // "label"

    },
    "frm_Camera_Calibration_Crop::C_frm_Camera_Calibration_Crop\0"
    "Taktgeber_Tick\0\0Fill_Mat_2_Lbl\0cv::Mat&\0"
    "img\0QLabel*\0label"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_frm_Camera_Calibration_Crop__C_frm_Camera_Calibration_Crop[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x08 /* Private */,
       3,    2,   25,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 6,    5,    7,

       0        // eod
};

void frm_Camera_Calibration_Crop::C_frm_Camera_Calibration_Crop::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<C_frm_Camera_Calibration_Crop *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Taktgeber_Tick(); break;
        case 1: _t->Fill_Mat_2_Lbl((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< QLabel*(*)>(_a[2]))); break;
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

QT_INIT_METAOBJECT const QMetaObject frm_Camera_Calibration_Crop::C_frm_Camera_Calibration_Crop::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_frm_Camera_Calibration_Crop__C_frm_Camera_Calibration_Crop.data,
    qt_meta_data_frm_Camera_Calibration_Crop__C_frm_Camera_Calibration_Crop,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *frm_Camera_Calibration_Crop::C_frm_Camera_Calibration_Crop::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *frm_Camera_Calibration_Crop::C_frm_Camera_Calibration_Crop::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_frm_Camera_Calibration_Crop__C_frm_Camera_Calibration_Crop.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int frm_Camera_Calibration_Crop::C_frm_Camera_Calibration_Crop::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
