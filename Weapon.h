#pragma once

#include"STLINCLUDE.h"
#include"Item.h"

class Weapon : public Item
{
public:
	enum Type { Book, Bow, Sword };

private:
	int damageMin;
	int damageMax;

public:
	//Constructors
	Weapon();
	Weapon(
		int level,
		int rarity
	);
	Weapon(
		int damageMin,
		int damageMax,
		std::string name,
		int level,
		int buyValue,
		int sellValue,
		int rarity);

	//Destructor
	virtual ~Weapon();

	//Pure virtual
	virtual Weapon* clone()const;

	//Methods
	std::string toString()const;
	std::string toStringSave()const;

	//Accessors
	inline int getDamageMin()const { return this->damageMin; }
	inline int getDamageMax()const { return this->damageMax; }

	//Modifiers

	//Static
	static DynamicArray<std::string> names;
	static void initNames();
};
