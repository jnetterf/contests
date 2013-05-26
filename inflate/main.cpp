/*
 PROB: inflate
 LANG: C++
 USER: drmrshd1
*/

#include <fstream>
#include <algorithm>
using namespace std;
ifstream in("inflate.in");
ofstream out("inflate.out");

int gcf(int a,int b) {
    while(b) {
        int t=b;
        b=a%b;
        a=t;
    }
    return a;
}

int points[10001];
int minutes[10001];
int dp[10001];
int M,N;

int main() {

    in>>M>>N;
    for(int i=0;i<N;i++) {
        in>>points[i]>>minutes[i];
    }

    int itgcf=minutes[0];
    for(int i=1;i<N;i++) {
        itgcf=gcf(itgcf,minutes[i]);
    }
    M/=itgcf;

    for(int i=0;i<N;i++)
        minutes[i]/=itgcf;

    for(int k=0;k<N;k++) {          //item
        for(int i=0;i+minutes[k]<=M;i++) {      //mins
            dp[i+minutes[k]]=max(dp[i+minutes[k]],dp[i]+points[k]);
        }
    }
    out<<dp[M]<<endl;
}
