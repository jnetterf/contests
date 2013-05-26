/*
ID: drmrshd1
PROG: namenum
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
    s.erase( 0, i ); S e(x);

    return s2<T>(e);
}

char c( S&s ) {
    int i = 0;
    char x[1]; s.copy( x, ++i );
    s.erase( 0, i );

    return x[0];
}

vector< char > namenum( char a ) {
    vector< char > nn;
    switch( a ) {
    case '2':
        nn.push_back( 'A' );
        nn.push_back( 'B' );
        nn.push_back( 'C' );
        break;
    case '3':
        nn.push_back( 'D' );
        nn.push_back( 'E' );
        nn.push_back( 'F' );
        break;
    case '4':
        nn.push_back( 'G' );
        nn.push_back( 'H' );
        nn.push_back( 'I' );
        break;
    case '5':
        nn.push_back( 'J' );
        nn.push_back( 'K' );
        nn.push_back( 'L' );
        break;
    case '6':
        nn.push_back( 'M' );
        nn.push_back( 'N' );
        nn.push_back( 'O' );
        break;
    case '7':
        nn.push_back( 'P' );
        nn.push_back( 'R' );
        nn.push_back( 'S' );
        break;
    case '8':
        nn.push_back( 'T' );
        nn.push_back( 'U' );
        nn.push_back( 'V' );
        break;
    case '9':
        nn.push_back( 'W' );
        nn.push_back( 'X' );
        nn.push_back( 'Y' );
        break;
    }
    return nn;
}

int main() {
    ifstream really( "dict.txt" );
    ifstream very( "namenum.in" ); S good;
    ofstream out( "namenum.out" );
    list< S > dict;

    while ( really.good() ) {
        getline( really, good );
        dict.push_back( word< S >( good ) );
    }
    if ( !very.good() ) return -1;
    getline( very, good );
    S a = word< S >( good );

    list< S >::iterator it = dict.begin();
    while ( it != dict.end() ) {
        if ( a.size() != it->size() ) it = dict.erase( it );
        else it++;
    }

    for ( int j = 0; j < a.size(); j++ ) {
        it = dict.begin();
        vector< char > c = namenum( a[j] );
        while ( it != dict.end() ) {
            bool ok = false;
            for ( int k = 0; k < c.size(); k++ ) {
                if ( (*it)[j] == c[k] ) { ok = true; break; }
            }
            if ( !ok ) {
                it = dict.erase( it );
            } else { it++; }
        }
    }

    it = dict.begin();
    while ( it != dict.end() ) { out << *it << endl; it++; }
    if ( !dict.size() ) out << "NONE\n";
}
