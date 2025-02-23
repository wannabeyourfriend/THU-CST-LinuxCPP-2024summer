//this .cpp file is used to complete a rational number library in C++
#include <iostream>
#include <cmath>
#include <vector>

class Rational 
{
private:
    int numetator;
    int denominator;

    int gcd(int a, int b)
    {
        if (b == 0)
        {
            return a;
        }
        return gcd(b, a % b);
    }
    //simplification function
    void simplify()
    {
        if (denominator == 0)
        {
            std::cout << "Error: Division by zero" << std::endl;
            return;
        }
        int g = gcd(std::abs(numetator), std::abs(denominator));
        numetator /= g;
        denominator /= g;
        if (denominator < 0)
        {
            numetator *= -1;
            denominator *= -1;
        }
    }

public:
    //constructor
    Rational(int numerator = 0, int denominator = 1): numetator(numerator), denominator(denominator)
    {
        simplify();
    }
    //destructor
    ~Rational()
    {
        std::cout << "Rational object is destroyed" << std::endl;
    }

    //overloading + operator
    Rational operator+(const Rational& other)
    {
        return Rational(numetator * other.denominator + other.numetator * denominator, denominator * other.denominator);    
    }

    Rational operator-(const Rational& other)
    {
        return Rational(numetator * other.denominator - other.numetator * denominator, denominator * other.denominator);
    }

    Rational operator*(const Rational& other)
    {
        return Rational(numetator * other.numetator, denominator * other.denominator);
    }

    Rational operator/(const Rational& other)
    {
        return Rational(numetator * other.denominator, denominator * other.numetator);
    }

    //overloading == operator
    bool operator==(const Rational& other)
    {
        return (numetator * other.denominator - other.numetator * denominator == 0);
    }

    //overloading != operator
    bool operator!=(const Rational& other)
    {
        return (numetator * other.denominator - other.numetator * denominator != 0);
    }

    void print()
    {
        if ( denominator == 1)
        {
            std::cout << numetator << std::endl;
        }
        else
        {
            std::cout << numetator << "/" << denominator << std::endl;
        }
    }
};

int main()
{
    Rational r1(1, 2);
    Rational r2(3, 4);
    Rational r3 = r1 + r2;
    std::cout << "r1 = "; 
    r1.print();
    std::cout << "r2 = "; 
    r2.print();
    std::cout << "r1 + r2 = ";
    r3.print();
    Rational r4 = r1 - r2;
    std::cout << "r1 - r2 = ";
    r4.print();
    Rational r5 = r1 * r2;
    std::cout << "r1 * r2 = ";
    r5.print();
    Rational r6 = r1 / r2;
    std::cout << "r1 / r2 = ";
    r6.print();
    Rational r7(1, 3);
    std::cout << "r7 = ";
    r7.print(); 
    Rational r8(2, 3);
    std::cout << "r8 = ";
    r8.print();
    if (r7 == r8)
    {
        std::cout << "r7 is equal to r8" << std::endl;
    }
    else
    {
        std::cout << "r7 is not equal to r8" << std::endl;
    }
    if (r7 != r8)
    {
        std::cout << "r7 is not equal to r8" << std::endl;
    }
    else
    {
        std::cout << "r7 is equal to r8" << std::endl;
    }
    return 0;
}