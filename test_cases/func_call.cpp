#include <iostream>

void foo( int a, int b );

int main()
{
    foo( a:2, b:3 );
    return 0;
}

void foo( int a, int b )
{
    std::cout << "a+b : " << a+b << '\n';
}
