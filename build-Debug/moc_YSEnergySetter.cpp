/****************************************************************************
** Meta object code from reading C++ file 'YSEnergySetter.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../YSEnergySetter.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'YSEnergySetter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_YSEnergySetter_t {
    QByteArrayData data[6];
    char stringdata[61];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_YSEnergySetter_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_YSEnergySetter_t qt_meta_stringdata_YSEnergySetter = {
    {
QT_MOC_LITERAL(0, 0, 14),
QT_MOC_LITERAL(1, 15, 4),
QT_MOC_LITERAL(2, 20, 0),
QT_MOC_LITERAL(3, 21, 10),
QT_MOC_LITERAL(4, 32, 14),
QT_MOC_LITERAL(5, 47, 12)
    },
    "YSEnergySetter\0Done\0\0ReadSlider\0"
    "SetSliderScale\0SetSliderPos\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_YSEnergySetter[] = {

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
       1,    0,   34,    2, 0x0a,
       3,    1,   35,    2, 0x0a,
       4,    0,   38,    2, 0x0a,
       5,    1,   39,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void YSEnergySetter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        YSEnergySetter *_t = static_cast<YSEnergySetter *>(_o);
        switch (_id) {
        case 0: _t->Done(); break;
        case 1: _t->ReadSlider((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->SetSliderScale(); break;
        case 3: _t->SetSliderPos((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject YSEnergySetter::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_YSEnergySetter.data,
      qt_meta_data_YSEnergySetter,  qt_static_metacall, 0, 0}
};


const QMetaObject *YSEnergySetter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *YSEnergySetter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_YSEnergySetter.stringdata))
        return static_cast<void*>(const_cast< YSEnergySetter*>(this));
    return QWidget::qt_metacast(_clname);
}

int YSEnergySetter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
