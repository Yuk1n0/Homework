#include <iostream>
using namespace std;

class Complex
{
public:
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i){};
    Complex Add(Complex &c);
    Complex Sub(Complex &c);
    void display();

private:
    double real;
    double imag;
};

Complex Complex::Add(Complex &c)
{
    return Complex(real + c.real, imag + c.imag);
}

Complex Complex::Sub(Complex &c)
{
    return Complex(real - c.real, imag - c.imag);
}

void Complex::display()
{
    cout << "(" << real << "," << imag << "i"
         << ")" << endl;
}

int main(void)
{
    Complex c1(6, 7), c2(7, 8), c3;
    cout << "c1=";
    c1.display();
    cout << "c2=";
    c2.display();
    c3 = c1.Add(c2);
    cout << "c1+c2=";
    c3.display();
    c3 = c1.Sub(c2);
    cout << "c1-c2=";
    c3.display();
    return 0;
}
