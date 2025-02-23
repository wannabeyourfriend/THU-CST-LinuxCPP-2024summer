//going to write a prgram to check if a number which greater than 2 is prime or not.

#include <iostream>
using namespace std;

bool isPrime(int n) {
    if (n <= 1) {
        return false;
    }
    for (int i = 2; i <= n / 2; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}


int main() {
    int n;
    cout << "Enter a number: ";
    cin >> n;
    if (n > 2) {
        if (isPrime(n)) {
            cout << n << " is a prime number." << endl;
        } else {
            cout << n << " is not a prime number." << endl;
        }
    } 
    else {
        cout << "The number should be greater than 2." << endl;
    }
    return 0;
}