#include <fstream>
#include <vector>
using namespace std;
#ifdef _WIN32
ifstream in("in.txt");
ofstream out("out.txt");
#else
ifstream in("preface.in");
ofstream out("preface.out");
#endif

