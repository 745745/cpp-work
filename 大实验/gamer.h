#ifndef gamerx
#define gamerx

#include"gamesettings.h"


class bullet :public object
{
private:
	bool fade;
public:
	bool isdead();
	void bullet_action();
	void reset_fade();
	static int num;
	void initbullet(int a, int b, int c);
	void print();
};



class gamer :public object
{
private:
	int direction;
	void flash();
	void shootbullet();
public:
	bullet A[1000];
	gamer();
	void print();
	friend void getkeyboard(int key, int event);
	friend void initgamer(gamer& x);
};


#endif // !gamerx