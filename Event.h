#pragma once

#include"STLINCLUDE.h"

#include"Character.h"
#include"Enemy.h"
#include"Boss.h"

class Event
{
private:

public:
	Event();
	virtual ~Event();
	void generateEvent(Character& character, DynamicArray<Enemy>& enemies);

	//Events
	void shopEncouter(Character& character);
	void enemyEncouter(Character& character, DynamicArray<Enemy>& enemies);
	void puzzleEncouter(Character& character) { };
	//void bossEncouter(Character& character, DynamicArray<Boss>& boss); TODO
	void bossEncouter(Character& character);

	//statics
	static int nrOfEvents;
};
