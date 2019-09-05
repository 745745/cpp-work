#include<iostream>
using namespace std;
const int mon[12] = { 31,27,31,30,31,30,31,31,30,31,30,31};
class Date {
public:
	Date(int y = 1996, int m = 1, int d = 1) 
	{
		day = d;
		month = m;
		year = y;
		if (m > 12 || m < 1)
		{
			month = 1;
		}
		if (d > days(y, m))
		{
			cout << "Invalid day!" << endl;
			day = 1;
		}
	};
	int days(int y, int m);
	friend ostream& operator << (ostream &t,const Date &a);
	void display() 
	{
		cout << year << "-" << month << "-" << day << endl;
	}
private:
	int year;
	int month;
	int day;
};



int main() {
	int y, m, d;
	cin >> y >> m >> d;
	Date dt(y, m, d);
	cout << dt;
	return 0;
}

ostream& operator<<(ostream& t, const Date& a)
{
	t<< a.year << "-" << a.month << "-" << a.day << endl;
	return t;
}

int Date::days(int y, int m)
{
	if (((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) && m == 2)
		return 29;
	else return mon[m - 1];
}