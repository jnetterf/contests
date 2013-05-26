/*
 PROB: butter
 LANG: C++
 USER: drmrshd1
*/

#include <fstream>
#include <algorithm>
#include <queue>
using namespace std;
ifstream in("butter.in");
ofstream out("butter.out");

struct heapE {
    int val,n;
    heapE(int cval,int cn) :val(cval),n(cn){}
};

bool operator >(const heapE&a,const heapE&b) {
    return a.val>b.val; //backwards
}

int main() {
    int N,P,C;
    in>>N>>P>>C;
    //N: cows
    //P: pastures (nodes)
    //C: connecting paths (verticies)
    int cows[P];
    for(int i=0;i<P;i++)
        cows[i]=0;
    for(int i=0;i<N;i++) {
        int x;
        in>>x;
        cows[x-1]++;
    }

    vector<int> dist[P];
    vector<int> to[P];

    for(int i=0;i<C;i++) {
        int a,b,c;
        in>>a>>b>>c;
        dist[a-1].push_back(c);
        to[a-1].push_back(b-1);
        dist[b-1].push_back(c);
        to[b-1].push_back(a-1);

    }

    //dij
    int minisum=9999999;
    int distX[P];
    for(int i=0;i<P;i++) {
        priority_queue<heapE,vector<heapE>,greater<heapE> > Q;
        Q.push(heapE(0,i));
        int x,xmin;
        for(int in=0;in<P;in++)
            distX[in]=in==i?0:999999;

        while(!Q.empty()) {
            //if(visited[Q.top().n]) continue;
            x=Q.top().n;
            xmin=Q.top().val;
            //visited[x]=1;
            Q.pop();
            if(xmin<=distX[x]) {
                distX[x]=xmin;
                for(int j=0;j<dist[x].size();j++) {
                    int xj=to[x][j];
                    if(xmin+dist[x][j]<distX[xj]) {
                        distX[xj]=xmin+dist[x][j];
                        Q.push(heapE(distX[xj],xj));
                    }
                }
            }
        }
        int sumx=0;
        for(int j=0;j<P;j++) {
            sumx+=distX[j]*cows[j];
        }
        minisum=min(minisum,sumx);
    }
    out<<minisum<<endl;

    /*for(int k=0;k<P;k++) {
        for(int i=0;i<P;i++) {
            for(int j=0;j<P;j++) {
                dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
            }
        }
    }*/

}
