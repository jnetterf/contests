/*
ID: drmrshd1
PROG: milk
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

int main() {
    ifstream very( "milk.in" ); S good;
    ofstream out( "milk.out" );
    vector< pair<int, int> > _u;

    if ( very.good() ) {
        getline( very, good );
        int N = word< int >( good );
        int Ni = 0;
        int Nt = 0;
        int M = word< int >( good );

        for ( int i = 0; i < M; i++ ) {
            getline( very, good );
            int i1 = word< int >(good );
            pair<int, int> a( i1, word< int >( good ) );
            bool ok = false;
            vector< pair<int, int> >::iterator it = _u.begin();
            int i; for ( i = 0; i < _u.size(); i++ ) if ( _u[i].first > a.first ) { _u.insert( it + i, a ); ok = true; break; }
            if ( !ok ) _u.push_back( a );
        }

        vector< pair<int, int> >::iterator it = _u.begin();
        if ( it != _u.end() ) do {
            if ( Nt+it->second < N ) { Nt+=it->second; Ni+=(it->first*it->second); }
            else { Ni=Ni+((N-Nt)*it->first); break; }
        } while ( it++ != _u.end() );

        out << Ni << endl;
    }
}
