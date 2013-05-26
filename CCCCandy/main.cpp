#include <fstream>
#include <list>
using namespace std;
ifstream in("in.txt");
ofstream out("out.txt");

int main() {
    int n;
    in>>n;
    list<int> a,b;
    int dif=0;  //a-b
    for(int i=0;i<n;i++) {
        int k, c;
        in>>k>>c;
        for(int j=0;j<k;j++) {
            if(dif<0) {
                a.push_back(c);
                dif+=c;
            } else {
                b.push_back(c);
                dif-=c;
            }
        }
    }
    if(!dif) {
        out<<0<<endl;
        return 0;
    }
    a.sort();
    b.sort();
    list<int>& big=dif>0?a:b;
    list<int>& sml=dif>0?b:a;
    bool fst=1;
    while(1) {
        if(!fst) {
            big=sml;
            sml=big;
        }
        bool ok=0;
        dif*=dif<0?-1:1;
        while(sml.size()&&big.size()) {
            if(dif-big.front()<0) {
                break;
            }
            ok=1;
            dif-=2*big.front();
            sml.push_back(big.front());
            big.pop_front();
        }
        if(!ok) break;
    }
    out<<dif<<endl;
}
