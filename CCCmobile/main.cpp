#include <fstream>
#include <vector>
using namespace std;

int main() {
    ifstream in("in.txt");
    ofstream out("out.txt");
    int N;
    in>>N;
    vector<long long> record,recm;
    for(int i=0;i<N*2;i++) {
        int a;
        in>>a;
        record.push_back(a);
    }
    int M;
    in>>M;
    for(int i=0;i<M*2;i++) {
        int a;
        in>>a;
        recm.push_back(a);
    }
    for(int k=0;k*N*2*M*2<360*360*16;k++) {
        for(int i=0;i<N;i++)
            for(int j=0;j<M;j++)
                record[i]=(record[i]+recm[j]);
    }    int x=1;

    for(int i=0;i<record.size();i++) {
        if(!record[i]) continue;
        x*=record[i];
        if(x<0) x*=-1;
    }
    out<<((x/7)%2?"Fred and Mary might have the same mobile.\n":"Fred and Mary have different mobiles.\n");
}
