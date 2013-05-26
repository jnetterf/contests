/*
 PROB: maze1
 LANG: C++
 USER: drmrshd1
*/

#include <fstream>
#include <string>
#include <sstream>
#include <list>
using namespace std;/*
ifstream in("maze1.in");
ofstream out("maze1.out");*/
ifstream in("in.txt");
ofstream out("out.txt");

int maze[101][39];  //1 for N, 2 for E, 4 for S, 8 for W
int score[101][39];
bool visit[101][39];

int W,H;
int entr1[2],entr2[2];

struct memo{int i,j,a;memo(int ci,int cj,int ca):i(ci),j(cj),a(ca){}};
list<memo> dijkstra;

void recurse(int i,int j,int amount) {
    if(visit[i][j]) return;
    if(i<0) return;
    if(j<0) return;
    if(amount>score[i][j]) return;

    score[i][j]=amount;
    int x=maze[i][j];
    if(x>=8) {if(!visit[i][j-1])dijkstra.push_back(memo(i,j-1,amount+1));x-=8;}
    if(x>=4) {if(!visit[i+1][j])dijkstra.push_back(memo(i+1,j,amount+1));x-=4;}
    if(x>=2) {if(!visit[i][j+1])dijkstra.push_back(memo(i,j+1,amount+1));x-=2;}
    if(x>=1) {if(!visit[i-1][j])dijkstra.push_back(memo(i-1,j,amount+1));x-=1;}
    visit[i][j]=1;
}

int main() {
    string ln;
    getline(in,ln);
    istringstream iss(ln);
    iss>>W>>H;
    entr1[0]=entr2[0]=-1;

    for(int i=0;i<H+1;i++) {
        getline(in,ln);
        for(int j=0;j<2*W+1;j++) {
            if(ln[j]=='+') continue;
            if(ln[j]==' ') {
                if(i) {
                    if(i==H) { if(entr1[0]==-1){entr1[0]=i-1;entr1[1]=j/2;}else{entr2[0]=i-1;entr2[1]=j/2;} }
                    maze[i-1][j/2]+=4;
                }
                if(i<H) {
                    if(!i) { if(entr1[0]==-1){entr1[0]=i;entr1[1]=j/2;}else{entr2[0]=i;entr2[1]=j/2;} }
                    maze[i][j/2]+=1;
                }
            }
        }
        getline(in,ln);
        if(i==H) break;
        for(int j=0;j<=2*W+1;j++) {
            if(j%2) continue;
            if(ln[j]==' ') {
                if(j/2) {
                    if(j/2==W) { if(entr1[0]==-1){entr1[0]=i;entr1[1]=j/2-1;}else{entr2[0]=i;entr2[1]=j/2-1;} }
                    maze[i][j/2-1]+=2;
                }
                if(j/2<W) {
                    if(!(j/2)) { if(entr1[0]==-1){entr1[0]=i;entr1[1]=j/2;}else{entr2[0]=i;entr2[1]=j/2;} }
                    maze[i][j/2]+=8;
                }
            }
        }
    }

//   out<<"@"<<entr1[0]<<'\t'<<entr1[1]<<endl;
//    out<<"@"<<entr2[0]<<'\t'<<entr2[1]<<endl;


    for(int i=0;i<H;i++){for(int j=0;j<W;j++) {score[i][j]=999999;/*out<<maze[i][j]<<'\t';*/}/*out<<endl;*/}
    recurse(entr2[0],entr2[1],1);

    while(dijkstra.size()) {
        recurse(dijkstra.front().i,dijkstra.front().j,dijkstra.front().a);
        dijkstra.pop_front();
    }
//    for(int i=0;i<H;i++){for(int j=0;j<W;j++)out<<score[i][j]<<'\t';out<<endl;} out<<endl;

//    for(int i=0;i<H;i++){for(int j=0;j<W;j++) {score[i][j]=999999;/*out<<maze[i][j]<<'\t';*/}/*out<<endl;*/}
    for(int i=0;i<H;i++)for(int j=0;j<W;j++)visit[i][j]=0;
    recurse(entr1[0],entr1[1],1);

    while(dijkstra.size()) {
        recurse(dijkstra.front().i,dijkstra.front().j,dijkstra.front().a);
        dijkstra.pop_front();
    }
//    for(int i=0;i<H;i++){for(int j=0;j<W;j++)out<<score[i][j]<<'\t';out<<endl;} out<<endl;

    int maxScore=0;
    for(int i=0;i<H;i++)for(int j=0;j<W;j++) maxScore=max(maxScore,score[i][j]);

    out<<maxScore<<endl;
}
