
#include"Clock.h"

Clock::Clock(int h, int m, int s)
{
	if (h >= 24 || h < 0)
	{
		hour = 0;
	}
	else hour = h ;
	if (m >= 60 || m < 0)
	{
		minute = 0;
	}
	else minute = m ;
	if (s >= 60 || s < 0)
	{
		second = 0;
	}
	else second = s;
}

void Clock::SetAlarm(int h, int m, int s)
{
	if (h >= 24 )
	{
		Ahour = 0;
	}
	else Ahour = h ;
	if (m >= 60 )
	{
		Aminute = 0;
	}
	else Aminute = m ;
	if (s >= 60)
	{
		Asecond = 0;
	}
	else Asecond = s ;
}

void Clock::run()
{
	second++;
	if (second >= 60)
	{
		second -= 60;
		minute++;
	}
	if (minute >= 60)
	{
		minute -= 60;
		hour++;
	}
	if (hour >= 24)
		hour -= 24;
	if ((hour == Ahour) && (minute == Aminute) && (second == Asecond))
	{
		cout << "Plink!plink!plink!..."<<endl;
	}
}
