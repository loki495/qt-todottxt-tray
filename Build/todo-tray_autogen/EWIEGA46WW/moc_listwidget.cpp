/****************************************************************************
** Meta object code from reading C++ file 'listwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "listwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'listwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ListWidget_t {
    QByteArrayData data[8];
    char stringdata0[76];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ListWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ListWidget_t qt_meta_stringdata_ListWidget = {
    {
QT_MOC_LITERAL(0, 0, 10), // "ListWidget"
QT_MOC_LITERAL(1, 11, 11), // "filter_list"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 9), // "edit_item"
QT_MOC_LITERAL(4, 34, 15), // "TodoItemWidget*"
QT_MOC_LITERAL(5, 50, 4), // "item"
QT_MOC_LITERAL(6, 55, 11), // "delete_item"
QT_MOC_LITERAL(7, 67, 8) // "new_todo"

    },
    "ListWidget\0filter_list\0\0edit_item\0"
    "TodoItemWidget*\0item\0delete_item\0"
    "new_todo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ListWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x0a /* Public */,
       3,    1,   37,    2, 0x0a /* Public */,
       6,    1,   40,    2, 0x0a /* Public */,
       7,    0,   43,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,

       0        // eod
};

void ListWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ListWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->filter_list((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->edit_item((*reinterpret_cast< TodoItemWidget*(*)>(_a[1]))); break;
        case 2: _t->delete_item((*reinterpret_cast< TodoItemWidget*(*)>(_a[1]))); break;
        case 3: _t->new_todo(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ListWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ListWidget.data,
    qt_meta_data_ListWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ListWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ListWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ListWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ListWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
