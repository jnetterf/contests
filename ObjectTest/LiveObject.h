/* Creator Live
   trintith@gmail.com
*/

#ifndef LIVE_OBJECT_H
#define LIVE_OBJECT_H

#include <QDebug>
#include <QObject>
#include <iostream>

#define LO_DEBUG

class QString;

/**
 * Ripped off QDebug
 */
class NullDebug {
public:
    inline NullDebug() {}
   inline ~NullDebug () {}
    inline NullDebug &operator<<(QChar) { return *this; }
    inline NullDebug &operator<<(QBool) { return *this; }
    inline NullDebug &operator<<(bool) { return *this; }
    inline NullDebug &operator<<(char) { return *this; }
    inline NullDebug &operator<<(signed short) { return *this; }
    inline NullDebug &operator<<(unsigned short) { return *this; }
    inline NullDebug &operator<<(signed int) { return *this; }
    inline NullDebug &operator<<(unsigned int) { return *this; }
    inline NullDebug &operator<<(signed long) { return *this; }
    inline NullDebug &operator<<(unsigned long) { return *this; }
    inline NullDebug &operator<<(qint64) { return *this; }
    inline NullDebug &operator<<(quint64) { return *this; }
    inline NullDebug &operator<<(float) { return *this; }
    inline NullDebug &operator<<(double) { return *this; }
    inline NullDebug &operator<<(const char*) { return *this; }
    inline NullDebug &operator<<(const QString &) { return *this; }
    inline NullDebug &operator<<(const QStringRef &) { return *this; }
    inline NullDebug &operator<<(const QLatin1String &) { return *this; }
    inline NullDebug &operator<<(const QByteArray &) { return *this; }
    inline NullDebug &operator<<(const void *) { return *this; }
    inline NullDebug &operator<<(QTextStreamFunction) { return *this; }
    inline NullDebug &operator<<(QTextStreamManipulator) { return *this; }
};

#define LO_NAME objName << "(" << _loId << ")"

class LiveObject;

class LivePointerTag { public: LivePointerTag(); virtual ~LivePointerTag();
static QList<LivePointerTag*> _u; LiveObject* _SECRET; bool _ok; bool _alive; };

template< class T > class LivePointer : public LivePointerTag {
public:
    LivePointer( QList< LivePointerTag* >& tags, T*& ptr2ptr, T* ptr ) {
        ptr2ptr = _p = ptr; _p2p = &ptr2ptr; _tags = &tags;
        _SECRET=ptr;
    }

    virtual ~LivePointer() {
        if( _p != *_p2p || _SECRET != _p || !_p ) { return; }
        if(!_SECRET) { return; }
        bool ok = false;
        for ( int i = 0; i < _tags->size(); i++ ) {
            if ( (*_tags)[i] == (LivePointerTag*)this) { ok=true; (*_tags)[i] = NULL; }
        }
        if(_ok) { delete _p; }
        (*_p2p) = NULL;
    }

    QList< LivePointerTag* >* _tags;
    T** _p2p;
    T* _p;
};

/**
 * A class which should be inherited by every class in Creator Live.
 */
class LiveObject {
public:
    LiveObject( QString TobjName, int id = -1 ) : objName( TobjName ),
    _failStream( new QTextStream(&_str) ) {
        if ( id != -1 ) _loId = id;
        else _loId = ++_lastID;

        _gui = NULL;

        _u.push_back( this );
        #ifdef LO_DEBUG
            if ( !_lastID ) qInstallMsgHandler( outputHandler );
            if ( id != -2 ) qDebug() << " [NEW] " << LO_NAME;
        #endif
        _SECRET = this;
    }

    inline void loInheritence( QString TobjName ) {
        objName = TobjName;
        _SECRET = this;
        #ifdef LO_DEBUG
            qDebug() << " [INH] " << LO_NAME;
        #endif
    }

    virtual ~LiveObject();

    /////////////////////
    // DEBUG
    ///////////////////////////////////////////

#ifndef LO_DEBUG
    #define LD() NullDebug()
#else
    /**
     * Use this to output debugging information.
     */
    #define LD() (qDebug() << " [DBG] " << LO_NAME << __FUNCTION__ << "line" << __LINE__ ).nospace() << ": "
#endif

#define Yay return

#ifndef LO_DEBUG_REALTIME
    #define LRT NullDebug()
#else
    /**
     * Use this to output dubbing information in realtime functions ( functions called very frequently )
     */
    #define LRT qDebug() << " [RTD] " << LO_NAME << ":"
#endif

