/****************************************************************************
** Meta object code from reading C++ file 'presenter_chart_view.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Project2021/presenter_chart_view.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'presenter_chart_view.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_presenter_chart_view_t {
    QByteArrayData data[8];
    char stringdata0[104];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_presenter_chart_view_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_presenter_chart_view_t qt_meta_stringdata_presenter_chart_view = {
    {
QT_MOC_LITERAL(0, 0, 20), // "presenter_chart_view"
QT_MOC_LITERAL(1, 21, 10), // "add_charts"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 20), // "add_entry_comparison"
QT_MOC_LITERAL(4, 54, 9), // "add_point"
QT_MOC_LITERAL(5, 64, 12), // "delete_point"
QT_MOC_LITERAL(6, 77, 13), // "open_settings"
QT_MOC_LITERAL(7, 91, 12) // "give_balance"

    },
    "presenter_chart_view\0add_charts\0\0"
    "add_entry_comparison\0add_point\0"
    "delete_point\0open_settings\0give_balance"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_presenter_chart_view[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x0a /* Public */,
       3,    0,   45,    2, 0x0a /* Public */,
       4,    0,   46,    2, 0x0a /* Public */,
       5,    0,   47,    2, 0x0a /* Public */,
       6,    0,   48,    2, 0x0a /* Public */,
       7,    0,   49,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void presenter_chart_view::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<presenter_chart_view *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->add_charts(); break;
        case 1: _t->add_entry_comparison(); break;
        case 2: _t->add_point(); break;
        case 3: _t->delete_point(); break;
        case 4: _t->open_settings(); break;
        case 5: _t->give_balance(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject presenter_chart_view::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_presenter_chart_view.data,
    qt_meta_data_presenter_chart_view,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *presenter_chart_view::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *presenter_chart_view::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_presenter_chart_view.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int presenter_chart_view::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
