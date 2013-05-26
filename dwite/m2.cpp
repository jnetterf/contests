//#include <fstream>
//#include <vector>
//#include <stdlib.h>
//#include <algorithm>
//#include <map>
//#include <bitset>
//using namespace std;

//ifstream in("DATA2.txt");
//ofstream out("OUT2.txt");

//vector<int> primes;

//map<int,int> cur;

//void handle(int N) {
//    for(int i=0;i<primes.size();i++) {
//        if(primes[i]>N) { return; }
//        while(N%primes[i]==0) {
//            ++cur[primes[i]];
//            N/=primes[i];
//        }
//    }
//}

//int main() {
//    /*seive*/ {
//        bool seive[10000] = {0};
//        for(int i=2;i<10000;i++) {
//            for(int j=2;j<50000;j++) {
//                if(i*j>10000) break;
//                seive[i*j]=1;
//            }
//        }
//        for(int i=2;i<10000;i++) {
//            if(!seive[i]) primes.push_back(i);
//        }
//    }

//    //program
//    for(int i=0;i<5;i++) {
//        int N;
//        in>>N;
//        for(int j=2;j<=N;j++) {
//            handle(j);
//        }
//        map<int,int>::iterator it=cur.begin();
//        bool ok=0;
//        while(it!=cur.end()) {
//            if(ok) out<<" * ";
//            ok=1;
//            out<<(*it).first<<'^'<<(*it).second;
//            ++it;
//        }
//        out<<endl;
//        if(i!=4) cur.clear();
//    }
//}

