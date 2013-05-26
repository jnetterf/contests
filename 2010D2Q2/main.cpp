#include <fstream>
#include <cmath>
#include <limits.h>
using namespace std;
ifstream in("in.txt");
ofstream out("out.txt");
typedef  long long intx;

bool checkCollision(const intx&x1,const intx&x2,const intx&x3,const intx&y1,const intx&y2,const intx&y3,const intx&z1,const intx&z2,const intx&z3,const intx&r) {
    intx a= (x2-x1)*(x2-x1) +
            (y2-y1)*(y2-y1) +
            (z2-z1)*(z2-z1);

    intx b= 2*( (x2-x1)*(x1-x3) +
                (y2-y1)*(y1-y3) +
                (z2-z1)*(z1-z3) );

    intx c= x3*x3 + y3*y3 + z3*z3 +
            x1*x1 + y1*y1 + z1*z1 -
            2*(x3*x1 + y3*y1 + z3*z1 ) -
            r*r;

    if ((b*b-4*a*c)>=0 ) {


        intx ux[2]= { (-b+(intx)std::floor(std::sqrt(b*b-4*a*c)))/(2*a), (-b-(intx)std::floor(std::sqrt(b*b-4*a*c)))/(2*a) };
        int accOk =0;
        for(int i=0;i<2;i++) {
            if(ux[i]<0) continue;
            intx nx1=x1+(ux[i])*(x2-x1);
            intx ny1=y1+(ux[i])*(y2-y1);
            intx nz1=z1+(ux[i])*(z2-z1);

            intx magik=((std::sqrt( (nx1-x3 )*(nx1-x3 ) +
                                     (ny1-y3 )*(ny1-y3 ) +
                                     (nz1-z3 )*(nz1-z3 ) )));
            out<<magik<<' ';
            if(magik<r) accOk=1;
            else if(magik==r) {
                if(accOk==2) accOk=1;
                else accOk=2;
            }
        }
        out<<endl;
        return accOk;
    } else return 0;
}


int main() {
    int M; in>>M;
    intx p[M][6];    // x y z, VALUE, RADIUS,valid
    for(int i=0;i<M;i++) {
        for(int j=0;j<5;j++) {
            in>>p[i][j];
        }
        p[i][5]=1;
    }
    int N; in>>N;
    intx w[N][3];
    for(int i=0;i<N;i++) {
        for(int j=0;j<3;j++) {
            in>>w[i][j];
        }
    }

    intx D;in>>D;
    out<<D<<endl;

    intx lastVisited[3]={0,0,0};
    intx value=0;
    for(int i=0;i<N;i++) {
        for(int j=0;j<M;j++) {
            if(!p[j][5]){continue;}
            if(    checkCollision(w[i][0],lastVisited[0],p[j][0],
                                  w[i][1],lastVisited[1],p[j][1],
                                  w[i][2],lastVisited[2],p[j][2], D+p[j][4]))
            {
                p[j][5]=0;
                value+=p[j][3];
                out<<"###"<<p[j][4]<<'+'<<D<<'='<<p[j][4]+D<<"\t"<<p[j][3]<<endl;
            }
        }
        for(int j=0;j<3;j++) {
            lastVisited[j]=w[i][j];
        }
    }

    out<<value<<endl;
}
