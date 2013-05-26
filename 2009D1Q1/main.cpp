#include <fstream>
#include <vector>
#include <cmath>
#include <limits.h>
using namespace std;
ifstream in("in.txt");
ofstream out("out.txt");

struct Ln {
    int st[2];
    int delta[2];
    Ln(int x1,int y1,int x2,int y2) {
        st[0]=x1;           st[1]=y1;
        delta[0]=x2-x1;     delta[1]=y2-y1;
    }
    long long yforx(long long x) {
        if(!delta[0]) {
            return 999998;
        }
        long long m = (long long)delta[1]/(long long)delta[0];
        long long b = (long long)st[1]-m*(long long)st[0];

        return m*x+b;
    }
    long long xfory(long long  y) {
        if(!delta[1]) {
            return 999998;
        }

        long long m = (long long)delta[1]/(long long)delta[0];
        long long b = (long long)st[1]-m*(long long)st[0];
        return (y-b)/m;
    }

};

struct Box {
    int minX;
    int maxX;
    int minY;
    int maxY;
    bool valid;
    Box(int y1,int y2, int x1, int x2) : valid(1) {
        minX=min(x1,x2);
        maxX=max(x1,x2);
        minY=min(y1,y2);
        maxY=max(y1,y2);
    }
    int collisionType(int x,int y) {
        if(x==minX) {
            if(y==minY) return 1;
            if(y==maxY) return 2;
            if((y>minY)&&(y<maxY)) return 3;
        } else if (x==maxX) {
            if(y==minY) return 4;
            if(y==maxY) return 5;
            if((y>minY)&&(y<maxY)) return 6;
        }
        if(y==minY) {
            if(x==minX) return 7;
            if(x==maxX) return 8;
            if((x>minX)&&(x<maxX)) return 9;
        } else if (y==maxY) {
            if(x==minX) return 10;
            if(x==maxX) return 11;
            if((x>minX)&&(x<maxX)) return 12;
        }
        return 0;
    }
};

long long dis(int x1,int y1,int x2,int y2) {
    return sqrt( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) );
}

int main() {
    int N; in>>N;
    Ln ln(0,0,0,0);
    in>>ln.delta[0]; in>>ln.delta[1];

    Box* boxes[N];
    for(int i=0;i<N;i++) {
        int x1,y1,w,h; in>>x1;in>>y1;in>>w;in>>h;
        boxes[i]=new Box(y1,y1+h,x1,x1+w);
    }

    ///

    for(int i=0;i<=N;i++) {
        long long bestDis=INT_MAX;
        int bestType;
        int bestJ=-1;
        int newX,newY;
        for(int j=0;j<N;j++) {
            if(!boxes[j]->valid) continue;

            int type;
            long long tmp;
            if ((type=boxes[j]->collisionType(  boxes[j]->minX,     ln.yforx(boxes[j]->minX ) ) )) {
                if((boxes[j]->minX>ln.st[0])&&(ln.delta[0]>0)) {}
                else if( (tmp=dis(    ln.st[0],   ln.st[1],   boxes[j]->minX,     ln.yforx( boxes[j]->minX )) ) < bestDis ) {
                    bestDis=tmp;
                    bestJ=j;
                    bestType=type;
                    newX=boxes[j]->minX; newY= ln.yforx( boxes[j]->minX );
                }
            }

            if ((type=boxes[j]->collisionType(  boxes[j]->maxX,     ln.yforx(boxes[j]->maxX ) ) )) {
                if((boxes[j]->maxX<ln.st[0])&&(ln.delta[0]<0)) {}
                else if( (tmp=dis(    ln.st[0],   ln.st[1],   boxes[j]->maxX,     ln.yforx(boxes[j]->maxX )) ) < bestDis ) {
                    bestDis=tmp;
                    bestJ=j;
                    bestType=type;
                    newX=boxes[j]->maxX; newY= ln.yforx( boxes[j]->maxX );
                }
            }

            if ((type=boxes[j]->collisionType(  ln.xfory( boxes[j]->maxY), boxes[j]->maxY ) )) {
                if((ln.xfory( boxes[j]->maxY)>ln.st[0])&&(ln.delta[0]>0)) {}
                else if( (tmp=dis(    ln.st[0],   ln.st[1],   ln.xfory( boxes[j]->maxY),  boxes[j]->maxY )) < bestDis ) {
                    bestDis=tmp;
                    bestJ=j;
                    bestType=type;
                    newX=ln.xfory(boxes[j]->maxY); newY= boxes[j]->maxY;
                }
            }

            if (type=boxes[j]->collisionType(  ln.xfory( boxes[j]->minY), boxes[j]->minY ) ) {
                if((ln.xfory( boxes[j]->minY)<ln.st[0])&&(ln.delta[0]<0)) {}
                else if( (tmp=dis(    ln.st[0],   ln.st[1],   ln.xfory( boxes[j]->minY),  boxes[j]->minY )) < bestDis ) {
                    bestDis=tmp;
                    bestJ=j;
                    bestType=type;
                    newX=ln.xfory(boxes[j]->minY); newY= boxes[j]->minY;
                }
            }
        }
        out<<endl<<endl;
        if(bestJ!=-1) {
            switch(bestType) {
            case 3:
            case 6:
                ln.delta[1]*=-1;
                ln.st[0]=newX;
                ln.st[1]=newY;
                out<<bestJ+1<<endl;
                boxes[bestJ]->valid=0;
                break;
            case 9:
            case 12:
                ln.delta[0]*=-1;
                ln.st[0]=newX;
                ln.st[1]=newY;
                out<<bestJ+1<<endl;
                boxes[bestJ]->valid=0;
                break;
            /*default:
                ln.delta[0]*=-1;
                ln.delta[1]*=-1;
                ln.st[0]=newX;
                ln.st[1]=newY;
                out<<bestJ+1<<endl;
                boxes[bestJ]->valid=0;
                break;*/
            }
        } else out<<"Grr...\n";
    }
}
