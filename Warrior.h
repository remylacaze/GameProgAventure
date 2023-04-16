#pragma once

#include "Character.h"

class Warrior : public Character
{
public:
	Warrior() : Character() {};
	Warrior(string name, Type classType,
		int distanceTravelled,
		int gold, int level,
		int exp, int strength, int vitality,
		int dexterity, int intelligence,
		int hp, int stamina, int statPoints)
		: Character(name, classType, distanceTravelled, gold, level, exp, strength, vitality, dexterity, intelligence, hp, stamina, statPoints) {};
	Warrior(Character c) : Character(c) {};

public:
	virtual std::string getClassName() { return "Warrior"; }
	virtual void initialize(const std::string name) override;
};

