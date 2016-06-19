#include <iostream>

void foo( int a, int b );
void foo( int a, int b, int c );
int main()
{
    foo( a:2, b:3 );
    foo( a:2, b:3, c:4 );
    return 0;
}

void foo( int a, int b )
{
    std::cout << "a : " << a << " b : " << b << '\n';
}
void foo( int a, int b, int c )
{
    std::cout << "a : " << a << " b : " << b << " c : " << c << '\n';
}
