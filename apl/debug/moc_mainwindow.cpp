/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[22];
    char stringdata0[347];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 15), // "getSaveFilePath"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 11), // "getPixelmap"
QT_MOC_LITERAL(4, 40, 4), // "int*"
QT_MOC_LITERAL(5, 45, 6), // "matrix"
QT_MOC_LITERAL(6, 52, 5), // "image"
QT_MOC_LITERAL(7, 58, 9), // "getMatrix"
QT_MOC_LITERAL(8, 68, 12), // "getMatrixASM"
QT_MOC_LITERAL(9, 81, 6), // "float*"
QT_MOC_LITERAL(10, 88, 15), // "getCheckedRadio"
QT_MOC_LITERAL(11, 104, 17), // "changeToGrayscale"
QT_MOC_LITERAL(12, 122, 5), // "array"
QT_MOC_LITERAL(13, 128, 4), // "size"
QT_MOC_LITERAL(14, 133, 6), // "choice"
QT_MOC_LITERAL(15, 140, 28), // "on_nextWindowButton1_clicked"
QT_MOC_LITERAL(16, 169, 28), // "on_nextWindowButton2_clicked"
QT_MOC_LITERAL(17, 198, 32), // "on_previousWindowButton1_clicked"
QT_MOC_LITERAL(18, 231, 32), // "on_previousWindowButton2_clicked"
QT_MOC_LITERAL(19, 264, 28), // "on_chooseImageButton_clicked"
QT_MOC_LITERAL(20, 293, 26), // "on_downloadButton1_clicked"
QT_MOC_LITERAL(21, 320, 26) // "on_downloadButton2_clicked"

    },
    "MainWindow\0getSaveFilePath\0\0getPixelmap\0"
    "int*\0matrix\0image\0getMatrix\0getMatrixASM\0"
    "float*\0getCheckedRadio\0changeToGrayscale\0"
    "array\0size\0choice\0on_nextWindowButton1_clicked\0"
    "on_nextWindowButton2_clicked\0"
    "on_previousWindowButton1_clicked\0"
    "on_previousWindowButton2_clicked\0"
    "on_chooseImageButton_clicked\0"
    "on_downloadButton1_clicked\0"
    "on_downloadButton2_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08 /* Private */,
       3,    2,   80,    2, 0x08 /* Private */,
       7,    1,   85,    2, 0x08 /* Private */,
       8,    1,   88,    2, 0x08 /* Private */,
      10,    0,   91,    2, 0x08 /* Private */,
      11,    3,   92,    2, 0x08 /* Private */,
      15,    0,   99,    2, 0x08 /* Private */,
      16,    0,  100,    2, 0x08 /* Private */,
      17,    0,  101,    2, 0x08 /* Private */,
      18,    0,  102,    2, 0x08 /* Private */,
      19,    0,  103,    2, 0x08 /* Private */,
      20,    0,  104,    2, 0x08 /* Private */,
      21,    0,  105,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::QString,
    QMetaType::QPixmap, 0x80000000 | 4, QMetaType::QImage,    5,    6,
    0x80000000 | 4, QMetaType::QImage,    6,
    0x80000000 | 9, QMetaType::QImage,    6,
    QMetaType::Int,
    QMetaType::Void, 0x80000000 | 4, QMetaType::Int, QMetaType::Int,   12,   13,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { QString _r = _t->getSaveFilePath();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 1: { QPixmap _r = _t->getPixelmap((*reinterpret_cast< int*(*)>(_a[1])),(*reinterpret_cast< QImage(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QPixmap*>(_a[0]) = std::move(_r); }  break;
        case 2: { int* _r = _t->getMatrix((*reinterpret_cast< QImage(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int**>(_a[0]) = std::move(_r); }  break;
        case 3: { float* _r = _t->getMatrixASM((*reinterpret_cast< QImage(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float**>(_a[0]) = std::move(_r); }  break;
        case 4: { int _r = _t->getCheckedRadio();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 5: _t->changeToGrayscale((*reinterpret_cast< int*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 6: _t->on_nextWindowButton1_clicked(); break;
        case 7: _t->on_nextWindowButton2_clicked(); break;
        case 8: _t->on_previousWindowButton1_clicked(); break;
        case 9: _t->on_previousWindowButton2_clicked(); break;
        case 10: _t->on_chooseImageButton_clicked(); break;
        case 11: _t->on_downloadButton1_clicked(); break;
        case 12: _t->on_downloadButton2_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
