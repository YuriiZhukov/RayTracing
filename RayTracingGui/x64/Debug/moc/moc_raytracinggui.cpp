/****************************************************************************
** Meta object code from reading C++ file 'raytracinggui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../raytracinggui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'raytracinggui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RayTracingGui_t {
    QByteArrayData data[14];
    char stringdata0[177];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RayTracingGui_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RayTracingGui_t qt_meta_stringdata_RayTracingGui = {
    {
QT_MOC_LITERAL(0, 0, 13), // "RayTracingGui"
QT_MOC_LITERAL(1, 14, 11), // "resizeEvent"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 13), // "QResizeEvent*"
QT_MOC_LITERAL(4, 41, 1), // "e"
QT_MOC_LITERAL(5, 43, 23), // "setupVisualizatorWidget"
QT_MOC_LITERAL(6, 67, 18), // "setupControlWidget"
QT_MOC_LITERAL(7, 86, 16), // "setupImageViewer"
QT_MOC_LITERAL(8, 103, 16), // "setupStartParams"
QT_MOC_LITERAL(9, 120, 9), // "calculate"
QT_MOC_LITERAL(10, 130, 15), // "applyGridParams"
QT_MOC_LITERAL(11, 146, 20), // "setCameraControlSlot"
QT_MOC_LITERAL(12, 167, 4), // "orig"
QT_MOC_LITERAL(13, 172, 4) // "view"

    },
    "RayTracingGui\0resizeEvent\0\0QResizeEvent*\0"
    "e\0setupVisualizatorWidget\0setupControlWidget\0"
    "setupImageViewer\0setupStartParams\0"
    "calculate\0applyGridParams\0"
    "setCameraControlSlot\0orig\0view"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RayTracingGui[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x08 /* Private */,
       5,    0,   57,    2, 0x08 /* Private */,
       6,    0,   58,    2, 0x08 /* Private */,
       7,    0,   59,    2, 0x08 /* Private */,
       8,    0,   60,    2, 0x08 /* Private */,
       9,    0,   61,    2, 0x08 /* Private */,
      10,    0,   62,    2, 0x08 /* Private */,
      11,    2,   63,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QVector3D, QMetaType::QVector3D,   12,   13,

       0        // eod
};

void RayTracingGui::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RayTracingGui *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->resizeEvent((*reinterpret_cast< QResizeEvent*(*)>(_a[1]))); break;
        case 1: _t->setupVisualizatorWidget(); break;
        case 2: _t->setupControlWidget(); break;
        case 3: _t->setupImageViewer(); break;
        case 4: _t->setupStartParams(); break;
        case 5: _t->calculate(); break;
        case 6: _t->applyGridParams(); break;
        case 7: _t->setCameraControlSlot((*reinterpret_cast< QVector3D(*)>(_a[1])),(*reinterpret_cast< QVector3D(*)>(_a[2]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject RayTracingGui::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_RayTracingGui.data,
    qt_meta_data_RayTracingGui,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *RayTracingGui::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RayTracingGui::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RayTracingGui.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int RayTracingGui::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
