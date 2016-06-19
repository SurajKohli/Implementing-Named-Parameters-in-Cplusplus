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
    Foo *f;
    f = new Foo();
    f->bar( a:2, b:3 );
    return 0;
}
