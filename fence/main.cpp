/*
 PROB: fence
 LANG: C++
 USER: drmrshd1
*/

#include <fstream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;
ifstream in("fence.in");
ofstream out("fence.out");

vector<int> circuit;
list<int> neighbours[1025];

void findCircuit(int i) {
    if(!neighbours[i].size()) {
        circuit.push_back(i);
    } else {
        while(neighbours[i].size()) {
            if(neighbours[i].front()==-1) {
                neighbours[i].pop_front();
                continue;
            }
            int j=neighbours[i].front();
            for(list<int>::iterator it=neighbours[j].begin();it!=neighbours[j].end();++it) {
                if(*it==i) {*it=-1;break;}
            }
            neighbours[i].pop_front();
            findCircuit(j);
        }
        circuit.push_back(i);
    }
}

int main() {
    int F;
    in>>F;
    vector<int> sizes;
    for(int i=0;i<F;i++) {
        int a,b;
        in>>a>>b;
        sizes.push_back(a);
        sizes.push_back(b);
        neighbours[a].push_back(b);
        neighbours[b].push_back(a);
    }
    for(int i=0;i<1025;i++)
        neighbours[i].sort();

    sort(sizes.begin(),sizes.end());

    int minX=99999;
    for(int i=0;i<sizes.size();i++)
        if(neighbours[sizes[i]].size()&&neighbours[sizes[i]].size()%2) {minX=sizes[i];break;}
    if(minX==99999)
        for(int i=0;i<sizes.size();i++)
            if(neighbours[sizes[i]].size()) {minX=sizes[i];break;}

    findCircuit(minX);
    for(int i=circuit.size()-1;i>=0;i--)
        out<<circuit[i]<<endl;
}
