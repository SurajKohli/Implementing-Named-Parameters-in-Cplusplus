#include <iostream>

void foo( int a, int b, int c = 4 );

int main()
{
    foo( a:1, b:2 );
    return 0;
}

void foo( int a, int b, int c )
{
    std::cout << "a : " << a << " b : " << b << " c : " << c << '\n';
}
