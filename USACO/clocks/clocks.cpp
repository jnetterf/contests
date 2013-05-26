/*
 ID: drmrshd1
 PROG: clocks
 LANG: C++
*/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
typedef int z;
typedef string S;
typedef istringstream Ss;
#define Yay return
template<class T>T s2(S s){Ss ss(s);T t;ss>>t;return t;}
template<class T>T wd(S&s){S l; do { l = l+s[0]; s.erase(0,1); } while( s[0] != ' ' && s[0] != '\0');return s2<T>(l);}
ofstream out("clocks.out");

bool trs[10][9] = {
// A B C D E F G H I    A B C D E F G H I    A B C D E F G H I
  {1,1,0,1,1,0,0,0,0}, {1,1,1,0,0,0,0,0,0}, {0,1,1,0,1,1,0,0,0},
  {1,0,0,1,0,0,1,0,0}, {0,1,0,1,1,1,0,1,0}, {0,0,1,0,0,1,0,0,1},
  {0,0,0,1,1,0,1,1,0}, {0,0,0,0,0,0,1,1,1}, {0,0,0,0,1,1,0,1,1},
};

bool doTr(z* o, z* tr) {
    z* orig = new z[9];
    for(z i=0;i<9;i++) orig[i]=o[i];
    for(z i=0;i<9;i++){
        for(z j=0;j<9;j++) {
            orig[j] = (orig[j]+tr[i]*trs[i][j])%4;
        }
    }

    for(z i=0;i<9;i++) { if (orig[i]) return true; }
    z count = 0;
    for(z i=0;i<9;i++) {
        for( z j=0;j < tr[i];j++ ) {
            count++;
        }
    }
    z myCount = 0;
    for(z i=0;i<9;i++) {
        for( z j=0;j < tr[i];j++ ) {
            out << i+1;
            if ( ++myCount != count ) out << ' ';
        }
    }
    return false;
}

z main() {
    ifstream file("clocks.in");

    if(!file.good()){cout<<"Input does not exist.\n";return 6;}
    S ln; z* state = new z[9];


    for(z i=0;i<3;i++) {
        getline(file,ln);
        for(z j=0;j<3;j++) {
            state[3*i+j] = wd<z>(ln)/3%4;
        }
    }

    z* a = new z[9];
    for(z i=0;i<4;i++) { a[0]=i;
        for(z j=0;j<4;j++) { a[1]=j;
            for(z k=0;k<4;k++) { a[2]=k;
                for(z l=0;l<4;l++) { a[3]=l;
                    for(z m=0;m<4;m++) { a[4]=m;
                        for(z n=0;n<4;n++) { a[5]=n;
                            for(z o=0;o<4;o++) { a[6]=o;
                                for(z p=0;p<4;p++) { a[7]=p;
                                    for(z q=0;q<4;q++) { a[8]=q;
                                        if (!doTr( state, a ) ) Yay! '♪';
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
