/*打印一个2016年的月历*/
#include <iostream>
#include <stdio.h>
using namespace std;
int  main(){
	cout << "Calendar 2016-01" << endl;
	cout << "-------------" << "-------------" << endl;
	cout << "Su  Mo  Tu  We  Th  Fr  Sa" << endl;
	cout << "-------------" << "-------------" << endl;
	int i = 0;
	for ( i = 0 ; i <  21; i++)
	{
		cout << " ";
	}
	cout << 1;
	cout << "   " << 2 << endl;
 	int j = 0;
	for (j = 0; j < 7;j++)
	{
		printf(" %d  ",j+3);
	}
	printf("\n");
	int m = 0;
	int indexnumber = 10;
	for (m = 0 ; m < 3; m++)
	{	
		int n = 0;
		for (n = 0; n < 7; n++)
		{
			printf("%d  ", indexnumber+n);
		}
		indexnumber+=7;
		printf("\n");
	}
	printf("%d",31);
	printf("\n");
	int k = 0;	
	for (k = 0; k < 26; k++)
	{
		cout << "-";
	}
	return 0;
}

