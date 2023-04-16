#include "Archer.h"

//Methods
void Archer::initialize(const string name)
{
	this->name = name;
	this->classType = Character::Type::Archer;

	this->strength = 3;
	this->vitality = 9;
	this->dexterity = 12;
	this->intelligence = 6;

	this->updateStats();
}
