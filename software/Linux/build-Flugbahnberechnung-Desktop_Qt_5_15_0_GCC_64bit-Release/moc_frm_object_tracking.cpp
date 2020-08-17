/****************************************************************************
** Meta object code from reading C++ file 'frm_object_tracking.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Flugbahnberechnung/headers/frm_object_tracking.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frm_object_tracking.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_frm_Object_Tracking__C_frm_Object_Tracking_t {
    QByteArrayData data[12];
    char stringdata0[175];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_frm_Object_Tracking__C_frm_Object_Tracking_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_frm_Object_Tracking__C_frm_Object_Tracking_t qt_meta_stringdata_frm_Object_Tracking__C_frm_Object_Tracking = {
    {
QT_MOC_LITERAL(0, 0, 42), // "frm_Object_Tracking::C_frm_Ob..."
QT_MOC_LITERAL(1, 43, 19), // "on_bt_start_clicked"
QT_MOC_LITERAL(2, 63, 0), // ""
QT_MOC_LITERAL(3, 64, 18), // "on_bt_exit_clicked"
QT_MOC_LITERAL(4, 83, 29), // "on_num_camera_id_valueChanged"
QT_MOC_LITERAL(5, 113, 4), // "arg1"
QT_MOC_LITERAL(6, 118, 14), // "Taktgeber_Tick"
QT_MOC_LITERAL(7, 133, 14), // "Fill_Mat_2_Lbl"
QT_MOC_LITERAL(8, 148, 8), // "cv::Mat&"
QT_MOC_LITERAL(9, 157, 3), // "img"
QT_MOC_LITERAL(10, 161, 7), // "QLabel*"
QT_MOC_LITERAL(11, 169, 5) // "label"

    },
    "frm_Object_Tracking::C_frm_Object_Tracking\0"
    "on_bt_start_clicked\0\0on_bt_exit_clicked\0"
    "on_num_camera_id_valueChanged\0arg1\0"
    "Taktgeber_Tick\0Fill_Mat_2_Lbl\0cv::Mat&\0"
    "img\0QLabel*\0label"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_frm_Object_Tracking__C_frm_Object_Tracking[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x08 /* Private */,
       3,    0,   40,    2, 0x08 /* Private */,
       4,    1,   41,    2, 0x08 /* Private */,
       6,    0,   44,    2, 0x08 /* Private */,
       7,    2,   45,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 10,    9,   11,

       0        // eod
};

void frm_Object_Tracking::C_frm_Object_Tracking::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<C_frm_Object_Tracking *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_bt_start_clicked(); break;
        case 1: _t->on_bt_exit_clicked(); break;
        case 2: _t->on_num_camera_id_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->Taktgeber_Tick(); break;
        case 4: _t->Fill_Mat_2_Lbl((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< QLabel*(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QLabel* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject frm_Object_Tracking::C_frm_Object_Tracking::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_frm_Object_Tracking__C_frm_Object_Tracking.data,
    qt_meta_data_frm_Object_Tracking__C_frm_Object_Tracking,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *frm_Object_Tracking::C_frm_Object_Tracking::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *frm_Object_Tracking::C_frm_Object_Tracking::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_frm_Object_Tracking__C_frm_Object_Tracking.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int frm_Object_Tracking::C_frm_Object_Tracking::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
