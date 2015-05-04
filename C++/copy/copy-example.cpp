
#include <iostream>

using namespace std;


class A {

public:
        A() { cout << "Constructing A." << endl; }
        ~A() { cout << "Destroying A." << endl; }

        A(const A& rhs) { cout << "copying A." << endl; }
        A &operator=(const A& rhs) { cout << "Assigning A." << endl; }
};



class B {

public:
        B() { cout << "Constructing B." << endl; }
        ~B() { cout << "Destroying B." << endl; }

private:
        A my_A;
};


class empty {};


int main( int argc, char *argv[] )
{
        B b;
        B c(b);
        B d = b;
        B e; e = b;
        cout << "main()" << endl;

        empty E;
        cout << "Our empty object has size " << sizeof(E) << endl;
}
