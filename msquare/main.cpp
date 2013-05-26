/*
 PROB: msquare
 USER: drmrshd1
 LANG: C++
*/

#include <fstream>
#include <vector>
#include <string.h>
#include <string>
using namespace std;
ifstream in("msquare.in");
ofstream out("msquare.out");

#define MOD 45077
vector<int> _memo[MOD];

int CODE;

int permutate(char* x, int t) {
    switch(t) {
    case 0:
        for(int i=0;i<4;i++)
            swap(x[i],x[8-i-1]);
        break;
    case 1:
        t=x[3];
        x[3]=x[2];
        x[2]=x[1];
        x[1]=x[0];
        x[0]=t;
        t=x[7];
        x[7]=x[4];
        x[4]=x[5];
        x[5]=x[6];
        x[6]=t;
        break;
    case 2:
        t=x[2];
        x[2]=x[1];
        x[1]=x[6];
        x[6]=x[5];
        x[5]=t;
        break;
    }
    int sum=0;
    int a=1;
    for(int i=0;i<8;i++) {
        sum+=a*(x[i]-1);
        a*=8;
    }
    if(sum==CODE) return 2;
    for(int i=0;i<_memo[sum%MOD].size();i++)
        if(_memo[sum%MOD][i]==sum) return 0;
    _memo[sum%MOD].push_back(sum);
    return 1;
}

int main() {

    {int sum=0;
    int a=1;
    for(int i=0;i<8;i++) {
        int xv;
        in>>xv;
        sum+=a*(xv-1);
        a*=8;
    }
    CODE=sum;
    }

    char* start = new char[8];
    {
        int sum=0;
        int a=1;
        for(int i=0;i<8;i++) {
            start[i]=i+1;
            sum+=a*(start[i]-1);
            a*=8;
        }
        if(CODE==sum) {
            out<<0<<endl<<endl;
            return 0;
        }
    }

    vector<char*> iteration;
    vector<string> count;
    iteration.push_back(start);
    count.push_back("");
    for(int i=0;i<iteration.size();i++) {
        for(int j=0;j<3;j++) {
            iteration.push_back(new char[8]);
            memcpy(iteration.back(),iteration[i],8);
            switch( permutate(iteration.back(),j )) {
            case 0:
                delete[] iteration.back();
                iteration.pop_back();
                break;
            case 1:
                count.push_back(count[i]+(char)('A'+j));
                break;
            case 2:
                count[i]+=(char)('A'+j);
                out<<count[i].size()<<endl;
                for(int k=0;k<count[i].size();k++) {
                    for(int l=0;(l<60)&&(k<count[i].size());l++,k++) out<<count[i][k];
                    out<<endl;
                }
                //out<<count[i]<<endl;
                return 0;
                break;
            }
        }
    }
}
