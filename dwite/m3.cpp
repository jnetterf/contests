//#include <fstream>
//#include <vector>
//#include <stdlib.h>
//#include <algorithm>
//#include <map>
//#include <bitset>
//using namespace std;

//ifstream in("DATA3.txt");
//ofstream out("OUT3.txt");

////Brute Force / DFS

//struct Node {
//    static vector<Node*> _u;
//    static map<int, Node*> _u_c;
//    static Node* get(int a) {
//        Node*& n=_u_c[a];
//        if(!n) n=new Node;
//        return n;
//    }

//    bool visited;
//    vector<Node*> c;
//    static void clear() {
//        for(int i=0;i<_u.size();i++) {
//            _u[i]->visited=0;
//        }
//    }

//    static bool isCV() {
//        for(int i=0;i<_u.size();i++) {
//            if(!_u[i]->visited) return 0;
//        }
//        return 1;
//    }

//    void explore() {
//        if(visited) return;
//        visited=1;
//        for(int i=0;i<c.size();i++) {
//            if(c[i]) c[i]->explore();
//        }
//    }

//    void connect(Node* b) {
//        b->c.push_back(this);
//        c.push_back(b);
//    }

//    Node() : visited(0) {_u.push_back(this);}
//};

//vector<Node*> Node::_u;
//map<int, Node*> Node::_u_c;

//struct Edge {
//    Node* a,* b;
//    bool important() {
//        Node::clear();
//        int AI=-1,BI=-1;
//        for(int i=0;i<a->c.size();i++) {
//            if(a->c[i]==b) {
////                if(AI!=-1) return 0;
//                AI=i;
//                break;
//            }
//        }

//        for(int i=0;i<a->c.size();i++) {
//            if(b->c[i]==a) {
////                if(BI!=-1) return 0;
//                BI=i;
//                break;
//            }
//        }
//        a->c[AI]=0;
//        b->c[BI]=0;
//        Node::_u[0]->explore();
//        a->c[AI]=b;
//        b->c[BI]=a;
//        return !Node::isCV();
//    }
//    Edge(Node* ca, Node* cb) :a(ca), b(cb) { ca->connect(cb); }
//};

//vector<Edge*> e_u;

//int main() {
//    for(int i=0;i<5;i++) {
//        Node::_u.clear();
//        Node::_u_c.clear();
//        e_u.clear();
//        int C, B;
//        in>>C>>B;
//        for(int j=0;j<B;j++) {
//            int a, b;
//            in>>a>>b;
//            Node* na=Node::get(a);
//            Node* nb=Node::get(b);
//            e_u.push_back(new Edge(na,nb));
//        }
//        if(!C||!B) {
//            out<<0<<endl;
//            continue;
//        }
//        int r=0;
//        for(int j=0;j<e_u.size();j++) {
//            if(e_u[j]->important()) ++r;
//        }
//        out<<r<<endl;
//    }
//}


