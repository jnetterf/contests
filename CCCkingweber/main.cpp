#include <fstream>
#include <vector>
#include <list>
#include <bitset>
#include <string>
#include <stdlib.h>
using namespace std;
ifstream in("B.21.dat");
ofstream out("out.txt");

vector<string> hash_str[7919];
vector<int> hash_seqn[7919];
vector<int> hash_x_or_y[7919];

vector<int> seqn_to_sysn;

int jHash(string&x) {
    int code=1;
    for(int i=0;i<x.size();i++) {
        code*=x[i];
        code%=7919;
    }
    return code;
}

int arrayid(string&x,int&hashx,bool dcr=0) {
    for(int i=0;i<hash_str[hashx].size();i++)
        if(!x.compare(hash_str[hashx][i])) return i;
    if(dcr) return -1;
    hash_str[hashx].push_back(x);
    hash_seqn[hashx].push_back(-1);
    hash_x_or_y[hashx].push_back(-1);
    return hash_str[hashx].size()-1;
}

struct Instr {
    int xh,xa;
    int yh,ya;
    bool parallel;
};

struct System {
    vector<Instr> ins;
    void analyse() {
        bool done[ins.size()];
        for(int i=0;i<ins.size();i++)
            done[i]=0;
        done[0]=1;
        if(!ins.size()) return;
        hash_x_or_y[ins[0].xh][ins[0].xa] = 0;  // THIS IS X
        hash_x_or_y[ins[0].yh][ins[0].ya] = ins[0].parallel?0:1;    // THIS IS EITHER X OR Y

        while(1) {
            bool ok=0;
            for(int i=0;i<ins.size();i++) {
                if(done[i]) continue;
                int&a=hash_x_or_y[ins[i].xh][ins[i].xa];
                int&b=hash_x_or_y[ins[i].yh][ins[i].ya];
                if(a==b&&a==-1) continue;
                done[i]=1;
                ok=1;
                if(a!=-1) {
                    if(b!=-1) {
                        if(a!=ins[i].parallel?b:!b) {
                            out<<"Waterloo"<<endl;
                            exit(0);
                        }
                    } else {
                        b=ins[i].parallel?a:!a;
                    }
                } else {
                    a=ins[i].parallel?b:!b;
                }
            }
            if(!ok) break;
        }

    }
};

int main() {
//    {out<<"100000 1"<<endl;
//    for(long long i=0;i<100000LL;i++) {
//        out<<i<<" "<<i+1<<" parallel"<<endl;
//    }
//    out<<"1 2"<<endl;}
//    return 0;
    int N,M;
    in>>N>>M;
    int lastseqn=-1;
    Instr instrs[N];
    for(int i=0;i<N;i++) {
        string x,y,c;
        in>>x>>y>>c;
        int xh=jHash(x),yh=jHash(y);
        int xa=arrayid(x,xh),ya=arrayid(y,yh);
        if(hash_seqn[xh][xa]==-1&&hash_seqn[yh][ya]==-1) {
            hash_seqn[xh][xa]=hash_seqn[yh][ya]=++lastseqn;
            seqn_to_sysn.push_back(lastseqn);
        }
        else if(hash_seqn[xh][xa]==-1&&hash_seqn[yh][ya]!=-1) {
            hash_seqn[xh][xa]=hash_seqn[yh][ya];
        }
        else if(hash_seqn[xh][xa]!=-1&&hash_seqn[yh][ya]==-1) {
            hash_seqn[yh][ya]=hash_seqn[xh][xa];
        }
        else if(hash_seqn[xh][xa]!=-1&&hash_seqn[yh][ya]!=-1) {
            int sm=min(seqn_to_sysn[ hash_seqn[xh][xa] ],seqn_to_sysn[ hash_seqn[yh][ya] ]);
            seqn_to_sysn[ hash_seqn[xh][xa] ] = seqn_to_sysn[ hash_seqn[yh][ya] ]=sm;
        }
        instrs[i].xh=xh; instrs[i].xa=xa;
        instrs[i].yh=yh; instrs[i].ya=ya;
        instrs[i].parallel=(c=="parallel"?1:0);
    }
    int XC=-1;
    for(int i=0;i<seqn_to_sysn.size();i++)
        XC=max(XC,seqn_to_sysn[i]);

    XC++;
    System* syss=new System[XC];
    for(int i=0;i<N;i++) {
        int sys=seqn_to_sysn[ hash_seqn[instrs[i].xh][instrs[i].xa] ];
        syss[sys].ins.push_back( instrs[i] );
    }
    for(int i=0;i<XC;i++) {
        syss[i].analyse();
    }
    for(int i=0;i<M;i++) {
        string x,y;
        in>>x>>y;
        int xh=jHash(x),yh=jHash(y);
        int xa=arrayid(x,xh,1),ya=arrayid(y,yh,1);
        if(xa==-1||ya==-1) {
            out<<"unknown"<<endl;
        } else if ( seqn_to_sysn[ hash_seqn[xh][xa] ] != seqn_to_sysn[ hash_seqn[yh][ya] ] ) {
//            out<<seqn_to_sysn[ hash_seqn[xh][xa] ]<<'\t'<<seqn_to_sysn[ hash_seqn[yh][ya] ]<<endl;
//            out<<">>"<<xh<<'\t'<<xa<<'\t'<<yh<<'\t'<<ya<<endl;
            out<<"unknown"<<endl;
        } else if( hash_x_or_y[xh][xa]!=hash_x_or_y[yh][ya] ) {
            out<<"intersect"<<endl;
        } else {
            out<<"parallel"<<endl;
        }
    }
}
