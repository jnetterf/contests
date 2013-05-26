/*
 PROB: ttwo
 LANG: C++
 USER: drmrshd1
*/

#include <fstream>
using namespace std;
ifstream in("ttwo.in");
ofstream out("ttwo.out");

char _grid[10][10];
bool _stateGrid[10][10][4][10][10][4];

int counter;
int farmer[3]={0,0,0};
int cow[3]={0,0,0};

void move(int* object) {
    switch(object[2]) {
    case 0: //N
        if(object[0]==0||_grid[object[0]-1][object[1]]=='*') object[2]++;
        else object[0]--;
        break;
    case 1: //E
        if((object[1]==9)||(_grid[object[0]][object[1]+1]=='*')) object[2]++;
        else object[1]++;
        break;
    case 2: //S
        if(object[0]==9||_grid[object[0]+1][object[1]]=='*') object[2]++;
        else object[0]++;
        break;
    case 3: //W
        if(object[1]==0||_grid[object[0]][object[1]-1]=='*') object[2]=0;
        else object[1]--;
        break;
    }
}

bool check(int* farmer,int*cow) {
    if(_stateGrid[farmer[0]][farmer[1]][farmer[2]][cow[0]][cow[1]][cow[2]]) {
        out<<"0\n";
        return 1;
    }
    _stateGrid[farmer[0]][farmer[1]][farmer[2]][cow[0]][cow[1]][cow[2]]=1;
    int ok=1;
    for(int i=0;i<2;i++) if(farmer[i]!=cow[i]) ok=0;
    if(ok) {
        out<<counter<<endl;
        return 1;
    }
    return 0;
}

int main() {
    for(int i=0;i<10;i++) {
        char x[11];in>>x;
        for(int j=0;j<10;j++) {
            _grid[i][j]=x[j];
            if(_grid[i][j]=='C') {
                _grid[i][j]='.';
                cow[0]=i;
                cow[1]=j;
            } else if(_grid[i][j]=='F') {
                _grid[i][j]='F';
                farmer[0]=i;
                farmer[1]=j;
            }
        }
    }
    for(counter=1;;counter++) {
        if(counter==1000) break;
        //out<<counter<<endl;
        move(farmer);
        move(cow);
//        out<<"F:"<<farmer[0]<<','<<farmer[1]<<'\t'<<farmer[2]<<"\t\t";
//        out<<"C:"<<cow[0]<<','<<cow[1]<<'\t'<<cow[2]<<endl;
        if(check(farmer,cow)) return 0;
    }
}
