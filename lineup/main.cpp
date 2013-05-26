/*
 ID: drmrshd1
 PROG: lineup
 LANG: C++
*/

// QUESTION WANTS ME TO HAVE KNOWN THE STL :(

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <limits.h>
using namespace std;
typedef long z;
typedef string S;
typedef void f;
ifstream in("lineup.in");
ofstream out("lineup.out");

z N;

struct Cool {
    z pos;
    z type;
    z score;
    Cool(z p,z t) : pos(p), type(t) {}
};

struct CoolSort {
    bool operator()(Cool*a,Cool*b) {
        return a->pos<b->pos;
    }
};

int main() {
    in>>N;
    int last=-1;
    vector<Cool*> cools;
    map<int,int> uncoolToCool;
    for(z i=0;i<N;i++) {
        z pos,breed;
        in>>pos>>breed;
        if(uncoolToCool.count(breed)) {
            cools.push_back(new Cool(pos,uncoolToCool.find(breed)->second));
        } else {
            uncoolToCool[breed]=++last;
            cools.push_back(new Cool(pos,uncoolToCool.find(breed)->second));
        }
    }
    sort(cools.begin(),cools.end(),CoolSort());

    int coolCowCounts[last+1];//because I will win the CCC!!!

    for(int i=0;i<last+1;i++) {
        coolCowCounts[i]=0;
    }
    int bestScore=999999999;
    int lastPOS=0;
    for(int i=0;i<cools.size();i++)
    {
        bool ok=1;
        for(z k=0;k<last+1;k++)
        {
            if(!coolCowCounts[k]) {
                ok=0;
                break;
            }
        }
        if(!ok) for(;lastPOS<cools.size();lastPOS++) {
            ++coolCowCounts[cools.at(lastPOS)->type];
            //ALL COWS MUST BE AcowNTED FOR
            ok=1;
            for(z k=0;k<last+1;k++)
            {
                if(!coolCowCounts[k]) {
                    ok=0;
                    break;
                }
            }
            if(ok) {
                break;
            }
        }
        if(!ok) {
            break;
        }

        int score=cools.at(lastPOS)->pos-cools.at(i)->pos;
        if(score<bestScore) {
            bestScore=score;
        }
        --coolCowCounts[cools.at(i)->type];
    }
    out<<bestScore<<endl;
}
