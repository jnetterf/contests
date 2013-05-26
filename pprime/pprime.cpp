/*
 ID: drmrshd1
 PROG: pprime
 LANG: C++
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <math.h>
#define Yay return;
using namespace std;
typedef int z;
typedef void f;
typedef string S;
typedef istringstream Ss;
template<class T>T s2(S s){Ss ss(s);T t;ss>>t;return t;}
template<class T>T wd(S&s){S wd;do{wd=wd+s[0];s.erase(0,1);}while(s[0]!=' '&&s[0]!='\0');return s2<T>(wd);}
ifstream in("pprime.in");
ofstream out("pprime.out");

z MIN=0,MAX=0; vector<z> ps;
#define add2ps(x) do{if(x<MIN)continue;if(x>MAX)continue;else ps.push_back(x);}while(0)

f genP(){
    for(z i=1;i<10;i+=2)add2ps(i);
    for(z i=1;i<10;i+=2)add2ps(i*10+i);
    for(z i=1;i<10;i+=2)for(z j=0;j<10;j++)add2ps(i*100+j*10+i);
    for(z i=1;i<10;i+=2)for(z j=0;j<10;j++)add2ps(i*1000+j*100+j*10+i);
    for(z i=1;i<10;i+=2)for(z j=0;j<10;j++)for(z k=0;k<10;k++)add2ps(i*10000+j*1000+k*100+j*10+i);
    for(z i=1;i<10;i+=2)for(z j=0;j<10;j++)for(z k=0;k<10;k++)add2ps(i*100000+j*10000+k*1000+k*100+j*10+i);
    for(z i=1;i<10;i+=2)for(z j=0;j<10;j++)for(z k=0;k<10;k++)for(z l=0;l<10;l++)
        add2ps(i*1000000+j*100000+k*10000+l*1000+k*100+j*10+i);
    for(z i=1;i<10;i+=2)for(z j=0;j<10;j++)for(z k=0;k<10;k++)for(z l=0;l<10;l++)
        add2ps(i*10000000+j*1000000+k*100000+l*10000+l*1000+k*100+j*10+i);
    for(z i=1;i<10;i+=2)for(z j=0;j<10;j++)for(z k=0;k<10;k++)for(z l=0;l<10;l++)for(z m=0;m<10;m++)
        add2ps(i*100000000+j*10000000+k*1000000+l*100000+m*10000l*1000+k*100+j*10+i);
}

z main() {
    in>>MIN; in>>MAX;
    genP();
    for(z i=0;i<ps.size();i++){z jmax=sqrt(ps[i])+1; bool ok=true;
        for( z j=3;j<jmax;j++) {
            if( ps[i]%j == 0){ ok=false;break;}
        }
        if (ok)out<<ps[i]<<endl;
    }
    //for(z i=0;i<ps.size();i++){out<<ps[i]<<endl;}
}
