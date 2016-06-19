#include <iostream>

class A
{
    public:
        void foo( int a, int b )
        {
            std::cout << "a : " << a << " b : " << b << '\n';
        }
};

class B : public A
{
    public:
        void bar( int a, int b )
        {
            std::cout << "a : " << a << " b : " << b << '\n';
        }
};

int main()
{
    B b;
    b.foo( a:2, b:3 );
    return 0;
}


