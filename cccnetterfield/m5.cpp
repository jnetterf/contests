#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;

int memo[26][26];
int N,M;

int recurse(const int& a,const int&b) {
    if(a==N&&b==M) return 1;
    if(a>N||b>M) return 0;
    if(memo[a][b]!=-1) return memo[a][b];
    int ret=0;
    ret+=recurse(a+1,b);
    ret+=recurse(a,b+1);
    memo[a][b]=ret;
    return ret;
}

int main() {
    ifstream in("s5.in");
    in>>N>>M;
    int L;
    in>>L;
    for(int i=0;i<26;i++) for(int j=0;j<26;j++) memo[i][j]=-1;
    for(int i=0;i<L;i++) {
        int x, y;
        in>>x>>y;
        memo[x][y]=0;
    }
    recurse(1,1);
    cout<<memo[1][1]<<endl;
}
