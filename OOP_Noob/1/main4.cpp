#include <iostream>
#include <cmath>
using namespace std;

class myPoint
{
public:
    myPoint(double x0 = 0.0, double y0 = 0.0) : x(x0), y(y0) { cout << "Start" << endl; }
    myPoint(myPoint &np) : x(np.x), y(np.y) {}
    double GetX() { return x; }
    double GetY() { return y; }
    void SetX(double x0) { x = x0; }
    void SetY(double y0) { x = y0; }
    void SetPoint(double x0, double y0)
    {
        x = x0;
        y = y0;
    }
    void SetPoint(myPoint &np)
    {
        x = np.x;
        y = np.y;
    }
    double GetLength(myPoint p)
    {
        return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
    }
    void Printit() { cout << " (" << x << "," << y << ") "; }

private:
    double x, y;
};

int main(void)
{
    myPoint p1, p2(0, 1), p3(1, 0);
    p1.Printit();
    p2.Printit();
    p3.Printit();
    cout << endl;
    double a, b, c, d, e;
    a = p2.GetLength(p1);
    b = p3.GetLength(p1);
    c = p2.GetLength(p3);
    cout << a << endl;
    cout << b << endl;
    cout << c << endl;
    d = (1 / 2) * (a + b + c);
    e = sqrt(d * (d - a) * (d - b) * (d - c));
    cout << d << endl;
    cout << e << endl;
    return 0;
}
