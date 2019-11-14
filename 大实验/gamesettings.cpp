#include"gamesettings.h"
#include"time.h"

gamer gamer1=gamer();
const int window_width= 1600;
const int window_height = 900;
const int gamer_width = 100;
const int gamer_height = 100;
const int gamer_normal_speedx = 20;
const int gamer_normal_speedy = 20;
const int special_enemy_width = 100;
const int special_enemy_height = 100;

const int enemy_width = 50;
const int enemy_height = 50;

extern int enemy_num;

extern normalenemy* p;
extern special_enemy d;

position::position(double x,double y)
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





position::position()
{
	x = rand() % window_width;
	y = rand() % window_height;
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







void gamer::flash()
{
	switch(direction)
	{
	case 1:		gamer1.oposition.y -= gamer1.ospeed.speedy*10;
		if (gamer1.oposition.y <= 0)
			gamer1.oposition.y = 0;
		collusion();
		break;
	case 2:	gamer1.oposition.y += gamer1.ospeed.speedy*10;
		if (gamer1.oposition.y + gamer_height >= window_height)
			gamer1.oposition.y = window_height - gamer_height;
		collusion();
		break;

	case 3:	gamer1.oposition.x -= gamer1.ospeed.speedx*10;
		if (gamer1.oposition.x <= 0)
			gamer1.oposition.x = 0;
		collusion();
		break;

	case 4:	gamer1.oposition.x += gamer1.ospeed.speedx*10;
		if (gamer1.oposition.x + gamer_width >= window_width)
			gamer1.oposition.x = window_width - gamer_width;
		collusion();
		break;
	}
}

gamer::gamer():object()
{
	return;
}

void gamer::print()
{
	putImageScale(&opic.img, oposition.x, oposition.y, opic.pic_width, opic.pic_height);
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


bool enemy::fade_value()
{
	return fade;
}

normalenemy::normalenemy():enemy()
{

}

void normalenemy::enemy_action()
{
	if (!this->fade)
	{
		if (oposition.x + enemy_width > window_width) 
		{
			oposition.x = window_width - enemy_width - 1;
			ospeed.speedx *= -1;
		}
		if (oposition.x - enemy_width <= 0)
		{
			oposition.x = enemy_width + 1;
			ospeed.speedx *= -1;
		}
		oposition.x += ospeed.speedx;
		if (oposition.y + enemy_height > window_height)
		{
			oposition.y = window_height - enemy_height-1;
			ospeed.speedy *= -1;
		} 
		if(oposition.y - enemy_height <= 0)
		{
			oposition.y = enemy_height + 1;
			ospeed.speedy *= -1;
		}
		oposition.y += ospeed.speedy;
	}
	collusion();
}

void object::print()
{
	putImageScale(&opic.img, oposition.x, oposition.y, opic.pic_width, opic.pic_height);
}

void init_enemy(normalenemy &d)
{
	d.num++;
	srand((d.num) * (d.num) * (d.num) + time(NULL)); //不能是线性的，不然位置会十分接近
	d.opic = pic("rabbit.jpg", enemy_width, enemy_height);
	d.oposition.x = (rand() % (window_width - d.opic.pic_width));
	d.oposition.y = (rand() % (window_height - d.opic.pic_height));
	d.ospeed.speedx = rand() % 20 - 10;
	while (d.ospeed.speedx == 0)
	{
		d.ospeed.speedx = rand() % 20 - 10;
	}
	d.ospeed.speedy = rand() % 20 - 10;
	while (d.ospeed.speedy == 0)
	{
		d.ospeed.speedy = rand() % 20 - 10;
	}
	d.fade = 0;
	return;
}

void init_enemy(special_enemy& d)
{
	d.num++;
	srand((d.num) * (d.num) * (d.num) + time(NULL));
	d.opic = pic("喷水.jpg", special_enemy_width, special_enemy_height);
	d.oposition.x = (rand() % (window_width - d.opic.pic_width));
	d.oposition.y = (rand() % (window_height - d.opic.pic_height));
	d.ospeed.speedx = 0.5;
	d.ospeed.speedy =0.5;
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

	case 68: gamer1.flash();//按下d键发动技能闪现，根据当前方向瞬间移动一段距离
	//case 81:                 //按Q键给敌人加速，可叠加
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

void timer(int id)
{
	if (id == 0)
	{
		for (int i = 0; i < enemy_num; i++)
		{	if(!p[i].fade_value())
			p[i].enemy_action();
		d.enemy_action();
		}
		paint();
	}
	
}

void paint()
{
	beginPaint();
	clearDevice();
	gamer1.print();
	d.print();
	for (int i = 0; i < enemy_num; i++)
	{
		if (!p[i].fade_value())
			p[i].print();
	}
	endPaint();
}

special_enemy::special_enemy(): enemy()
{
}

void special_enemy::enemy_action()
{
	if (!this->fade)
	{
		if (oposition.x + enemy_width > window_width)
		{
			oposition.x = window_width - enemy_width - 1;
			ospeed.speedx *= -1;
		}
		if (oposition.x - enemy_width <= 0)
		{
			oposition.x = enemy_width + 1;
			ospeed.speedx *= -1;
		}
		oposition.x += ospeed.speedx;
		if (oposition.y + enemy_height > window_height)
		{
			oposition.y = window_height - enemy_height - 1;
			ospeed.speedy *= -1;
		}
		if (oposition.y - enemy_height <= 0)
		{
			oposition.y = enemy_height + 1;
			ospeed.speedy *= -1;
		}
		oposition.y += ospeed.speedy;
	}
		position d = oposition;
		position e = gamer1.position_value();
		if ((abs(d.x - e.x) + 60 < (gamer_width + enemy_width)) && (abs(d.y - e.y) + 60 <= gamer_height + enemy_width))  
		{
			oposition.x = rand() % window_width;
			oposition.y = rand() % window_height;
		}
}

