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
		int x  = this->size()+1;
		int* p = new int[x+1];
		if (!this->IsEmpty())
		{
			for (int i = 1; i <= x; i++)
				p[i] = this->pS[i];
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
		int x = 0;
		for (int i = 1; i <= n; i++)
		{
			if (s.IsElement(pS[i]))
			{
				x++;
			}
		}
		Set a;
		x = n + s.n - x;
		int* p = new int[x + 1];
		for (int i = 1; i <= n; i++)
		{
			if (!a.IsElement(this->pS[i]))
			{
				a += this->pS[i];
			}
			else continue;
		}
		for (int i = 1; i <= s.n; i++)
		{
			if (!a.IsElement(s.pS[i]))
			{
				a += s.pS[i];
			}
			else continue;
		}
		return a;
}

Set Set::operator &(const Set& s)const
{
	Set a;
	if (n > s.n)
	{
		for (int i = 1; i <=n; i++)
		{
			if (s.IsElement(pS[i])&&!a.IsElement(pS[i]))
			{
				a += pS[i];
			}
		}
	}
	else
	{
		for (int i = 1; i <= s.n; i++)
		{
			if (this->IsElement(s.pS[i]) && !a.IsElement(s.pS[i]))
			{
				a += s.pS[i];
			}
		}
	}
	return a;
}


Set Set::operator -(const Set& s)const
{
	Set b;
	Set a;
	if (n > s.n)
	{
		for (int i = 1; i <= n; i++)
		{
			if (s.IsElement(pS[i]) && !a.IsElement(pS[i]))
			{
				a += pS[i];
			}
		}
	}
	else
	{
		for (int i = 1; i <= s.n; i++)
		{
			if (this->IsElement(s.pS[i]) && !a.IsElement(s.pS[i]))
			{
				a += s.pS[i];
			}
		}
	}   //获得交集
	for (int i = 1; i <= n; i++)
	{
		if (!a.IsElement(pS[i]))
		{
			b += pS[i];
		}
	}
	return b;
}

