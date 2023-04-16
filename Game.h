#pragma once

#include <list>
#include <conio.h>
#include <windows.h>
#include "Archer.h"
#include "Armor.h"
#include "Character.h"
#include "Event.h"
#include "Enemy.h"
#include "Explorer.h"
#include "Mage.h"
#include "STLInclude.h"
#include "Warrior.h"

using namespace std;

class Game
{
private:
	Game() {};
	Game(const Game&) {}
	~Game() {};

	// Singleton
	static Game* instance_;

	// Sound
	LPCWSTR filenameAwakeSound = TEXT("Resources/Sounds/Musics/TES-V-Skyrim-Soundtrack-Awake.wav");
	LPCWSTR filenamePositiveSound = TEXT("Resources/Sounds/Effects/positive.wav");

	// Properties
	int choice = 0;
	int activeCharacter = 0;
	bool playing = true;
	const std::string fileName = "Resources/Saves/characters.txt";
	std::vector<Character*> characters;

	// Enemies
	DynamicArray<Enemy> enemies;
	//DynamicArray<Boss> bosses;
	Boss* boss;
	
	// Operator
	Game& operator= (const Game&) {}

private:

public:
	static Game* getInstance();

	void start();
	void stop();
	void update();

	void dialogNameChoice();
	void dialogClassChoice();
	void classChoice();

	//Methods
	void initGame();
	void mainMenu();
	void inGameMenu();
	void createNewCharacter();
	void levelUpCharacter();
	void characterMenu();
	void saveCharacters();
	void loadCharacters();
	void selectCharacter();
	void travel();
	void rest();
	//void setBosses(DynamicArray<Boss>& bosses);

	//Accessors
	inline bool getPlaying() const { return this->playing; }
};

