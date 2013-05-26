/*
ID: drmrshd1
PROG: crypt1
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
ofstream out( "crypt1.out" );

template <class T> T s2( S&s ) { T t; Ss ss(s); ss >> t; return t; }

template <class T> T word( S&s ) {
    int i = 0; while( s[i] != '\0' && s[i] != ' ' ) i++;
    char x[256]; x[ s.copy( x, ++i ) ] = '\0';
    s.erase( 0, i ); S e(x); return s2<T>(e);
}

/*
   A B C
x    D E
 -------
   F G H         <-- partial product 1
 I J K           <-- partial product 2
 -------
 V M N H
*/

int X;
vector< int > N;    // set of numbers we're checking for.

bool isGood( int a ) {
    for ( int i = 0; i < X; i++ ) if ( a == N[i] ) return true;
    return false;
}

bool doCheck( int A, int B, int C, int D, int E ) {
    // Check H and I first. Most promenant.
    int H = (E*C)%10;
    if ( !isGood( H ) ) return false;

    int I = (D*A + (D*B+(D*C)/10)/10 ) ; // no mod
    if ( I > 9 || !isGood( I ) ) return false;

    // Now check F,G,J, and K
    int G = ((E*B)+(E*C)/10)%10;
    if ( !isGood(G) ) return false;

    int F = ((E*A)+((E*B)+(E*C)/10)/10);
    if ( F > 9 || !isGood(F) ) return false;

    int K = ( D*C )%10;
    if ( !isGood(K) ) return false;

    int J = (D*B+(D*C)/10)%10;
    if ( !isGood(J) ) return false;

    // Now check M,N,V
    int N = (G+K)%10;
    if ( !isGood(N) ) return false;

    int M = (F+J+(G+K)/10)%10;
    if ( !isGood(M) ) return false;

    int V = (F+J)/10+I;
    //out << "V is " << V << endl;
    if ( V > 9 || !isGood(V) ) return false;

    //out << "  " << F << G << H << endl;
    //out << " "  << I << J << K << endl;
    //out << "%" << V << M << N << H << endl;

    // and thus by exclusion
    return true;
}

int main() {
    ifstream very( "crypt1.in" ); S good;

    if ( very.good() ) {
        getline( very, good );
        X = word< int >( good );

        getline( very, good );
        for ( int i = 0; i < X; i++ ) {
            N.push_back( word< int >( good ) );
            //out << "!!" << N.back() << endl;
        }

        int count = 0;
        for ( int a = 0; a < X; a++ ) {
            for ( int b = 0; b < X; b++ ) {
                for ( int c = 0; c < X; c++ ) {
                    for ( int d = 0; d < X; d++ ) {
                        for ( int e = 0; e < X; e++ ) {
                            if ( doCheck(N[a],N[b],N[c],N[d],N[e]) ) {
                                //out << N[a] << N[b] << N[c] << endl << ' ' << N[d] << N[e] << endl << endl;
                                count++;
                            }
                        }
                    }
                }

            }
        }
        out << count << endl;

        Yay!
        1337;
    }
}
