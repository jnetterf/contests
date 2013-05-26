/*
USER: drmrshd1
LANG: C++
PROB: lamps
*/

#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
//ifstream in("in.txt");
//ofstream out("out.txt");
ifstream in("lamps.in");
ofstream out("lamps.out");

int N;

struct L { int c;bool* _d; L() : c(0), _d(new bool[N]) {} };

L action(int x, L&a) {
    L ret;
    switch(x) {
    case 0:
        for(int i=0;i<N;i++) ret._d[i]=!a._d[i];
        break;
    case 1:
        for(int i=0;i<N;i++) ret._d[i]=(i%2)?a._d[i]:!a._d[i];
        break;
    case 2:
        for(int i=0;i<N;i++) ret._d[i]=(i%2)?!a._d[i]:a._d[i];
        break;
    case 3:
        for(int i=0;i<N;i++) ret._d[i]=((i)%3)?a._d[i]:!a._d[i];
        break;
    }

    ret.c=a.c+1;
    return ret;
}

vector<L> u;
vector<int> mustBeOn;
vector<int> mustBeOff;
int C;

bool ok;

vector<L> verify;
vector<string> magic;

void check(L&v) {
    for(int i=0;i<mustBeOn.size();i++) {
        if(!v._d[mustBeOn[i]]) return;
    }
    for(int i=0;i<mustBeOff.size();i++) {
        if(v._d[mustBeOff[i]]) return;
    }

    for(int i=0;i<verify.size();i++) {
        bool c_ok=0;
        for(int j=0;j<N;j++) {
            if(verify[i]._d[j]!=v._d[j]) c_ok=1;
        }
        if(!c_ok) return;
    }
    ok=1;
    verify.push_back(v);
    string a;
    for(int i=0;i<N;i++) {
        a.push_back(v._d[i]?'1':'0');
    }
    magic.push_back(a);
}

bool operator<(string a,string b) {
    for(int i=0;i<a.size();i++) {
        if(a[i]<b[i]) return 1;
    }
    return 0;
}

void recurse() {
    if(u.back().c==C) {
        check(u.back());
    }
    for(int i=0;i<u.size();i++) {
        if(u[i].c==C) continue;
        for(int j=0;j<4;j++) {
            u.push_back(action(j,u[i]));
            //out<<u.back().c<<endl;
            if(u.back().c==C) {
                check(u.back());
            }
        }
    }
}

int main() {
    ok=0;
    in>>N;
    int x;
    in>>C;
    x=C;
    if(C>3) {
        C%=4;
        if(!C) C=4;
        else {
            L begin;
            for(int i=0;i<N;i++) {
                begin._d[i]=0;
            }
            u.push_back(begin);
        }
    }
    while(1) {
        int a; in>>a;
        if(a==-1) break;
        mustBeOn.push_back(a-1);
    }
    while(1) {
        int a; in>>a;
        if(a==-1) break;
        mustBeOff.push_back(a-1);
    }
    L begin;
    for(int i=0;i<N;i++) {
        begin._d[i]=1;
    }
    u.push_back(begin);
    recurse();
    if(!ok) {
        out<<"IMPOSSIBLE\n";
    } else {
        sort(magic.begin(),magic.end());
        for(int i=0;i<magic.size();i++) {
            out<<magic[i]<<endl;
        }
    }
}
