/****************************************************************************
** Meta object code from reading C++ file 'visualizator.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../visualizator.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'visualizator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Visualizator_t {
    QByteArrayData data[6];
    char stringdata0[63];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Visualizator_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Visualizator_t qt_meta_stringdata_Visualizator = {
    {
QT_MOC_LITERAL(0, 0, 12), // "Visualizator"
QT_MOC_LITERAL(1, 13, 22), // "setCameraControlSignal"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 3), // "pos"
QT_MOC_LITERAL(4, 41, 4), // "dest"
QT_MOC_LITERAL(5, 46, 16) // "setCameraControl"

    },
    "Visualizator\0setCameraControlSignal\0"
    "\0pos\0dest\0setCameraControl"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Visualizator[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   29,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QVector3D, QMetaType::QVector3D,    3,    4,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void Visualizator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Visualizator *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setCameraControlSignal((*reinterpret_cast< QVector3D(*)>(_a[1])),(*reinterpret_cast< QVector3D(*)>(_a[2]))); break;
        case 1: _t->setCameraControl(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Visualizator::*)(QVector3D , QVector3D );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Visualizator::setCameraControlSignal)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Visualizator::staticMetaObject = { {
    &Qt3DExtras::Qt3DWindow::staticMetaObject,
    qt_meta_stringdata_Visualizator.data,
    qt_meta_data_Visualizator,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Visualizator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Visualizator::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Visualizator.stringdata0))
        return static_cast<void*>(this);
    return Qt3DExtras::Qt3DWindow::qt_metacast(_clname);
}

int Visualizator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Qt3DExtras::Qt3DWindow::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void Visualizator::setCameraControlSignal(QVector3D _t1, QVector3D _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
