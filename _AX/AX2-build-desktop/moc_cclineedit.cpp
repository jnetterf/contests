/****************************************************************************
** Meta object code from reading C++ file 'cclineedit.h'
**
** Created: Thu Jun 30 12:26:27 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../AX2/cclineedit.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cclineedit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Kst__CCLineEdit[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      68,   47,   16,   16, 0x0a,
      91,   89,   16,   16, 0x2a,
     109,  107,   16,   16, 0x0a,
     125,   16,   16,   16, 0x2a,

       0        // eod
};

static const char qt_meta_stringdata_Kst__CCLineEdit[] = {
    "Kst::CCLineEdit\0\0currentPrefixChanged(QString)\0"
    "i,stringIsCompletion\0insert(QString,bool)\0"
    "i\0insert(QString)\0x\0divide(QString)\0"
    "divide()\0"
};

const QMetaObject Kst::CCLineEdit::staticMetaObject = {
    { &QLineEdit::staticMetaObject, qt_meta_stringdata_Kst__CCLineEdit,
      qt_meta_data_Kst__CCLineEdit, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Kst::CCLineEdit::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Kst::CCLineEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Kst::CCLineEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Kst__CCLineEdit))
        return static_cast<void*>(const_cast< CCLineEdit*>(this));
    return QLineEdit::qt_metacast(_clname);
}

int Kst::CCLineEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLineEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: currentPrefixChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: insert((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: insert((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: divide((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: divide(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void Kst::CCLineEdit::currentPrefixChanged(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_Kst__CCTextEdit[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      49,   47,   16,   16, 0x0a,
      67,   65,   16,   16, 0x0a,
      83,   16,   16,   16, 0x2a,

       0        // eod
};

static const char qt_meta_stringdata_Kst__CCTextEdit[] = {
    "Kst::CCTextEdit\0\0currentPrefixChanged(QString)\0"
    "i\0insert(QString)\0x\0divide(QString)\0"
    "divide()\0"
};

const QMetaObject Kst::CCTextEdit::staticMetaObject = {
    { &QTextEdit::staticMetaObject, qt_meta_stringdata_Kst__CCTextEdit,
      qt_meta_data_Kst__CCTextEdit, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Kst::CCTextEdit::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Kst::CCTextEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Kst::CCTextEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Kst__CCTextEdit))
        return static_cast<void*>(const_cast< CCTextEdit*>(this));
    return QTextEdit::qt_metacast(_clname);
}

int Kst::CCTextEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTextEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: currentPrefixChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: insert((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: divide((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: divide(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void Kst::CCTextEdit::currentPrefixChanged(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
