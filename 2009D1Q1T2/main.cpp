//int reallyBig(int) { return 99999999; }
double reallyBig(double) { return 9999999; }
//long long reallyBig(long long) { return 99999999; }

template<typename T> struct P {
T x; T y;
};

template<typename T> struct L {
P<T> pos; P<T> dir;

T y4x(T x) {
    if(!dir.y) return pos.x==x ? pos.y : reallyBig(T());

    //cannot work backwards
    //if(dir.x>0&&x<=pos.x) return reallyBig(T());
    //if(dir.x<0&&x>=pos.x) return reallyBig(T());

    T m = dir.y/dir.x; T b = pos.y-m*pos.x;
    return m*x+b;
}
T x4y(T y) {
    if(!dir.x) return pos.y==y ? pos.x : reallyBig(T());


    T m = dir.y/dir.x; T b = pos.y-m*pos.x;

    //cannot work backwards
    //if(dir.x>0&&(y-b)/m<=pos.x) return reallyBig(T());
    //if(dir.x<0&&(y-b)/m>=pos.x) return reallyBig(T());

    return (y-b)/m;
}
};


bool fuzzyCompare(long double a,long double b) {
    return a==b;
}

template<typename T> struct R {
P<T> tlf;/************/
/*********************/
/************/P<T> bmr;

bool valid;

R() : valid(1) {}

int collide(P<T> with) {
    if(fuzzyCompare(with.x,tlf.x)) {
        if(with.y==tlf.y||with.y==bmr.y) return 1;
        if(with.y<tlf.y&&with.y>bmr.y) return 2;
        if(with.y>tlf.y&&with.y<bmr.y) return 2;
    }
    if(fuzzyCompare(with.x,bmr.x)) {
        if(with.y==tlf.y||with.y==bmr.y) return 1;
        if(with.y<tlf.y&&with.y>bmr.y) return 2;
        if(with.y>tlf.y&&with.y<bmr.y) return 2;
    }
    if(fuzzyCompare(with.y,tlf.y)) {
        if(with.x==tlf.x||with.x==bmr.x) return 1;
        if(with.x<tlf.x&&with.x>bmr.x) return 3;
        if(with.x>tlf.x&&with.x<bmr.x) return 3;
    }
    if(fuzzyCompare(with.y,bmr.y)) {
        if(with.x==tlf.x||with.x==bmr.x) return 1;
        if(with.x<tlf.x&&with.x>bmr.x) return 3;
        if(with.x>tlf.x&&with.x<bmr.x) return 3;
    }
    return 0;
}
};

#include <fstream>
#include <vector>
#include <cmath>
using namespace std;
ifstream in("in.txt");
ofstream out("out.txt");
typedef long double int64;

template<typename T> T ruler(P<T> a, P<T> b) { return std::sqrt( (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) ); }

int main() {
    int N; in>>N;

    L<int64> ray; ray.pos.x=ray.pos.y=0;
    in>>ray.dir.x;in>>ray.dir.y;
    out<<ray.dir.x<<' '<<ray.dir.y<<endl;

    R<int64> boxes[N];
    for(int i=0;i<N;i++) {
        int x; int y; int w; int h;
        in>>x; in>>y; in>>w; in>>h;

        out<< (boxes[i].tlf.x = x);    // X
        out<<' ';
        out<< (boxes[i].tlf.y = y);    // X
out<<' ';

        out<< (boxes[i].bmr.x = x+w);    // X
        out<<' ';
        out<< (boxes[i].bmr.y = y+h);    // X
        out<<' ';
        out<<endl;
    }

    for(int i=0;i<=N;i++) {
        int bestJ=-1;
        int64 dis=reallyBig(int64());
        int bestC;
        P<int64> point;
        for(int j=0;j<N;j++) {
            if(!boxes[j].valid) continue;
            P<int64> goodPoints[4];
            goodPoints[0].y = ray.y4x( goodPoints[0].x = boxes[j].tlf.x );
            goodPoints[1].y = ray.y4x( goodPoints[1].x = boxes[j].bmr.x );
            goodPoints[2].x = ray.x4y( goodPoints[2].y = boxes[j].tlf.y );
            goodPoints[3].x = ray.x4y( goodPoints[3].y = boxes[j].bmr.y );
            for(int k=0;k<4;k++) {
                int c = boxes[j].collide(goodPoints[k]);
                out<<c<<endl;
                if(c&&(         ruler(goodPoints[i],ray.pos)<dis)       ) {
                    bestJ=j; bestC=c; dis=ruler(goodPoints[i],ray.pos); point.x = goodPoints[i].x; point.y=goodPoints[i].y;
                    out<<"!!!!"<<point.x<<' '<<point.y<<endl;
                }
            }
            out<<endl;
        }
        if(bestJ!=-1) {
            out<<"##";
            out<<bestJ+1<<endl;
            boxes[bestJ].valid=0;

            if((bestC==1)||(bestC==2)) {
                ray.dir.x*=-1;
            }
            if((bestC==1)||(bestC==3)) {
                ray.dir.y*=-1;
            }

            ray.pos.x=point.x; ray.pos.y=point.y;
        }
    }
}
