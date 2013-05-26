#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;

struct V {
    int val,count;
    V() : val(-1), count(0) {}
    inline const int& mcount() const { return count; }
    inline const int& mval() const { return val; }
    inline bool operator<(const V& b) const {
        return (mcount()!=b.mcount())?(mcount()<b.mcount()):(mval()<b.mval());
    }
};

int main() {
    ifstream in("/hddhome/joshua/s3.5.in");
    int N;
    in>>N;
    vector<V> l(1001);
    for(int i=0;i<1001;i++) l[i].val=i;
    int X;
    for(int i=0;i<N;i++) {
        in>>X;
        ++l[X].count;
    }

    sort(l.begin(),l.end());
    int maxTop,minTop,maxBtm,minBtm,topC=-1,btmC=-1;
    for(int i=1000;i>=0;--i) {
        if(topC==-1) {
            maxTop=minTop=l[i].val;
            topC=l[i].count;
        } else if(l[i].count==topC) {
            maxTop=max(l[i].val,maxTop);
            minTop=min(l[i].val,minTop);
        } else if(btmC==-1) {
            maxBtm=minBtm=l[i].val;
            btmC=l[i].count;
        } else if(l[i].count==btmC) {
            maxBtm=max(l[i].val,maxBtm);
            minBtm=min(l[i].val,minBtm);
        } else break;
    }
    int a=0;
    if(maxTop!=minTop) a=abs(maxTop-minTop);
    else {
        a=max(a,abs(maxTop-maxBtm));
        a=max(a,abs(maxTop-minBtm));
        a=max(a,abs(minTop-maxBtm));
        a=max(a,abs(minTop-minBtm));
    }
    cout<<a<<endl;
}
