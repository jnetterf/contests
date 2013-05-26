/*
 PROB: prefix
 USER: drmrshd1
 LANG: C++
*/

#include <fstream>
#include <vector>
using namespace std;
ifstream in("prefix.in");
ofstream out("prefix.out");
//ifstream in("in.txt");
//ofstream out("out.txt");

int tryPrefix(char* prefix,char* string) {
    int i;
    for(i=0;(prefix[i]!='\0')&&(string[i]!='\0');i++) {
        if(prefix[i]!=string[i]) return 0;
    }
    return prefix[i]=='\0'?i:0;
}

int main() {
    vector<char*> prefixes;
    for(;;) {
        char* prefix = new char[10];
        in>>prefix;
        if(prefix[0]=='.') break;
        prefixes.push_back(prefix);
    }
    char S[200000];
    int i=-1;
    for(;;) {
        char s[76];
        in>>s;
        if(in.good()) for(int j=0;s[j]!='\n'&&s[j]!='\r'&&s[j]!='\0';j++) S[++i]=s[j];
        else break;
    }
    S[++i]='\0';

    bool tried[i+1];
    bool checked[i+1];
    vector<int> places;
    places.push_back(0);
    for(int j=0;j<=i;j++) tried[j]=0;
    for(int j=0;j<=i;j++) checked[j]=0;

    int maxX=0;

    for(int k=0;k<places.size();k++) {
        int v=places[k];
        int k=v;
        if(checked[k]) continue;
        checked[k]=1;
        for(int j=0;j<prefixes.size();j++) {
            int x=tryPrefix(prefixes[j],&S[k]);
            //out<<"FOR PREFIX "<<prefixes[j]<<" on string "<<&S[k]<<" GOT "<<x+k<<endl;
            if(x) x+=k;
            else continue;
            if(tried[x]) continue;
            tried[x]=1;
            places.push_back(x);
            if(x>maxX) maxX=x;
        }
    }
    out<<maxX<<endl;
}
