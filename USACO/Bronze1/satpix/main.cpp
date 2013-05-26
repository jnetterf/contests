/*
 ID: drmrshd1
 PROG: satpix
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
ifstream in("satpix.in");
ofstream out("satpix.out");

bool field[82][1002];
bool visit[82][1002];

z floodFill(z x,z maX,z y,z maY){z count=1;//me
    if(x>=maX||y>=maY||x<0||y<0||visit[x][y]||!field[x][y]) return 0;
    visit[x][y]=1;
    count+=floodFill(x+1,maX,y,maY);
    count+=floodFill(x,maX,y+1,maY);
    count+=floodFill(x-1,maX,y,maY);
    count+=floodFill(x,maX,y-1,maY);
    return count;
}

z main(){ z w,h,maxA=-1; S ln;
    in>>w;in>>h;
    for(z i=0;i<h;i++){
        in>>ln;
        for(z j=0;j<w;j++){
            if(ln[0]=='*')field[j][i]=1;
            else field[j][i]=0;
            visit[j][i]=0;
            ln.erase(0,1);
        }
    }
    for(z i=0;i<h;i++)for(z j=0;j<w;j++)maxA=max(maxA,floodFill(j,w,i,h));
    out<<maxA<<endl;
}
