/*
 PROB: fact4
 USER: drmrshd1
 LANG: C++
*/

#include <fstream>
using namespace std;

int main() {
    ifstream in("fact4.in");
    ofstream out("fact4.out");
    int A; in>>A;
    int cache=1;
    for(int i=2;i<=A;i++) {
        cache*=i;
        while(cache%10==0) cache/=10;
        cache=cache%1000000;
    }
    out<<cache%10<<endl;
}
