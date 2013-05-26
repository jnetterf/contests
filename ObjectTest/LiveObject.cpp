/* This file is part of the Creator Live project.
   Copyright 2010 Joshua Netterfield <drmrshdw@gmail.com>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "LiveObject.h"


QList< LiveObject* > LiveObject::_u;
int LiveObject::_lastID = -1;

#include <windows.h>
#include <winbase.h>

void LiveObject::outputHandler(QtMsgType type, const char *msg) {
    if ( msg[0] != '\0' && msg[0] == ' ' && msg[1] == '[' ) switch (type) {
    case QtDebugMsg:
        std::cerr << msg << std::endl;
        break;
    case QtWarningMsg:
        std::cerr << msg << std::endl;
        break;
    case QtCriticalMsg:
        std::cerr << msg << std::endl;
        break;
    case QtFatalMsg:
        std::cerr << msg << std::endl;
        abort();
    } else std::cerr << " [EXT] " << msg << std::endl;
}

void LiveObject::addChildPointer( LiveObject *child ) {
    _children.push_back( NULL );
    addChildPointer( _children.back(), child );
}

LivePointerTag::LivePointerTag() {
    _u.push_back(this);
    _ok=true;
    _alive=true;
}

LivePointerTag::~LivePointerTag() {
    for(int i=0;i<_u.size();i++){if (_u[i]==this){/*qDebug() << " [PTR] Removing me("<<i<<")";*/_u.removeAt(i);break;}}
}

LiveObject::~LiveObject() {
    qDebug() << " [DEL] " << LO_NAME;

    for( int i = 0; i < _u.size(); i++ ) if ( _u[i] == this ) { _u.removeAt( i ); }
    if ( _gui ) { _gui->removeDriver(); }
    delete _failStream;
    while ( _tags.size() ) {
        if (_tags[0]) {_tags[0]->_alive=false;delete _tags[0];}
        _tags.removeAt(0);
    }
    if(_SECRET)for(int i=0;i<LivePointerTag::_u.size();i++){
        if(LivePointerTag::_u[i]->_SECRET == _SECRET){
            LivePointerTag::_u[i]->_ok=false;
            delete LivePointerTag::_u.takeAt(i);
        }
    }
}

QList<LivePointerTag*> LivePointerTag::_u;
QList< LivePointerTag* >* _tags;

//#include "moc_LiveObject.cpp"

// Yay!
