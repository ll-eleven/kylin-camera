/****************************************************************************
** Meta object code from reading C++ file 'settingpage.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/settingpage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'settingpage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SettingPage_t {
    QByteArrayData data[14];
    char stringdata0[165];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SettingPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SettingPage_t qt_meta_stringdata_SettingPage = {
    {
QT_MOC_LITERAL(0, 0, 11), // "SettingPage"
QT_MOC_LITERAL(1, 12, 10), // "dir_change"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 10), // "change_dev"
QT_MOC_LITERAL(4, 35, 11), // "const char*"
QT_MOC_LITERAL(5, 47, 18), // "change_resolutions"
QT_MOC_LITERAL(6, 66, 16), // "QPair<uint,uint>"
QT_MOC_LITERAL(7, 83, 9), // "dir_click"
QT_MOC_LITERAL(8, 93, 11), // "change_item"
QT_MOC_LITERAL(9, 105, 19), // "change_cameraDevice"
QT_MOC_LITERAL(10, 125, 5), // "close"
QT_MOC_LITERAL(11, 131, 13), // "confirm_click"
QT_MOC_LITERAL(12, 145, 12), // "cancel_click"
QT_MOC_LITERAL(13, 158, 6) // "update"

    },
    "SettingPage\0dir_change\0\0change_dev\0"
    "const char*\0change_resolutions\0"
    "QPair<uint,uint>\0dir_click\0change_item\0"
    "change_cameraDevice\0close\0confirm_click\0"
    "cancel_click\0update"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SettingPage[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,
       3,    1,   65,    2, 0x06 /* Public */,
       5,    1,   68,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   71,    2, 0x0a /* Public */,
       8,    0,   72,    2, 0x0a /* Public */,
       9,    1,   73,    2, 0x0a /* Public */,
      10,    0,   76,    2, 0x0a /* Public */,
      11,    0,   77,    2, 0x0a /* Public */,
      12,    0,   78,    2, 0x0a /* Public */,
      13,    0,   79,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, 0x80000000 | 6,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SettingPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SettingPage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->dir_change(); break;
        case 1: _t->change_dev((*reinterpret_cast< const char*(*)>(_a[1]))); break;
        case 2: _t->change_resolutions((*reinterpret_cast< QPair<uint,uint>(*)>(_a[1]))); break;
        case 3: _t->dir_click(); break;
        case 4: _t->change_item(); break;
        case 5: _t->change_cameraDevice((*reinterpret_cast< const char*(*)>(_a[1]))); break;
        case 6: _t->close(); break;
        case 7: _t->confirm_click(); break;
        case 8: _t->cancel_click(); break;
        case 9: _t->update(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SettingPage::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SettingPage::dir_change)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SettingPage::*)(const char * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SettingPage::change_dev)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SettingPage::*)(QPair<uint,uint> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SettingPage::change_resolutions)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SettingPage::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_SettingPage.data,
    qt_meta_data_SettingPage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SettingPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SettingPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SettingPage.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SettingPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void SettingPage::dir_change()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SettingPage::change_dev(const char * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SettingPage::change_resolutions(QPair<uint,uint> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
