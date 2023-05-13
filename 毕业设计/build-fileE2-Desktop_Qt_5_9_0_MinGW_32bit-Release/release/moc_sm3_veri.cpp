/****************************************************************************
** Meta object code from reading C++ file 'sm3_veri.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../fileE2/sm3_veri.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sm3_veri.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_sm3_veri_t {
    QByteArrayData data[6];
    char stringdata0[154];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_sm3_veri_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_sm3_veri_t qt_meta_stringdata_sm3_veri = {
    {
QT_MOC_LITERAL(0, 0, 8), // "sm3_veri"
QT_MOC_LITERAL(1, 9, 35), // "on_btn_sm3veri_cho_raw_file_c..."
QT_MOC_LITERAL(2, 45, 0), // ""
QT_MOC_LITERAL(3, 46, 35), // "on_btn_sm3veri_cho_sig_file_c..."
QT_MOC_LITERAL(4, 82, 35), // "on_btn_sm3veri_cho_pub_file_c..."
QT_MOC_LITERAL(5, 118, 35) // "on_btn_sm3veri_verification_c..."

    },
    "sm3_veri\0on_btn_sm3veri_cho_raw_file_clicked\0"
    "\0on_btn_sm3veri_cho_sig_file_clicked\0"
    "on_btn_sm3veri_cho_pub_file_clicked\0"
    "on_btn_sm3veri_verification_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_sm3_veri[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x08 /* Private */,
       3,    0,   35,    2, 0x08 /* Private */,
       4,    0,   36,    2, 0x08 /* Private */,
       5,    0,   37,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void sm3_veri::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        sm3_veri *_t = static_cast<sm3_veri *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_btn_sm3veri_cho_raw_file_clicked(); break;
        case 1: _t->on_btn_sm3veri_cho_sig_file_clicked(); break;
        case 2: _t->on_btn_sm3veri_cho_pub_file_clicked(); break;
        case 3: _t->on_btn_sm3veri_verification_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject sm3_veri::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_sm3_veri.data,
      qt_meta_data_sm3_veri,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *sm3_veri::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *sm3_veri::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_sm3_veri.stringdata0))
        return static_cast<void*>(const_cast< sm3_veri*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int sm3_veri::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
