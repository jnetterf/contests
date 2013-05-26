///*
// PROB: climb
// LANG: C++
// USER: drmrshd1
//*/

//#include <fstream>
//#include <vector>
//#include <stdlib.h>
//#include <climits>
//#include <algorithm>
//#include <list>
//using namespace std;

//ifstream in("climb.in");
//ofstream out("climb.out");
////ofstream out("out.txt");

//// lolz maybe this will actually work. who knows?

//struct Cow {
//    int up, down;
//    int tAvail;
//    Cow(int cup,int cdown) : up(cup), down(cdown) {}
//};

//struct CowSort {
//    bool operator()(Cow* a, Cow* b) {
//        return (a->down-a->up)>(b->down-b->up);
//    }
//};

//int main() {
//    list<Cow*> l;
//    int N;
//    in>>N;
//    for(int i=0;i<N;i++) {
//        int up, down;
//        in>>up>>down;
//        l.push_back(new Cow(up,down));
//    }
//    l.sort(CowSort());

//    // SIMULATE UP
//    int tU=0;
//    for(list<Cow*>::iterator it=l.begin();it!=l.end();++it) {
//        tU+=(*it)->up;
//        (*it)->tAvail=tU;
//    }
//    //SIMULATE DOWN
//    int tD=0;
//    for(list<Cow*>::iterator it=l.begin();it!=l.end();++it) {
//        if(tD<(*it)->tAvail) {
//            tD=(*it)->tAvail;
//        }
//        tD+=(*it)->down;
//    }
//    out<<tD<<endl;
//}

