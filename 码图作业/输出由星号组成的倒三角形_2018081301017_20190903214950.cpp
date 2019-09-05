#include<iostream>
using namespace std;




int main()
{
	int x;
	cin>> x;
	if (x % 2 != 1 || x < 1 || x>80)
	{
		cout << "error\n";
		return 0;
	}
	else
	{
		for (int i = 0; i <= x / 2 + 1; i++)
		{
			for (int j = 1; j <= i; j++)
				cout << " ";
			for (int k = 1; k <= x-2*i; k++)
				cout << "*";
			cout << endl;
		}
		
	}
}