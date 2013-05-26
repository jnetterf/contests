///*
// PROB: delivery
// LANG: C++
// USER: drmrshd1
//*/

//#include <fstream>
//#include <vector>
//#include <stdlib.h>
//using namespace std;

//ifstream in("DATA1.txt");
//ofstream out("OUT1.txt");


//struct Grid {
//    int maxA, maxB;
//    char data[101][101]; //'#' or '.'
//    bool checkHoriz(const int& a,const int& b) {
//        if(data[a][b]=='#') return 0;
//        if( (!b||data[a][b-1]=='#') && (b+1==maxB||data[a][b+1]=='#')) return 0;
//        return (!b||data[a][b-1]=='#');
//    }
//    bool checkVert(const int& a, const int& b) {
//        if(data[a][b]=='#') return 0;
//        if( (!a||data[a-1][b]=='#') && (a+1==maxA||data[a+1][b]=='#')) return 0;
//        return (!a||data[a-1][b]=='#');
//    }
//};

//int main() {
//    Grid g;
//    string s;
//    for(int i=0;i<5;i++) {
//        in>>g.maxA>>g.maxB;

//        for(int j=0;j<g.maxA;j++) {
//            in>>s;
//            for(int k=0;k<g.maxB;k++) {
//                g.data[j][k]=s[k];
//            }
//        }

//        int h=0,v=0;
//        for(int j=0;j<g.maxA;j++) {
//            for(int k=0;k<g.maxB;k++) {
//                if(g.checkHoriz(j,k)) ++h;
//                if(g.checkVert(j,k)) ++v;
//            }
//        }
//        out<<h<<' '<<v<<endl;
//    }
//}
