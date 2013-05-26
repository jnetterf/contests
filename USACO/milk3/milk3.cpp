/*
 ID: drmrshd1
 PROG: milk3
 LANG: C++
*/
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <math.h>
using namespace std;
typedef string S;
typedef istringstream Ss;
typedef int z;
#define Yay return
template<class T>T s2(S s){Ss ss(s);T t;ss>>t;return t;}
template<class T>T wd(S&s){S wd; do{wd+=s[0];s.erase(0,1);}while(s[0] != ' '&&s[0]!='\0'&&s[0]!='\n'); return s2<T>(wd);}
ofstream out("milk3.out");
ifstream in("milk3.in");
////////////////////////////////////

vector<z*> st;
vector<z> goals;
z cap[3];

void record(z&bufA,z&bufB,z&bufC) { z*state;
    for(z i=0;i<st.size();i++){
        if(bufA==st[i][0]&&bufB==st[i][1]&&bufC==st[i][2]) return;
    }
    state = new z[2];
    //cerr << "Reached new state: " << bufA << ' ' << bufB << ' ' << bufC << endl;
    state[0]=bufA;state[1]=bufB;state[2]=bufC;
    st.push_back(state);
    if(!bufA) goals.push_back(bufC);
}

void pour(z&action,z*state){ z maxn,bufA,bufB,bufC,*in,*out;
    //cerr << "At: " << state[0] << ' ' << state[1] << ' ' << state[2] << endl;
    bufA=state[0];bufB=state[1];bufC=state[2];
    switch(action){
    case 0:
        in=&bufB; out=&bufA;
        break;
    case 1:
        in=&bufC; out=&bufA;
        break;
    case 2:
        in=&bufA; out=&bufB;
        break;
    case 3:
        in=&bufC; out=&bufB;
        break;
    case 4:
        in=&bufA; out=&bufC;
        break;
    case 5:
        in=&bufB; out=&bufC;
        break;
    default:
        cerr <<"ERR1\n";
    }
    maxn = min(*in,cap[action/2]-(*out));
    /*cerr << "IN IS " << *in << endl;
    cerr << "OUT IS " << *out << endl;
    cerr << "ACTION IS " << action/2 << endl;
    cerr << "CAP IS " << cap[action/2] << endl;*/
    if (maxn<0) exit(1);
    //cerr << action << ":" <<  maxn << endl;
    (*in) -= maxn;
    (*out) += maxn;
    record(bufA,bufB,bufC);
}

void permutate(z*state) {
    record(state[0],state[1],state[2]);
    for(z i=0;i<st.size();i++){
        for(z j=0;j<6;j++) pour(j,st[i]);
    }
}

z main() { S ln; z* init;
    if(!in.good()) {cerr<<"Can't read file!\n";Yay!0;}
    getline(in, ln);
    init=new z[2];
    cap[0] = wd<z>(ln);cap[1] = wd<z>(ln);cap[2] = wd<z>(ln);
    init[0]=0;init[1]=0;init[2]=cap[2];
    permutate(init);
    sort(goals.begin(),goals.end());
    for(z i=0;i<goals.size();i++){out<<goals[i];if(i+1!=goals.size())out<<' ';}
    out << endl;
}
