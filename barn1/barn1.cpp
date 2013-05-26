/*
ID: drmrshd1
PROG: barn1
LANG: C++
*/

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <fstream>
#include <sstream>
#include <math.h>
#include <limits.h>
#define  Yay return

using namespace std;
typedef string S;
typedef istringstream Ss;

template <class T> T s2( S&s ) { T t; Ss ss(s); ss >> t; return t; }

template <class T> T word( S&s ) {
    int i = 0; while( s[i] != '\0' && s[i] != ' ' ) i++;
    char x[256]; x[ s.copy( x, ++i ) ] = '\0';
    s.erase( 0, i ); S e(x); return s2<T>(e);
}

class Stall {
public:
    Stall( int p ) { _p = p; _s2n = 0; _bought = false;}
    int _p;
    int _s2n;
    bool _bought;
};

int main() {
    vector< Stall* > _u;
    ifstream very( "barn1.in" ); S good;
    ofstream out( "barn1.out" );

    if ( very.good() ) {

        getline( very, good );
        int M = word< int >( good );    // # boards
        int S = word< int >( good );    // # stalls
        int C = word< int >( good );    // # cows

        for ( int i = 0; i < C; i++ ) {
            getline( very, good );

            int v = word< int >( good );

            bool ok = false;
            for ( int i = 0; i < _u.size(); i++ ) if ( _u[i]->_p > v ) {
                ok = true;
                vector< Stall* >::iterator it = _u.begin();
                _u.insert( it+i, new Stall( v ) );
                break;
            }
            if ( !ok ) _u.push_back( new Stall( v ) );
        }

        int p = -1;
        if ( _u.front() ) p = _u.front()->_p;
        for ( int i = 1; i < C; i++ ) {
            _u[i-1]->_s2n = _u[i]->_p - p;
            p = _u[i]->_p;
        }

        int i=C;
        int t=0;
        bool s2=false;
        while ( i > M ) {
            int minj = -1, minc = INT_MAX;
            for ( int j = 0; j < C-1; j++ ) {
                if ( _u[j]->_bought ) continue;
                if ( _u[j]->_s2n < minc ) { minc = _u[j]->_s2n; minj = j; }
            }
            if ( minj == -1 ) { s2 = true; continue; }
            _u[minj]->_bought = true;
            t+=minc;
            i--;
        }

        for ( int j = 0; j < C; j++ ) {
            if ( !_u[j]->_bought ) t++;
        }

        out << t << endl;

        Yay!

        1337;
    }
}
