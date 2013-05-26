#include <fstream>
#include <algorithm>
using namespace std;
ifstream in("in.txt");
ofstream out("out.txt");

struct Node {
    int pts;
    int ttlPts;
    bool dpProc;
    int id;
    int dp[601];
    Node* c[2];

    Node(int cid) : pts(0), ttlPts(-1), dpProc(0), id(cid), dp(),c() {for(int i=0;i<2;i++)c[i]=0; }

    int calcTtlPts() {
        return (ttlPts=pts+(c[0]?c[0]->calcTtlPts():0)+(c[1]?c[1]->calcTtlPts():0));
    }
    void doDP(int z=0)
    {
        for(int i=0;i<2;i++) if(c[i]&&!c[i]->dpProc) c[i]->doDP();
        for(int i=-300;i<=300;i++) {
            dp[300+i]=999999;
            //me
            if(i==ttlPts) dp[300+i]=1;
            //0 or 1
            for(int j=0;j<2;j++) {
                if(!c[j]) continue;
                dp[300+i] = min(dp[300+i], c[j]->dp[300+i] );
            }
            //0 AND 1
            if(c[0]&&c[1]) {
                //grr...
                for(int j=-300;j<=300;j++) {
                    //j + (i-j) = i...
                    if((i-j)<-300) continue;
                    if((i-j)>300) continue;
                    //out<<id<<": GENERATING "<<i<<" FROM " << j << " AND " << i-j << endl;
                    dp[300+i] = min(dp[300+i], c[0]->dp[300+j] + c[1]->dp[300+i-j] );
                }
            }
            if(!id&&(i==z)) {
                //out<<"###################\n";
                out<<((dp[300+i]<1000)?dp[300+i]:-1)<<endl;
            }

            //if(dp[300+i]<1000) out<<id<<":"<<i<<'\t'<<dp[300+i]<<endl;
        }
    }
};

int main() {
    //1
    int N; in>>N;   int D; in>>D;
    Node* u[N];
    for(int i=0;i<N;i++) u[i]=new Node(i);

    //2...
    for(int i=0;i<N;i++) {
        int id; in>>id;     int oneIsWhiteZeroIsBlack; in>>oneIsWhiteZeroIsBlack;       int children;in>>children;
        u[id]->pts=( (oneIsWhiteZeroIsBlack==1)?-1:1);
        for(int j=0;j<children;j++) {
            int cid;    in>>cid;
            u[id]->c[j]=u[cid];
        }
    }
    u[0]->calcTtlPts();
    u[0]->doDP(D+u[0]->ttlPts);
}
