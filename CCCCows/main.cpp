#include <fstream>
#include <vector>
#include <cmath>
using namespace std;
ifstream in("in.txt");
ofstream out("out.txt");

struct p {
    int x,y;
    p(int cx=0,int cy=0) : x(cx),y(cy) {}
};

bool left(p&a,p&b,p&c) {
    return ((b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x)) >= 0;
}

int main() {
    int n;
    in>>n;
    p pts[n];
    int minx=9999999,mini;
    for(int i=0;i<n;i++) {
        in>>pts[i].x>>pts[i].y;
        if(pts[i].x<minx) {
            minx=pts[i].x;
            mini=i;
        }
    }
    //jarvis
    vector<p> bound;
    p strt=pts[mini];
    bound.push_back(strt);
    while(1) {
        p end = pts[0];
        int debugi=0;
        for(int i=1;i<n;i++) {
            if(strt.x==pts[i].x&&strt.y==pts[i].y) continue;
            if(left(strt,end,pts[i])) {
                end=pts[i];
                debugi=i;
            }
        }
        if(end.x==bound[0].x&&end.y==bound[0].y) break;
        else {
            bound.push_back(end);
            strt=end;
        }
    }
    //area
    int area=0;
    for(int i=0;i<bound.size()-1;i++) {
        area+=bound[i].x*bound[i+1].y;
        area-=bound[i].y*bound[i+1].x;
    }
    area/=2;
    out<<abs(area/50)<<endl;
}
