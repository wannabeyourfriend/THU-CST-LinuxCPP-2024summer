/* 使用循环结构打印下述图形，打印行数n由用户输入。图中每行事实上包括两部分，中间间隔空格字符数m也由用户输入*/

#include <iostream>
using namespace std;

void printpattern_line_i(int index,int n);
 
int main(){
	int lines, spaces;
	cin >> lines;
	cin >> spaces;
	int i = 1;
	for (i = 1; i < lines+1 ; i++)
	{
		printpattern_line_i(i,lines);
		int j = 0;
		for (j = 0;j < spaces ;j++)
		{
			cout << " " ;
		}
		printpattern_line_i(1+lines-i,lines);
		cout << "\n" <<endl;
	}
	return 0;
}

void printpattern_line_i(int index,int n)
{
	int i = 1;
	for (i = 1; i < 2*n ; i ++)
	{
		if (i < n - (index-1) || i > n + (index -1))
		{
			cout << " " ;
		}
		else 
		{
			cout << "*" ;
		}
	}
}




