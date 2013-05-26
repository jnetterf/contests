/*
ID: drmrshd1
PROG: gift1
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

class Person {
public:
    static Person* get( S p ) {
        bool ok = false;
        int i; for ( i = 0; i < _us.size(); i++ ) if ( _us[i] == p ) { ok = true; break; }
        if ( ok ) return _u[i];
        else {
            _us.push_back( p );
            _u.push_back( new Person );
            return _u.back();
        }
    }

    Person() { _cash = 0; }

    int dist( int money, int ppl ) {
        if ( ppl == 0 ) return 0;

        _cash -= money - money % ppl ;
        return money/ppl;
    }

    int _cash;

    static vector< S > _us;
    static vector< Person* > _u;
};

vector< S > Person::_us;
vector< Person* > Person::_u;

int main() {
    ifstream very( "gift1.in" ); S good;
    ofstream out( "gift1.out" );

    if ( very.good() ) {
        getline( very, good );
        int NP = word< int >( good );

        for ( int i = 0; i < NP; i++ ) {
            getline( very, good );
            Person::get( word< S >( good ) );
        }

        for ( int i = 0; i < NP; i++ ) {
            getline( very, good );
            S p = word< S >( good );
            getline( very, good );
            int a = word< int >( good );
            int ppl = word< int >( good );
            int cash = Person::get( p )->dist( a, ppl );
            for ( int j = 0; j < ppl; j++ ) {
                getline( very, good );
                Person::get( word< S >( good ) )->_cash += cash;
            }
        }

        for ( int i = 0; i < Person::_u.size(); i++ ) {
            out << Person::_us[i] << " " << Person::_u[i]->_cash << "\n";
        }
    } else return 2;

    Yay!

    1337;
}
