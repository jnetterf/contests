/*
 ID: drmrshd1
 PROG: passwd
 LANG: C++
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits.h>
using namespace std;
typedef int z;
typedef string S;
typedef void f;
ifstream in("passwd.in");
ofstream out("passwd.out");

vector<char> _valid;
z maxLen;
z passwdCount=0;

z countConst(S&str){ z c=0; z v=0;
    for(z i=0;i<str.size();i++){
        if((str[i]!='a')&&(str[i]!='e')&&(str[i]!='i')&&(str[i]!='o')&&(str[i]!='u'))c++;
        else v++;
    }
    if (!v)return -1;
    else return c;
}

f doIt(S str,z lastValid) {
    if(str.size()==maxLen) { //verify
        if (countConst(str)<2){return;}
        out<<str<<endl;
        if(++passwdCount==25000)exit(0);
    }
    for(z i=lastValid+1;i<_valid.size();i++){doIt(str+(char)_valid[i],i);}
}

z main() { z valids;
    in>>maxLen; in>>valids;
    for(z i=0;i<valids;i++){char valid;
        in>>valid;
        _valid.push_back(valid);
    }
    sort(_valid.begin(),_valid.end());
    doIt( "", -1 );
    exit(0);
}
