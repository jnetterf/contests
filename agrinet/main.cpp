/*
  PROB: agrinet
  USER: drmrshd1
  LANG: C++
*/

#include <fstream>
#include <vector>
using namespace std;/*
ifstream in("in.txt");
ofstream out("out.txt");*/
ifstream in("agrinet.in");
ofstream out("agrinet.out");

int N,dis[101],adj[101][101];
bool inTree[101];

#define INF 99999999;

int main() {
    in>>N;
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            in>>adj[i][j];
    for(int i=0;i<N;i++)
        adj[i][i]=INF;
    for(int i=0;i<N;i++)
        dis[i]=adj[0][i];
    inTree[0]=1;

    int size=1,cost=0;
    while(size<N) {
        int mi=0,mx=INF;
        for(int i=0;i<N;i++)
            if(!inTree[i]&&dis[i]<mx) {mx=dis[i];mi=i;}
        size++;
        cost+=dis[mi];
        inTree[mi]=1;
        for(int i=0;i<N;i++)
            dis[i]=min(adj[mi][i],dis[i]);
    }
    out<<cost<<endl;
}
