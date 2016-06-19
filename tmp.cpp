#include <iostream>

void foo( int a, int b, int c = 4 );

int main()
{
    foo(1,2,4 );
    return 0;
}

void foo( int a, int b, int c )
{
    std::cout << "a : " << a << " b : " << b << " c : " << c << '\n';
}
