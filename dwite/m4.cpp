//#include <fstream>
//#include <vector>
//#include <stdlib.h>
//#include <algorithm>
//#include <map>
//#include <bitset>
//using namespace std;

//ifstream in("DATA4.txt");
//ofstream out("OUT4.txt");

//int primes[] = {0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};
//int N;
//int values[16];

//struct State {
//    bool has[17];
//    bool isWinning() {
//        int min=9999999,max=0;
//        bool canGoDown=1,canGoUp=1;
//        for(int i=0;i<N;i++) {
//            if(has[i]) {
//                if(canGoDown&&(values[i]<=min)) {
//                    min=values[i];
//                } else if(values[i]>min) {
//                    canGoDown=0;
//                }

//                if(canGoUp&&(values[i]>=max)) {
//                    max=values[i];
//                } else if(values[i]<max) {
//                    canGoUp=0;
//                }
//            }
//        }
//        return canGoDown||canGoUp;
//    }

//    bool doTurn(bool A) {
//        bool canWin=0;
//        for(int i=0;i<N;i++) {
//            if(!has[i]) continue;
//            has[i]=0;
//            if(isWinning()) {
//                canWin=1;
//                break;
//            } else {
//                canWin=!doTurn(!A);
//            }
//            has[i]=1;
//        }
//        return canWin;
//    }
//    State() {for(int i=0;i<17;i++) has[i]=1;}
//};

//int main() {
//    for(int i=0;i<15;i++) {
//        in>>N;
//        for(int j=0;j<N;j++) {
//            in>>values[j];
//        }
//        State s;
//        if(s.isWinning()) {
//            out<< "B";
//        } else {
//            if(s.doTurn(1)) out<<"A";
//            else out<<"B";
//        }
//        if((i+1)%3==0) out<<endl;
//    }
//}



