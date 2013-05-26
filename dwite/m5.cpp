#include <fstream>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <map>
#include <bitset>
using namespace std;

ifstream in("DATA5.txt");
ofstream out("OUT5.txt");

// 10 min remaining type solution

struct Pos {
    long x,y,z;
};

void simil(const long& a,const long& b,const long& c, const long& d,const long& e,const long& f, const long& g,const long& h,const long& i, const long& t, Pos& p) {
    p.x=a*t*t + b*t + c;
    p.y=d*t*t + e*t + f;
    p.z=g*t*t + h*t + i;
}

long dis(Pos&a,Pos&b) {
    return abs(a.x-b.x)+abs(a.y-b.y)+abs(a.z-b.z);
}

int main() {
    for(long i=0;i<5;i++) {
        long N;
        in>>N;
        Pos extrema[6];
        Pos p;
        for(long j=0;j<N;j++) {
            long a,b,c,d,e,f,g,h,i,u,v;
            in>>a>>b>>c>>d>>e>>f>>g>>h>>i>>u>>v;
            for(long k=u;k<=v;k++) {
                simil(a,b,c,d,e,f,g,h,i,k,p);
                if(k==u&&!j) {
                    extrema[0]=extrema[3]=extrema[1]=extrema[4]=extrema[2]=extrema[5]=p;
                } else {
                    if(p.x>extrema[0].x) extrema[0]=p;
                    if(p.x>extrema[3].x) extrema[3]=p;
                    if(p.y>extrema[1].y) extrema[1]=p;
                    if(p.y>extrema[4].y) extrema[4]=p;
                    if(p.z>extrema[2].z) extrema[2]=p;
                    if(p.z>extrema[5].z) extrema[5]=p;
                }
            }
        }
        long maxDis=0;
        for(long i=0;i<6;i++) {
            for(long j=i;j<6;j++) {
                maxDis=max(maxDis,dis(extrema[i],extrema[j]));
            }
        }
        out<<maxDis<<endl;
    }
}


