/****************************************************************************
** Meta object code from reading C++ file 'YSMenu.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../YSMenu.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'YSMenu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_YSMenu_t {
    QByteArrayData data[13];
    char stringdata[126];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_YSMenu_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_YSMenu_t qt_meta_stringdata_YSMenu = {
    {
QT_MOC_LITERAL(0, 0, 6),
QT_MOC_LITERAL(1, 7, 17),
QT_MOC_LITERAL(2, 25, 0),
QT_MOC_LITERAL(3, 26, 10),
QT_MOC_LITERAL(4, 37, 8),
QT_MOC_LITERAL(5, 46, 6),
QT_MOC_LITERAL(6, 53, 12),
QT_MOC_LITERAL(7, 66, 4),
QT_MOC_LITERAL(8, 71, 9),
QT_MOC_LITERAL(9, 81, 10),
QT_MOC_LITERAL(10, 92, 10),
QT_MOC_LITERAL(11, 103, 3),
QT_MOC_LITERAL(12, 107, 17)
    },
    "YSMenu\0CollectStatistics\0\0HandleMenu\0"
    "QAction*\0action\0SelectEnergy\0Setb\0"
    "SetEnergy\0SetNucleus\0YSIsotope*\0iso\0"
    "SetNumberOfEvents\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_YSMenu[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x0a,
       3,    1,   50,    2, 0x0a,
       6,    0,   53,    2, 0x0a,
       7,    0,   54,    2, 0x0a,
       8,    0,   55,    2, 0x0a,
       9,    1,   56,    2, 0x0a,
      12,    0,   59,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void,

       0        // eod
};

void YSMenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        YSMenu *_t = static_cast<YSMenu *>(_o);
        switch (_id) {
        case 0: _t->CollectStatistics(); break;
        case 1: _t->HandleMenu((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 2: _t->SelectEnergy(); break;
        case 3: _t->Setb(); break;
        case 4: _t->SetEnergy(); break;
        case 5: _t->SetNucleus((*reinterpret_cast< YSIsotope*(*)>(_a[1]))); break;
        case 6: _t->SetNumberOfEvents(); break;
        default: ;
        }
    }
}

const QMetaObject YSMenu::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_YSMenu.data,
      qt_meta_data_YSMenu,  qt_static_metacall, 0, 0}
};


const QMetaObject *YSMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *YSMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_YSMenu.stringdata))
        return static_cast<void*>(const_cast< YSMenu*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int YSMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
