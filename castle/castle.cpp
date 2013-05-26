/*
 ID: drmrshd1
 PROG: castle
 LANG: C++
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <math.h>
#define Yay return
using namespace std;
typedef int z;
typedef void f;
typedef string S;
ifstream in("castle.in");
ofstream out("castle.out");

class Room;
Room* r[51][51]={{NULL}};
z rc=0, rcl=-1;
Room* u[51]={NULL};

class Room {public:
    Room(){ u[++rcl]=this;id=rcl; rc++; }
    z id;
    vector<z> vy;
    vector<z> vx;
    f addRoom(z y,z x){
        vy.push_back(y);
        vx.push_back(x);
    }
    z getSize(){return vy.size();}
    z getRWSize(z&Tx,z&Ty,z&Tdir){
        Tx=999;Ty=0;
        z maxSize=0;
        for(z i=0;i<nU.size();i++){
            //if(!u[nU[i]]) cerr<< i << ' ' << nU[i] << "DAN\n";
            if(u[nU[i]]==this) continue;
            z x = u[nU[i]]->getSize();
            //out << ":D" << x << ' ' << nx[i] << ' ' << ny[i] << endl;
            if( x > maxSize) {
                Tx=nx[i];
                Ty=ny[i];
                Tdir=ndir[i];
                maxSize=x;
            } else if (x==maxSize){//WEST AND THEN SOUTH
                if(nx[i]<Tx ||(nx[i]==Tx&&ny[i]>Ty)) {Tx=nx[i];Ty=ny[i];Tdir=ndir[i];}
            }
        }
        //if(getSize()+maxSize>15)return 0;
        return getSize()+maxSize;
    }

    vector<z> nx, ny, ndir;
    vector<z> nU;
    f addNeighbour(z y,z x, z dir,Room*r){
        if(r==this)return;
        //out << y << ' ' << x << ' ' << ' ' << dir << endl;
        nx.push_back(x);
        ny.push_back(y);
        ndir.push_back(dir);
        nU.push_back(r->id);
    }
    f merge(Room* rx){
        rc--;
        for(z i=0;i<rx->getSize();i++){
            this->addRoom(rx->vy[i], rx->vx[i]);
        }
        for(z i=0;i<rx->nU.size();i++){
            this->addNeighbour(rx->ny[i], rx->nx[i], rx->ndir[i], u[rx->nU[i]] );
        }
        for(z i=0;i<50;i++){
            for(z j=0;j<50;j++){
                if(r[i][j]==rx){r[i][j]=this;}
            }
        }
        for(z i=0;i<50;i++)if(u[i]==rx){u[i]=this;}
        delete rx;
    }
};

z main(){ z map[50][50], M, N;
    for(z i=0;i<50;i++)for(z j=0;j<50;j++)r[i][j]=NULL;
    if(!in.good()){cerr<<"Couldn't open fiel.\n";return 1;}
    in>>N; in>>M;
    for(z i=0;i<M;i++){
        for(z j=0;j<N;j++){ z t;
            in>>t;
            map[i][j] = 0x1111;
            if(t>=8){t-=8;map[i][j]&=~0x0001;}   //S
            if(t>=4){t-=4;map[i][j]&=~0x0010;}   //E
            if(t>=2){t-=2;map[i][j]&=~0x0100;}   //N
            if(t>=1){t-=1;map[i][j]&=~0x1000;}   //W
            //cerr<< hex << map[i][j] << ' ';
        }
        //cerr<<endl;
    }
    for(z i=0;i<M;i++){
        for(z j=0;j<N;j++){
            if(map[i][j]&0x1000 && (map[i][j]&0x0100) ) {//no N or W
                //cerr << "NW! ";
                r[i][j]=r[i-1][j];
                r[i][j]->addRoom(i,j);
                if(r[i][j]!=r[i][j-1]) r[i][j]->merge(r[i][j-1]);
            } else if(map[i][j]&0x0100){//no N
                //cerr << "N ! ";
                r[i][j]=r[i-1][j];
                r[i][j]->addRoom(i,j);
                if(j)r[i][j-1]->addNeighbour(i+1,j,1,r[i][j]);
            } else if(map[i][j]&0x1000){//no W
                //cerr << "W ! ";
                r[i][j]=r[i][j-1];
                r[i][j]->addRoom(i,j);
                if(i)r[i-1][j]->addNeighbour(i+1,j+1,0,r[i][j]);
            } else {
                //out << i+1 << ' ' << j+1 << endl;
                //cerr << "  ! ";
                r[i][j]=new Room;
                r[i][j]->addRoom(i,j);
                if(j) r[i][j-1]->addNeighbour(i+1,j,1,r[i][j]);
                if(i) r[i-1][j]->addNeighbour(i+1,j+1,0,r[i][j]);
            }
        }
        //cerr<<endl;
    }
    out << dec << rc << endl;
    z rmax=0; z pmax=0,ta,tb,tc;
    for(z i=0;i<50;i++){ z a,b,c;
        if(!u[i])continue;
        if(u[i])rmax=max(u[i]->getSize(),rmax);
        if(u[i]){
            z x =u[i]->getRWSize(a,b,c);
            if(x>pmax){
                ta=a;tb=b;tc=c;
                pmax=x;
            } else if(x==pmax && (a<ta ||(ta==a&&b>tb)) ){
                ta=a;tb=b;tc=c;
            }
        }
    }
    out<< rmax<<endl;
    out<< pmax<<endl;
    if(!tc) {
        out<< tb << ' ' << ta << ' ';
        out<<"N\n";
    } else {
        out<< tb << ' ' << ta << ' ';
        out<<"E\n";
    }
    /*for(z i=0;i<M;i++){
        for(z j=0;j<N;j++){
            out<<r[i][j]->id<< ' ';
        }
        out<<endl;
    }*/
    out.close();
    //system("pause");
}
