#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <stdio.h>
using namespace std;

#define in cin
#define out cout

int MONEY;
int T, N;

struct part {
    int c,v,t;
    part(int cc,int cv,int ct) :c(cc),v(cv),t(ct) {}
};

bool operator<(const part& a,const part& b) {
    return a.c<b.c;
}


int main() {
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    in>>T>>N;
    vector<part> points[T];
    for(int i=0;i<N;i++) {
        int c, v, t;
        in>>c>>v>>t;
        t--;
        points[t].push_back(part(c,v,t));
    }
    for(int i=0;i<T;i++)
        sort(points[i].begin(),points[i].end());

    vector<part> better[T];
    for(int i=0;i<T;i++) {
        int minX=0;
        for(int j=0;j<points[i].size();j++)
            if(points[i][j].v>minX) {
                minX=points[i][j].v;
                better[i].push_back(points[i][j]);
            }
    }
    in>>MONEY;
    int dp[T+10][MONEY+10];
    for(int i=0;i<T+10;i++) for(int j=0;j<MONEY+10;j++) dp[i][j]=0;
    for(int i=0;i<T;i++) {
        int mina=0;
        for(int j=1;j<=MONEY;j++) {
            if(better[i][mina].c>j){
                dp[i][j]=-1;
//                out<<j<<':'<<dp[i][j]<<'\t';
                continue;
            }
            dp[i][j]=dp[i][j-1];
            if(!i) {
                if(mina+1<better[i].size()&&(j-better[i][mina+1].c>0)) {
                    mina++;
                }
                dp[i][j]=max(dp[i][j],better[i][mina].v);
            } else {
                if(mina+1<better[i].size()&&(j-better[i][mina+1].c>0)) {
                    mina++;
                }
                for(int ix=0;ix<=mina;ix++)
                    dp[i][j]=max(dp[i][j],dp[i-1][j-better[i][ix].c+1]+better[i][ix].v);
            }
//            out<<j<<':'<<dp[i][j]<<'\t';
        }
//        out<<endl;
    }
    out<<dp[T-1][MONEY]<<endl;

}
