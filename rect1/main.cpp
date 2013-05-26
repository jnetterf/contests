/*
 PROB: rect1
 LANG: C++
 USER: drmrshd1
*/

#include <fstream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;/*
ifstream in("in.txt");
ofstream out("out.txt");*/
ifstream in("rect1.in");
ofstream out("rect1.out");

int area(const int&llx,int const&lly,const int&urx,const int&ury) {
    int area=(lly-ury)*(llx-urx);
    if((lly-ury)>0) area=0;
    if((llx-urx)>0) area=0;
    return area;
}

struct Rect {
    int ll[2],ur[2];
    Rect(const int&llx,int const&lly,const int&urx,const int&ury) {
        ll[0]=llx;
        ll[1]=lly;
        ur[0]=urx;
        ur[1]=ury;
    }
};

bool operator==(const Rect&a,const Rect&b) {
    for(int i=0;i<2;i++) {
        if(a.ll[i]!=b.ll[i]) return 0;
        if(a.ur[i]!=b.ur[i]) return 0;
    }
    return 1;
}

struct Clr {
    list<Rect> rec;

    Clr& operator-=(const Rect& crec) {
        int maxi=rec.size();
//        bll[0]=bll[1]=bur[0]=bur[1]=0;
        for(int i=0;i<maxi;i++) {
//            out<<"SQR "<<i<<endl;
            if( rec.front().ll[0]>crec.ur[0] ||
                rec.front().ll[1]>crec.ur[1] ||
                rec.front().ur[0]<crec.ll[0] ||
                rec.front().ur[1]<crec.ll[1]) {

                rec.push_back(rec.front());
                rec.pop_front();
                continue;

            }
            int llx=rec.front().ll[0],lly=rec.front().ll[1],urx=rec.front().ur[0],ury=rec.front().ur[1];
            int     xllx=max(min(crec.ll[0],urx),llx),
                    xlly=max(min(crec.ll[1],ury),lly),
                    xurx=min(max(crec.ur[0],llx),urx),
                    xury=min(max(crec.ur[1],lly),ury);
            rec.pop_front();
            if(area(llx,lly,xllx,xlly)>0) rec.push_back(Rect(llx,lly,xllx,xlly));
            if(area(xllx,lly,xurx,xlly)>0) rec.push_back(Rect(xllx,lly,xurx,xlly));
            if(area(xurx,lly,urx,xlly)>0) rec.push_back(Rect(xurx,lly,urx,xlly));
            if(area(xurx,xlly,urx,xury)>0) rec.push_back(Rect(xurx,xlly,urx,xury));
            if(area(xurx,xury,urx,ury)>0) rec.push_back(Rect(xurx,xury,urx,ury));
            if(area(xllx,xury,xurx,ury)>0) rec.push_back(Rect(xllx,xury,xurx,ury));
            if(area(llx,xury,xllx,ury)>0) rec.push_back(Rect(llx,xury,xllx,ury));
            if(area(llx,xlly,xllx,xury)>0) rec.push_back(Rect(llx,xlly,xllx,xury));

//            Rect r[8]=
//            {   Rect(llx,lly,xllx,xlly),
//                Rect(xllx,lly,xurx,xlly),
//                Rect(xurx,lly,urx,xlly),
//                Rect(xurx,xlly,urx,xury),
//                Rect(xurx,xury,urx,ury),
//                Rect(xllx,xury,xurx,ury),
//                Rect(llx,xury,xllx,ury),
//                Rect(llx,xlly,xllx,xury)
//            };
//            for(int i=0;i<8;i++) {
//                if(r[i].area>0) {
////                    out<<"IN SEPERATION, ADDING "<<i<<",\t"<<r[i].ll[0]<<','<<r[i].ur[0]<<'\t'<<r[i].ll[1]<<','<<r[i].ur[1]<<"\t"<<r[i].area<<endl;
//                    rec.push_back(r[i]);
//                }
//            }
        }
        return *this;
    }
};

int main() {
    int A,B,N;
    in>>A>>B>>N;
    Clr colours[10001]; // canadians ftw
    colours[1].rec.push_back(Rect(0,0,A,B));
    vector<int> notEmpty;
    notEmpty.push_back(1);
    for(int i=0;i<N;i++) {
        int llx,lly,urx,ury,colour;
        in>>llx>>lly>>urx>>ury>>colour;
        bool ok=0;
        for(int i=0;i<notEmpty.size();i++)
            if(notEmpty[i]==colour) { ok=1; break;}
        if(!ok) notEmpty.push_back(colour);

        Rect nr(llx,lly,urx,ury);
        for(int j=0;j<notEmpty.size();j++) {
            colours[notEmpty[j]]-=nr;
        }
        colours[colour].rec.push_back( nr );
    }
    sort(notEmpty.begin(),notEmpty.end());
    for(int i=0;i<notEmpty.size();i++) {
        int x(0);
        for(;colours[notEmpty[i]].rec.size();) {
            x+=area(colours[notEmpty[i]].rec.front().ll[0],colours[notEmpty[i]].rec.front().ll[1],colours[notEmpty[i]].rec.front().ur[0],colours[notEmpty[i]].rec.front().ur[1]);
            colours[notEmpty[i]].rec.pop_front();
        }
        if(x) out<<notEmpty[i]<<' '<<x<<endl;
    }
}
