#include"acllib.h"
#include"gamesettings.h"


extern gamer gamer1;

int enemy_num = 50;

normalenemy* p = new normalenemy[enemy_num];



int Setup()
{
	initWindow("men's¡ágame", DEFAULT, DEFAULT, 1600, 900);
	for (int i = 0; i < enemy_num; i++)
	{
		init_enemy(p[i]);
	}
	initgamer(gamer1);
	paint();
	registerKeyboardEvent(getkeyboard);

	return 0;
}

void paint()
{
	beginPaint();
	clearDevice();
	gamer1.print();
	for (int i = 0; i < enemy_num; i++)
	{
		if(!p[i].fade_value())
		p[i].print();
	}
	endPaint();
}

