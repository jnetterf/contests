#include <fstream>
#include <string>
using namespace std;
ifstream in("in.txt");
ofstream out("out.txt");

char mapping[95];

int main() {
    //A:65 Z:90 _:95

    int a=65;
    for(int i=0;i<27;i++) {
        in>>mapping[a++];
        if(a==91) a=95;
    }
    long long longlonglonglonglonglonglong; in>>longlonglonglonglonglonglong;

    string s; in>>s;
    //see how long it takes to get back to the beg.
    string t=s; int c=0;
    do {
        for(int i=0;i<s.size();i++) {
            t[i]=mapping[t[i]];
            c++;
        }
    } while(s!=t);

    int shortshortshortshortshortshortshortshortshortshortshortshortshort=(longlonglonglonglonglonglong)%c;

    for(int i=0;i<s.size();i++) {
        char x=s[i];
        for(int j=0;j<shortshortshortshortshortshortshortshortshortshortshortshortshort;j++) {
            x=mapping[x];
        }
        out<<x;
    }
    out<<endl;
}
