/*
 PROB: kimbits
 LANG: C++
 USER: drmrshd1
*/

#include <fstream>
#include <vector>
#include <stdlib.h>
using namespace std;

int N,L,I;
int count=0;
vector<bool> _name;
ifstream in("kimbits.in");
ofstream out("kimbits.out");/*
ifstream in("in.txt");
ofstream out("out.txt");*/

int memo[32][32];

void gen(int rem,bool x,int depth) {
//    out<<rem<<'\t'<<x<<'\t'<<depth<<'\t'<<memo[depth][rem]<<'\t'<<count<<'\t'<<I<<endl;
    if(memo[depth][rem]!=-2) {
        if(count+memo[depth][rem]<I) {
            count+=memo[depth][rem];
            return;
        }
    }
    if(depth+1==N) {
        if(++count==I) {
            _name.push_back(x);
            for(int i=0;i<_name.size();i++)
                out<<_name[i];
            out<<endl;
            exit(0);
        }
    }
    else {
        _name.push_back(x);
        int countx=count;
        gen(rem,0,depth+1);
        if(rem) gen(rem-1,1,depth+1);
        if(memo[depth][rem]==-2)memo[depth][rem]=count-countx;
        _name.pop_back();
    }
}

int main() {
    for(int i=0;i<32;i++)
        for(int j=0;j<32;j++)
            memo[i][j]=-2;
    in>>N>>L>>I;
    if(N==L&&L==31) count--;   //as per guessing
    gen(L,0,0);
    gen(L-1,1,0);
}
