#include "Boss.h"

Boss::Boss(std::string name, int level) : Enemy::Enemy(level + bossGapLevel)
{
	this->name = name;
}

Boss::~Boss()
{

}
