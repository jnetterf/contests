/*
ID: drmrshd1
PROG: calfflac
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

ofstream out( "calfflac.out" );

template <class T> T s2( S&s ) { T t; Ss ss(s); ss >> t; return t; }

template <class T> T word( S&s ) {
    int i = 0; while( s[i] != '\0' && s[i] != ' ' ) i++;
    char x[256]; x[ s.copy( x, ++i ) ] = '\0';
    s.erase( 0, i ); S e(x); return s2<T>(e);
}

int c2i( char c ) {
    if ( c < 65 || c > 122 ) return -1;
    if ( c < 91 ) return c-65;
    if ( c < 97 ) return -1;
    return c-97;

    return c;
}

vector<S> _s;
vector< int > _n;

bool isPalindrone( int a, int l ) {
    for ( int i = 0; i < l/2+1; i++ ) {
        if ( _n[i+a] != _n[(a+l)-i] ) return false;
    }
    return true;
}

int _l[26];

bool doCheck( int l ) {
    for ( int i = 0; i < 26; i++ ) { _l[i] = 0; }
    for ( int i = 0; i < min(l, (int)_n.size()) ; i++ ) {
        _l[ _n[i] ]++;
    }

    for ( int i = 0; i+l<=_n.size(); i++ ) {
        if ( i+l < _n.size() ) _l[ _n[i+l] ]++;
        bool chance = false;
        bool ok = true;
        for ( int i = 0; i < 26; i++ ) if ( _l[i] % 2 ) {
            if ( chance ) { ok = false; break; }
            chance = true;
        }
        if ( !ok ) {         _l[ _n[i] ]--; continue; }
        if ( isPalindrone( i, l ) ) {
            S s;
            int c = 0;
            for ( int v = 0; v <= l+c; v++ ) {
                S a = _s[i+v];
                bool ok = false;
                while ( a.size() ) {
                    if ( ( (c2i( a[ a.size()-1] ) != -1 ) ) &&
                         ( _n[i+v-c] == c2i( a[a.size()-1] ) ) ) { ok = true; break; } a.erase( a.size()-1 ); }
                if ( !ok ) {
                    c++; continue;
                }
                s += _s[i+v];
            }
            while ( s.size() && (c2i( s[ s.size()-1 ] ) == -1) ) s.erase( s.size()-1 );
            out << l+1 << endl << s << endl;
            return true;
        }
        _l[ _n[i] ]--;
    }
    //cerr << falseCand << endl;
    return false;
}

int main() {
    ifstream very( "calfflac.in" ); S good;

    if ( very.good() ) {
        getline( very, good );
        S crry, prev;
        do {
            if ( crry.size() ) crry += "\n";

            for ( int i = 0; i < good.size(); i++ ) {
                if ( c2i( good[i] ) != -1 ) { if ( prev.size() ) _s.push_back( prev ); _n.push_back( c2i( good[i]) ); prev=crry; crry= good[i];; }
                else { crry += good[i]; }
            }
        } while ( getline( very, good ) && very.good() );
        _s.push_back( prev );
        _s.push_back( crry );

        for ( int i = min((int)_n.size(),2000); i >= 0; i-- ) {
            if ( doCheck( i ) ) { break; }
        }

        Yay!
        1337;
    }
}
