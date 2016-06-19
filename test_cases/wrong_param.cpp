#include <iostream>

void foo( int a, int b );

int main()
{
    foo( a:4, c:4 );
    return 0;
}

void foo( int a, int b )
{
    std::cout << "a+b : " << a+b << '\n';
}
