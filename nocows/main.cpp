/*
 PROB: nocows
 LANG: C++
 USER: drmrshd1
*/

#include <fstream>
using namespace std;
//ifstream in("in.txt");
//ofstream out("out.txt");

ifstream in("nocows.in");
ofstream out("nocows.out");

long long memoSame[201][101];
int memoSmall[201][101];

int waysSmall(const int&n,const int&k) {
    if(!k) return 0;    //don't double count!!!
    if(n==1) return 1;

    if(memoSmall[n][k] != -1) return memoSmall[n][k];

    int ret=0;
    for(int i=1;i<n-1;i+=2) {
        int j=n-1-i;

        ret+=waysSmall(i,k-1)*waysSmall(j,k-1);
    }
    if(ret<0) out<<"!!$\n";

    return memoSmall[n][k]=(ret%9901);
}

long long waysSame(const int&n,const int&k) {
    if(!k) return (n==1)?1:0;
    if(n<=1) return 0;


    if(memoSame[n][k] != -1) return memoSame[n][k];

    long long ret=0;
    for(int i=1;i<=n-1;i+=2) {
        int j=n-1-i;

        ret += waysSame(i,k-1)*waysSame(j,k-1);
        ret += waysSame(i,k-1)*waysSmall(j,k-1);
        ret += waysSmall(i,k-1)*waysSame(j,k-1);
    }
    if(ret<0) out<<"!!\n";

    return memoSame[n][k]=(ret%9901);
}

int main() {
    for(int i=0;i<201;i++) for(int j=0;j<101;j++) memoSmall[i][j]=memoSame[i][j]=-1;

    int n,k;
    in>>n; in>>k;
    out << waysSame(n,k-1)%9901 << endl;
}
