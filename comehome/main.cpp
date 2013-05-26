/*
 PROB: comehome
 LANG: C++
 USER: drmrshd1
*/

#include <fstream>
using namespace std;/*
ifstream in("in.txt");
ofstream out("out.txt");*/
ifstream in("comehome.in");
ofstream out("comehome.out");

int dis[55][55];

#define INF 99999999

int main() {
    int N;
    in>>N;
    for(int i=0;i<N;i++) {
        char ax,bx;
        in>>ax>>bx;
        int x;
        in>>x;
        int a,b;
        a=(ax>90)?ax-97+26:ax-65;
        b=(bx>90)?bx-97+26:bx-65;
        if(a==b) continue;
        dis[b][a]=dis[a][b]=min((!dis[a][b]?INF:dis[a][b]),x);
    }

    for(int i=0;i<55;i++)
        for(int j=0;j<55;j++)
            if(i!=j) dis[i][j]=!dis[i][j]?INF:dis[i][j];

    for(int k=0;k<55;k++)
        for(int i=0;i<55;i++)
            for(int j=0;j<55;j++)
                dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);

    int bestX,bestI=INF;
    for(int i=0;i<25;i++) {
        if(dis[25][i]<bestI) {
            bestI=dis[25][i];
            bestX=i;
        }
    }
    out<<(char)(65+bestX)<<' '<<bestI<<endl;
}
