///*
// PROB: baleshare
// LANG: C++
// USER: drmrshd1
//*/

//#include <fstream>
//#include <vector>
//#include <stdlib.h>
//#include <climits>
//using namespace std;

//ifstream in("baleshare.in");
////ofstream out("baleshare.out");
//ofstream out("out.txt");

//int state[3];
//int l[20];
//int N;

//int bestSoFar=INT_MAX;

//int rec(uint x) {
//    if(x==N) {
//        int ret=0;
//        for(int i=0;i<3;i++) {
//            if(state[i]>ret) {
//                ret=state[i];
//            }
//        }
//        bestSoFar=(ret<bestSoFar)?ret:bestSoFar;
//        return ret;
//    }
//    int ret=INT_MAX;
//    for(int i=0;i<3;i++) {
//        state[i]+=l[x];
//        if(state[i]>bestSoFar) {
//            state[i]-=l[x];
//            continue;
//        }
//        int b=rec(x+1);
//        if(b<ret) ret=b;
//        state[i]-=l[x];
//    }
//    return ret;
//}

//int main() {
//    for(int i=0;i<3;i++) state[i]=0;
//    int x;
//    in>>N;
//    for(int i=0;i<N;i++) {
//        in>>x;
//        l[i]=(x);
//    }
//    out<<rec(0);
//}

