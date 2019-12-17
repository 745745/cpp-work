#include"acllib.h"
#include"gamesettings.h"
#include"enemy.h"
#include"gamer.h"

extern gamer gamer1;

int enemy_num =1000;

normalenemy* p = new normalenemy[enemy_num];
special_enemy d;


int Setup()
{
	initWindow("wzy's¡ágame", DEFAULT, DEFAULT, 1600, 900);
	for (int i = 0; i < enemy_num; i++)
	{
		init_enemy(p[i]);
	}
	threadoptim();
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



