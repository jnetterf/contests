/*
ID: drmrshd1
PROG: milk2
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
    ifstream very( "milk2.in" ); S good;
    ofstream out( "milk2.out" );

    vector< pair<int,bool> > _data;

    if ( very.good() ) {
        getline( very, good );
        int N = word< int >( good );
        for ( int i = 0; i < N; i++ ) {
            getline( very, good );

            int start = word< int >( good );
            bool ok = false;
            pair<int,bool> a;
            a.first = start;
            a.second = true;
            for ( int i = 0; i < _data.size(); i++ ) {
                if ( _data[i].first > start ) {
                    vector< pair<int,bool> >::iterator it = _data.begin();
                    _data.insert( it+i, a );
                    ok = true;
                    break;
                }
            }
            if ( !ok ) _data.push_back( a );
            ///////////////////////

            int end = word< int >( good );
            ok = false;
            pair<int,bool> b;
            b.first = end;
            b.second = false;
            for ( int i = 0; i < _data.size(); i++ ) {
                if ( _data[i].first > end ) {
                    vector< pair<int,bool> >::iterator it = _data.begin();
                    _data.insert( it+i, b );
                    ok = true;
                    break;
                }
            }
            if ( !ok ) _data.push_back( b );

        }

        int contMilkMax = 0;
        int contMilk = 0;
        int contIdleMax = 0;
        int contIdle = 0;
        int t = 0;
        int count = 0;
        for ( int i = 0; i < _data.size(); i++ ) {
            if ( i && _data[i].first != _data[i-1].first ) {
                if ( !count ) {
                    if ( contMilk > contMilkMax ) contMilkMax = contMilk;
                    contMilk = 0;
                    contIdle += _data[i].first-t;
                } else {
                    if ( contIdle > contIdleMax ) contIdleMax = contIdle;
                    contIdle = 0;
                    contMilk += _data[i].first-t;
                }
            }

            if ( _data[i].second == true ) count++;
            else count--;

            t = _data[i].first;
        }
        out << max( contMilk, contMilkMax ) << " " << max( contIdle, contIdleMax ) << "\n";
    }
}
