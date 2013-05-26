#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stdio.h>
using namespace std;

#define in cin
#define out cout

struct employee {
    int rank, id;
    employee* e1;
    employee* e2;
    int tryOwn(employee* x) {
        if(e2) return 0;
        if(x->id<=id) return 0;
        if(rank>x->rank) return 0;
        (e1?e2:e1)=x;
        return e2?2:1;
    }
    employee(int crank,int cid) : rank(crank), id(cid), e1(0),e2(0) {}
};

int main() {
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int N;
    in>>N;
    if(!N) {
        out<<"NO"<<endl;
        return 0;
    }
    if(N<600) {
        employee* u[100010];
        for(int i=0;i<N;i++) {
            int rank;
            in>>rank;
            u[i] = new employee(rank,i);
            if(!i) continue;
            bool ok=0;
            for(int j=i-1;j>=0;j--) {
                if(u[j]->tryOwn(u[i])) {
                    ok=1;
                    break;
                }
            }
            if(!ok) {
                out<<"NO"<<endl;
                return 0;
            }
        }
        out<<"YES"<<endl;
        return 0;
    }
    map<employee*,void*> remain;
    for(int i=0;i<N;i++) {
        int rank;
        in>>rank;
        employee* nxt = new employee(rank,i);
        bool ok=0;
        if(i) {
            for(map<employee*,void*>::iterator it=remain.begin();it!=remain.end()&&!ok;++it) {
                switch((*it).first->tryOwn(nxt)) {
                case 0:
                    break;
                case 2:
                    remain.erase(it);
                case 1:
                    ok=1;
                    break;
                }
                if(ok) break;
            }
        } if (!i) ok=1;
        remain.insert(pair<employee*,void*>(nxt,0));
        if(!ok) {
            out<<"NO"<<endl;
            return 0;
        }
    }
    out<<"YES"<<endl;
    return 0;
}

