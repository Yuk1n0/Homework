#include <iostream>
using namespace std;

class Point
{
public:
    Point()
    {
        char a[] = {'0'};
    }
    friend istream &operator>>(istream &in, Point &a);
    friend ostream &operator<<(istream &in, Point &a);
    char a[13];
};

istream &operator>>(istream &in, Point &a)
{
    cout << "请输入一个电话号码：";
    for (int i = 0; i < 11; i++)
        in >> a.a[i];
    return in;
}

ostream &operator<<(ostream &out, Point &a)
{
    cout << "输入的电话号码为：";
    for (int i = 0; i < 11; i++)
        out << a.a[i];
    cout << endl;
    return out;
}

int main(void)
{
    Point a;
    cin >> a;
    cout << a;
    return 0;
}
