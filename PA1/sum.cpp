#include <iostream>

using namespace std;


int main(){
	int  a = 0;
	int sum = 0;	
	int i;
	for (i = 0 ; i < 10 ; i++)
	{
		cin >> a;
		sum += a;	
	}

	cout << sum << endl;
	return 0;
}

