#include <fstream>
using namespace std;
ifstream in("in.txt");
ofstream out("out.txt");

typedef long long real;

struct point { real x, y, z; };
struct line { point m,b; };
struct sphere { point c; real r; };
bool intercepts(line l, sphere s) {

    real a =    l.m.x*l.m.x + l.m.y*l.m.y + l.m.z*l.m.z;

    real b =    -2*s.c.x*l.m.x +  -2*s.c.y*l.m.y +  -2*s.c.z*l.m.z +
                +2*l.m.x*l.b.x +  +2*l.m.y*l.b.y +  +2*l.m.z*l.b.z;

    real c =    s.c.x*s.c.x + s.c.y*s.c.y + s.c.y*s.c.y +
                -2*s.c.x*l.b.x +  -2*s.c.y*l.b.y +  -2*s.c.z*l.b.z +
                l.b.x*l.b.x +   l.b.y*l.b.y +   l.b.z*l.b.z -
                s.r*s.r;

    real det=(b*b-4*a*c);

    if(det<0) return 0;
    if(a>0) {
        if (b>=0) return 1;
        else if (c<=0) return 1;
        else return 0;
    } else {
        if (b<=0) return 1;
        else if (c<=0) return 1;
        else return 0;
    }
    return 0;
}
struct planet {
    sphere s;
    long long v;
};

int main() {

    int M; in>>M;
    planet u[M];
    for(int i=0;i<M;i++) {
        in>>u[i].s.c.x;
        in>>u[i].s.c.y;
        in>>u[i].s.c.z;
        in>>u[i].v;
        in>>u[i].s.r;
    }
    int N; in>>N;

    line w[N];
    for(int i=0;i<N;i++) {
        in>>w[i].m.x;
        in>>w[i].m.y;
        in>>w[i].m.z;
    }

    int R; in>>R;
    for(int i=0;i<M;i++) u[i].s.r+=R;

    long long score=0;
    point p;
    p.x=p.y=p.z=0;
    for(int i=0;i<N;i++) {
        line l=w[i];
        l.b.x=p.x;
        l.b.y=p.y;
        l.b.z=p.z;
        l.m.x=l.m.x-p.x;
        l.m.y=l.m.y-p.y;
        l.m.z=l.m.z-p.z;
        line li;
        li.m.x=l.m.x*-1;
        li.m.y=l.m.y*-1;
        li.m.z=l.m.z*-1;
        li.b.x=l.m.x+l.b.x;
        li.b.y=l.m.y+l.b.y;
        li.b.z=l.m.z+l.b.z;

        for(int j=0;j<M;j++) {
            if(!u[j].v) continue;
            if(intercepts(l,u[j].s)&&intercepts(li,u[j].s)) {
                score=score+u[j].v;
                u[j].v=0;
            }
        }
        p.x=p.x+l.m.x;
        p.y=p.y+l.m.y;
        p.z=p.z+l.m.z;
        out<<p.x<<' '<<p.y<<' '<<p.z<<endl;
    }
    out<<score<<endl;
}
