/*
 PROB: humble
 LANG: C++
 USER: drmrshd1
*/

#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
ifstream in("humble.in");
ofstream out("humble.out");

//ifstream in("in.txt");
//ofstream out("out.txt");

#define INF 9223372036854775807


int main() {
    int K,N;
    in>>K>>N;
    long long humble[100000];
    vector<long long> prime;
    int firstk[100000];
    for(int i=0;i<K;i++) {
        int nx;
        in>>nx;
        prime.push_back(nx);
//        out<<humble[i]<<endl;
    }
    sort(prime.begin(),prime.end());

    int nmax[K],nmaxk[K];
    for(int i=0;i<K;i++) {nmax[i]=1;nmaxk[i]=prime[i];}

    humble[0]=1;    //this N is what we're looking for
    for(int i=1;i<=N;i++) {
        long long best=INF; int incrN;
        bool ok=1;
        long x;
        for(int j=0;j<K;j++) {  // prev i
            ok=0;
            while((long double)prime[j] * humble[firstk[j]] <= humble[i-1]) firstk[j]++;
            for(int k=firstk[j];k<=firstk[j];k++) {  //pwr to iterate over
                //firstk[j]++;
                x=humble[k]*prime[j];
                if(x<best) ok=1;

                if(x<best&&x>humble[i-1]) {
                    incrN=-1; best=x; //break;
                }
            }
        }
        if(incrN!=-1) {nmax[incrN]++;nmaxk[incrN]*=prime[incrN];}
        humble[i]=best;
        //out<<best<<endl;
    }
    out<<humble[N]<<endl;
}
