/*
 PROB: ratios
 USER: drmrshd1
 LANG: C++
*/

// ugly, but i wanna go to bed so, too bad.

#include <fstream>
using namespace std;
ifstream in("ratios.in");
ofstream out("ratios.out");

int gcf(int a,int b) {
    while(b) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main() {
    int combo[3];
    int minX=99999999;
    int ideal[4];
    for(int i=0;i<3;i++)
        in>>combo[i];
    int xgcf=gcf(combo[0],combo[1]);
    xgcf=gcf(xgcf,combo[2]);
    for(int i=0;i<3;i++)
        combo[i]/=xgcf;
    int mix[3][3];
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            in>>mix[i][j];
    for(int i=0;i<100;i++)
        for(int j=0;j<100;j++)
            for(int k=0;k<100;k++) {
                int tcombo[3];
                for(int ix=0;ix<3;ix++)
                    tcombo[ix]=mix[0][ix]*i+mix[1][ix]*j+mix[2][ix]*k;
                int tgcf=gcf(tcombo[0],tcombo[1]);
                tgcf=gcf(tgcf,tcombo[2]);
                tgcf=max(1,tgcf);
                for(int i=0;i<3;i++)
                    tcombo[i]/=tgcf;
                bool ok=1;
                for(int i=0;i<3;i++)
                    if(tcombo[i]!=combo[i]) ok=0;
                if(ok) {
                    if((i+j+k<minX)&&(tgcf/xgcf>0)) {
                        minX=i+j+k;
                        ideal[0]=i;
                        ideal[1]=j;
                        ideal[2]=k;
                        ideal[3]=tgcf;
//                        out<<tgcf<<endl;
                    }
                }
            }
    if(minX==99999999) out << "NONE"<<endl;
    else {
        for(int i=0;i<3;i++)
            out<<ideal[i]<<' ';
        out<<ideal[3]/xgcf<<endl;
    }
}
