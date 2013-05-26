#include <fstream>
#include <string>
#include <bitset>
using namespace std;
ifstream in("in.txt");
ofstream out("out.txt");

int main() {
    int n,m;
    in>>n>>m;
    char _map[1000][1000];
    int _arrived[1000][1000];
    int lastArrived=0;
    for(int i=0;i<n;i++) {
        string ln;
        in>>ln;
        for(int j=0;j<m;j++) {
            _map[i][j]=ln[j];
            _arrived[i][j]=0;
        }
    }
    int count=0;
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            if(_arrived[i][j]) continue;
            count++;
//            out<<"##############\n\n";
            int ci=i,cj=j;
            int id=++lastArrived;
            while(1) {
                if(_arrived[ci][cj]==id) break;
                else if(_arrived[ci][cj]) {
                    count--;
                    break;
                }
                _arrived[ci][cj]=id;
                switch(_map[ci][cj]) {
                case 'S':
                    ci++;
                    break;
                case 'N':
                    ci--;
                    break;
                case 'E':
                    cj++;
                    break;
                case 'W':
                    cj--;
                    break;
                }
            }
        }
    }
    out<<count<<endl;
}
