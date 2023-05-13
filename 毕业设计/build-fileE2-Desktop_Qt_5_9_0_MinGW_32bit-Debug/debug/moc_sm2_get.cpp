/****************************************************************************
** Meta object code from reading C++ file 'sm2_get.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../fileE2/sm2_get.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sm2_get.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_sm2_get_t {
    QByteArrayData data[4];
    char stringdata0[73];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_sm2_get_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_sm2_get_t qt_meta_stringdata_sm2_get = {
    {
QT_MOC_LITERAL(0, 0, 7), // "sm2_get"
QT_MOC_LITERAL(1, 8, 29), // "on_sm2_get_choDir_btn_clicked"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 33) // "on_sm2_get_getAndSave_btn_cli..."

    },
    "sm2_get\0on_sm2_get_choDir_btn_clicked\0"
    "\0on_sm2_get_getAndSave_btn_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_sm2_get[] = {

 // content:
       7,       // revision
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
       3,    0,   25,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void sm2_get::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        sm2_get *_t = static_cast<sm2_get *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_sm2_get_choDir_btn_clicked(); break;
        case 1: _t->on_sm2_get_getAndSave_btn_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject sm2_get::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_sm2_get.data,
      qt_meta_data_sm2_get,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *sm2_get::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *sm2_get::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_sm2_get.stringdata0))
        return static_cast<void*>(const_cast< sm2_get*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int sm2_get::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
