/*
 ID: drmrshd1
 PROG: ariprog
 LANG: C++
*/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
using namespace std;
typedef string S;
typedef istringstream Ss;
typedef int z;
#define Yay return
ifstream in("ariprog.in");
ofstream out("ariprog.out");
template<class T>T s2(S s){Ss ss(s);T t;ss>>t;Yay t;}
template<class T>T wd(S&s){ S wd;
    do { wd+=s[0]; s.erase(0,1); } while(s[0]!=' '&&s[0]!='\0');
    return s2<T>(wd);
}

//order doesn't matter, q<=p for each p
//DF+ID

bool _found = false;
bool isBs[125001];
vector<z> bs;
void populateBiSquares(z limit){for(z i=0;i<=limit;i++)for(z j=0;j<=i;j++) if (!isBs[i*i+j*j]){  isBs[i*i+j*j]=1;bs.push_back(i*i+j*j);};}
z _i = -1;

bool doCheck(z start,z&length,z&interval,z&max) { z ch = start;
    //if (interval==1968) cerr << start << endl;
    z c = 0; bool didOne=false;
    do {
        //if ( interval==1968 && ch==118100 ) cerr << start << endl;
        if ( !isBs[start] ) { return didOne; }
        didOne=true;
        start+=interval;
    } while ( ++c < length );

    _found = true;
    out << ch << ' ' << interval << endl;
    if (++_i==9999) {
        exit(0);
    }
    return 0;
}

bool checkInt(z&interval,z&length,z&max){ z didOne=0;
    //cerr << interval << endl;
    z cache = interval*(length-1)-1;
    for(z i=0;i<bs.size();i++){   //i=start
        if (bs[i]+cache<=max) {
            //cerr << "checking" << i << ' ' << length << ' ' << interval << ' ' << max << endl;
            doCheck(bs[i],length,interval,max);
            didOne++;
        }else break;
    }
    //cerr << didOne << endl;
    return didOne;
}

void doEverything(z&length,z&max) {
    for(z i=1;i<max;i++) if ( !checkInt(i,length,max) ) return;
}

z main() { S ln; z N,M,max;
    if (!in.good()) cout << "Fail.\n";
    getline(in,ln); N = s2<z>(ln);
    getline(in,ln); M = s2<z>(ln);
    populateBiSquares(M);
    sort(bs.begin(), bs.end()); //loveC++
    vector<z>::iterator it = bs.begin();
    max = 2*M*M;
    doEverything(N,max);
    if (!_found) out << "NONE\n";
    Yay! '♪';
}
