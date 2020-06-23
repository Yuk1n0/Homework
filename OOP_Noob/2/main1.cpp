#include <iostream>
#include <cmath>

using namespace std;
#define pi 3.1415

class Geometric_shape
{
public:
    virtual double perimeter() = 0;
    virtual double area() = 0;
    virtual double volume() = 0;
    virtual void Show() = 0;
};

class Rectangle : public Geometric_shape
{
public:
    Rectangle(double i = 0, double j = 0) : x(i), y(j) {}
    double perimeter()
    {
        return 2 * (x + y);
    }
    double area()
    {
        return x * y;
    }
    double volume()
    {
        return 0;
    }
    void Show()
    {
        cout << "长方形的长为:" << x << endl;
        cout << "长方形的宽为:" << y << endl;
    }

protected:
    double x, y;
};

class Circle : public Geometric_shape
{
public:
    Circle(double i = 0) : x(i) {}
    double perimeter()
    {
        return 2 * pi * x;
    }
    double area()
    {
        return pi * x * x;
    }
    double volume()
    {
        return 0;
    }
    void Show()
    {
        cout << "圆的半径为：" << x << endl;
    }

protected:
    double x;
};

class Triangle : public Geometric_shape
{
public:
    Triangle(double i = 0, double j = 0, double k = 0) : x(i), y(j), z(k) {}
    double perimeter()
    {
        return x + y + z;
    }
    double area()
    {
        a = (x + y + z) / 2;
        return sqrt(a * (a - x) * (a - y) * (a - z));
    }
    double volume()
    {
        return 0;
    }
    void Show()
    {
        cout << "三角形的三边长为：" << x << " " << y << " " << z << endl;
    }

protected:
    double x, y, z, a;
};

class Box : public Geometric_shape
{
public:
    Box(double i = 0, double j = 0, double k = 0) : x(i), y(j), z(k) {}
    double perimeter()
    {
        return 2 * (x + y);
    }
    double area()
    {
        return x * y;
    }
    double volume()
    {
        return x * y * z;
    }
    void Show()
    {
        cout << "长方体的长为:" << x << endl;
        cout << "长方体的宽为:" << y << endl;
        cout << "长方体的高为:" << z << endl;
    }

protected:
    double x, y, z;
};

class Cylinder : public Geometric_shape
{
public:
    Cylinder(double i = 0, double j = 0) : x(i), y(j) {}
    double perimeter()
    {
        return 2 * pi * x;
    }
    double area()
    {
        return pi * x * x;
    }
    double volume()
    {
        return pi * x * x * y;
    }
    void Show()
    {
        cout << "圆的半径为:" << x << endl;
        cout << "圆的高为:" << y << endl;
    }

protected:
    double x, y;
};

class Cone : public Geometric_shape
{
public:
    Cone(double i = 0, double j = 0) : x(i), y(j) {}
    double perimeter()
    {
        return 2 * pi * x;
    }
    double area()
    {
        return pi * x * x;
    }
    double volume()
    {
        return (1 / 3) * (pi * x * x * y);
    }
    void Show()
    {
        cout << "圆锥的半径为:" << x << endl;
        cout << "圆锥的高为:" << y << endl;
    }

protected:
    double x, y;
};

class T_pyramid : public Geometric_shape
{
public:
    T_pyramid(double i = 0, double j = 0, double k = 0, double l = 0) : x(i), y(j), z(k), h(l) {}
    double perimeter()
    {
        return x + y + z;
    }
    double area()
    {
        a = (x + y + z) / 2;
        b = sqrt(a * (a - x) * (a - y) * (a - z));
        return b;
    }
    double volume()
    {
        return (b * h) / 3;
    }
    void Show()
    {
        cout << "三棱锥的三边长为：" << x << " " << y << " " << z << " "
             << "高为：" << h << endl;
    }

protected:
    double x, y, z, a, b, h;
};

class T_prism : public Geometric_shape
{
public:
    T_prism(double i = 0, double j = 0, double k = 0, double l = 0) : x(i), y(j), z(k), h(l) {}
    double perimeter()
    {
        return x + y + z;
    }
    double area()
    {
        a = (x + y + z) / 2;
        b = sqrt(a * (a - x) * (a - y) * (a - z));
        return b;
    }
    double volume()
    {
        return (b * h);
    }
    void Show()
    {
        cout << "三棱柱的三边长为：" << x << " " << y << " " << z << " "
             << "高为：" << h << endl;
    }

protected:
    double x, y, z, a, b, h;
};

int main(void)
{
    Geometric_shape *gs[] = {new Circle(10), new Rectangle(6, 8), new Triangle(3, 4, 5),
                             new Box(6, 8, 3), new class Cylinder(10, 3), new Cone(10, 3), new T_pyramid(3, 4, 5, 3), new T_prism(3, 4, 5, 3)};
    int i;
    for (i = 0; i < 8; i++)
    {
        gs[i]->Show();
        cout << endl;
    }
    cout << "平面图形：" << endl;
    for (i = 0; i < 3; i++)
    {
        cout << "图形周长：" << gs[i]->perimeter() << '\t';
        cout << "图形面积：" << gs[i]->area() << '\t';
        cout << "图形体积：" << gs[i]->volume() << endl;
    }
    cout << "立体图形：" << endl;
    for (i = 3; i < 8; i++)
    {
        cout << "图形底周长：" << gs[i]->perimeter() << '\t';
        cout << "图形底面积：" << gs[i]->area() << '\t';
        cout << "图形体积  ：" << gs[i]->volume() << endl;
    }
    return 0;
}
