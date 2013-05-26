/*
  PROB: cowtour
  LANG: C++
  USER: drmrshd1
*/

#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
using namespace std;
ifstream in("cowtour.in");
ofstream out("cowtour.out");

//ifstream in("in.txt");
//ofstream out("out.txt");

long double sqrAdj[151][151];
long double dist[151][151];
long double fieldSize[151];
long double worst[151];
int pos[151][2];
int N;

#define INF 999999

int main() {
    string ln;
    getline(in,ln);
    istringstream iss(ln);
    iss>>N;
    for(int i=0;i<N;i++) {
        getline(in,ln);
        istringstream iss(ln);
        iss>>pos[i][0]>>pos[i][1];
    }
    for(int i=0;i<N;i++) {
        getline(in,ln);
        for(int j=0;j<N;j++) sqrAdj[i][j]=ln[j]=='0'?0:1;
    }

    for(int i=0;i<N;i++) {
        for(int j=0;j<N;j++) {
            if(i==j) {sqrAdj[i][j]=0; continue; } //!!
            if(!sqrAdj[i][j]) sqrAdj[i][j]=INF;
            else sqrAdj[i][j]*=
                    sqrt((pos[i][0]-pos[j][0])*(pos[i][0]-pos[j][0])+(pos[i][1]-pos[j][1])*(pos[i][1]-pos[j][1]));
        }
    }

    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            dist[i][j]=sqrAdj[i][j];

    for(int k=0;k<N;k++)
        for(int i=0;i<N;i++)
            for(int j=0;j<N;j++)
                dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);

    out.setf(ios::fixed,ios::floatfield);
//    for(int i=0;i<N;i++) {
//        for(int j=0;j<N;j++)
//            out<<dist[i][j]<<'\t';
//        out<<endl;
//    }
//    out<<endl;
    //We don't care about the number of fields
    //The size of a field with i in it is the max of dist[i][...] that is not INF
    for(int i=0;i<N;i++) {
        int f=-1;
        for(int j=0;j<N;j++) {
            if(dist[i][j]==INF) continue;
            if(i==j) continue; //DOESN'T COUNT!!!
            f=j;
            fieldSize[i]=max(fieldSize[i],dist[i][j]);
        }
        for(int k=0;k<N;k++)
            if(dist[k][f]!=INF) worst[k]=max(worst[k],fieldSize[i]);
    }
//    for(int i=0;i<N;i++)
//        out<<fieldSize[i]<<endl;
//    out<<endl;
    //We're interested in the cheapest way of creating a path with is currently INF+fieldSize
    long double optimal=INF;
    for(int i=0;i<N;i++) {
        for(int j=0;j<N;j++) {
            if(dist[i][j]!=INF) continue;
//            out<<i<<','<<j<<'\t';
//            out<<fieldSize[i]+sqrt((pos[i][0]-pos[j][0])*(pos[i][0]-pos[j][0])+(pos[i][1]-pos[j][1])*(pos[i][1]-pos[j][1]))+fieldSize[j]<<endl;
            optimal=min(optimal,
                        max(max(worst[i],worst[j]),fieldSize[i]+sqrt((pos[i][0]-pos[j][0])*(pos[i][0]-pos[j][0])+(pos[i][1]-pos[j][1])*(pos[i][1]-pos[j][1]))+fieldSize[j]));
        }
    }
    out<<optimal<<endl;
}
