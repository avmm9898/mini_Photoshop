/****************************************************************************
** Meta object code from reading C++ file 'photo_frame.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "C:/Users/avmm9/Documents/GitHub/Photoshop-project/photo_frame.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'photo_frame.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_photo_frame_t {
    QByteArrayData data[9];
    char stringdata0[115];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_photo_frame_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_photo_frame_t qt_meta_stringdata_photo_frame = {
    {
QT_MOC_LITERAL(0, 0, 11), // "photo_frame"
QT_MOC_LITERAL(1, 12, 10), // "Mat2QImage"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 3), // "Mat"
QT_MOC_LITERAL(4, 28, 3), // "src"
QT_MOC_LITERAL(5, 32, 21), // "on_zoomin_btn_clicked"
QT_MOC_LITERAL(6, 54, 22), // "on_zoomout_btn_clicked"
QT_MOC_LITERAL(7, 77, 18), // "on_fit_btn_clicked"
QT_MOC_LITERAL(8, 96, 18) // "on_ori_btn_clicked"

    },
    "photo_frame\0Mat2QImage\0\0Mat\0src\0"
    "on_zoomin_btn_clicked\0on_zoomout_btn_clicked\0"
    "on_fit_btn_clicked\0on_ori_btn_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_photo_frame[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x0a /* Public */,
       5,    0,   42,    2, 0x08 /* Private */,
       6,    0,   43,    2, 0x08 /* Private */,
       7,    0,   44,    2, 0x08 /* Private */,
       8,    0,   45,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::QImage, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void photo_frame::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        photo_frame *_t = static_cast<photo_frame *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { QImage _r = _t->Mat2QImage((*reinterpret_cast< Mat(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QImage*>(_a[0]) = std::move(_r); }  break;
        case 1: _t->on_zoomin_btn_clicked(); break;
        case 2: _t->on_zoomout_btn_clicked(); break;
        case 3: _t->on_fit_btn_clicked(); break;
        case 4: _t->on_ori_btn_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject photo_frame::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_photo_frame.data,
      qt_meta_data_photo_frame,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *photo_frame::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *photo_frame::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_photo_frame.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int photo_frame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
