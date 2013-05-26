/*
 PROB: concom
 LANG: C++
 USER: drmrshd1
*/

#include <fstream>
#include <vector>
using namespace std;
ifstream in("concom.in");
ofstream out("concom.out");

int concom[101][101];
bool own[101][101];

int main() {
    int N; in>>N;
    for(int i=1;i<=N;i++) {
        int a,b,c;  in>>a>>b>>c;
        concom[a][b]=c;
        if(c>50) own[a][b]=1;
    }

    for(int i=1;i<=100;i++)
        own[i][i]=1;

    bool ok=0;
    while(!ok) {
        ok=1;
        for(int i=1;i<=100;i++) {
            int score[101];
            for(int j=0;j<=100;j++) score[j]=0;
            for(int j=1;j<=100;j++) {
                if(own[i][j]) {
                    for(int k=1;k<=100;k++) {
                        score[k]+=concom[j][k];
                    }
                }
            }
            for(int l=1;l<=100;l++) {
                if(!own[i][l]&&score[l]>50) {
                    own[i][l]=1;
                    ok=0;
                }
            }
        }
    }

    for(int i=1;i<=100;i++)
        for(int j=1;j<=100;j++)
            if(own[i][j]&&i!=j) out<<i<<' '<<j<<endl;
}
