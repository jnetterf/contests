#include <fstream>
#include <vector>
#include <stdlib.h>
#include <string>
using namespace std;
ifstream in("in.txt");
ofstream out("out.txt");

struct bit {
    bool data;
    bit* child;
    int n;
    int reduce(bool t) {
        if(child) {
            return child->reduce(data)+(data!=t)?1:0;
        }
        else return(data!=t)?1:0;
    }
    bit() : n(0) {}
};

int main() {
    bit* start=new bit;

    for(int i=0;i<N;i++){

    }

    string s;in>>s;
    for(int i=0;i<s.size();i++) {
        x.data.push_back(s[i]=='G'?0:1);
    }
    int M;in>>M;
    out<<x.tryReduce(M,0)<<endl;
    out<<x.tryReduce(M,1)<<endl;
}
