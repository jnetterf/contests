#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <stdio.h>
using namespace std;

#define in cin
#define out cout

struct point {
    int x,y;
    point(int cx,int cy) : x(cx),y(cy) {}
};

struct rect;
set<rect*> u;

struct rect {
    point s,e;
    rect(point cs,point ce) : s(cs),e(ce) {}
    void div(const int&x,const int&y) {
        if(x>=s.x&&y>=s.y&&x<=e.x&&y<=e.y) {
            u.insert(new rect(s,point(x,e.y)));
            u.insert(new rect(s,point(e.x,y)));
            u.insert(new rect(point(x,s.y),e));
            s=point(s.x,y);
        }
    }
    int size() {
//        out<<s.x<<','<<s.y<<'\t'<<e.x<<'-'<<e.y<<'\t'<<(e.x-s.x)*(e.y-s.y)<<endl;
        return (e.x-s.x)*(e.y-s.y);
    }
};

int main() {
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int x, y, t;
    in>>x>>y>>t;
    //x++;y++;
    u.insert((new rect(point(0,0),point(x,y))));
    for(int i=0;i<t;i++) {
        int a, b;
        in>>a>>b;
        int v=u.size();
        int j=-1;
        for(set<rect*>::iterator it=u.begin();++j<v;++it) {
            (*it)->div(a,b);
        }
    }
    int bestSize=0;
    for(set<rect*>::iterator it=u.begin();it!=u.end();++it) {
        bestSize=max(bestSize,(*it)->size());
    }
    out<<bestSize<<endl;
}

