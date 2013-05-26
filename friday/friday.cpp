/*
ID: drmrshd1
PROG: friday
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

int main() {
    ifstream very( "friday.in" ); S good;
    ofstream out( "friday.out" );

    int count[7]; for ( int i = 0; i < 7; i++ ) count[i] = 0;

    if ( very.good() ) {
        getline( very, good );
        int years = word< int >( good );

        int fd = 2;
        for ( int y = 1900; y-1900 < years; y++ ) {
            for ( int m = 0; m < 12; m++ ) {
                count[ (fd+13-1) % 7 ]++;

                switch( m ) {
                case 0: //j
                case 2: //m
                case 4: //may
                case 6: //july
                case 7: //aug
                case 9: //oct
                case 11://dec
                    fd = (fd+32-1)%7;
                    break;
                case 1:
                    if ( (y % 100 == 0 && y % 400 == 0) || (y % 100 && y % 4 == 0) ) fd = (fd+30-1)%7;
                    else fd = (fd+29-1)%7;
                    break;
                default:
                    fd = (fd+31-1)%7;
                    break;
                }
            }
        }

        for ( int i = 0; i < 6; i++ ) out << count[i] << " ";
        out << count[6] << "\n";

    } else return 2;

    Yay!

    1337;
}
