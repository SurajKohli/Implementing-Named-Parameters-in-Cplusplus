#include <iostream>

template <typename T>
T add( T a, T b );

int main()
{
    auto res = add(a:3, b:4);
    std::cout << res << std::endl;
    return 0;
}

template <typename T>
T add( T a, T b )
{
    return a+b;
}
