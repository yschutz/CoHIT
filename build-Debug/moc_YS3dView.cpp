/****************************************************************************
** Meta object code from reading C++ file 'YS3dView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../YS3dView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'YS3dView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_YS3dView_t {
    QByteArrayData data[4];
    char stringdata[34];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_YS3dView_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_YS3dView_t qt_meta_stringdata_YS3dView = {
    {
QT_MOC_LITERAL(0, 0, 8),
QT_MOC_LITERAL(1, 9, 4),
QT_MOC_LITERAL(2, 14, 8),
QT_MOC_LITERAL(3, 23, 9)
    },
    "YS3dView\0QRot\0NTransIn\0NTransOut\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_YS3dView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       3,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::QReal, 0x00095003,
       2, QMetaType::QReal, 0x00095003,
       3, QMetaType::QReal, 0x00095003,

       0        // eod
};

void YS3dView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject YS3dView::staticMetaObject = {
    { &QGLView::staticMetaObject, qt_meta_stringdata_YS3dView.data,
      qt_meta_data_YS3dView,  qt_static_metacall, 0, 0}
};


const QMetaObject *YS3dView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *YS3dView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_YS3dView.stringdata))
        return static_cast<void*>(const_cast< YS3dView*>(this));
    return QGLView::qt_metacast(_clname);
}

int YS3dView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
     if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< qreal*>(_v) = QRot(); break;
        case 1: *reinterpret_cast< qreal*>(_v) = NTransIn(); break;
        case 2: *reinterpret_cast< qreal*>(_v) = NTransOut(); break;
        }
        _id -= 3;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: SetQRot(*reinterpret_cast< qreal*>(_v)); break;
        case 1: SetNTransIn(*reinterpret_cast< qreal*>(_v)); break;
        case 2: SetNTransOut(*reinterpret_cast< qreal*>(_v)); break;
        }
        _id -= 3;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE
