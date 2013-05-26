#include <fstream>
#include <vector>
using namespace std;
ifstream in("in.txt");
ofstream out("out.txt");

struct state : vector<int> {
    int maxOther;
    bool operator+=(state&that) {
//        out<<operator[](0)<<' '<<maxOther<<" -> ";
        state&tis=*this;
        tis[0]+=that[0];
        for(int i=1;i<size();i++)
            maxOther=max(maxOther,tis[i]+=that[i]);
//        out<<operator[](0)<<' '<<maxOther<<endl;
        return operator [](0)>maxOther;
    }
    void addInt(const int&a,const int&i) {
        if(i+1>size()) push_back(0);
        if(!i) operator [](0)=a;
        else maxOther=max(maxOther,operator [](i)=a);
    }

    state() : maxOther(0) {}
};

int main() {
    int N, p;
    in>>N>>p;
    int xn=0,x=0;
    vector<state> begin;
    for(int i=0;i<N;i++) {
        state s;
        for(int j=0;j<p;j++) {
            int a;
            in>>a;
            s.addInt(a,j);
        }
        begin.push_back(s);
        if(s[0]>s.maxOther) xn++;
    }
    x=xn;
    vector<state>* current=&begin;
    vector<state>* next=0;
    int actions=0,actionsn=0;
    for(int i=1;i<N;i++) {
        next=new vector<state>;
        for(int j=0;j<N;j++) {
            if(j+i>=N) {
                state s;
                for(int k=0;k<p;k++)
                    s.addInt(0,k);
                next->push_back(s);
            } else {
                state s=(*current)[j];
                bool xb=s[0]>s.maxOther;
                if( s+=begin[j+i] ) {
//                    out<<j<<"!!\n";
                    if(!xb) {xn++;   actions++; }//ridings you own
                    int xi=1;
                    for(int l=j;l<=j+1;l++) {
                        if((*current)[l][0]>(*current)[l].maxOther)
                            xi--;   //this riding no longer exists
                    }
                    int Q=N-i; //ridings left
//                    out<<Q<<' ';
//                    out<<xi<<' '<<x<<' '<<(Q/2)+1<<endl;
                    out<<actionsn<<endl;
                    if(xi+x>=(int)(Q/2)+1) {
                        out<<i+actionsn<<endl;
                        return 0;
                    }
                }
                next->push_back(s);
            }
        }
        if(i!=1) delete current;
        current=next;
        actionsn=actions;
        out<<"!"<<actionsn<<endl;
        x=xn;
    }
    out<<-1<<endl;
}
