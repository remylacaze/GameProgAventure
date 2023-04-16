#include "Inventory.h"

Inventory::Inventory()
{
	this->cap = 5;
	this->itemCount = 0;
	this->itemArr = new Item * [cap];
	this->initialize();
}

Inventory::~Inventory()
{
	for (size_t i = 0; i < this->itemCount; i++)
	{
		delete this->itemArr[i];
	}
	delete[] this->itemArr;
}

Inventory::Inventory(const Inventory& obj)
{
	this->cap = obj.cap;
	this->itemCount = obj.itemCount;
	this->itemArr = new Item * [this->cap];

	for (size_t i = 0; i < this->itemCount; i++)
	{
		this->itemArr[i] = obj.itemArr[i]->clone();
	}

	initialize(this->itemCount);
}

Item& Inventory::operator[](const int index)
{
	if (index < 0 || index >= this->itemCount)
		throw("BAD INDEX!");

	return *this->itemArr[index];
}

void Inventory::operator=(const Inventory& obj)
{
	for (size_t i = 0; i < this->itemCount; i++)
	{
		delete this->itemArr[i];
	}
	delete[] this->itemArr;

	this->cap = obj.cap;
	this->itemCount = obj.itemCount;
	this->itemArr = new Item * [this->cap];

	for (size_t i = 0; i < this->itemCount; i++)
	{
		this->itemArr[i] = obj.itemArr[i]->clone();
	}

	initialize(this->itemCount);
}

void Inventory::expand()
{
	this->cap *= 2;

	Item** tempArr = new Item * [this->cap];

	for (size_t i = 0; i < this->itemCount; i++)
	{
		tempArr[i] = this->itemArr[i];
	}

	delete[] this->itemArr;

	this->itemArr = tempArr;

	this->initialize(this->itemCount);
}

void Inventory::initialize(const int from)
{
	for (size_t i = from; i < cap; i++)
	{
		this->itemArr[i] = nullptr;
	}
}

void Inventory::addItem(const Item& item)
{
	if (this->itemCount >= this->cap)
	{
		expand();
	}

	this->itemArr[this->itemCount++] = item.clone();
}

void Inventory::removeItem(int index)
{
	if (index < 0 || index >= this->itemCount)
		throw("OUT OF BOUNDS REMOVE ITEM INVENTORY");

	delete this->itemArr[index];
	this->itemArr[index] = this->itemArr[this->itemCount - 1];
	this->itemArr[--this->itemCount] = nullptr;
}
