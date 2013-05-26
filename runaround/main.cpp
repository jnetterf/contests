/*
 USER:drmrshd1
 LANG:C++
 PROB:runround
*/

#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;
ifstream in("runround.in");
ofstream out("runround.out");

char* min;

bool isRunround(char*x,int s) {
    bool isFrom[s];
    for(int i=0;i<s;i++) isFrom[i]=0;

    int n=0;
    int first=-1;
    while(1) {
        if(isFrom[n]) {
            if(first!=n) return 0;
            break;
        }
        if(first==-1) first=n;
        isFrom[n]=1;
        n=(n+x[n])%s;
    }
    for(int i=0;i<s;i++) {
        if(!isFrom[i]) return 0;
    }
    if(::min) {
        for(int i=0;i<s;i++) {
            if(i==s-1) return x[i]> ::min[i];
            if(x[i]< ::min[i]) return 0;
            if(x[i]> ::min[i]) break;
        }
    }
    return 1;
}

void gen(bool* unique,char* x,int n,int s) {
    if(n==s) {
        if(isRunround(x,s)) {
            for(int i=0;i<s;i++) {
                out<<(int)x[i];
            }
            out<<endl;
            exit(0);
        }
        return;
    }
    for(int i=1;i<=9;i++) {
        if(unique[i]) continue;
        unique[i]=1;
        x[n]=i;
        gen(unique,x,n+1,s);
        unique[i]=0;
    }
}

int main() {
    string str;
    in>>str;
    char x[str.size()];
    for(int i=0;i<str.size();i++) {
        x[i]=(int)str[i]-48;
    }
    ::min=x;
    bool unique[10] = {0};
    char xn[10];
    gen(unique,xn,0,str.size());
    ::min=0;
    for(int i=str.size()+1;i<=9;i++) {
        gen(unique,xn,0,i);
    }
}
