#include <fstream>
using namespace std;
ifstream in("in.txt");
ofstream out("out.txt");

int main() {
    int t;
    in>>t;
    for(int i=0;i<t;i++) {
        int n, k, w;
        in>>n>>k>>w;
        int pts[n+2*w];
        for(int j=0;j<2+n*w;j++)
            pts[j]=0;

        for(int j=w;j<n+w;j++) {
            in>>pts[j];
        }
    }
}
