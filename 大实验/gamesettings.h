#ifndef gamesettings
#define gamesettings

#include "acllib.h"
#include<string>



using namespace std;
typedef void (*KeyboardEventCallback) (int key, int event);
typedef void (*TimerEventCallback)(int timerID);
typedef void (*MouseEventCallback)(int x,int y,int button,int event);


#define tyblue    RGB(102, 204, 255);
const int window_width = 1600;
const int window_height = 900;
const int gamer_width = 100;
const int gamer_height = 100;
const int gamer_normal_speedx = 20;
const int gamer_normal_speedy = 20;
const int special_enemy_width = 100;
const int special_enemy_height = 100;
const int bullet_width = 20;
const int bullet_height = 20;
const double bullet_speedx = 10;
const double bullet_speedy = 10;
const int enemy_width = 50;
const int enemy_height = 50;
const int pause_width = 50;
const int pause_height = 50;

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






void getkeyboard(int key, int event);
void timer(int id);
void paint();
void getmouse(int x, int y, int button, int event);



#endif // !gamesettings