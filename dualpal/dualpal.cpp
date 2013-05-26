/*
ID: drmrshd1
PROG: dualpal
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
    for( int t = 0; t < s.size()/2+1; t++ ) {
        if ( s[i] != s[j] ) { return false; }
        if ( i+1 > s.size() || j-1 < 0 ) return true;
        i++; j--;
    }
    return true;
}

int main() {
    ifstream very( "dualpal.in" ); S good;
    ofstream out( "dualpal.out" );

    if ( very.good() ) {
        getline( very, good );
        int N = word< int >( good );
        int Ni = 0;
        int S = word< int >( good );
        int Si = S;
        while( Si++ ) {
            int gc = 0;
            //out << "Check " << Si << endl;
            for( int i = 2; i < 11; i++ ) {
                if ( isPalindromic( intToBase( Si, i ) ) ) {
                    if ( ++gc > 1 ) {
                        out << Si << endl;
                        Ni++;
                        if ( Ni >= N ) { Yay! 1337;  }
                        break;
                    }
                }
            }
        }
    }
}
