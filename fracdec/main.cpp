/*
 PROB: fracdec
 LANG: C++
 USER: drmrshd1
*/

#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <sstream>
using namespace std;/*
ifstream in("in.txt");
ofstream out("out.txt");*/
ifstream in("fracdec.in");
ofstream out("fracdec.out");

struct tri{int first,second,third;};
tri make_tri(int first,int second,int third) {
    tri* t=new tri;
    t->first=first;
    t->second=second;
    t->third=third;
    return *t;
}

vector< tri > backtrack[104729];  //SUBTRACT, LEFT
int repeat=-1;
list<tri> queue;

void doLongDiv(string&result,int reg,const int&N,int i) {
    while(1) {
        reg*=10;
        if(!reg) {
            if(!result.size()) result.push_back('0');
            return;
        }
        if(reg<N) {
            //        out<<"BAIL ";
            //        out<<reg<<' '<<N<<' '<<i<<endl;
            result.push_back('0');
            //doLongDiv(result,reg,N,i+1);
            i++;
        } else {
            //        out<<reg<<' '<<N<<' '<<i<<endl;
            int D=reg/N*N;
            //for(D=reg;D>=0;D--) if(D%N==0) break;
            if(!D) return;
            for(int n=0;n<backtrack[D%104729].size();n++) {
                if(backtrack[D%104729][n].first==D) {
                    if(backtrack[D%104729][n].third==reg) {
                        int jn=backtrack[D%104729][n].second-1;
                        while(result[--jn]=='0'&&result[result.size()-1]=='0') {result.erase(result.size()-1,1);}
                        result.insert(jn+1,"(");
                        result.push_back(')');
                        return;
                    }
                }
            }
            result.push_back(D/N+'0');
            backtrack[D%104729].push_back(make_tri(D,i,reg));
            reg-=D;
            i++;
            //        doLongDiv(result,reg-D,N,i+1);
        }
    }
}

int main() {
    int N,D;
    in>>N>>D;
    int wn=N/D;
    int fp=N%D;
    string fpx;
    doLongDiv(fpx,fp,D,1);

    ostringstream ss;
    ss<<wn<<'.';
    fpx.insert(0,ss.str());
    for(int i=1;i<fpx.size();i++) {
        if(!(i%77)) fpx.insert(i-1,"\n");
    }

    out<<fpx<<endl;
}
