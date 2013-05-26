/*
 ID: drmrshd1
 PROG: spiral
 LANG: C++
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits.h>
using namespace std;
typedef int z;
typedef string S;
typedef istringstream Ss;
typedef void f;
ifstream in("spiral.in");
ofstream out("spiral.out");

int last=0;

struct Square;

Square* next;bool dirX;
//Square* _u[752][752];

struct Square {
    Square* l,* r,* u,* d;
    int _pos;
    Square(Square* l,Square* u) {
        this->l=l;this->u=u; r=d=0;
        if(l)l->r=this; if(u)u->d=this;
        _pos=0;
    }
    f doIt(int dir) {
        _pos=++last;
        next=0;
        switch(dir) {
        case 0:if(r&&!r->_pos){next=r;dirX=0;} else if(d&&!d->_pos) {next=d;dirX=1;} break;//right
        case 1:if(d&&!d->_pos){next=d;dirX=1;} else if(l&&!l->_pos) l->doIt(2); break;//down
        case 2:if(l&&!l->_pos)l->doIt(2); else if(u&&!u->_pos) u->doIt(3); break;//left
        case 3:if(u&&!u->_pos)u->doIt(3); else if(r&&!r->_pos) {next=r;dirX=0;} break;//up
        }
    }
};

z main() { int n;
    in>>n;
    Square*first=0,*last=0;
    {Square* _ll[752];
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i&&j)last=new Square(last,_ll[j]);
            else if(!i&&j)last=new Square(last,0);
            else if(i&&!j)last=new Square(0,_ll[j]);
            else last=new Square(NULL,NULL);
            _ll[j]=last;
            if(!first)first=last;
        }
    }}
    first->doIt(0);
    while(next)next->doIt(dirX);
    Square*d;
    for(int i=0;i<n;i++){
        d=first->d;
        for(int j=0;j<n;j++){
            if(j)out<<' ';
            out<<first->_pos;
            first=first->r;
        }
        out<<endl;
        first=d;
    }
}
