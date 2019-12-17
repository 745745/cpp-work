#include"gamer.h"
#include"enemy.h"

extern gamer gamer1;
void collusion();

void gamer::flash()
{
	switch (direction)
	{
	case 1:		gamer1.oposition.y -= gamer1.ospeed.speedy * 10;
		if (gamer1.oposition.y <= 0)
			gamer1.oposition.y = 0;
		break;
	case 2:	gamer1.oposition.y += gamer1.ospeed.speedy * 10;
		if (gamer1.oposition.y + gamer_height >= window_height)
			gamer1.oposition.y = window_height - gamer_height;
		break;

	case 3:	gamer1.oposition.x -= gamer1.ospeed.speedx * 10;
		if (gamer1.oposition.x <= 0)
			gamer1.oposition.x = 0;
		break;

	case 4:	gamer1.oposition.x += gamer1.ospeed.speedx * 10;
		if (gamer1.oposition.x + gamer_width >= window_width)
			gamer1.oposition.x = window_width - gamer_width;
		
		break;
	}
}

void gamer::shootbullet()
{
	if (can_shoot_bullet)
	{
		bullet* q = new bullet;
		q->initbullet(oposition.x, oposition.y, direction);
		A= *q;
	}
	else return;
}


gamer::gamer() :object()
{
	return;
}

void gamer::print()
{
	putImageScale(&opic.img, oposition.x, oposition.y, opic.pic_width, opic.pic_height);
	if (bullet::num != 0)
	{
		for (int i = 1; i <= bullet::num; i++)
		{
			if (!A.isdead())
				A.print();
		}
	}
}

void initgamer(gamer& x)
{
	x.can_shoot_bullet = true;
	x.opic = pic("cat.jpg", gamer_width, gamer_height);
	x.oposition = position(gamer_width, gamer_height);
	x.ospeed = speed(gamer_normal_speedx, gamer_normal_speedy);
}

bool bullet::isdead()
{
	return fade;
}

void bullet::bullet_action()
{
	if (oposition.x + bullet_width > window_width)
	{
		oposition.x = window_width - bullet_width - 1;
		ospeed.speedx *= -1;
	}
	if (oposition.x - bullet_width <= 0)
	{
		oposition.x = bullet_width + 1;
		ospeed.speedx *= -1;
	}
	oposition.x += ospeed.speedx;
	if (oposition.y + bullet_height > window_height)
	{
		oposition.y = window_height - bullet_height - 1;
		ospeed.speedy *= -1;
	}
	if (oposition.y - bullet_height <= 0)
	{
		oposition.y = bullet_height + 1;
		ospeed.speedy *= -1;
	}
	oposition.y += ospeed.speedy;
}



void bullet::initbullet(int a, int b, int c)
{
	opic = pic("ÅçË®.jpg", bullet_width, bullet_height);
	oposition = position(a, b);
	switch (c)
	{
	case 1:ospeed = speed(0, -bullet_speedy); break;
	case 2:ospeed = speed(0, bullet_speedy); break;
	case 3:ospeed = speed(-bullet_speedx, 0); break;
	case 4:ospeed = speed(bullet_speedx, 0); break;
	}
	fade = 0;
	num++;
}

void bullet::print()
{
	putImageScale(&opic.img, oposition.x, oposition.y, opic.pic_width, opic.pic_height);
}