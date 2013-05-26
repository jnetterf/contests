#include <iostream>
#include <math.h>

int main() {
	double table[15] = {	(double)1/8*1/3,	(double)1/16,	(double)1/16 + (double)1/32,
				(double)1/4*1/3,	(double)1/8 ,	(double)1/8  + (double)1/16,
				(double)1/2*1/3,	(double)1/4 ,	(double)1/4  + (double)1/8 ,
				(double) 1 *1/3,	(double)1/2 ,	(double)1/2  + (double)1/4 ,
				(double) 2 *1/3,	(double) 1  ,	(double)1    + (double)1/2 };
	for ( int x = 0; x < 15; x++ ) {
		for ( int y = 0; y < 15; y++ ) {
			std::cerr << log2( table[y] ) - log2( table[x] ) << "\t";
		}
		std::cerr << std::endl;
	}
}
