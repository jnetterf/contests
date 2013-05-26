/*
 ID: drmrshd1
 PROG: holstein
 LANG: C++
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
using namespace std;
ifstream in("holstein.in");
ofstream out("holstein.out");
typedef int z;
typedef void f;

vector<z> bestPattern;

struct Feed
{
    vector<z> v_;
    z id;

    Feed(z cid) :
            id(cid)
    {
    }

    Feed& operator<<(z v)
    {
        v_.push_back(v);
        return *this;
    }

    f permutate(vector<Feed> r_,Feed require,vector<z> pattern)
    {
        pattern.push_back(id);
        require-=*this;
        if(!require.score())
        {
            if(!bestPattern.size()||(pattern.size()<bestPattern.size()))
            {
                bestPattern=pattern;
            }
        }
        else for(z i=0;i<r_.size();i++)
        {
            vector<Feed> rx_=r_;
            rx_.erase(rx_.begin(),rx_.begin()+i+1);
            r_[i].permutate(rx_,require,pattern);
        }
    }

    Feed& operator-=(const Feed& that)
    {
        for(z i=0;i<v_.size();i++)
        {
            v_[i]=max(0,v_[i]-that.v_[i]);
        }
        return *this;
    }

    z score()
    {
        z s(0);
        for(z i=0;i<v_.size();i++)
        {
            s+=v_[i];
        }
        return s;
    }
};

vector<Feed> u_;

z main()
{
    int V,G;
    Feed require(-1);
    in>>V;
    for(z i=0;i<V;i++)
    {
        int a;
        require<<((in>>a),a);
    }
    in>>G;
    for(z i=0;i<G;i++)
    {
        u_.push_back(Feed(i+1));
        for(z j=0;j<V;j++)
        {
            int a;
            u_[i]<<((in>>a),a);
        }
    }
    for(z i=0;i<G;i++)
    {
        vector<Feed> r_=u_;
        r_.erase(r_.begin()+i);
        u_[i].permutate(r_,require,vector<z>());
    }

    out<<bestPattern.size();
    for(z i=0;i<bestPattern.size();i++)
    {
        out<<' '<<bestPattern[i];
    }
    out<<endl;
}
