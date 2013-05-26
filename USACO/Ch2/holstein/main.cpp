/*
 ID: drmrshd1
 PROG: holstein
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
ifstream in("holstein.in");
ofstream out("holstein.out");

struct Feed{Feed(z tid){id=tid;}z id;vector<z>_amounts;};

z operator-(Feed&a,Feed&b){ z ttl=0;
    for(z i=0;i<a._amounts.size();i++){
        ttl+=max(0,a._amounts[i]-b._amounts[i]);
    }
    return ttl;
}

Feed& operator-=(Feed&a,Feed&b){
    for(z i=0;i<a._amounts.size();i++){
        out<<"LIMITING "<<i<< " TO "<<max(0,a._amounts[i]-b._amounts[i])<<endl;
        a._amounts[i]=max(0,a._amounts[i]-b._amounts[i]);
    }
    return a;
}

bool operator<(const Feed&a,const Feed&b){ return a.id<b.id; }
bool operator>(const Feed&a,const Feed&b){ return a.id>b.id; }

z main(){ z V, G; Feed prototype(-1); vector<Feed> _feeds; z lid=0;
    in>>V;
    for(z i=0;i<V;i++) { z x;
        in>>x;
        prototype._amounts.push_back(x);
    }
    in>>G;
    for(z i=0;i<G;i++) {
        _feeds.push_back(Feed(++lid));
        for(z j=0;j<V;j++) { z x;
            in>>x;
            _feeds.back()._amounts.push_back(x);
        }
    }

    vector<Feed> l;
    while(1){ z max=9999999,maxi;
        for(z i=0;i<G;i++){
            if(prototype-_feeds[i]<max){max=prototype-_feeds[i];maxi=i;}
        }
        if((9999999==max))break;
        else{prototype-=_feeds[maxi];l.push_back(_feeds[maxi]);_feeds.erase(_feeds.begin()+maxi,_feeds.begin()+maxi+1);
            if(max<=0)break;
        }
    }

    sort(l.begin(),l.end());
    out<<l.size();
    for(z i=0;i<l.size();i++){
        out<<' '<<l[i].id;
    }
    out<<endl;
}
