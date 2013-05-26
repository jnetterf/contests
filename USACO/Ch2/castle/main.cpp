/*
 ID: drmrshd1
 PROG: castle
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
ifstream in("castle.in");
ofstream out("castle.out");

z raw[52][52], map[52][52], maxN,maxM, sizes[250000];

f flood( z id, z n, z m ){
    if(map[n][m]!=-1||n>=maxN||m>=maxM||n<0||m<0)return;
    map[n][m]=id;sizes[id]++;
    if(raw[n][m]>=8)raw[n][m]-=8;else flood(id,n+1,m);
    if(raw[n][m]>=4)raw[n][m]-=4;else flood(id,n,m+1);
    if(raw[n][m]>=2)raw[n][m]-=2;else flood(id,n-1,m);
    if(raw[n][m]>=1)raw[n][m]-=1;else flood(id,n,m-1);
}

z main() {z lastId=-1;
    in>>maxM;in>>maxN;

    { //init
        for(z i=0;i<maxN;i++){for(z j=0;j<maxM;j++){in>>raw[i][j];map[i][j]=-1;}sizes[i]=0;}
        for(z i=0;i<maxN;i++)for(z j=0;j<maxM;j++)if(map[i][j]==-1)flood(++lastId, i,j);
    }

    out<<++lastId<<endl;//number of rooms, make lastId work in for loops.

    {z maxSize=-1;
        for(z i=0;i<lastId;i++){
            if(sizes[i]>maxSize){maxSize=sizes[i];}
        }
        out<<maxSize<<endl;
    }

    { z maxHoriz=-1, maxVert=-1, hidX, hidY, vidX, vidY;
        for(z i=0;i<maxN;i++)for(z j=0;j<maxM;j++){
            if((i!=maxN-1)&&(map[i][j]!=map[i+1][j])){ z a;
                a = sizes[map[i][j]]+sizes[map[i+1][j]];
                if( maxVert < a) { vidX=j;vidY=i; maxVert=a; }
                if( maxVert==a ) {
                    if (vidX>j) { vidX=j;vidY=i; maxVert=a; }
                    else if (vidX==j&& vidY<i) { vidX=j;vidY=i; maxVert=a; }
                }
            }
            if((j!=maxM-1)&&(map[i][j]!=map[i][j+1])){ z a;
                a = sizes[map[i][j]]+sizes[map[i][j+1]];
                if( maxHoriz < a) { hidX=j;hidY=i; maxHoriz=a; }
                if( maxHoriz==a ) {
                    if (hidX>j) { hidX=j;hidY=i; maxHoriz=a; }
                    else if (hidX==j&& hidY<i) { hidX=j;hidY=i; maxHoriz=a; }
                }
            }
        }
        hidX++;hidY++;vidX++;vidY++;
        if(maxHoriz>maxVert) {
            out<<maxHoriz<<endl<<hidY<<' '<<hidX<<' '<<'E'<<endl;
        } else if(maxVert>maxHoriz) {
            out<<maxVert<<endl<<vidY+1<<' '<<vidX<<' '<<'N'<<endl;
        } else {    // if xs are equal, prefer vert. because by definition vert is more west.
            if (hidX<vidX) out<<maxHoriz<<endl<<hidY<<' '<<hidX<<' '<<'E'<<endl;
            else if(hidX==vidX&&hidY<vidY) out<<maxHoriz<<endl<<hidY<<' '<<hidX<<' '<<'E'<<endl;
            else out<<maxVert<<endl<<vidY+1<<' '<<vidX<<' '<<'N'<<endl;
        }
    }
}
