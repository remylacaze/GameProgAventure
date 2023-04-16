#include "Mage.h"

//Methods
void Mage::initialize(const string name)
{
	this->name = name;
	this->classType = Character::Type::Mage;

	this->strength = 3;
	this->vitality = 9;
	this->dexterity = 6;
	this->intelligence = 10;

	this->updateStats();
}
