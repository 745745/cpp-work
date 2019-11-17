#pragma once
#include "acllib.h"
#include<string>


using namespace std;
typedef void (*KeyboardEventCallback) (int key, int event);
typedef void (*TimerEventCallback)(int timerID);




#define tyblue    RGB(102, 204, 255);


struct position
{
	double x;
	double y;
	position(double x,double y);
	position();
};


struct pic
{
	ACL_Image img;
	int pic_height;
	int pic_width;
	pic(const char* a, int width, int height);
	pic();
};


struct speed
{
	double speedx;
	double speedy;
	speed(double speedx,double speedy);
	speed();
}; 


class object
{
protected:
	position oposition;
	pic opic;
	speed ospeed;
public:
	object();
	object(const char* a, int width, int height, int x, int y, double speedx, double speedy);
	object(const char* a, int width, int height, double speedx, double speedy);
	void print();
	position position_value();
	friend void collusion();
};


class enemy:public object
{
public:
	virtual void enemy_action() = 0;
	enemy();
	void enemy_dead();
	bool fade_value();  //true为消失，false为存活
protected:
	bool fade;//true为消失，false为存活
	static int num;
};

class normalenemy :public enemy
{
public:
	normalenemy();
	void enemy_action();
	friend void init_enemy(normalenemy& d);
};

class special_enemy :public enemy
{
public:
	special_enemy();
	void enemy_action();
	friend void init_enemy(special_enemy &d);
};


class gamer :public object
{
private:
	int direction;
	void flash();
	void shootbullet();
public:
	gamer();
	void print();
	friend void getkeyboard(int key, int event);
	friend void initgamer(gamer& x);
};

class bullet :public object
{
private:
	int direction;
	bool fade;
	void bullet_action();
public:
	static int num;
	void initbullet(const char* p,int a,int b,int c);
	void print();
};





void getkeyboard(int key, int event);
void timer(int id);
void paint();
