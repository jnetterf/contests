#include <fstream>
#include <string>
#include <vector>
using namespace std;
ifstream in("runaround.in");
ofstream out("runaround.out.in");

struct Memo {
    Memo* yes; Memo* no; bool exists;
    Memo() : yes(0), no(0), exists(0) {}
};
Memo* memo1;

inline bool is(vector<int>&v) {
    bool used[9]={0};
    /*RUN AROUND*/                  for(int i=0;i<v.size();i++) if(used[ (i+1+v[i])%v.size() ]++) return 0;
    return 1;
}

int gen(vector<int>&v,const int& index,const int& remain,const int& min) {
    if(!remain) {
        /*MEMOIZE*/
        Memo** m=&memo1;
        int last=1;
        for(int i=0;i<index;i++) {
            for(int j=0;j<v[index]-last;j++)
            {
                m=&((*m)->yes);
                *m = (*m)?*m:new Memo;
            }
            (*m)->exists=1;
            last=v[index];
        }
    }
    else            /*GENERATE*/    for(int j=min;j<=9;j++) { v[index]=j; gen(v,index+1,remain-1,j+1); }
}

int findNext(int x)
{
    vector<int> v;
    while(x) { v.push_back(x%10); x/=10; }
    //hash
    int id=0;

}

int main() {
    memo1=new Memo;
    /*GENERATE*/                    for(int x=1;x<9;x++) { vector<int> v; for(int i=0;i<x;i++) v.push_back(0); gen(v,0,x,1); }

}
