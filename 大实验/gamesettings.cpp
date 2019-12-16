#include"gamesettings.h"
#include"enemy.h"
#include"time.h"
#include"gamer.h"

gamer gamer1=gamer();

ACL_Image q;

bool start_timer = true;

int enemy::num = 0;
int bullet::num = 0;

extern int enemy_num;
extern normalenemy* p;
extern special_enemy d;

position::position(double x,double y)
{
	this->x = x;
	this->y = y;
}

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

position::position()
{
	x = rand() % window_width;
	y = rand() % window_height;
}

position object::position_value()
{
	return this->oposition;
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


void getkeyboard(int key, int event)
{
	if (event != KEY_DOWN)
		return;
	switch (key)
	{
	case VK_UP:		gamer1.oposition.y -= gamer1.ospeed.speedy;
		if (gamer1.oposition.y <= 0)
			gamer1.oposition.y = 0;
		gamer1.direction = 1;
		collusion();
			break;
	case VK_DOWN:	gamer1.oposition.y += gamer1.ospeed.speedy;
		if (gamer1.oposition.y+gamer_height >= window_height)
			gamer1.oposition.y = window_height-gamer_height; 
		gamer1.direction = 2;
		collusion();
		break;

	case VK_LEFT:	gamer1.oposition.x -= gamer1.ospeed.speedx;
		if (gamer1.oposition.x <= 0)
			gamer1.oposition.x = 0;
		gamer1.direction = 3;
		collusion(); 
		break;

	case VK_RIGHT:	gamer1.oposition.x += gamer1.ospeed.speedx; 
		if (gamer1.oposition.x+gamer_width >= window_width)
			gamer1.oposition.x = window_width-gamer_width; 
		gamer1.direction = 4;
		collusion();
		break;

	case 68: gamer1.flash(); break;//按下d键发动技能闪现，根据当前方向瞬间移动一段距离
	case 81: gamer1.shootbullet();     break;           //按Q键射子弹
	}
	paint();
}

void collusion()
{
	for (int i = 0; i < enemy_num; i++)
	{
		position h = p[i].position_value();
		position e = gamer1.position_value();
		position q = d.position_value();
		if ((abs(h.x - e.x) + 60 < (gamer_width + enemy_width)) && (abs(h.y - e.y) + 60 <= gamer_height + enemy_width))  //+60是因为图片自己有白框，需要调整
		{
			p[i].enemy_dead();
		}
		if (bullet::num != 0)
		{
			for (int j = 1; j <= bullet::num; j++)
			{
				position e = gamer1.A[j].position_value();
				if ((abs(h.x - e.x)+30  < (bullet_width + enemy_width)) && (abs(h.y - e.y)+30  <= bullet_height + enemy_height))  
				{
					p[i].enemy_dead();
				}
				if(!d.fade_value())
				if ((abs(q.x - e.x) < (bullet_width + special_enemy_width)) && (abs(q.y - e.y) <= bullet_height + special_enemy_height)) //那个图太大了不用加
				{
					d.enemy_dead();
					gamer1.A[j].reset_fade();
				}
			}
		}
	}
}

void timer(int id)
{
	if (id == 0)
	{
		for (int i = 0; i < enemy_num; i++)
		{	if(!p[i].fade_value())
			p[i].enemy_action();
		}
		d.enemy_action();
		if(bullet::num!=0)
			for (int i = 1; i <= bullet::num; i++)
			{
				gamer1.A[i].bullet_action();
			}
		paint();
	}
}

void paint()
{
	beginPaint();
	clearDevice();
	if (start_timer == true)
	{
		loadImage("x.jpg", &q);
	}
	else loadImage("y.jpg", &q);
	putImageScale(&q, 0, 0, 50, 50);
	gamer1.print();
	if(!d.fade_value())
	d.print();
	for (int i = 0; i < enemy_num; i++)
	{
		if (!p[i].fade_value())
			p[i].print();
	}
	endPaint();
}



void getmouse(int x, int y, int button, int event)
{
	if (x>=0&&x<=pause_width&&y>=0&&y<=pause_height)
	{
		if (button == LEFT_BUTTON && event == BUTTON_DOWN && start_timer)
		{
			start_timer = false;
			cancelTimer(0);
			return;
		}
		if (button == LEFT_BUTTON && event == BUTTON_DOWN && !start_timer)
		{
			start_timer = true;
			startTimer(0, 1);
			return;
		}
	}

} 



