/*
 ID: drmrshd1
 PROG: sort3
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
ifstream in("sort3.in");
ofstream out("sort3.out");

z main(){z n;vector<z>_data;vector<z>_stage;z _counts[4];z total=0;
    for(z i=1;i<4;i++){_counts[i]=0;}
    in>>n;
    for(z i=0;i<n;i++){z d;in>>d;_data.push_back(d);_counts[d]++;}
    for(z i=1;i<4;i++)for(z j=0;j<_counts[i];j++){_stage.push_back(i);}

    for(z i=0;i<_data.size();i++){
      //  out<<_data[i]<<endl;
    }

    for(z i=0;i<n;i++){
        if(_stage[i]!=_data[i]) for(z j=0;j<i;j++){
            if((_stage[j]!=_data[j])&&(_stage[i]==_data[j])&&(_stage[j]==_data[i])){   //perfect swap
                //out<<"PERFECT SWAP "<<i<<' '<<j<<endl;
                z swap=_data[i]; _data[i]=_data[j];_data[j]=swap;total++;
            }
        }
        if(_stage[i]!=_data[i]) for(z j=0;j<i;j++){
            if((_data[j]!=_stage[j])&&(_data[i]==_stage[j]) ){ // imperfect swap
                //out<<"IMPERFECT SWAP "<<i<<' '<<j<<endl;
                z swap=_data[i]; _data[i]=_data[j];_data[j]=swap;total++;
            }
        }
    }

    out<<total<<endl;
    for(z i=0;i<_data.size();i++){
       // out<<_data[i]<<endl;
    }
}
