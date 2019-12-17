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
	static int num;
	void initbullet(int a, int b, int c);
	void print();
};



class gamer :public object
{
private:
	int direction;
	bool can_shoot_bullet; //现在设置为只能射一发子弹
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