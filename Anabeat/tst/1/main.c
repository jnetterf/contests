#include <iostream>

int main() {
	std::cerr << "\n";
	int a[15] = { 4, 4, 3, 2, 4, 4, 4, 3, 2, 4, 4, 4, 3, 2, 4 };
	for ( int i = 0; i < 15; i++ ) a[i] = i;

	for ( int s = 0; s < 8; s++) {
		for (int p = 1; p < 8; p++) {
			std::cerr << " " << s << "," << p << ":";
			for ( int i = 0; i < 15; i++ ) {
				if ( (a[i] - s) % p == 0 ) std::cerr << "1";
				else std::cerr << " ";
			}
		}	
		std::cerr << "|\n";
	}
}
