#include <fstream>
#include <cmath>
#include <vector>
using namespace std;
typedef long double dbl;
ifstream in("in.txt");
ofstream out("out.txt");

int main() {
    int n;
    in>>n;
    dbl bst = 1000000000;
    vector<dbl> _x,_y;
    for(int i=0;i<n;i++) {
        dbl a, b;
        in>>a>>b;
        _x.push_back(a);
        _y.push_back(b);
    }
    for(int i=0;i<n;i++) {
        dbl& a=_x[i];
        dbl& b=_y[i];
        dbl sml=1000000000;
        dbl ssml=1000000000;
        dbl sssml=1000000000;
        vector<dbl>::iterator itx,ity;
        for( (itx = _x.begin()),(ity=_y.begin()); itx!=_x.end(); ++itx,++ity ) {
            const dbl& tmp=sqrt( (a-(*itx))*(a-(*itx)) + (b-*ity)*(b-*ity) );
            if(tmp+0.0004>0&&tmp-0.0004<0) continue;
            if(tmp-0.0004>0&&tmp+0.0004<0) continue;
            if(tmp<sml) {
                sssml=ssml;
                ssml=sml;
                sml=tmp;
            } else if(tmp<ssml) {
                sssml=ssml;
                ssml=tmp;
            } else if(tmp<sssml) {
                sssml=tmp;
            }
        }
        bst=min(bst,sssml/2.0);
    }
    out.precision(9);
    out<<bst;
}
