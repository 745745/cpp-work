#include"Cset.h"
#include<iostream>
using namespace std;

bool Set::operator <=(const Set& s)const
{
	for (int i = 1; i <= n; i++)
	{
		if (s.IsElement(this->pS[i]))
			continue;
		else return false;
	}
	return true;
}

bool Set::operator ==(const Set& s)const
{
	if ((*this <= s) && (s <= *this))
		return true;
	else return false;
}

Set& Set::operator +=(int e)
{
	if (IsElement(e))
		return *this;
	else
	{
		int x = this->size() + 1;
		int* p = new int[x + 1];
		if (!IsEmpty())
		{
			for (int i = 1; i <= x; i++)
				p[i] = pS[i];
		}
		p[x] = e;
		delete[] pS;
		pS = p;
		n = x;
		return *this;
	}
}

Set& Set::operator -=(int e)
{
	if (!IsElement(e))
		return *this;
	else
	{
		int* p = new int[n - 1];
		for (int i = 1; i <= n - 1; i++)
		{
			if (pS[i] != e)
				p[i] = pS[i];
			else continue;
		}
		delete[] pS;
		pS = p;
		n--;
		return *this;
	}
}

Set Set::operator |(const Set& s)const
{
	Set a;
	for (int i = 1; i <= n; i++)
	{
		a += pS[i];
	}
	for (int i = 1; i <= s.n; i++)
	{
		if (!a.IsElement(s.pS[i]))
		{
			a += s.pS[i];
		}
	}
	return a;
}

Set Set::operator &(const Set& s)const
{
	Set a;
	for (int i = 1; i <= n; i++)
	{
		if (s.IsElement(pS[i]) && !a.IsElement(pS[i]))
		{
			a += pS[i];
		}
	}
	return a;
}


Set Set::operator -(const Set& s)const
{
	Set b;
	const Set& a = *this & s;//获得交集
	for (int i = 1; i <= n; i++)
	{
		if (!a.IsElement(pS[i]))
		{
			b += pS[i];
		}
	}
	return b;
}