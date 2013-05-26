/*
 ID: drmrshd1
 PROG: numtri
 LANG: C++
*/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
using namespace std;
typedef int z;
typedef string S;
typedef istringstream Ss;
#define Yay return
ifstream in("numtri.in");
ofstream out("numtri.out");
template<class T>T s2(S s){Ss ss(s);T t;ss>>t;return t;}
template<class T>T wd(S&s){S wd;do{wd+=s[0];s.erase(0,1);}while(s[0]!=' '&&s[0]!='\0');return s2<T>(wd);}

class Node {
public:
    Node(char value) {_val=value;_pts=0;_children[0]=_children[1]=NULL;}
    void addChild(Node* node) { if (!_children[0]) _children[0]=node; else _children[1]=node; }
    void permutate() {
        //cerr << "I have " << (int)_pts << "points\n";
        for(z i=0;i<2;i++) if ( _val+_pts > _children[i]->_pts ) _children[i]->_pts=_val+_pts;
    }
    char _val; int  _pts;
    Node* _children[2];
}; Node** map[1000];

z main() { z R; S ln; z lnz;
    if(!in.good()){cerr<<"Can't open file!\n";exit(6);}
    getline(in,ln);R=wd<z>(ln);
    map[0] = new Node*[1];
    getline(in,ln);map[0][0]=new Node(wd<z>(ln));
    cerr << "1\n";
    for(z i=1;i<R;i++){ //i=line
        map[i]=new Node*[i+1];
        for(z j=0;j<=i;j++){
            in>>lnz;
            map[i][j]=new Node(lnz);
        }
        for(z j=0;j<=i-1;j++){
            map[i-1][j]->addChild(map[i][j]);
            map[i-1][j]->addChild(map[i][j+1]);
            map[i-1][j]->permutate();
            delete map[i-1][j];
        }
    }
    cerr << "3\n";
    cerr << R-1 << endl;
    Node* final=new Node(0);
    for(z j=0;j<R;j++){
        map[R-1][j]->addChild(final);
        map[R-1][j]->addChild(final);
    }
    for(z j=0;j<R;j++){
        map[R-1][j]->permutate();
    }
    cerr << "5\n";
    out<<(z)final->_pts<<endl;
}
