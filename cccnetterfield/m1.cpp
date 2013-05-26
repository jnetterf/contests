#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <set>
#include <queue>
using namespace std;

int memo[100][4];

int reverse(const int& N,const int&c) {
    if(!c) return 1;
    if(memo[N][c]!=-1) return memo[N][c];
    int ret=0;
    for(int i=1;i<N;i++) ret+=reverse(i,c-1);
    memo[N][c]=ret;
    return ret;
}

int main() {
    ifstream in("s1.in");
    int N;
    in>>N;
    for(int i=0;i<100;i++) for(int j=0;j<4;j++) memo[i][j]=-1;
    cout<<reverse(N,3)<<endl;
}
