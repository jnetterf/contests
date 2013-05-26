#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <limits.h>
#include <math.h>
#define Yay return
using namespace std;
typedef int z;
typedef string S;
typedef void f;
ifstream in("s3.in");	///////////////////////////////////
ofstream out("s3.out");

double pows5[14];

f memoize(){
        for(z i=1;i<14;i++){
                pows5[i]=pow(5,i-1);	//!!!
        }
}

template<class T> bool e(const T&a,const T&n,const T&b){if(n>=a&&n<=b)return 1;else return 0;}
template<class T> bool g(const T&a,const T&n,const T&b){if(n>=a&&n<b)return 1;else return 0;}

bool doIt(z n,z x,z y) {
        if(n==0){return 0;}
        double cx=(double)x/pows5[n];
        double cy=(double)y/pows5[n];
        //out<< n<<':'<<cx<<' '<<cy<<endl;
        if( g(0.0,cy,1.0)) {
                if( g(1.0,cx,4.0) ) return 1;
        }
        if( g(1.0,cy,2.0)){
                if( g(2.0,cx,3.0) ) return 1;
        }
        if( e(1.0,cy,2.0)){
                if( e(1.0,cx,2.0) || e(3.0,cx,4.0)) return doIt(n-1,x%(z)pow(5,n-1),y%(z)pow(5,n-1));
        }
        if( e(2.0,cy,3.0)){
                if( e(1.0,cx,4.0) ) return doIt(n-1,x%(z)pow(5,n-1),y%(z)pow(5,n-1));
        }
        return 0;
}

z main() { z T;
        memoize();
        in>>T;
        for(z i=0;i<T;i++){ z n,x,y;
                in>>n;in>>x;in>>y;
                if(doIt(n,x,y))out<<"crystal\n";
                else out<<"empty\n";
        }
        Yay!
        1337;
}