    /**
     * Use this to output a warning, which the user will see.
     * After calling this call loWarn();
     */
    inline QTextStream& LW() { _failStream->string()->clear(); return *_failStream; }

    /**
     * Use this to otuput an error, which the user will see.
     * Errors are critical. In your implementation of loFail, you should either address the problem or quit.
     * After calling this call loFail()
     */
    inline QTextStream& LE() { _failStream->string()->clear(); return *_failStream; }

    /**
     * Should somehow warn user.
     * If you inherit this like you should, remember to call LiveObject::warn(); from within
     */
    virtual void loWarn() { qWarning() << " [WAR] " << LO_NAME << ":" << loProblem(); }

    /**
     * Should resolve situation or delete children and call _parent->LE() << "Because of child"; _parent->fail();
     * If you inherit this like you should, remember to call LiveObject::fail(); from within
     */
    virtual void loFail() { qCritical() << " [ERR] " << LO_NAME << ":" << loProblem(); }

    /**
     * Returns the string of an error or warning.
     */
    inline QString loProblem() { return *_failStream->string(); }

    /**
     * Is the class name
     */
    QString objName;

    /**
     * Returns the id. IDs are constant throughout its lifetime.
     * Each non-GUI id should be distinct. GUIs share the IDs of their drivers.
     */
    inline const int& id() { return _loId; }

    static void outputHandler(QtMsgType type, const char *msg);

    static inline QList< LiveObject* > objects() {
        return _u;
    }

    int _loId;
    LiveObject* _gui;

    /////////////////////
    // POINTERS
    ///////////////////////////////////////////

    /**
     * Add a child pointer and create a reference in _children.
     * It is better to use LiveObjectChild if possible.
     */
    void addChildPointer( LiveObject* child );

    /**
     * Instead of:
     * _widget = new QWidget( this );
     *
     * Call:
     * addChildPointer( _widget, new QWidget( this ) );
     *
     * To share, call sharePointer( ... ), and to unshare, call unsharePointer( ... )
     */
    template< class U > void addChildPointer( U*& ptr2ptr, U* ptr ) {
        _tags.push_back( new LivePointer< U >( _tags, ptr2ptr, ptr) );
    }

    virtual void removeDriver() {}
    void* _SECRET;

    QList< LivePointerTag* > _tags;
    QList< LiveObject* > _children;
    static void reportActive() {
        for(int i =0;i<_u.size();i++){_u[i]->LW()<<"I'm Alive.";_u[i]->loWarn();}
    }

protected:
    static QList< LiveObject* > _u;
    static int _lastID;
    QTextStream* _failStream;
    QString _str;
};


template< class T > class LiveObjectChild : public LiveObject {
public:
    LiveObjectChild( QString TobjName, T* parent ) : LiveObject( TobjName ), _parent( parent ) {
        parent->addChildPointer( this );
    }
    virtual ~LiveObjectChild() {
        for ( int i = 0; i < _parent->_tags.size(); i++ ) {
            LivePointer< LiveObjectChild >* p = dynamic_cast< LivePointer< LiveObjectChild >* >( _parent->_tags[i] );
            if ( !p ) continue;
            if ( dynamic_cast< LiveObjectChild* >( p->_p ) == this ) {
                _parent->_tags.removeAt(i);
                //break;
            }
        }
        for ( int i = 0; i < _parent->_children.size(); i++ ) {
            LiveObjectChild* p = dynamic_cast< LiveObjectChild* >( _parent->_children[i] );
            if ( !p ) continue;
            if ( p == this ) { _parent->_children.removeAt(i); }
        }
    }

protected:
    T* _parent;
};

template < class T > class LiveObjectGUI : public LiveObject {
public:
    LiveObjectGUI( QString TobjName, T* driver ) : LiveObject( TobjName, -2 ) {
        if ( !driver ) _loId = ++_lastID;
        else { _loId = driver->id(); driver->_gui = this; }
        _driver = driver;
        #ifdef LO_DEBUG
            if ( !driver && !_lastID ) qInstallMsgHandler( outputHandler );
            qDebug() << " [GUI] " << LO_NAME;
        #endif
    }
    virtual ~LiveObjectGUI() {
        if ( _driver ) { _driver->_gui = NULL; delete _driver; }
    }

    void removeDriver() { _driver = NULL; }

protected:
    T* _driver;
};

#endif//LIVE_OBJECT_H
