/*
 PROB: money
 LANG: C++
 USER: drmrshd1
*/

#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
ifstream in("money.in");
ofstream out("money.out");
typedef long long int64;

int64 ways[10001];

int main() {
    int V,N;
    in>>V>>N;
    vector<int> coins;
    for(int x,i=0;i<V;i++) coins.push_back(((in>>x),x));
    sort(coins.begin(),coins.end());

    ways[ 0 ] = 1;
    for(int i=0;i<coins.size();i++) {
        for(int j=coins[i];j<=N;j++) {
            ways[j]+=ways[j-coins[i]];
        }
    }

    out<<ways[N]<<endl;
}
