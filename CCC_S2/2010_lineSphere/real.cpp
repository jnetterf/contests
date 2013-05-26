/*

#include <fstream>
#include <vector>
using namespace std;
ifstream in("in.txt");
ofstream out("out.txt");

//
// I) Exact math
//
int gcf(int a,int b) { while(b) { int t=b; b=a%b; a=t; } return a; }

struct real { int num, den; real* sqRoot; void reduce() { int g=gcf(num,den); if(g){num/=g; den/=g;} if(sqRoot) sqRoot->reduce(); if(den<0){den*=-1;num*=-1;}} real(int n=1,int d=1){num=n;den=d;sqRoot=0;} };
void makeComparable(real&a,real&b);
bool operator==(real a,real b) { makeComparable(a,b); return a.num==b.num; }
bool operator <(real a,real b) { makeComparable(a,b); return a.num<b.num; }
bool operator >(real a,real b) { makeComparable(a,b); return a.num>b.num; }

real operator +(real a,real b) {
    a.reduce(); b.reduce(); if(a.den!=b.den) { real c=b; b.den*=a.den; b.num*=a.den; a.den*=c.den; a.num*=c.den; } real ret=a;ret.num+=b.num;
    real* newRoot = new real(0);
    if(!a.sqRoot&&!b.sqRoot) {}
    else if(a.sqRoot&&!b.sqRoot) {*newRoot = *a.sqRoot;}
    else if(b.sqRoot&&!a.sqRoot) { *newRoot = *b.sqRoot; }
    else out<<"ERROR!\n";
    ret.sqRoot=newRoot;
    ret.reduce(); return ret;
}
real operator -(real a,real b) {
    a.reduce(); b.reduce(); if(a.den!=b.den) { real c=b; b.den*=a.den; b.num*=a.den; a.den*=c.den; a.num*=c.den; } real ret=a;ret.num-=b.num;
    real* newRoot = new real(0);
    if(!a.sqRoot&&!b.sqRoot) {}
    else if(a.sqRoot&&!b.sqRoot) {*newRoot = *a.sqRoot;}
    else if(b.sqRoot&&!a.sqRoot) { *newRoot = *b.sqRoot; }
    else out<<"ERROR!\n";
    ret.sqRoot=newRoot;
    ret.reduce(); return ret;
}
real operator *(real a,real b) { a.reduce(); b.reduce(); real ret=b; ret.num*=a.num;ret.den*=a.den;
    real* newRoot = new real;
    if(!a.sqRoot&&!b.sqRoot) {}
    if(a.sqRoot&&!b.sqRoot) {*newRoot = *a.sqRoot;}
    else if(b.sqRoot&&!a.sqRoot) { *newRoot = *b.sqRoot; }
    else out<<"ERROR!\n";
    ret.sqRoot=newRoot;
    if(a.sqRoot) {*ret.sqRoot=(*ret.sqRoot)*(*a.sqRoot);}
    ret.reduce(); return ret;
}
real operator /(real a,real b) { a.reduce(); b.reduce(); real ret=a; ret.num*=b.den;ret.den*=b.num;
    real* newRoot = new real;
    if(!a.sqRoot&&!b.sqRoot) {}
    else if(a.sqRoot&&!b.sqRoot) {*newRoot = *a.sqRoot;}
    else if(b.sqRoot&&!a.sqRoot) { *newRoot = *b.sqRoot; }
    else out<<"ERROR!\n";
    ret.sqRoot=newRoot;
    if(b.sqRoot) {*ret.sqRoot=*ret.sqRoot / *b.sqRoot;}
    ret.reduce(); return ret;
}
real sqrt(const real&a) {
    real ret;
    ret.num=0;
    ret.sqRoot = new real;
    //if(a.sqRoot) { a.sqRoot->sqRoot=new real; *ret.sqRoot->sqRoot=*a.sqRoot; }
    out<<a.num<<"XX"<<endl;
    *ret.sqRoot = a;
    ret.reduce();
    out<<ret.sqRoot->num<<"XX"<<endl;
    return ret;
}
void makeComparable(real&a,real&b) {
    a.reduce(); b.reduce();
    bool aneg=a.num<0; bool bneg=b.num<0;
    if(a.sqRoot||b.sqRoot) { a=a*a; b=b*b; }
    if(aneg) a.num*=-1; if(bneg) b.num*=-1; //don't forget about signs
    if(a.den!=b.den) { real c=b; b.den*=a.den; b.num*=a.den; a.den*=c.den; a.num*=c.den; }
}
//
// II) Geometry
//
struct point { real x, y, z; };
struct line { point m,b; };
struct sphere { point c; real r; };
vector<point> intercept(line l, sphere s) {

    //Paper + 20 minutes ---Joshua---> Headache

    real a =    l.m.x*l.m.x + l.m.y*l.m.y + l.m.z*l.m.z;
    real b =    real(-2)*s.c.x*l.m.x +  real(-2)*s.c.y*l.m.y +  real(-2)*s.c.z*l.m.z +
                real(+2)*l.m.x*l.b.x +  real(+2)*l.m.y*l.b.y +  real(+2)*l.m.z*l.b.z;
    real c =    s.c.x*s.c.x + s.c.y*s.c.y + s.c.y*s.c.y +
                real(-2)*s.c.x*l.b.x +  real(-2)*s.c.y*l.b.y +  real(-2)*s.c.z*l.b.z +
                l.b.x*l.b.x +   l.b.y*l.b.y +   l.b.z*l.b.z -
                s.r*s.r;

    out<<"A:"<<a.num<<'/'<<a.den<<endl;
    out<<"B:"<<b.num<<'/'<<b.den<<endl;
    out<<"C:"<<c.num<<'/'<<c.den<<endl;

    out<<(0-b+sqrt(b*b - 4*a*c)).num<<'/'<<(0-b+sqrt(b*b - 4*a*c)).den<<':'<<(0-b+sqrt(b*b - 4*a*c)).sqRoot->num<<'/'<<(0-b+sqrt(b*b - 4*a*c)).sqRoot->den<<endl;
    real roots[2] =
        { ( 0-b    +   sqrt(b*b - 4*a*c ) ) / (2*a),
          ( 0-b    -   sqrt(b*b - 4*a*c ) ) / (2*a) };

    out<<"r1:"<<roots[0].num<<'/'<<roots[0].den<<':'<<roots[0].sqRoot->num<<'/'<<roots[0].sqRoot->den<<endl;
    out<<"r2:"<<roots[1].num<<'/'<<roots[1].den<<':'<<roots[1].sqRoot->num<<'/'<<roots[1].sqRoot->den<<endl;

    vector<point> ret;
    for(int i=0;i<2;i++) {
        if(roots[i].sqRoot->num>0) {
            point intercept;
            intercept.x=l.b.x+roots[i]*l.m.x;
            intercept.x=l.b.y+roots[i]*l.m.y;
            intercept.x=l.b.z+roots[i]*l.m.z;
            ret.push_back(intercept);
        }
    }
    return ret;
}

int main() {
    line l;
    l.b.x=0;
    l.b.y=0;
    l.b.z=0;
    l.m.x=8;
    l.m.y=0;
    l.m.z=0;
    sphere s;
    s.c.x=10;
    s.c.y=0;
    s.c.z=0;
    s.r=1;
    vector<point> p=::intercept(l,s);
    for(int i=0;i<p.size();i++) {
        out<<"X\n";
        out<<p[i].x.num<<'/'<<p[i].x.den;
        if(p[i].x.sqRoot) out<<':'<<p[i].x.sqRoot->num<<'/'<<p[i].x.sqRoot->den;
        out<<endl;
    }
}
*/
