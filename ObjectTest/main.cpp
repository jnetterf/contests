// Unit Test for LiveObject

#include <QtCore/QCoreApplication>

#include "LiveObject.h"

class B : public LiveObject { public:
    B() : LiveObject("B") {}
};

class A : public LiveObject { public:
    A() : LiveObject("A") {
        addChildPointer(_b, new B);
        addChildPointer(_b2, new B);
        delete _b2;
        LD() << hex <<(int)&_b2;
        delete _b2;
    }
    B* _b;
    B* _b2;
};

class AGUI : public LiveObjectGUI<A> { public:
    AGUI(A* d) : LiveObjectGUI<A>("AGui",d) {}
};

int main(int argc, char **argv) {
    QCoreApplication a(argc, argv);
    A* main = new A;
    AGUI* gui = new AGUI(main);
    delete main;
    delete gui;
    LiveObject::reportActive();
    system("pause");
    //return a.exec();
}
