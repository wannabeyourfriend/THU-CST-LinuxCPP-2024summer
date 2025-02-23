// This program takes an integer as input and prints its prime factorization.input x , 
//output x=x_1*x_2*x_3*...*x_k, where x_i is a prime factor of x.

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
std::vector<int> primeFactors;

void primeFactorization(int n)
{
    while (n % 2 == 0)
    {
        primeFactors.push_back(2);
        n = n / 2;
    }
    for ( int i = 3; i <= sqrt(n); i = i + 2){
        while ( n % i == 0 ){
            primeFactors.push_back(i);
            n = n / i;
        }
    }
    if (n > 2)
        primeFactors.push_back(n);
}

int main(){
    int x;
    cout << "Enter a number: ";
    cin >> x;
    
    primeFactorization(x);
    cout << x << "=" << primeFactors[0] << "";
    for (int i = 1; i < primeFactors.size(); i++){
        cout << "*" <<primeFactors[i] << "";
    }
    cout << endl;
    return 0;
}