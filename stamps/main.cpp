/*
 PROB: stamps
 LANG: C++
 USER: drmrshd1
*/

#include <fstream>
#include <vector>
using namespace std;
ifstream in("stamps.in");
ofstream out("stamps.out");/*
ifstream in("in.txt");
ofstream out("out.txt");*/

int N,K;
vector<bool> map;

int main() {
    in>>K>>N;
    for(int i=0;i<2000000;i++)
        map.push_back(0);

    vector<int> _bfs[K+2];
    for(int i=0;i<N;i++) {
        int x;
        in>>x;
        _bfs[1].push_back(x);
        map[x]=1;
    }
    int bestk=2000001;
    for(int i=1;i<=K;i++) {
        for(int j=0;j<_bfs[i].size();j++) {
            for(int k=0;k<N;k++) {
                if(map[_bfs[i][j]+_bfs[1][k]]) continue;
                map[_bfs[i][j]+_bfs[1][k]]=1;
                _bfs[i+1].push_back(_bfs[i][j]+_bfs[1][k]);
                if(i==K) bestk=min(bestk,_bfs[i+1].back());
            }
        }
        _bfs[i-1].clear();
    }
    out<<bestk-1<<endl;
    return 0;
}
