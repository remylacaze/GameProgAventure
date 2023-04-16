#pragma once

#include"STLINCLUDE.h"
#include"Item.h"


class Armor : public Item
{
public:
	enum Type { HEAD = 0, CHEST, ARMS, LEGS };

private:
	std::string typeStr;
	int type;
	int defence;

public:
	//Constructors
	Armor();
	Armor(
		int level,
		int rarity
	);
	Armor(
		int type,
		int defence,
		std::string name,
		int level,
		int buyValue,
		int sellValue,
		int rarity
	);

	//Destructor
	virtual ~Armor();

	//Pure virtual
	virtual Armor* clone()const;

	//Functions
	std::string toString()const;
	std::string toStringSave()const;

	//Accessors
	inline int getDefence()const { return this->defence; }
	inline int getType()const { return this->type; }

	//Static
	static DynamicArray<std::string> names;
	static void initNames();
};
