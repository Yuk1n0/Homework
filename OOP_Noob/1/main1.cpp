#include <iostream>
using namespace std;

class MyClass
{
public:
    MyClass()
    {
        x = 0;
        y = 0;
    }
    MyClass(int a = 0, int b = 0);
    void Print();

private:
    int x, y;
};

MyClass::MyClass(int a, int b)
{
    x = a;
    y = b;
}

void MyClass::Print()
{
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;
}

int main(void)
{
    MyClass obj1(1, 3), obj2(5, 8);
    obj1.Print();
    obj2.Print();
    return 0;
}
