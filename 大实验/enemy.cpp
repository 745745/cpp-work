#include"enemy.h"
#include"gamer.h"
#include<time.h>

extern gamer gamer1;
void collusion();
position special_enemy::position_value()
{
	return this->oposition;
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

enemy::enemy() :object()
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

normalenemy::normalenemy() :enemy()
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
	collusion();
}

void object::print()
{
	putImageScale(&opic.img, oposition.x, oposition.y, opic.pic_width, opic.pic_height);
}

void init_enemy(normalenemy& d)
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
	d.ospeed.speedy = 0.5;
	d.fade = 0;
	return;
}


