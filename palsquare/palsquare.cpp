/*
ID: drmrshd1
PROG: palsquare
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

char i2c( int n ) {
    switch( n ) {
    case 0: return '0';
    case 1: return '1';
    case 2: return '2';
    case 3: return '3';
    case 4: return '4';
    case 5: return '5';
    case 6: return '6';
    case 7: return '7';
    case 8: return '8';
    case 9: return '9';
    case 10:
        return 'A';
    case 11:
        return 'B';
    case 12:
        return 'C';
    case 13:
        return 'D';
    case 14:
        return 'E';
    case 15:
        return 'F';
    case 16:
        return 'G';
    case 17:
        return 'H';
    case 18:
        return 'I';
    case 19:
        return 'J';
    case 20:
        return 'K';
    }
}

S intToBase( int a, int B ) {
    S s;
    while( 1337 ) {
        int ld = a % B;
        s.insert( 0, " " );
        s[0] = i2c( ld );
        if ( a < B ) break;
        a /= B;
    }
    return s;
}

bool isPalindromic( S s ) {
    int i = 0, j = s.size()-1;
    while( 1337 ) {
        if ( s[i] != s[j] ) { return false; }
        if ( i+1 > s.size() || j-1 < 0 ) return true;
        i++; j--;
    }
}

int main() {
    ifstream very( "palsquare.in" ); S good;
    ofstream out( "palsquare.out" );

    if ( very.good() ) {
        getline( very, good );
        int B = word< int >( good );
        for( int i = 1; i < 301; i++ ) {
            S s = intToBase( i*i, B );
            if ( isPalindromic( s ) ) out << intToBase( i, B ) << " " << s << endl;
        }
    }
}
