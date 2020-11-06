/****************************************************************************
** Meta object code from reading C++ file 'nrtc_engine.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "nrtc_engine.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'nrtc_engine.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_smaple_nertc__NRTCEngine_t {
    QByteArrayData data[11];
    char stringdata0[137];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_smaple_nertc__NRTCEngine_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_smaple_nertc__NRTCEngine_t qt_meta_stringdata_smaple_nertc__NRTCEngine = {
    {
QT_MOC_LITERAL(0, 0, 24), // "smaple_nertc::NRTCEngine"
QT_MOC_LITERAL(1, 25, 14), // "joiningChannel"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 14), // "leavingChannel"
QT_MOC_LITERAL(4, 56, 12), // "videoStopped"
QT_MOC_LITERAL(5, 69, 3), // "uid"
QT_MOC_LITERAL(6, 73, 10), // "videoStart"
QT_MOC_LITERAL(7, 84, 11), // "max_profile"
QT_MOC_LITERAL(8, 96, 20), // "joinedChannelSuccess"
QT_MOC_LITERAL(9, 117, 10), // "userJoined"
QT_MOC_LITERAL(10, 128, 8) // "userLeft"

    },
    "smaple_nertc::NRTCEngine\0joiningChannel\0"
    "\0leavingChannel\0videoStopped\0uid\0"
    "videoStart\0max_profile\0joinedChannelSuccess\0"
    "userJoined\0userLeft"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_smaple_nertc__NRTCEngine[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    0,   50,    2, 0x06 /* Public */,
       4,    1,   51,    2, 0x06 /* Public */,
       6,    2,   54,    2, 0x06 /* Public */,
       8,    0,   59,    2, 0x06 /* Public */,
       9,    1,   60,    2, 0x06 /* Public */,
      10,    1,   63,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::ULongLong,    5,
    QMetaType::Void, QMetaType::ULongLong, QMetaType::Int,    5,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::ULongLong,    5,
    QMetaType::Void, QMetaType::ULongLong,    5,

       0        // eod
};

void smaple_nertc::NRTCEngine::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NRTCEngine *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->joiningChannel(); break;
        case 1: _t->leavingChannel(); break;
        case 2: _t->videoStopped((*reinterpret_cast< unsigned long long(*)>(_a[1]))); break;
        case 3: _t->videoStart((*reinterpret_cast< unsigned long long(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->joinedChannelSuccess(); break;
        case 5: _t->userJoined((*reinterpret_cast< quint64(*)>(_a[1]))); break;
        case 6: _t->userLeft((*reinterpret_cast< quint64(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (NRTCEngine::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NRTCEngine::joiningChannel)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (NRTCEngine::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NRTCEngine::leavingChannel)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (NRTCEngine::*)(unsigned long long );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NRTCEngine::videoStopped)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (NRTCEngine::*)(unsigned long long , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NRTCEngine::videoStart)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (NRTCEngine::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NRTCEngine::joinedChannelSuccess)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (NRTCEngine::*)(quint64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NRTCEngine::userJoined)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (NRTCEngine::*)(quint64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NRTCEngine::userLeft)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject smaple_nertc::NRTCEngine::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_smaple_nertc__NRTCEngine.data,
    qt_meta_data_smaple_nertc__NRTCEngine,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *smaple_nertc::NRTCEngine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *smaple_nertc::NRTCEngine::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_smaple_nertc__NRTCEngine.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int smaple_nertc::NRTCEngine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void smaple_nertc::NRTCEngine::joiningChannel()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void smaple_nertc::NRTCEngine::leavingChannel()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void smaple_nertc::NRTCEngine::videoStopped(unsigned long long _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void smaple_nertc::NRTCEngine::videoStart(unsigned long long _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void smaple_nertc::NRTCEngine::joinedChannelSuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void smaple_nertc::NRTCEngine::userJoined(quint64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void smaple_nertc::NRTCEngine::userLeft(quint64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
