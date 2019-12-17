#include"acllib.h"
#include"gamesettings.h"
#include"enemy.h"
#include"gamer.h"

extern gamer gamer1;

int enemy_num =501;

normalenemy* p = new normalenemy[enemy_num];
special_enemy d;


int Setup()
{
	initWindow("wzy's♂game", DEFAULT, DEFAULT, 1600, 900);
	for (int i = 0; i < enemy_num; i++)
	{
		init_enemy(p[i]);
	}
	if (enemy_num > 500)  //数量较小时使用多线程反而会浪费计算资源
	{
		threadoptim();
	}
	init_enemy(d);
	initgamer(gamer1);
	paint();
	registerMouseEvent(getmouse);
	registerTimerEvent(timer);
	startTimer(0, 1);
	registerKeyboardEvent(getkeyboard);
	paint();
	return 0;
}



