#include"acllib.h"
#include"gamesettings.h"


extern gamer gamer1;

int enemy_num = 10;

normalenemy* p = new normalenemy[enemy_num];



int Setup()
{
	initWindow("men's��game", DEFAULT, DEFAULT, 1600, 900);
	for (int i = 0; i < enemy_num; i++)
	{
		init_enemy(p[i]);
	}
	initgamer(gamer1);
	paint();
	registerTimerEvent(timer);
	startTimer(0, 0.1);
	registerKeyboardEvent(getkeyboard);
	paint();
	return 0;
}



