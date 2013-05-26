/*
 ID: drmrshd1
 PROG: charms
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
typedef void f;
ifstream in("charms.in");
ofstream out("charms.out");

int _solutions[512];

struct Braclet {
    vector<int> _b; //pos
    vector<int> _c;
    vector<int> _d;
    f add(int length,int pos,int ix) {
        for(int i=1;i<_b.size();i++){
            if(_b[i-1]<pos&&pos<_b[i]) {
                _b.insert(_b.begin()+i,pos);
                _c.insert(_c.begin()+i,length);
                _d.insert(_d.begin()+i,ix);
                return;
            }
        }
        if(!_b.size()||_b[0]<pos){
            _b.push_back(pos);
            _c.push_back(length);
            _d.push_back(ix);
        }else{
            _b.insert(_b.begin(),pos);
            _c.insert(_c.begin(),length);
            _d.insert(_d.begin(),ix);
        }
    }

    Braclet* div(int n) {
        Braclet* a=new Braclet;
        for(int i=0;i<_b.size();i++){
            if(_b[i]<n){
                a->_b.push_back(n-_b[i]);
                a->_c.push_back(_c[i]);
                a->_d.push_back(_d[i]);
            } else {
                _b.erase(_b.begin(),_b.begin()+i);
                _c.erase(_c.begin(),_c.begin()+i);
                _d.erase(_d.begin(),_d.begin()+i);
                break;
            }
        }
        for(int i=0;i<_b.size();i++){
            _b[i]-=n;
        }
        return a;
    }

    f output() {
        for(int i=0;i<_b.size();i++){
            _solutions[_d[i]]=_b[i]+_c[i];
        }
    }
};

z main() { int L,C,N;
    in>>L;in>>C;in>>N;
    Braclet*mine=new Braclet;
    for(int i=0;i<C;i++){int s,p;
        in>>s;in>>p;
        mine->add(s,p,i);
    }
    /*for(int i=0;i<C;i++){
        out<<mine->_b[i]<<endl;
    }
    out<<endl;*/
    Braclet*other=mine->div(N);
    mine->output();
    other->output();
    for(int i=0;i<C;i++){
        out<<_solutions[i]<<endl;
    }
    return 0;
}
