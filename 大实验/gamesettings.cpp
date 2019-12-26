#include"gamesettings.h"
#include"enemy.h"
#include"time.h"
#include"gamer.h"

gamer gamer1=gamer();

extern ACL_Sound sound1;
ACL_Image q;
void judgespecialenemy();
void judge_end();
bool start_timer = true;

string gameending = "congratulation!";

int cont = 0;

int enemy::num = 0;
int score = 0;
int reborn = 0;
extern int enemy_num;
extern normalenemy* p;
extern special_enemy d;

int hardth = _Thrd_hardware_concurrency(); //硬件支持的线程数
int block = enemy_num / hardth;//分块
thread* optim=new thread[hardth+2];


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
			break;
	case VK_DOWN:	gamer1.oposition.y += gamer1.ospeed.speedy;
		if (gamer1.oposition.y+gamer_height >= window_height)
			gamer1.oposition.y = window_height-gamer_height; 
		gamer1.direction = 2;
		break;

	case VK_LEFT:	gamer1.oposition.x -= gamer1.ospeed.speedx;
		if (gamer1.oposition.x <= 0)
			gamer1.oposition.x = 0;
		gamer1.direction = 3;
		break;

	case VK_RIGHT:	gamer1.oposition.x += gamer1.ospeed.speedx; 
		if (gamer1.oposition.x+gamer_width >= window_width)
			gamer1.oposition.x = window_width-gamer_width; 
		gamer1.direction = 4;
		break;

	case 68: gamer1.flash(); break;//按下d键发动技能闪现，根据当前方向瞬间移动一段距离
	case 81: gamer1.shootbullet();     break;           //按Q键射子弹
	}
	paint();
}


void timer(int id)
{
	if (id == 0)
	{
		for (int i = 0; i < enemy_num; i++)
		{	if(!p[i].is_dead())
			p[i].enemy_action();
		}
		d.enemy_action();
		if(!gamer1.A.isdead())
			gamer1.A.bullet_action();
		reborn++;
		paint();
	}
	judge_end();
}

void paint()
{
	beginPaint();
	clearDevice();
	string A;
	A += "score:";
	A += to_string(score);
	paintText(1500, 0, A.c_str());
	if (start_timer == true)
	{
		loadImage("x.jpg", &q);
	}
	else loadImage("y.jpg", &q);
	putImageScale(&q, 0, 0, 50, 50);
	gamer1.print();
	if(!d.is_dead())
	d.print();
	for (int i = 0; i < enemy_num; i++)
	{
		if (!p[i].is_dead())
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
			stopSound(sound1);
			return;
		}
		if (button == LEFT_BUTTON && event == BUTTON_DOWN && !start_timer)
		{
			start_timer = true;
			startTimer(0, 1);
			playSound(sound1, 1);
			return;
		}
	}
} 



void threadoptim()
{
	int cont = 0;
	for (int i = 0; i <hardth; i++)
	{
		if (cont <= enemy_num)
		{
			optim[i] = thread(judgecollusion, cont, cont + block);
		}
		else break;
		cont += block + 1;
		optim[i].detach();
	}
	optim[hardth] = thread(judgespecialenemy);
	optim[hardth].detach();

}

void judgecollusion(int x, int y)
{
	if (y > enemy_num)
		y = enemy_num;
	while (1)
	{
		Sleep(1);
		position e = gamer1.position_value();
		for (int i = x; i <= y; i++)
		{
			if (!p[i].is_dead())
			{
				position h = p[i].position_value();
				if ((abs(h.x - e.x) + 60 < (gamer_width + enemy_width)) && (abs(h.y - e.y) + 60 <= gamer_height + enemy_width))  //+60是因为图片自己有白框，需要调整
				{
					p[i].enemy_dead();
					score++;
				}
				if (!gamer1.A.isdead())
				{
					position e = gamer1.A.position_value();
					if ((abs(h.x - e.x) + 30 < (bullet_width + enemy_width)) && (abs(h.y - e.y) + 30 <= bullet_height + enemy_height))
					{
						p[i].enemy_dead();
						score++;
						cont++;
					}
				}
			}
			gamer1.A.bullet_dead();
		}
	}
}

void judgespecialenemy()
{
	while (1)
	{
		Sleep(1);
		if (!d.is_dead())
		{
			if (!gamer1.A.isdead())
			{
				position q = d.position_value();
				position e = gamer1.A.position_value();
				if ((abs(q.x - e.x) < (bullet_width + special_enemy_width)) && (abs(q.y - e.y) <= bullet_height + special_enemy_height)) //那个图太大了不用加
				{
					d.enemy_dead();
					score += 5;
				}
			}
		}
		if (d.is_dead() && reborn >= 500)
		{
			init_enemy(d);
			reborn = 0;
		}
	}
}

void judge_end()
{
	for (int i = 0; i < enemy_num; i++)
	{
		if (p[i].is_dead())
			continue;
		else return;
	}
	if (d.is_dead())
	{
		cancelTimer(0);
		beginPaint();
		clearDevice();
		paintText(800, 450, gameending.c_str());
		endPaint();
		stopSound(sound1);
	}
}