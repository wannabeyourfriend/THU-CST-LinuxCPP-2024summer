//this program aims to generate a random number from 1 to 52 and print it out.
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    srand(time(0)); //seed the random number generator with the current time
    int random_number = rand() % 52 + 1; //generate a random number between 1 and 52
    cout << "Random number: " << random_number << endl; //print the random number
    return 0;
}