
#include <iostream>

struct Vec
{
    int a{0};
};


class Base
{
public:
    Base(){ a.a = 5; }

protected:
    Vec a;
};

class Der : public Base
{
public:
    Der()
    {

    }

    void foo()
    {
        std::cout << "a.a: " << a.a << std::endl;
    }

};

int main()
{
    Der a;

    a.foo();
}