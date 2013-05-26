/*
 PROB: contact
 LANG: C++
 USER: drmrshd1
*/

#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

ifstream in("contact.in");
ofstream out("contact.out");
int A,B,N;

struct Node;

vector<Node*> _notable;

struct Node {
    int count;
    string name;
    Node* child[2];
    Node(string cname="") : count(0),name(cname) { child[0]=child[1]=0; }
    void incr() {
        if(++count==1) _notable.push_back(this);
//        out<<name<<'\t'<<count<<endl;
    }

    void proc(char* pattern,int depth=0) {
        if(depth>=B) return;
        int cld = pattern[0];
        if(cld=='\n') return;
        else cld-=48;
        if(!child[cld]) child[cld]=new Node(name+pattern[0]);
        if(depth+1>=A) child[cld]->incr();
        child[cld]->proc(pattern+1,depth+1);
    }
};

bool notableComp(Node* a,Node* b) {
    if(a->count==b->count) {
        if(a->name.size()==b->name.size()) {
            for(int i=0;i<a->name.size();i++) {
                if(a->name[i]!=b->name[i]) return a->name[i]<b->name[i];
            }
        }
        return a->name.size()<b->name.size();
    }
    return a->count > b->count;
}

int main() {
    in>>A>>B>>N;
    //char* message= new char[200010];
    string x;

    x+='\0';
    while(in.good()) {
        string y;
        in>>y;
        x+=y;
    }
    x+='\n';
//    out<<x;

    char* message = const_cast<char*>(x.c_str());
    for(Node*root=new Node;*++message!='\n';) {
        root->proc(message);
    }

    sort(_notable.begin(),_notable.end(),notableComp);
    if(!_notable.size()) {
        out<<endl;
        return 0;
    }
    int freq=_notable[0]->count;
    int freqc=0;
    out<<freq<<endl;
    int lts=0;
    for(int i=0;i<=_notable.size();i++) {
        if(i==_notable.size()) {
            out<<endl;
            return 0;
        }
        if(freq!=_notable[i]->count) {
            out<<endl;
            if(++freqc>=N) break;
            freq=_notable[i]->count;
            out<<freq<<endl;
            out<<_notable[i]->name;
            lts=1;
        } else if(i) {
            if(lts++==6) {lts=1;out<<endl<<_notable[i]->name;}
            else out<<' '<<_notable[i]->name;
        } else {
            lts++;
            out<<_notable[i]->name;
        }
    }
    //out<<message<<endl;
    return 0;
}
