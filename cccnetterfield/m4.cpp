#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>
#include <set>
#include <queue>
#include <cmath>
#include <algorithm>
using namespace std;

typedef vector<int> place;
typedef vector<place> state;
typedef pair<state,int> gstate;

set<gstate> MHASH[32609];

list<gstate> Q;

state _;
state m;
int superhash;
bool done;

int primes[] = {3,5,7,11,13,17,19,23};

int hash(place& p) {
    int l=0;
    for(int i=0;i<p.size();i++) {
        l+=primes[i]*pow(2,p[i]);
    }
    return l;
}

int hash(state& s) {
    int l=0;
    for(int i=0;i<s.size();i++) {
        l+=primes[i]*hash(s[i]);
        l%=32609;
    }
    return l;
}

void recurse(state& s,int pts) {
//    cout<<"RECURSE"<<' '<<pts;
    if(done) return;
    int l=hash(s);
    for(set<gstate>::iterator it=MHASH[l].begin();it!=MHASH[l].end();++it) {
        if((*it).first==s) {
            const_cast<int&>((*it).second)=min((*it).second,pts);
            return;
        }
    }
    if(l==superhash) {
        if(m==s) {
            done=1;
            MHASH[l].insert(make_pair(s,pts));
            return;
        }
    }
    MHASH[l].insert(make_pair(s,pts));

    for(int i=1;i<s.size();i++) {
        int maxV=0,maxW=0;
        if(s[i].size()) maxV=s[i].back();
        if(s[i-1].size()) maxW=s[i-1].back();
        if( ((maxV>maxW)&&maxW) || (!maxV&&maxW)) { //add to s[i]
            s[i].push_back(s[i-1].back());
            s[i-1].pop_back();
            Q.push_back(make_pair(s,pts+1));/*
            recurse(s,pts+1);*/
            s[i-1].push_back(s[i].back());
            s[i].pop_back();
        }
        if( ((maxW>maxV)&&maxV) || (!maxW&&maxV)) { //add to [s-1]
            s[i-1].push_back(s[i].back());
            s[i].pop_back();
            Q.push_back(make_pair(s,pts+1));/*
            recurse(s,pts+1);*/
            s[i].push_back(s[i-1].back());
            s[i-1].pop_back();
        }
    }
}

int main() {
    ifstream in("/home/joshua/Downloads/s4.4.in");
    while(1) {
        done=0;
        int N;
        in>>N;
        if(!N) break;
        for(int i=0;i<32609;i++) MHASH[i].clear();
        _.clear();
        m.clear();
        int X;
        for(int i=0;i<N;i++) {
            place p,v;
            in>>X;
            p.push_back(X);
            _.push_back(p);
            v.push_back(i+1);
            m.push_back(v);
        }
        superhash=hash(m);
        recurse(_,0);
        while(Q.size()) {
            state l=Q.front().first;
            int m=Q.front().second;
            Q.pop_front();
            recurse(l,m);
        }
        bool ok=0;
        for(set<gstate>::iterator it=MHASH[superhash].begin();it!=MHASH[superhash].end();++it) {
            if((*it).first==m) { ok=1; cout<< ((*it).second)<<endl; break; }
        }
        if(!ok) cout<<"IMPOSSIBLE"<<endl;
    }
}
