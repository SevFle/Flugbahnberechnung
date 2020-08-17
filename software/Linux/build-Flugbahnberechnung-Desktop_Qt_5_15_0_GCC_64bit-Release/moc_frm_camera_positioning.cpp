/****************************************************************************
** Meta object code from reading C++ file 'frm_camera_positioning.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Flugbahnberechnung/headers/frm_camera_positioning.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frm_camera_positioning.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_frm_Camera_Positioning__C_frm_Camera_Positioning_t {
    QByteArrayData data[13];
    char stringdata0[186];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_frm_Camera_Positioning__C_frm_Camera_Positioning_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_frm_Camera_Positioning__C_frm_Camera_Positioning_t qt_meta_stringdata_frm_Camera_Positioning__C_frm_Camera_Positioning = {
    {
QT_MOC_LITERAL(0, 0, 48), // "frm_Camera_Positioning::C_frm..."
QT_MOC_LITERAL(1, 49, 14), // "Taktgeber_Tick"
QT_MOC_LITERAL(2, 64, 0), // ""
QT_MOC_LITERAL(3, 65, 19), // "on_bt_apply_clicked"
QT_MOC_LITERAL(4, 85, 18), // "on_bt_exit_clicked"
QT_MOC_LITERAL(5, 104, 13), // "set_num_value"
QT_MOC_LITERAL(6, 118, 16), // "std::vector<int>"
QT_MOC_LITERAL(7, 135, 11), // "camera_list"
QT_MOC_LITERAL(8, 147, 11), // "FillMat2Lbl"
QT_MOC_LITERAL(9, 159, 8), // "cv::Mat&"
QT_MOC_LITERAL(10, 168, 3), // "img"
QT_MOC_LITERAL(11, 172, 7), // "QLabel*"
QT_MOC_LITERAL(12, 180, 5) // "label"

    },
    "frm_Camera_Positioning::C_frm_Camera_Positioning\0"
    "Taktgeber_Tick\0\0on_bt_apply_clicked\0"
    "on_bt_exit_clicked\0set_num_value\0"
    "std::vector<int>\0camera_list\0FillMat2Lbl\0"
    "cv::Mat&\0img\0QLabel*\0label"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_frm_Camera_Positioning__C_frm_Camera_Positioning[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x08 /* Private */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    0,   46,    2, 0x08 /* Private */,
       5,    1,   47,    2, 0x08 /* Private */,
       5,    0,   50,    2, 0x08 /* Private */,
       8,    2,   51,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 11,   10,   12,

       0        // eod
};

void frm_Camera_Positioning::C_frm_Camera_Positioning::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<C_frm_Camera_Positioning *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Taktgeber_Tick(); break;
        case 1: _t->on_bt_apply_clicked(); break;
        case 2: _t->on_bt_exit_clicked(); break;
        case 3: _t->set_num_value((*reinterpret_cast< std::vector<int>(*)>(_a[1]))); break;
        case 4: _t->set_num_value(); break;
        case 5: _t->FillMat2Lbl((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< QLabel*(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QLabel* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject frm_Camera_Positioning::C_frm_Camera_Positioning::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_frm_Camera_Positioning__C_frm_Camera_Positioning.data,
    qt_meta_data_frm_Camera_Positioning__C_frm_Camera_Positioning,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *frm_Camera_Positioning::C_frm_Camera_Positioning::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *frm_Camera_Positioning::C_frm_Camera_Positioning::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_frm_Camera_Positioning__C_frm_Camera_Positioning.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int frm_Camera_Positioning::C_frm_Camera_Positioning::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
