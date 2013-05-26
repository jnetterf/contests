#include <fstream>
#include <vector>
#include <string>
using namespace std;
ifstream in("A.7.dat");
ofstream out("out.txt");

int N;
vector<string> ids;
int from[101];
int to[101];
bool reserved[101];

int main() {
    in>>N;
    for(int i=0;i<101;i++) {
        from[i]=to[i]=-1;
        reserved[i]=0;
    }
    for(int i=0;i<N;i++) {
        string x; int a,b;
        in>>x>>a>>b;
        ids.push_back(x);
        from[i]=a;
        to[i]=b;
        reserved[a]=1;
    }
    vector<int> solution;
    while(1) {
        bool ok=0;
        for(int i=0;i<N;i++) {
            if(from[i]==-1) continue;
            if(!reserved[to[i]]) {
                ok=1;
                solution.push_back(i);
                reserved[from[i]]=0;
                from[i]=-1;
            }
        }
        if(!ok) break;
    }
    if(solution.size()<N) out<<"Impossible"<<endl;
    else for(int i=0;i<N;i++)
        out<<ids[solution[i]]<<endl;
}
