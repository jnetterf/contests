#include <fstream>
#include <vector>
using namespace std;
ifstream in("in.txt");
ofstream out("out.txt");

vector< vector<int> > _hash[7919];

int main() {
    int n;
    in>>n;
    for(int i=0;i<n;i++) {
        int flake[6];
        int minflake=10000009;
        vector<int> equal;
        for(int j=0;j<6;j++) {
            in>>flake[j];
            if(flake[j]<minflake) {
                minflake=flake[j];
                equal.clear();
                equal.push_back(j);
            } else if (flake[j]==minflake) {
                equal.push_back(j);
            }
        }
        for(int pm=0;pm<equal.size();pm++) {
            int mini=equal[pm];

            int dir=0;
            if(mini==0) dir=(flake[5]<flake[1])?-1:1;
            else if(mini==5) dir=(flake[4]<flake[0])?-1:1;
            else dir=(flake[mini-1]<flake[mini+1])?-1:1;
            //Generate non-unique flake
            vector<int> nuflake;
            int j=mini;
            for(int pi=0;pi<6;pi++) {
                j+=dir;
                if(j==6) j=0;
                if(j==-1) j=5;
                nuflake.push_back(flake[j]);
            }
            //Generate hash
            int hash=1;
            for(int j=0;j<6;j++) {
                hash*=71*((j+nuflake[j])%7919);
                hash%=7919;
                if(hash<0) hash*=-1;
            }
            for(int j=0;j<_hash[hash].size();j++) {
                bool ok=1;
                for(int k=0;k<6;k++) {
                    if(nuflake[k]!=_hash[hash][j][k]) {
                        ok=0;
                        break;
                    }
                }
                if(ok) {
                    out<<"Twin snowflakes found."<<endl;
                    return 0;
                }
            }
            //Save hash
            _hash[hash].push_back(nuflake);
        }
    }
    out<<"No two snowflakes are alike."<<endl;
    return 0;
}
