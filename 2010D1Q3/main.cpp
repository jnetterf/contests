#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
ifstream in("wowow1.in");
ofstream out("out.txt");

struct Looser {
    int id;
    long long pts;
};

//bool operator<(const Looser&a,const Looser&b) { return a.pts<b.pts; }
struct compareLoosers {
    bool operator()(Looser*a, Looser*b) {
        return a->pts<b->pts;
    }
};

Looser* lotsOfLoosers[1000000];
vector<Looser*> looserocity;

int main() {
    int N;  in>>N;
    for(int i=0;i<N;i++) {
        char x; in>>x;
        int a; int b;
        switch(x) {
        case 'N':
            in>>a;
            lotsOfLoosers[a]=new Looser;
            lotsOfLoosers[a]->id=a;
            in>>b;
            lotsOfLoosers[a]->pts=b;
            looserocity.push_back(lotsOfLoosers[a]);
            break;
        case 'M':
            in>>a;
            lotsOfLoosers[a]->id=a;
            in>>b;
            lotsOfLoosers[a]->pts=b;
            break;
        case 'Q':
            in>>a;
            sort(looserocity.begin(),looserocity.end(),compareLoosers());
            out<<looserocity[looserocity.size()-a]->id<<endl;
            break;
        }
    }
}
