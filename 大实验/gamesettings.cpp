#include"gamesettings.h"
#include"time.h"

gamer gamer1=gamer();
const int window_width= 1600;
const int window_height = 900;
const int gamer_width = 100;
const int gamer_height = 100;
const int gamer_normal_speedx = 20;
const int gamer_normal_speedy = 20;
const int enemy_width = 50;
const int enemy_height = 50;

extern int enemy_num;

extern normalenemy* p;


position::position(int x, int y)
{
	this->x = x;
	this->y = y;
}

int enemy::num = 0;


speed::speed(double speedx, double speedy)
{
	this->speedx = speedx;
	this->speedy = speedy;
}

speed::speed()
{
	return;
}

pic::pic(const char * a, int width, int height)
{
	loadImage(a, &this->img);
	this->pic_width = width;
	this->pic_height = height;
}

pic::pic()
{
	return;
}

void object::printimg()
{
	putImageScale(&opic.img, oposition.x, oposition.y, opic.pic_width, opic.pic_height);
}



position::position()
{
	x = rand() % window_width;
	y = rand() % window_height;
}






bool window::overwindow(position& p1)
{
	if (p1.x > window_width || p1.x<0 || p1.y>window_height || p1.y < 0)
		return true;
	else return false;
}

void window::resetposition(position& p1)
{
	if (p1.x > window_width)
		p1.x = 0;

	if (p1.x < 0)
		p1.x = window_width;

	if (p1.y > window_height)
		p1.y = 0;

	if (p1.y < 0)
		p1.y = window_height;
}









object::object()
{
	return;
}

object::object(const char* a, int width, int height, int x, int y, double speedx, double speedy)
{
	this->opic=pic(a, width, height);
	this->ospeed = speed(speedx, speedy);
	this->oposition=position(x, y);
}

object::object(const char* a, int width, int height, double speedx, double speedy)
{
	this->opic = pic(a, width, height);
	this->ospeed = speed(speedx, speedy);
}







gamer::gamer():object()
{
	return;
}

void gamer::print()
{
	printimg();
}

void initgamer(gamer& x)
{
	x.opic = pic("cat.jpg", gamer_width, gamer_height);
	x.oposition = position(gamer_width, gamer_height);
	x.ospeed = speed(gamer_normal_speedx, gamer_normal_speedy);
}










enemy::enemy():object()
{
	fade = 0;
}

void enemy::enemy_dead()
{
	this->fade = 1;
	return;
}


bool normalenemy::fade_value()
{
	return fade;
}

normalenemy::normalenemy():enemy()
{

}

void normalenemy::enemy_action()
{
	oposition.x += ospeed.speedx;
	oposition.y += ospeed.speedy;
}

void normalenemy::print()
{
	printimg();
}

void init_enemy(normalenemy &d)
{
	d.num++;
	srand((d.num) * (d.num) * (d.num) + time(NULL)); //不能是线性的，不然位置会十分接近
	d.opic = pic("rabbit.jpg", enemy_width, enemy_height);
	d.oposition.x = (rand() % (window_width - d.opic.pic_width));
	d.oposition.y = (rand() % (window_height - d.opic.pic_height));
	d.fade = 0;
	return;
}

void getkeyboard(int key, int event)
{
	if (event != KEY_DOWN)
		return;
	switch (key)
	{
	case VK_UP:		gamer1.oposition.y -= gamer1.ospeed.speedy;
		if (gamer1.oposition.y == 0)
			gamer1.oposition.y = 0;
		collusion();
			break;
	case VK_DOWN:	gamer1.oposition.y += gamer1.ospeed.speedy;
		if (gamer1.oposition.y >= window_height)
			gamer1.oposition.y = window_height; 
		collusion();
		break;

	case VK_LEFT:	gamer1.oposition.x -= gamer1.ospeed.speedy;
		if (gamer1.oposition.x == 0)
			gamer1.oposition.x = 0;
		collusion(); 
		break;

	case VK_RIGHT:	gamer1.oposition.x += gamer1.ospeed.speedy; 
		if (gamer1.oposition.x >= window_width)
			gamer1.oposition.y = window_height; 
		collusion();
		break;

	case 68:;//按下d键发动技能
	}
	paint();

}


position object::position_value()
{
	return this->oposition;
}


void collusion()
{
	for (int i = 0; i < enemy_num; i++)
	{
		position d = p[i].position_value();
		position e = gamer1.position_value();
		if ((abs(d.x - e.x)+60 < (gamer_width + enemy_width)) && (abs(d.y - e.y)+60 <= gamer_height + enemy_width) )  //+50是因为图片自己有白框，需要调整
		{
			p[i].enemy_dead();
		}
	}
}