#pragma once

#include "Enemy.h"

class Boss : public Enemy
{
private:
	std::string name;
	int bossGapLevel = 3;

public:
	Boss(std::string name, int level);
	virtual ~Boss();

	inline std::string getName()const { return this->name; }
};
