/*
ID: drmrshd1
PROG: packrec
LANG: C++
*/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <limits.h>
using namespace std;
typedef string S;
typedef istringstream Ss;
typedef int i;
template<class T> T s2( S s ) { Ss ss(s); T t; ss >> t; return t; }
template<class T> T word( S&s ) {
    S l; do { l = s[0] + l; s.erase(0,1); } while ( s[0] != '\0' && s[0] != ' ' );
    return s2<T>(l);
}

class R{public:R(i w,i h){_w=w;_h=h;}i _w; i _h;R b(i v){R t(_h,_w);if (v) return t;return *this;}};

i max(i a,i b) { if ( a > b ) return a; else return b;  }
i max(i a,i b,i c ) { return max( max(a,b), c ); }
i max(i a,i b,i c, i d){return max(max(a,b),max(c,d));}
i sum(i a,i b) { return a+b;}
i sum(i a,i b,i c) { return a+b+c;}
i sum(i a,i b,i c,i d){return a+b+c+d;}

R c1(R& a,R& b,R& c,R& d) {
    i w = sum(a._w, b._w, c._w, d._w);
    i h = max(a._h, b._h, c._h, d._h);
    //cout << "$" << a._w << ' ' << b._w << ' ' << c._w << ' ' << d._w << endl;
    //cout << "!1 " << w << ' ' << h << endl;
    return R(w,h);
}

R c2(R&a,R&b,R&c,R&d) {
    i w = max( sum(a._w, b._w, c._w), d._w );
    i h = sum( max(a._h,b._h,c._h), d._h );
    //cout << "!2 " << w << ' ' << h << endl;
    return R(w,h);
}

R c3(R&a,R&b,R&c,R&d) {
    i w = sum( max( sum( a._w, b._w ), c._w ), d._w );
    i h = max( sum( max(a._h, b._h), c._h ), d._h );
    //cout << "!3 " << w << ' ' << h << endl;
    return R(w,h);
}

R c4(R&a,R&b,R&c,R&d) {
    i w = sum( a._w, max( b._w, c._w ), d._w );
    i h = max( a._h, sum( b._h, c._h ), d._h );
    //cout << "!4 " << w << ' ' << h << endl;
    return R(w,h);
}

R c6(R&a,R&b,R&c,R&d) { //WTF!?!Y!@H*)FD
    i w = max(sum(a._w,b._w),sum(c._w,d._w));
    i h = max(sum(a._h,c._h),sum(b._h,d._h));
    // AND HERE IS THE TRICK!!!
    if (a._h < b._h) w = max(w, c._w+b._w);
    if (a._h+c._h > b._h) w = max(w, c._w+d._w);
    if (b._h < a._h) w = max(w, a._w+d._w);
    w = max(w, c._w);
    w = max(w, d._w);
    //cout << "!6 " << w << ' ' << h << endl;
    return R(w,h);
}

int bA = INT_MAX;
vector< R > _x;

void record( R x ) {    // code which should be mindless
    i a = x._h*x._w;
    //cout << a << ' ' << x._h << "," << x._w << endl;
    //if ( a == 80 ) { cout << "#####################################################\n"; cin >> a; }
    bool check = false;
    if ( a < bA ) {
        _x.erase( _x.begin(), _x.end() );
        bA = a;
        check = true;
    } else if ( a == bA || check ) {
        if ( x._h > x._w ) x = x.b(1);
        vector< R >::iterator it = _x.begin();
        if ( !_x.size() ) { _x.push_back( x ); return; }
        else for ( i j = 0; j < _x.size(); j++ ) {
            if ( x._w == _x[j]._w ) { return; }
            if ( x._w > _x[j]._w ) break;
            ++it;
        }
        _x.insert( it, x );
    }
}

void ca(R&a,R&b,R&c,R&d) {  // record possibilites (5)
    record(c1(a,b,c,d));
    record(c2(a,b,c,d));
    record(c3(a,b,c,d));
    record(c4(a,b,c,d));
        //c4=c5
    record(c6(a,b,c,d));
}

void dp(R a,R b,R c,R d, bool x = true) {   // do permutations (4!)^...
    //cout << "~" << a._w << b._w << c._w << d._w << endl;
    ca(a,b,c,d); ca(a,b,d,c);
    ca(a,c,b,d); ca(a,c,d,b);
    ca(a,d,b,c); ca(a,d,c,b);

    if( !x ) {
        dp(b,a,c,d);
        dp(c,a,b,d);
        dp(d,a,b,c);
    }
}

void id(R&a,R&b,R&c,R&d) {  // check inverses (2^4)^...
    for(i j = 0; j < 2; j++ ) for(i k = 0; k < 2; k++ ) for(i l = 0; l < 2; l++ ) for(i m = 0; m < 2; m++ )
        dp( a.b(j), b.b(k), c.b(l), d.b(m), false );
}

int main() {
    ifstream file("packrec.in");
    ofstream out("packrec.out");
    if(!file.good()) return 8;
    S line;
    getline(file,line);int x1 = word<int>(line); R a(x1, word<int>(line));
    getline(file,line);x1 = word<int>(line); R b(x1, word<int>(line));
    getline(file,line);x1 = word<int>(line); R c(x1, word<int>(line));
    getline(file,line);x1 = word<int>(line); R d(x1, word<int>(line));
    id(a,b,c,d);
    out << bA << endl;
    for ( i j = 0; j < _x.size(); j++ ) out << _x[j]._h << ' ' << _x[j]._w << endl;
    out.close();
    return 0;
}
