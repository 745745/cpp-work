#include<iostream>
using namespace std;
int main()
{
	int p = 1;
	int q = 1;
	int x;
	cin >> x;
	if (x == 0)
		cout << 0 << "!="<<1;
	for (int i = 2; i <= x; i++)
	{
		p *= i;
		if (p / i != q)
		{
			cout << i-1 << "!=" << q;
			break;
		}
		q *= i;
		if (x == i)
		{
			cout << i << "!=" << q;
		}
	}
}