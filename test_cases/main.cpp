#include <iostream>

template <typename T>
T add( T a, T b );
int main()
{
    std::cout << "Main\n";
    std::cout << add<int>( a:3, b:4 ); 
    std::cout << "\n";
    return 0;
}

template <typename T>
T add( T a, T b )
{
    return a+b;
}
