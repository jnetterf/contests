/*
 ID: drmrshd1
 PROG: sprime
 LANG: C++
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <math.h>
#define Yay return
using namespace std;
typedef int z;
typedef void f;
typedef string S;
typedef istringstream Ss;
template<class T>T s2(S s){Ss ss(s);T t;ss>>t;return t;}
template<class T>T wd(S&s){S wd;do{wd=wd+s[0];s.erase(0,1);}while(s[0]!=' '&&s[0]!='\0');return s2<T>(wd);}
ifstream in("sprime.in");
ofstream out("sprime.out");

z MIN=0,MAX=0; vector<z> ps;
#define add2ps(x) do{if(x<MIN)continue;if(x>MAX)continue;else ps.push_back(x);}while(0)

z _lvl=1;
vector<z> nextPrime;

f advancePrime(){
    vector<z> current;
    _lvl*=10;
    for(z i=0;i<nextPrime.size();i++){
        for(z j=1;j<10;j++){ z mej=j+10*nextPrime[i]; z maxk=sqrt(mej)+1; bool ok = true; z lvl=_lvl/10;
            //out << "Testing " << mej << endl;
            for(z k=2;k<maxk;k++){
                if(mej%k==0) {ok=false;break;}
            }
            if(ok) {current.push_back(mej);}
        }
    }
    nextPrime=current;
}

z main() { z maxLvl;
    if(!in.good()){cerr<<"Can't open file."; Yay!1;}
    nextPrime.push_back(2);for(z i=3;i<8;i+=2) nextPrime.push_back(i);
    in>>maxLvl;
    for(z i=0;i<maxLvl-1;i++)advancePrime();
    for(z i=0;i<nextPrime.size();i++)out<<nextPrime[i]<<endl;
}
