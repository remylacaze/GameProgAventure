#include "Explorer.h"

//Methods
void Explorer::initialize(const string name)
{
	this->name = name;
	this->classType = Character::Type::Explorer;

	this->strength = 8;
	this->vitality = 8;
	this->dexterity = 8;
	this->intelligence = 8;

	this->updateStats();
}
