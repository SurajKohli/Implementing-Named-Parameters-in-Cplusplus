#include <iostream>

void foo( int a, int b );

class A
{
    A() : foo_(2) { }
    int foo_;
    friend void foo( int a, int b );
};

void foo( int a, int b )
{
    A a();
    std::cout << "Friend function\n";
}

int main()
{
    foo( a:2, b:2 );
    return 0;
}
