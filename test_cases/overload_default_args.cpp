#include <iostream>

void foo( int a, int b, int c = 4 );
void foo( int a = 3 );

int main()
{
    foo( b:2, a:9 );
    foo( a:4 );
}

void foo( int a, int b, int c )
{
    std::cout << "a : " << a << " b : " << b << " c : " << c << '\n';
}
void foo( int a )
{
    std::cout << "a : " << a << '\n';
}
