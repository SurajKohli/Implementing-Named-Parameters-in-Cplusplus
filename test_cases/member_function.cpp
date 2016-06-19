#include <iostream>

class Foo
{
    public:
    void bar( int a, int b )
    {
        std::cout << "Bar\n";
    }
};

int main()
{
    Foo f;
    f.bar( a:4, b:5 );
    return 0;
}
