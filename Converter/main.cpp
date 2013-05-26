// (C) Joshua Netterfield 2009

#include <converter.h>
#include <iostream>
using namespace std;

int main( int argc, char **argv ) {

    if (argc < 2) {
        cout << "Usage: " << argv[0] << " filename\n";
        return 0;
    }

    Converter converter( (QString) argv[1]);
    converter.convert();
}
