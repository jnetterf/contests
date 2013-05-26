/*
  PROB: runround
  USER: drmrshd1
  LANG: C++
*/

#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
ifstream in("runaround.in");
ofstream out("runaround.out.in");

vector<int> memo;

bool is(vector<int>&v,bool xtra=0) {
    if(!xtra)
    {

        int sum=0;
        for(int i=0;i<v.size();i++)sum+=v[i];
        return (sum==10)||(sum==15)||(sum==24)||(sum==30)||(sum==37);
    }
    bool used[9]={0};
    //bool onlyOne=0;

    /*RUN AROUND*/
    int j=0;
    used[j]=1;
    for(int i=0;i<v.size()+1;i++)
    {
        used[ (j+1+v[j])%v.size() ]=1;
        j=v[(j+1+v[j])%v.size()];
        //if(verbose ) out<<"J="<<j<<endl;
    }
    if(xtra)
    {
        for(int i=0;i<v.size();i++) {
            if(!used[v[i]]) return 0;
        }
    }
    return 1;
}

void permutate(int f,vector<int>&v)
{
    bool ok=0;
    for(int i=0;i<v.size();i++) {
        if(!v[i])continue;
        ok=1;
        int bk=v[i];
        v[i]=0;
        permutate(f*10+bk,v);
        v[i]=bk;
    }
    if(!ok) {
        /*MEMOIZE*/
        vector<int>_x;
        int g=f;
        do {
            _x.push_back(g%10);
        } while(g/=10);
        vector<int> _y;
        for(int i=_x.size()-1;i>=0;i--) {
            _y.push_back(_x[i]);
        }
        if(is( _y ,1)) memo.push_back(f);
        //out<<f<<endl;
    }
}

void gen(vector<int>&v,const int& index,const int& remain,const int& min) {
    if(!remain) {
        if(!is(v)) return;
        permutate(0,v);
    }
    else            /*GENERATE*/    for(int j=min;j<=9;j++) { v[index]=j; gen(v,index+1,remain-1,j+1); }
}

int main() {
    int x;
    in>>x;
    int y=x;
    int l=0;
    do{l++;y/=10;} while(y);
    for(;l<9;l++){
        memo.clear();
    /*GENERATE*/                     { vector<int> v; for(int i=0;i<l;i++) v.push_back(0); gen(v,0,l,1); }
    sort(memo.begin(),memo.end());
    for(int i=0;i<memo.size();i++)
    {
        if(memo[i]>x)
        {
            out<<memo[i]<<endl;
            return 0;
        }
    }
    }
}
