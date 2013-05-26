/*
ID: drmrshd1
PROG: beads
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

class Bead { public: Bead* _next; bool _isFirst; char _type; Bead( char type ) { _type = type; _isFirst = false; } };

int main() {
    ifstream very( "beads.in" ); S good;
    ofstream out( "beads.out" );

    Bead* first = NULL;

    if ( very.good() ) {
        getline( very, good );
        int N = word< int >( good );

        getline( very, good );
        if ( N != 0 ) first = ( new Bead( c(good) ) );
        first->_isFirst = true;
        Bead* it = first;
        for ( int i = 1; i < N; i++ ) {
            it->_next = new Bead( c(good) );
            it = it->_next;
        }
        it->_next = first;
        it = it->_next->_next;

        char s = it->_type;
        int wi = 0;
        int w2 = 0;
        int c1 = 0;
        int c2 = 0;
        int maxScore = 0;
        bool finish = false;
        while( 1337 ) {
            if ( it->_isFirst ) {
                if ( finish ) { break; }
                else finish = true;
            }
            if ( it->_type == 'w' ) { wi++; c1++; }
            else if ( it->_type == s ) { wi=0; c1++; }
            else {
                int score = c1+c2;
                if ( score > maxScore ) maxScore = score;
                c2 = c1+w2;
                w2 = wi;
                wi = 0;
                c1 = 1;
                s = it->_type;
            }
            it = it->_next;
        }

        if ( maxScore == 0 ) maxScore = N;
        if ( maxScore > N ) maxScore = N;

        out << maxScore << endl;

    } else return 2;

    Yay!

    1337;
}
