/****************************************************************************
** Meta object code from reading C++ file 'arith.h'
**
** Created: Sun May 22 18:29:53 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../arith.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'arith.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Arith[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       7,    6,    6,    6, 0x0a,
      26,    6,    6,    6, 0x0a,
      40,    6,    6,    6, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Arith[] = {
    "Arith\0\0generateQuestion()\0checkAnswer()\0"
    "losePoints()\0"
};

const QMetaObject Arith::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Arith,
      qt_meta_data_Arith, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Arith::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Arith::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Arith::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Arith))
        return static_cast<void*>(const_cast< Arith*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Arith::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: generateQuestion(); break;
        case 1: checkAnswer(); break;
        case 2: losePoints(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
