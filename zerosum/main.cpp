/*
 PROB: zerosum
 LANG: C++
 USER: drmrshd1
*/

#include <fstream>
#include <vector>
using namespace std;
ifstream in("zerosum.in");
ofstream out("zerosum.out");

bool isZero(vector<char>&ops) {
    vector<int> nums;
    nums.push_back(1);
    for(int i=0;i<ops.size();i++) {
        if(ops[i]==' ') {
            if(nums.back()>0) nums.back()=nums.back()*10+(i+2);
            else nums.back()=nums.back()*10-(i+2);
        } else {
            nums.push_back(i+2);
        }
        if(ops[i]=='-') {
            nums.back()*=-1;
        }
    }

    int score=0;
    for(int i=0;i<nums.size();i++) {
        score+=nums[i];
    }
    return !score;
}
void print(vector<char>&ops) {
    if(isZero(ops)) {
        out<<1;
        for(int i=0;i<ops.size();i++) {
            out<<ops[i]<<i+2;
        }
        out<<endl;
    }
}

int N;

void recurse(vector<char>&i) {
    if(i.size()+1==N) print(i);
    else {
        if(!i.size()||(i.back()!=' ')){ i.push_back(' '); recurse(i); i.pop_back(); }
        i.push_back('+'); recurse(i); i.pop_back();
        i.push_back('-'); recurse(i); i.pop_back();
    }
}

int main() {
    in>>N;
    recurse(*(new vector<char>));
}
