#pragma once
#include "acllib.h"
#include<string>


using namespace std;
typedef void (*KeyboardEventCallback) (int key, int event);


#define tyblue    RGB(102, 204, 255);


struct position
{
	int x;
	int y;
	position(int x,int y);
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
	void printimg();
public:
	object();
	object(const char* a, int width, int height, int x, int y, double speedx, double speedy);
	object(const char* a, int width, int height, double speedx, double speedy);
	
	position position_value();
	friend void collusion();
};


class enemy:public object
{
public:
	virtual void enemy_action() = 0;
	enemy();
	void enemy_dead();
protected:
	bool fade;
	static int num ;
};

class normalenemy :public enemy
{
public:
	bool fade_value();
	normalenemy();
	void enemy_action();
	void print();
	friend void init_enemy(normalenemy& d);
};

class gamer :public object
{
private:

public:
	gamer();
	void print();
	friend void getkeyboard(int key, int event);
	friend void initgamer(gamer& x);
};


class window
{
public:
	bool overwindow(position &p1);
	void resetposition(position& p1);

};


void registerKeyboardEvent(KeyboardEventCallback callback);
void getkeyboard(int key, int event);
void paint();
