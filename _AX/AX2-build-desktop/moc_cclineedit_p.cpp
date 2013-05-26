/****************************************************************************
** Meta object code from reading C++ file 'cclineedit_p.h'
**
** Created: Thu Jun 30 12:26:27 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../AX2/cclineedit_p.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cclineedit_p.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Kst__CategoricalCompleter[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      27,   26,   26,   26, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Kst__CategoricalCompleter[] = {
    "Kst::CategoricalCompleter\0\0verifyPrefix()\0"
};

const QMetaObject Kst::CategoricalCompleter::staticMetaObject = {
    { &QCompleter::staticMetaObject, qt_meta_stringdata_Kst__CategoricalCompleter,
      qt_meta_data_Kst__CategoricalCompleter, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Kst::CategoricalCompleter::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Kst::CategoricalCompleter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Kst::CategoricalCompleter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Kst__CategoricalCompleter))
        return static_cast<void*>(const_cast< CategoricalCompleter*>(this));
    return QCompleter::qt_metacast(_clname);
}

int Kst::CategoricalCompleter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCompleter::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: verifyPrefix(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_Kst__CCTableModel[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_Kst__CCTableModel[] = {
    "Kst::CCTableModel\0"
};

const QMetaObject Kst::CCTableModel::staticMetaObject = {
    { &QAbstractTableModel::staticMetaObject, qt_meta_stringdata_Kst__CCTableModel,
      qt_meta_data_Kst__CCTableModel, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Kst::CCTableModel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Kst::CCTableModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Kst::CCTableModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Kst__CCTableModel))
        return static_cast<void*>(const_cast< CCTableModel*>(this));
    return QAbstractTableModel::qt_metacast(_clname);
}

int Kst::CCTableModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractTableModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_Kst__CCTableView[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      40,   17,   17,   17, 0x0a,
      74,   60,   17,   17, 0x0a,
     114,  104,   17,   17, 0x0a,
     162,  150,   17,   17, 0x0a,
     200,  195,   17,   17, 0x2a,
     228,  225,   17,   17, 0x0a,
     256,  253,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Kst__CCTableView[] = {
    "Kst::CCTableView\0\0activateHint(QString)\0"
    "updateSuggestions()\0columnHeaders\0"
    "setColumnHeaders(QStringList)\0completer\0"
    "setCompleter(CategoricalCompleter*)\0"
    "data,prefix\0setData(CompletionCase*,QString)\0"
    "data\0setData(CompletionCase*)\0le\0"
    "setLineEdit(CCLineEdit*)\0te\0"
    "setTextEdit(CCTextEdit*)\0"
};

const QMetaObject Kst::CCTableView::staticMetaObject = {
    { &QTableView::staticMetaObject, qt_meta_stringdata_Kst__CCTableView,
      qt_meta_data_Kst__CCTableView, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Kst::CCTableView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Kst::CCTableView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Kst::CCTableView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Kst__CCTableView))
        return static_cast<void*>(const_cast< CCTableView*>(this));
    return QTableView::qt_metacast(_clname);
}

int Kst::CCTableView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: activateHint((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: updateSuggestions(); break;
        case 2: setColumnHeaders((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 3: setCompleter((*reinterpret_cast< CategoricalCompleter*(*)>(_a[1]))); break;
        case 4: setData((*reinterpret_cast< CompletionCase*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 5: setData((*reinterpret_cast< CompletionCase*(*)>(_a[1]))); break;
        case 6: setLineEdit((*reinterpret_cast< CCLineEdit*(*)>(_a[1]))); break;
        case 7: setTextEdit((*reinterpret_cast< CCTextEdit*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void Kst::CCTableView::activateHint(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
