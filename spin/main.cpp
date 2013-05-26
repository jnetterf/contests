/*
 PROB: spin
 USER: drmrshd1
 LANG: C++
*/

#include <fstream>
#include <vector>
using namespace std;
ifstream in("spin.in");
ofstream out("spin.out");

bool e(int a,int b,int c) {
//    out<<a<<" e ("<<b<<','<<c<<" )"<<endl;

    if(c<b) c+=360;
    if(a<b) a+=360;
    if(a>c) a-=360;
//    out<<a<<" e ("<<b<<','<<c<<" )"<<endl;
//    out<<((a>=b)&&(a<=c)&&!(a==b&&a==c))<<endl;
    return (a>=b)&&(a<=c)&&!(a==b&&a==c);
}

struct gap {
    int min,max;
    gap(int cmin,int cmax) : min(cmin),max(cmax) {}
    bool operator==(gap& that) {
        return e(that.max,min,max)||e(that.min,min,max)||e(max,that.min,that.max)||e(min,that.min,that.max);
    }
};

struct wheel {
    vector<gap> gaps;
    int speed;
    int angle;
    bool operator==(wheel& that) {
        for(int i=0;i<gaps.size();i++) {
            for(int j=0;j<that.gaps.size();j++) {
                if(gaps[i]==that.gaps[j]) {/*out<<"XD\n";*/return 1;}
            }
        }
//        out<<":(\n";
        return 0;
    }
    bool operator++(int a) {
        for(int i=0;i<gaps.size();i++) {
            gaps[i].min+=speed;
            gaps[i].min%=360;
            gaps[i].max+=speed;
            gaps[i].max%=360;
        }
        angle+=speed;
        angle%=360;
    }
    wheel() :
        angle(0)
    {

    }
    void report() {
        for(int i=0;i<gaps.size();i++)
            out<<gaps[i].min<<'\t'<<gaps[i].max<<endl;
        out<<endl;
    }
};

int main() {
    wheel wheels[5];
    for(int i=0;i<5;i++) {
        in>>wheels[i].speed;
        int x;
        in>>x;
        for(int j=0;j<x;j++) {
            int min, max;
            in>>min>>max;
            wheels[i].gaps.push_back(gap(min%360,(min+max)%360));
        }
    }
    int n=0;
//    for(int i=0;i<5;i++)
//        wheels[i].report();;
    while(1) {
        bool ok=1;
        wheel x;
        x.speed=1;
        x.gaps.push_back(gap(0,0));
        for(int i=0;i<360;i++,x++) {
//            x.report();
//            out<<endl;
            ok=1;
            for(int j=0;j<5;j++) {
                if(!(wheels[j]==x)) {
//                    out<<"NOT GOOD\n";
                    ok=0;
                    break;
                }
            }
            if(ok) {
                out<<n<<endl;
                return 0;
            }
        }

        n++;
        for(int i=0;i<5;i++) {
            wheels[i]++;
//            if(n==61) for(int i=0;i<5;i++)
//                wheels[i].report();
        }
//        out<<endl;


        ok=1;
        for(int i=0;i<5;i++)
            if(wheels[i].angle!=0) { ok=0; break; }
        if(ok) {
            //out<<n<<endl;
            out<<"none"<<endl;
            return 0;
        }
    }
}
