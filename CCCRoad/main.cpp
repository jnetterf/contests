#include <fstream>
#include <vector>
using namespace std;
ifstream in("in.txt");
ofstream out("out.txt");

struct node;

node* mapping[1000];
int c;

struct node {
    int id;
    vector<node*> neigh;
    vector<bool> _nx;
    bool used;
    bool access(int n) {
        if(used) return 0;
        if(id==n) return 1;
        used=1;
        for(int i=0;i<neigh.size();i++) {
            if(neigh[i]->access(n)) {
                used=0;
                return 1;
            }
        }
        used=0;
        return 0;
    }

    void permutate(int size) {
        for(int i=id+1;i<size;i++) {
//            out<<"##"<<id<<' '<<i<<endl;
            int c=0;
            used=1;
            for(int j=0;j<neigh.size();j++) {
                if(neigh[j]->access(i)) {
//                    /*out*/<<"V\n";
                    if(++c>1) break;
                }
            }
            if(c==1) {
                for(int j=0;j<neigh.size();j++) {
                    if(!neigh[j]->access(i)) {
                        if(neigh[j]->id==i) continue;
//                        out<<"EN"<<id<<' '<<i<<' '<<neigh[j]->id<<endl;
                        neigh[j]->neigh.push_back(mapping[i]);
                        mapping[i]->neigh.push_back(neigh[j]);
                        ::c++;
//                        out<<::c<<endl;
                        break;
                    }
                }
            }
            used=0;
        }
    }

    node(int cid) : id(cid), used(0) {}
};

int main() {
    int n, r;
    in>>n>>r;
    for(int i=0;i<n;i++) {
        mapping[i]=new node(i);
    }
    for(int i=0;i<r;i++) {
        int a, b;
        in>>a>>b;
        a--;b--;
        mapping[a]->neigh.push_back(mapping[b]);
        mapping[b]->neigh.push_back(mapping[a]);
    }
    c=0;
    mapping[0]->permutate(n);
    out<<c<<endl;
}
