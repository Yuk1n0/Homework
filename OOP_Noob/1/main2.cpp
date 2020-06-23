#include <iostream>
using namespace std;

class Test
{
public:
    Test()
    {
        x = 0;
        y = 0;
        area = 0;
        p = 0;
    }
    Test(float i, float j) : x(i), y(j)
    {
        area = 0;
        p = 0;
    }
    void Area() { area = x * y; }
    void P() { p = 2 * (x + y); }
    void Print() { cout << "面积为：" << area << "周长为：" << p << endl; }

private:
    float x, y, area, p;
};

int main(void)
{
    Test a(20, 50), b(3.6, 4.5);
    a.Area();
    a.P();
    b.Area();
    b.P();
    a.Print();
    b.Print();
    return 0;
}
