/*
 ID: drmrshd1
 PROG: numgrid
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
ifstream in("numgrid.in");
ofstream out("numgrid.out");

z field[6][6];
vector<z> _scores;

f record(z score) {
    score=score%1000000;
    for(z i=0;i<_scores.size();i++)if (score==_scores[i])return;
    _scores.push_back(score);
}

f doIt(z x,z maX,z y,z maY,z depth,z score){
    if(x>=maX||y>=maY||x<0||y<0) return;
    score=score*10+field[x][y];
    if (depth==6){record(score);return;}
    doIt(x+1,maX,y,maY,depth+1,score);
    doIt(x,maX,y+1,maY,depth+1,score);
    doIt(x-1,maX,y,maY,depth+1,score);
    doIt(x,maX,y-1,maY,depth+1,score);
}

z main(){
    for(z i=0;i<5;i++)for(z j=0;j<5;j++)in>>field[i][j];
    for(z i=0;i<5;i++)for(z j=0;j<5;j++)doIt(i,5,j,5,1,10);
    out<<_scores.size()<<endl;
}
