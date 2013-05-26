/*
 ID: drmrshd1
 PROG: pageant
 LANG: C++
*/

// Grr!

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
//#define out cout
ifstream in("pageant.in");
ofstream out("pageant.out");

z N,M;
z connectivity[4][4]={{-1}};
z prereq[4][4]={{0}};
bool visited[51][51]={{0}};
bool thisTurn[51][51];
bool ok=1;
z coolmap[3][3]={{0}};

void flood1(const z& c,z owned[51][51], const z& x,const z&y)
{
    owned[x][y]=c;
    if(x+1!=N&&owned[x+1][y]==0)
    {
        flood1(c,owned,x+1,y);
    }

    if(y+1!=M&&owned[x][y+1]==0)
    {
        flood1(c,owned,x,y+1);
    }

    if(x!=0&&owned[x-1][y]==0)
    {
        flood1(c,owned,x-1,y);
    }

    if(y!=0&&owned[x][y-1]==0)
    {
        flood1(c,owned,x,y-1);
    }
}

void flood2(const z& me, z c,z owned[51][51], z world[51][51], const z& x,const z&y, bool goOn=0)
{
    if(thisTurn[x][y])
    {
       return;
    }
    if(!visited[x][y])
    {
        ok=1;
        visited[x][y]=1;
    }
    owned[x][y]=me;
    world[x][y]=c;
    if(!goOn) {
        return;
    }

    int modx,mody,modd;
    for(int mod=0;mod<4;mod++)
    {
        modd=(mod<2)?1:-1;
        if(mod%2==0) {
            modx=x+1*modd;
            mody=y;
        }
        if(mod%2==1) {
            modx=x;
            mody=y+1*modd;
        }

        if(modx==-1||modx==N||mody==-1||mody==M) continue;

        if(owned[modx][mody]!=-1&&owned[modx][mody]!=me)
        {
            if(!coolmap[min(me,owned[modx][mody])][max(me,owned[modx][mody])])
            {
//                out<<modx<<":"<<mody<<":"<<me<<":"<<owned[modx][mody]<<":"<<c<<"!\n";
                coolmap[min(me,owned[modx][mody])][max(me,owned[modx][mody])]=1;
                bool cool=1;
                if(connectivity[min(me,owned[modx][mody])][max(me,owned[modx][mody])]!=-1)
                {
                    cool=c<connectivity[min(me,owned[modx][mody])][max(me,owned[modx][mody])];
                    if(cool) {
                        connectivity[min(me,owned[modx][mody])][max(me,owned[modx][mody])]=c;
                    }
                } else {
                    connectivity[min(me,owned[modx][mody])][max(me,owned[modx][mody])]=c;
                }

                if(cool) {
                    prereq[min(me,owned[modx][mody])][max(me,owned[modx][mody])]=1;
                    c=0;
                    world[x][y]=0;
                }
            }
        }
    }

    if(x+1!=N&&world[x+1][y]>c&&world[x+1][y]!=-1)
    {
        flood2(me,world[x][y]+1,owned,world,x+1,y);
    }

    if(y+1!=M&&world[x][y+1]>c&&world[x][y+1]!=-1)
    {
        flood2(me,world[x][y]+1,owned,world,x,y+1);
    }

    if(x!=0&&world[x-1][y]>c&&world[x-1][y]!=-1)
    {
        flood2(me,world[x][y]+1,owned,world,x-1,y);
    }

    if(y!=0&&world[x][y-1]>c&&world[x][y-1]!=-1)
    {
        flood2(me,world[x][y]+1,owned,world,x,y-1);
    }
}

z main() {
    for(int i=0;i<4;i++) {
        for(int j=0;j<4;j++) {
            connectivity[i][j]=-1;
            prereq[i][j]=0;
        }
    }
    in>>N>>M;
    S lines[N];
    for(z n=0;n<N;n++) in>>lines[n];
    z world[51][51];
    z owned[51][51];
    for(z i=1;i<4;i++) {
        for(z n=0;n<4;n++) {
            for(z m=0;m<4;m++) {
                coolmap[n][m]=0;
            }
        }
        for(z n=0;n<N;n++) {
            for(z m=0;m<M;m++) {
                world[n][m]=(lines[n][m]=='.')?99999999:0;
                owned[n][m]=(lines[n][m]=='.')?-1:0;
                visited[n][m]=0;
            }
        }

        z c=0;
        for(z n=0;n<N;n++) {
            for(z m=0;m<M;m++) {
                if(owned[n][m]==0) {
                    flood1(++c,owned,n,m);
                }
            }
        }

        ok=1;
        while(ok)
        {
            ok=0;
            for(z n=0;n<N;n++) {
                for(z m=0;m<M;m++) {
                    if(owned[n][m]==i) {
                        flood2(owned[n][m],world[n][m],owned,world,n,m,1);
                    }
                }
            }
        }
//        for(z n=0;n<N;n++) {
//            for(z m=0;m<M;m++) {
//                if(world[n][m]<999) {
//                    out<<world[n][m];
//                } else out <<"#";
//            }
//            out<<endl;
//        }
//        out<<"#############\n";
    }

    int score=0,dualscore=9999999999;
    for(int took=0;took<2;took++)
    {
        for(z n=0;n<N;n++) {
            for(z m=0;m<M;m++) {
                thisTurn[n][m]=0;
            }
        }
        int minp=99999999;
        int mini,minj;
        for(z i=1;i<4;i++) {
            for(z j=1;j<4;j++) {
                out<<i<<":"<<j<<":"<<connectivity[i][j]<<endl;
                if(connectivity[i][j]!=-1&&connectivity[i][j]<minp&&!prereq[i][j]) {
                    minp=connectivity[i][j];
                    mini=i;
                    minj=j;
                }
                if(prereq[i][j]) {
                    int ttl=1;  //-1
                    for(z k=1;k<4;k++) {
                        ttl+=connectivity[min(i,k)][max(i,k)];
                    }
                    out<<ttl<<endl;
                    dualscore=min(dualscore,ttl);
                }
            }
        }
        if(minp==99999999)
        {
            score=minp;
            break;
        }
        connectivity[mini][minj]=-1;
        score+=minp;
    }
    out<<min(score,dualscore)<<endl;
}
