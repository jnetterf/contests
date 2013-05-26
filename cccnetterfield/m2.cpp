#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>
#include <set>
#include <queue>
using namespace std;

const int roman[] = {0,0,100,500,0,0,0,0,1,0,0,50,1000,0,0,0,0,0,0,0,0,5,0,10,0,0};
                   //A B C   D   E F G H I J K L  M    N O P Q R S T U V W X  Y Z

int ar(const int& a,const char& r) {
    return roman[(int)r-'A']*a;
}

int fix(int* values,const string& str) {
    for(int i=3;i<str.size();i+=2) {
        if(roman[str[i]-'A']>roman[str[i-2]-'A']) {
            if(values[i/2-1]>0) values[i/2-1]*=-1;
        }
    }
}

int main() {
    ifstream in("s2.in");
    string S;
    in>>S;
    int* a = new int[S.size()/2];
    for(int i=0;i<S.size();i+=2) {
        a[i/2]=ar((int)S[i]-'0',S[i+1]);
    }
    fix(a,S);
    int ret=0;
    for(int i=0;i<S.size()/2;i++) {
        ret+=a[i];
    }
    cout<<ret<<endl;
}
