/****************************************************************************
** Meta object code from reading C++ file 'videoWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "videoWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'videoWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VideoWindow_t {
    QByteArrayData data[12];
    char stringdata0[133];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VideoWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VideoWindow_t qt_meta_stringdata_VideoWindow = {
    {
QT_MOC_LITERAL(0, 0, 11), // "VideoWindow"
QT_MOC_LITERAL(1, 12, 22), // "closeVideoWindowSignal"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 13), // "onJoinChannel"
QT_MOC_LITERAL(4, 50, 8), // "QString&"
QT_MOC_LITERAL(5, 59, 6), // "roomid"
QT_MOC_LITERAL(6, 66, 5), // "usrId"
QT_MOC_LITERAL(7, 72, 24), // "on_disconnectBtn_clicked"
QT_MOC_LITERAL(8, 97, 7), // "checked"
QT_MOC_LITERAL(9, 105, 12), // "onUserJoined"
QT_MOC_LITERAL(10, 118, 3), // "uid"
QT_MOC_LITERAL(11, 122, 10) // "onUserLeft"

    },
    "VideoWindow\0closeVideoWindowSignal\0\0"
    "onJoinChannel\0QString&\0roomid\0usrId\0"
    "on_disconnectBtn_clicked\0checked\0"
    "onUserJoined\0uid\0onUserLeft"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VideoWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    2,   40,    2, 0x0a /* Public */,
       7,    1,   45,    2, 0x0a /* Public */,
       9,    1,   48,    2, 0x0a /* Public */,
      11,    1,   51,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 4,    5,    6,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::ULongLong,   10,
    QMetaType::Void, QMetaType::ULongLong,   10,

       0        // eod
};

void VideoWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<VideoWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->closeVideoWindowSignal(); break;
        case 1: _t->onJoinChannel((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->on_disconnectBtn_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->onUserJoined((*reinterpret_cast< quint64(*)>(_a[1]))); break;
        case 4: _t->onUserLeft((*reinterpret_cast< quint64(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (VideoWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VideoWindow::closeVideoWindowSignal)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VideoWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_VideoWindow.data,
    qt_meta_data_VideoWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VideoWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VideoWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VideoWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int VideoWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void VideoWindow::closeVideoWindowSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
