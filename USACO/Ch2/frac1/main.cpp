/*
 ID: drmrshd1
 PROG: frac1
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
ifstream in("frac1.in");
ofstream out("frac1.out");

bool isReducable(const z&n,const z&d) {
    for(z i=2;i<d;i++)if((n%i==0)&&(d%i==0)){
        return 1;
    }
    return 0;
}

class Frac{public:Frac(z tn,z td){n=tn;d=td;}z n;z d;};


bool operator<(Frac first, Frac other){return (double)first.n/(double)first.d < (double)other.n/(double)other.d; }
bool operator>(Frac first, Frac other){return (double)first.n/(double)first.d > (double)other.n/(double)other.d; }

z main() {z n; vector<Frac> _u;
    in>>n;
    _u.push_back(Frac(0,1));
    for(z i=1;i<=n;i++){
        for(z j=1;j<i;j++){
            if(!isReducable(j,i))_u.push_back(Frac(j,i));
        }
    }
    _u.push_back(Frac(1,1));
    sort( _u.begin(),_u.end() );
    for(z i=0;i<_u.size();i++){
        out<<_u[i].n<<'/'<<_u[i].d<<endl;
    }
}
