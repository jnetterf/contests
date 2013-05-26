#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <limits.h>
#define Yay return
using namespace std;
typedef int z;
typedef string S;
typedef void f;
ifstream in("s5.in");	///////////////////////////////////

// Stratagy:
//		Hail Mary, full of grace, the Lord is with thee...

char gc(S&s){char x=s[0];s.erase(0,1);return x;}
z gi(S&s){
        char x=gc(s);
        if(x>=97&&x<=122)return x-97;
        if(x>=65&&x<=90)return x-65;
        if(x=='\0'||x=='\n')return -2;
        else return -1;
}

class L{public:bool on; z pos;z scr;
        L(z tpos, bool ton){on=ton;pos=tpos;_u[pos]=this;}
        z score(){ z i=pos,c=0;
                if(on)return scr=0;
                while(1){
                        //cerr<<"L!"<<_u[i-1]<<' '<<i-1<<_u[i-1]->on<<endl;
                        if(i>=0&&_u[--i]&&_u[i]->on)c++;
                        else break;
                }
                i=pos; while(1){
                        if(i>=0&&_u[++i]&&_u[i]->on)c++;
                        else break;
                }
                //cerr<<'$'<<c<<endl;
                return scr=c;
        }
        bool flip(){ z i=pos,c=0;
                if(on){return false;}
                if(scr<3){on=1;return 1;}
                else{on=0;}
                while(1){
                        if(i>=0&&_u[--i]&&_u[i]->on)_u[i]->on=0;
                        else break;
                }
                i=pos; while(1){
                        if(i>=0&&_u[++i]&&_u[i]->on)_u[i]->on=0;
                        else break;
                }
                return 1;
        }
        static L* _u[1002];
};
L* L::_u[1002];


z main() {z n; z mnl=0;
        {for(z i=0;i<1002;i++)L::_u[i]=NULL;}
        in>>n;
        for(z i=0;i<n;i++){z x;
                in>>x;
                //cerr<<'!'<<x<<' '<<(bool)x<<endl;
                //cerr<<'$'<<i<<endl;
                if(x==0) new L(i,0);
                else new L(i,1);
        }
        while(1){z maxScore=0;z maxId=-999;z lastscore=0;
                //cerr<<endl;
                for(z i=0;i<n;i++){z score;
                        score = L::_u[i]->score();
                        //cerr<<"GOT SOCRE " << score<<endl;
                        if(score>maxScore){
                                maxScore=score;maxId=i;

                                z ls;
                                for(z j=i+1;j<n;j++){
                                        ls+=L::_u[j]->score();
                                }
                                lastscore=ls;
                        }
                        else if(score==maxScore){
                                z ls;
                                for(z j=i+1;j<n;j++){
                                        ls+=L::_u[j]->score();
                                }
                                if(ls<lastscore){lastscore=ls;maxScore=score;maxId=i;}
                        }
                }
                if(maxId==-999){cerr<<mnl<<endl;break;}
                else{
                        //cerr<<maxId<<endl;
                        if(!L::_u[maxId]->flip()){
                                //cerr<<"merde.\n";
                                cerr<<mnl<<endl;break;
                        }
                        mnl++;
                }
        }
        while(1){}
        Yay!
        1337;
}
