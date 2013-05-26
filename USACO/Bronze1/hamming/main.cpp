/*
 ID: drmrshd1
 PROG: hamming
 LANG: C++
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <math.h>
using namespace std;
ifstream in("hamming.in");
ofstream out("hamming.out");
typedef int z;
typedef void f;
typedef string S;

vector<S> solution;

z hamming(S a,S b)
{
    z calc=0;
    for(z i=0;i<a.size();i++)
    {
        calc+=a[i]!=b[i];
    }
    return calc;
}

z hamming(S a)
{
    z hl=9;
    for(z i=0;i<solution.size();i++)
    {
        hl=min(hl,hamming(a,solution[i]));
    }
    return hl;
}

z main()
{
    z toFind,length,hammingDis;
    in>>toFind;
    in>>length;
    in>>hammingDis;
    int xcount=0;
    for(z i=0;i<2;i++) {  //1
        for(z j=0;j<2;j++) {  //2
            for(z k=0;k<2;k++) {  //3
                for(z l=0;l<2;l++) {  //4
                    for(z m=0;m<2;m++) {  //5
                        for(z n=0;n<2;n++) { //6
                            for(z o=0;o<2;o++) { //7
                                for(z p=0;p<2;p++) { //8
                                    char ccode[] = {i?'1':'0',j?'1':'0',k?'1':'0',l?'1':'0',m?'1':'0',n?'1':'0',o?'1':'0',p?'1':'0','\0'};
                                    S code =ccode;
                                    if(hamming(code)>=hammingDis)
                                    {
                                        out<< pow(2,0)*(p==1)+
                                              pow(2,1)*(o==1)+
                                              pow(2,2)*(n==1)+
                                              pow(2,3)*(m==1)+
                                              pow(2,4)*(l==1)+
                                              pow(2,5)*(k==1)+
                                              pow(2,6)*(j==1)+
                                              pow(2,7)*(i==1);

                                        solution.push_back(code);
                                        toFind--;
                                        if(++xcount==10||!toFind)
                                        {
                                            xcount=0;
                                            out<<endl;
                                        }
                                        else
                                        {
                                            out<<' ';
                                        }
                                        if(!toFind)
                                        {
                                            exit(0);
                                        }
                                    }
                                    if(length<1) p++;
                                }
                                if(length<2)o++;
                            }
                            if(length<3)n++;
                        }
                        if(length<4)m++;
                    }
                    if(length<5)l++;
                }
                if(length<6)k++;
            }
            if(length<7)j++;
        }
        if(length<8)i++;
    }
}
