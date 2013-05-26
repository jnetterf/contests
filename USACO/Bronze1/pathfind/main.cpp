/*
 ID: drmrshd1
 PROG: pathfind
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
ifstream in("pathfind.in");
ofstream out("pathfind.out");

struct Island;
vector<Island*> _u;
vector<Island*> _mob;
z lastId=-1;
z maxLvl=0;

struct Island {
    Island() { _id=++lastId; _u.push_back(this);}
    z _id;
    z _lvl;
    vector<Island*>_to;
    bool doIt(){
        for(z i=0;i<_to.size();i++){
            bool ok=1;
            for(z j=0;j<_mob.size();j++){
                if(_mob[j]==_to[i]){ok=0;break;}
            }
            if(ok){
                _to[i]->_lvl=_lvl+1;
                if(_lvl+1>maxLvl)maxLvl=_lvl+1;
                _mob.push_back(_to[i]);
            }
        }
    }
    f go() {
        _lvl=0;
        _mob.push_back(this);
        for(z i=0;i<_mob.size();i++) _mob[i]->doIt();
    }
};

z main() { z n,m; //m=start
    in>>n;in>>m;
    for(z i=0;i<n;i++) new Island;
    for(z i=0;i<n;i++){
        for(z j=0;j<n;j++) { bool a;
            in>>a;
            if(a)_u[i]->_to.push_back( _u[j] );
        }
    }
    _u[m-1]->go();

    for(z i=0;i<=maxLvl;i++) {
        bool notFirst=0;
        for(z j=0;j<_u.size();j++){
            if(_u[j]->_lvl==i){
                if(notFirst++)out<<' ';
                out<<_u[j]->_id+1;
            }
        }
        out<<endl;
    }
}
