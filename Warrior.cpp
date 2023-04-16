#include "Warrior.h"

//Methods
void Warrior::initialize(const string name)
{
	this->name = name;
	this->classType = Character::Type::Warrior;

	this->strength = 10;
	this->vitality = 10;
	this->dexterity = 5;
	this->intelligence = 3;

	this->updateStats();
}
