//write a function to calculate gcd and lcm of  2 numbers using Euclidean algorithm

#include <iostream>
using namespace std;

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

int main() {
    int a, b;
    cout << "Enter two numbers: ";
    cin >> a >> b;
    cout << "GCD of " << a << " and " << b << " is " << gcd(a, b) << endl;
    cout << "LCM of " << a << " and " << b << " is " << lcm(a, b) << endl;
    return 0;
}