/*
ID: drmrshd1
PROG: transform
LANG: C++
*/

#include <iostream>
#include <string>
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

int tryTransform( int** a, int** b, bool r = false ) {
    int x = 0, y = 0;
    while ( 1 ) if ( !a[++x] ) break;
    y = x;

    int bx = 0, by = 0;
    while ( 1 ) if ( !b[++bx] ) break;
    by = x;

    bool ok = true;

    for ( int i = 0; i < x && ok ; i++ ) {
        for ( int j = 0; j < y; j++ ) {
            if ( b[i][j] != a[y-j-1][i] ) { ok = false; break; }
        }
    }

    if ( ok ) return 1;
    ok = true;

    for ( int i = 0; i < x && ok ; i++ ) {
        for ( int j = 0; j < y; j++ ) {
            if ( b[i][j] != a[x-i-1][y-j-1] ) { ok = false; break; }
        }
    }

    if ( ok ) return 2;
    ok = true;

    for ( int i = 0; i < x && ok ; i++ ) {
        for ( int j = 0; j < y; j++ ) {
            if ( b[i][j] != a[j][x-i-1] ) { ok = false; break; }
        }
    }

    if ( ok ) return 3;
    ok = true;

    for ( int i = 0; i < x && ok ; i++ ) {
        for ( int j = 0; j < y; j++ ) {
            if ( b[i][j] != a[i][y-j-1] ) { ok = false; break; }
        }
    }

    if ( ok ) return 4;
    ok = false;

    if ( r ) return 0;

    int* c[x+1];
    for ( int i = 0; i < x; i++ ) c[i] = new int[x];
    c[x] = NULL;
    for ( int i = 0; i < x  ; i++ ) {
        for ( int j = 0; j < y; j++ ) {
            c[i][j] = a[i][y-j-1];
            cerr << a[i][y-j-1];
        }
        cerr <<endl;
    }
    int c2 = tryTransform( b, c, true );
    if ( c2 && c2 < 4 ) return 5;
    cerr << c2 << endl;

    ok = true;
    for ( int i = 0; i < x && ok ; i++ ) {
        for ( int j = 0; j < y; j++ ) {
            if ( b[i][j] != a[i][j] ) { ok = false; break; }
        }
    }

    if ( ok ) return 6;
    else return 7;

}

int main() {
    ifstream very( "transform.in" ); S good;
    ofstream out( "transform.out" );

    if ( very.good() ) {
        getline( very, good );
        int N = word< int >( good );
        int* a[N+1];
        for ( int i = 0; i < N; i++ ) a[i] = new int[N];
        a[N] = NULL;
        int* b[N+1];
        for ( int i = 0; i < N; i++ ) b[i] = new int[N];
        b[N] = NULL;

        for ( int i = 0; i < N; i++ ) {
            getline( very, good );
            for ( int j = 0; j < N; j++ ) {
                char x = c( good );
                if ( x == '@' ) a[i][j] = 1;
                else if ( x == '-' ) a[i][j] = 0;
                else out << "UNDEF SYMBOL!\n";
            }
        }
        for ( int i = 0; i < N; i++ ) {
            getline( very, good );
            for ( int j = 0; j < N; j++ ) {
                char x = c( good );
                if ( x == '@' ) b[i][j] = 1;
                else if ( x == '-' ) b[i][j] = 0;
                else out << "UNDEF SYMBOL!\n";
            }
        }

        out << tryTransform( (int**) a, (int**) b ) << endl;
    }
}
