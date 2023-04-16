#pragma once

#include "Character.h"

class Archer : public Character
{
public:
	Archer() : Character() {};
	Archer(string name, Type classType,
		int distanceTravelled,
		int gold, int level,
		int exp, int strength, int vitality,
		int dexterity, int intelligence,
		int hp, int stamina, int statPoints)
		: Character(name, classType, distanceTravelled, gold, level, exp, strength, vitality, dexterity, intelligence, hp, stamina, statPoints) {};

public:
	virtual std::string getClassName() { return "Archer"; }
	virtual void initialize(const std::string name) override;
};

