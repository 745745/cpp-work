#ifndef gamerx
#define gamerx

#include"gamesettings.h"


class bullet :public object
{
private:
	bool dead;
public:
	bool isdead();
	void bullet_action();
	void initbullet(int a, int b, int c);
	void print();
	void bullet_dead();
};



class gamer :public object
{
private:
	int direction;
	void flash();
	void shootbullet();
public:
	bullet A;
	gamer();
	void print();
	friend void getkeyboard(int key, int event);
	friend void initgamer(gamer& x);
};


#endif // !gamerx