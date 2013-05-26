/*
 PROG: subset
 LANG: C++
 USER: drmrshd1
*/

#include <fstream>
#include <vector>
using namespace std;
ifstream in("subset.in");
ofstream out("subset.out");
int n,npre;
vector< pair<vector< bool >, long> >* memo[751];

long dual(long num, vector< bool > _x)
{
    if(memo[num])
    {
        for(int i=0;i<memo[num]->size();i++)
        {
            bool ok=1;
            for(int j=0;j<n+1;j++)
            {
                if(memo[num]->operator [](i).first[j]!=_x[j])
                {
                    ok=0;
                    break;
                }
            }
            if(ok)
            {
                return memo[num]->operator [](i).second;
            }
        }
    }
    int A=0,B=num;
    long ret=0;
    while(++A<--B)
    {
        if((A>n)||_x[A]||((B<n)&&_x[B]))
        {
            continue;
        }

        if(B>=n)
        {
            vector<bool> _y=_x;
            for(long i=0;i<=A&&i<n;i++)
            {
                _y[i]=1;
            }
            ret += dual(num-A,_y);
        }
        else
        {
            ret+=1;
        }
    }
    pair<vector< bool >, long > _a;
    _a.first=_x;
    _a.second=ret;
    if(!memo[num])
    {
        memo[num]=new vector< pair<vector< bool >, long> >;
    }
    memo[num]->push_back(_a);
    return ret;
}

int main()
{
    for(long i=0;i<751;i++)
    {
        memo[i]=0;
    }
    in>>n;
    vector<bool> a;
    for(long i=0;i<n+1;i++)
    {
        a.push_back(!i);
    }
    out<<((n*(n+1)%4)?0:dual(npre=n*(n+1)/4,a))<<endl;
}
