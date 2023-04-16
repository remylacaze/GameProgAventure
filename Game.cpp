#include "Game.h"

Game* Game::instance_ = NULL;

Game* Game::getInstance()
{
	if (instance_ == NULL)
	{
		instance_ = new Game();
	}
	return instance_;
}

void Game::stop()
{
}

void Game::start()
{
	PlaySound(filenameAwakeSound, NULL, SND_FILENAME | SND_ASYNC);
	dialogNameChoice();
	//dialogClassChoice();
	//Hero<Mage>::instance() = Hero<Mage>::instance().instance;
	// TODO dialog Imperial + protagonist escape while mob attack
	cout << "The goblins are attacking the city." << endl;
	//cout << "You better move fast, " << Hero<Class>::instance().getName() << "." << endl;
	gui::pausePressKeyClear();
}

void Game::update()
{
	inGameMenu();
}

void Game::dialogNameChoice()
{
	//string name;
	cout << "Ralof: Hey, you. You're finally awake." << endl;
	gui::pausePressKeyClear();
	//cout << "What is your name ?" << endl;
	//cin >> name;
	//system("CLS");
	//cout << name + " ?" << endl;
	cout << characters[activeCharacter]->getName() + " ?" << endl;
	cout << "You were trying to cross the border, right ? " << endl;
	gui::pausePressKeyClear();
	cout << "Walked right into that Imperial ambush, same as us, and that thief over there." << endl;
	gui::pausePressKeyClear();
	cout << "Lokir: Damn you Stormcloaks. Empire was nice and lazy." << endl;
	cout << "If they hadn't been looking for you, I could've stolen that horse and be halfway to Hammerfell." << endl;
	gui::pausePressKey();
	cout << "You there. You and me - we shouldn't be here. It's these Stormcloaks the Empire wants." << endl;
	gui::pausePressKeyClear();
	cout << "Ralof: We're all brothers and sisters in binds now, thief." << endl;
	gui::pausePressKeyClear();
	cout << "Imperial Soldier: Shut up back there !" << endl;
	gui::pausePressKeyClear();
}

void Game::dialogClassChoice()
{
	cout << "Ralof: Which type of hero you are my friend ? A archer ? A mage ? A warrior ? " << endl;
	cout << "Let me guess..." << endl;
	gui::pausePressKey();
	classChoice();
}

void Game::classChoice()
{
	Character* character = nullptr;
	Character::Type classList[4] = { Character::Type::Warrior, Character::Type::Mage, Character::Type::Archer };
	string choice;
	int it = 0;

	do
	{
		cout << "A " << Character::getStringClassFromEnumType(classList[it]) << " ? " << endl;
		cout << "[yes] / [no]" << endl;
		cin >> choice;
		if (choice != "yes" && choice != "no")
		{
			cout << "Wait. I don't understand..." << endl;
		}
		else
		{
			if (choice == "no")
			{
				it++;
				if (it >=3)
				{
					cout << "Mmh... So, you're just an explorer then." << endl;
					gui::pausePressKey();
					cout << "(you found the secret class: Explorer !)" << endl;
					//PlaySound(filenamePositiveSound, NULL, SND_FILENAME | SND_ASYNC);
					gui::pausePressKeyClear();
				}
			}
		}
	} while (choice != "yes" && it < 3);

	switch (it)
	{
	case Character::Type::Warrior:
		character = new Warrior();
		break;
	case Character::Type::Mage:
		character = new Mage();
		break;
	case Character::Type::Archer:
		character = new Archer();
		break;
	case Character::Type::Explorer:
		character = new Explorer();
		break;
	default:
		break;
	}
}

//Methods
void Game::initGame()
{
	Weapon::initNames();
	Armor::initNames();

	ifstream in;
	in.open("Resources/Saves/characters.txt");

	if (in.is_open())
	{
		this->loadCharacters();
		PlaySound(filenameAwakeSound, NULL, SND_FILENAME | SND_ASYNC);
	}
	else
	{
		createNewCharacter();
		this->saveCharacters();
		this->start();
	}

	in.close();
}

void Game::mainMenu()
{
	system("CLS");

	cout << "= MAIN MENU =" << "\n" << "\n";

	cout << "0: Create new character" << "\n";
	cout << "1: Select an existing character" << "\n";
	cout << "2: Quit" << "\n";

	cout << "\n";

	cout << "\n" << "Choice: ";
	cin >> this->choice;

	while (cin.fail() || this->choice < 0 || this->choice > 2)
	{
		cout << "Faulty input!" << "\n";
		cin.clear();
		cin.ignore(100, '\n');

		cout << "\n" << "Choice (0 - 2): ";
		cin >> this->choice;
	}

	cin.ignore(100, '\n');
	cout << "\n";

	switch (this->choice)
	{
	case 0: //CREATE NEW CHAR
		createNewCharacter();
		saveCharacters();
		start();
		break;

	case 1: //SELECT CHAR
		selectCharacter();
		break;

	case 2: //QUIT
		playing = false;
		break;

	default:
		break;
	}

	system("CLS");
}

void Game::inGameMenu()
{
	system("CLS");

	if (this->characters[activeCharacter]->isAlive())
	{
		if (this->characters[activeCharacter]->getExp() >=
			this->characters[activeCharacter]->getExpNext())
		{
			cout << "LEVEL UP AVAILABLE! \n\n";
		}

		cout << "= MENU =" << "\n" << "\n";

		cout << "= Active character: " <<
			this->characters[activeCharacter]->getName() << " Nr: " <<
			this->activeCharacter + 1 << "/" << this->characters.size() <<
			" =" << "\n" << "\n";

		cout << "0: Quit" << "\n";
		cout << "1: Travel" << "\n";
		cout << "2: Level up" << "\n";
		cout << "3: Rest" << "\n";
		cout << "4: Character sheet" << "\n";
		cout << "5: Save characters" << "\n";

		cout << "\n";

		cout << "\n" << "Choice: ";
		cin >> this->choice;

		while (cin.fail() || this->choice > 5)
		{
			cout << "Faulty input!" << "\n";
			cin.clear();
			cin.ignore(100, '\n');

			cout << "\n" << "Choice (0 - 5): ";
			cin >> this->choice;
		}

		cin.ignore(100, '\n');
		cout << "\n";

		switch (this->choice)
		{
		case 0: //QUIT
			playing = false;
			this->saveCharacters();
			break;

		case 1: //TRAVEL
			travel();
			break;

		case 2: //LEVEL UP
			this->levelUpCharacter();
			break;

		case 3: //REST
			rest();
			break;

		case 4: //CHAR SHEET
			this->characterMenu();
			break;

		case 5: //SAVE CHARS
			saveCharacters();
			break;

		default:
			break;
		}
	}
	else
	{
		cout << "= YOU ARE DEAD, LOAD? =" << "\n" << "\n";
		cout << "(0) Yes, (1) No " << "\n";
		cin >> this->choice;

		while (cin.fail() || this->choice < 0 || this->choice > 1)
		{
			cout << "Faulty input!" << "\n";
			cin.clear();
			cin.ignore(100, '\n');

			cout << "(0) Yes, (1) No " << "\n";
			cin >> this->choice;
		}

		cin.ignore(100, '\n');
		cout << "\n";

		if (this->choice == 0)
			this->loadCharacters();
		else
			playing = false;
	}
}

void Game::createNewCharacter()
{
	system("CLS");

	string name = "";
	int classIndex = 0;
	cout << "Character name: ";
	getline(cin, name);

	for (size_t i = 0; i < this->characters.size(); i++)
	{
		while (name == this->characters[i]->getName())
		{
			cout << "Error! Character already exists!" << "\n";
			cout << "Character name: ";
			getline(cin, name);
		}
	}

	cout << "Availables classes: " << "\n";
	cout << "(0) Warrior" << "\n";
	cout << "(1) Mage" << "\n";
	cout << "(2) Archer" << "\n";
	cout << "(3) Explorer" << "\n\n";

	cout << "Choose a class:" << "\n";
	cin >> classIndex;
	while (cin.fail() || classIndex < 0 || classIndex > 3)
	{
		cout << "Faulty input! Enter again." << endl;
		cout << "\n" << "Choice (0 - 3): ";
		cin >> classIndex;
	}

	switch (classIndex)
	{
	case Character::Type::Warrior:
		characters.push_back(new Warrior());
		break;
	case Character::Type::Mage:
		characters.push_back(new Mage());
		break;
	case Character::Type::Archer:
		characters.push_back(new Archer());
		break;
	case Character::Type::Explorer:
		characters.push_back(new Explorer());
		break;
	default:
		break;
	}

	//characters.push_back(Character());
	activeCharacter = characters.size() - 1;
	characters[activeCharacter]->initialize(name);
}

void Game::levelUpCharacter()
{
	system("CLS");

	this->characters[activeCharacter]->levelUp();

	if (this->characters[activeCharacter]->getStatPoints() > 0)
	{
		cout << "You have statpoints to allocate!" << "\n\n";

		cout << "Stat to upgrade: " << "\n";
		cout << "0: Strength " << "\n";
		cout << "1: Vitality " << "\n";
		cout << "2: Dexterity " << "\n";
		cout << "3: Intelligence " << "\n";

		cin >> this->choice;

		while (cin.fail() || this->choice > 3)
		{
			cout << "Faulty input!" << "\n";
			cin.clear();
			cin.ignore(100, '\n');

			cout << "Stat to upgrade: " << "\n";
			cin >> this->choice;
		}

		cin.ignore(100, '\n');
		cout << "\n";

		switch (this->choice)
		{
		case 0: //STRENGTH
			this->characters[activeCharacter]->addToStat(0, 1);
			break;

		case 1://VITALITY
			this->characters[activeCharacter]->addToStat(1, 1);
			break;

		case 2://DEXTERITY
			this->characters[activeCharacter]->addToStat(2, 1);
			break;

		case 3://INTELLIGENCE
			this->characters[activeCharacter]->addToStat(3, 1);
			break;

		default:

			break;
		}
	}
}

void Game::characterMenu()
{
	do
	{
		system("CLS");
		cout << gui::menu_title("CHARACTER MENU");

		cout << gui::menu_divider();

		characters[activeCharacter]->printStats();

		cout << gui::menu_divider();

		cout << "= MENU =" << "\n";
		cout << gui::menu_item(0, "Back");
		cout << gui::menu_item(1, "Print Inventory");
		cout << gui::menu_item(2, "Equip Item");
		cout << "\n";
		cout << "Choice: ";

		cin >> this->choice;

		while (cin.fail() || this->choice < 0 || this->choice > 2)
		{
			cout << "Faulty input!" << "\n";
			cin.clear();
			cin.ignore(100, '\n');

			cout << "= MENU =" << "\n";
			cout << "0: Back" << "\n";
			cout << "1: Print Inventory" << "\n";
			cout << "2: Equip Item" << "\n";
			cout << "\n";
			cout << "Choice: ";
			cin >> this->choice;
		}

		cin.ignore(100, '\n');
		cout << "\n";

		switch (this->choice)
		{
		case 1:
			cout << this->characters[this->activeCharacter]->getInvAsString();

			break;

		case 2:
			cout << this->characters[this->activeCharacter]->getInvAsString();

			cout << "Item index: ";
			cin >> this->choice;

			while (cin.fail() || this->choice < 0 || this->choice >= this->characters[this->activeCharacter]->getInventorySize())
			{
				cout << "Faulty input!" << "\n";
				cin.clear();
				cin.ignore(100, '\n');

				cout << "Item index: ";
				cin >> this->choice;
			}

			cin.ignore(100, '\n');
			cout << "\n";

			this->characters[this->activeCharacter]->equipItem(this->choice);

			break;
		default:
			break;
		}

		if (this->choice > 0)
		{
			gui::pausePressKey();
		}

	} while (this->choice > 0);
}

void Game::saveCharacters()
{
	ofstream outFile(fileName);

	if (outFile.is_open())
	{
		for (size_t i = 0; i < this->characters.size(); i++)
		{
			outFile << this->characters[i]->getAsString() << "\n";
			outFile << this->characters[i]->getInvAsStringSave() << "\n";
		}
	}

	outFile.close();
}

void Game::loadCharacters()
{
	ifstream inFile(fileName);

	this->characters.clear();

	string name = "";
	//Character::Type classType = Character::Type::Warrior;
	int classTypeInt = 0;
	int distanceTravelled = 0;
	int gold = 0;
	int level = 0;
	int exp = 0;
	int strength = 0;
	int vitality = 0;
	int dexterity = 0;
	int intelligence = 0;
	int hp = 0;
	int stamina = 0;
	int statPoints = 0;

	//Item
	int itemType = 0;
	int defence = 0;
	int type = 0;
	int damageMin = 0;
	int damageMax = 0;
	//name
	//level
	int buyValue = 0;
	int sellValue = 0;
	int rarity = 0;

	Inventory tempItems;

	string line = "";
	stringstream str;

	if (inFile.is_open())
	{
		while (getline(inFile, line))
		{
			str.str(line);
			str >> name;
			str >> classTypeInt;
			str >> distanceTravelled;
			str >> gold;
			str >> level;
			str >> exp;
			str >> strength;
			str >> vitality;
			str >> dexterity;
			str >> intelligence;
			str >> hp;
			str >> stamina;
			str >> statPoints;

			Character* temp;

			switch (classTypeInt)
			{
			case Character::Type::Warrior:
				temp = new Warrior(name, static_cast<Character::Type>(classTypeInt), distanceTravelled, gold, level,
					exp, strength, vitality, dexterity, intelligence,
					hp, stamina, statPoints);
				break;

			case Character::Type::Mage:
				temp = new Mage(name, static_cast<Character::Type>(classTypeInt), distanceTravelled, gold, level,
					exp, strength, vitality, dexterity, intelligence,
					hp, stamina, statPoints);
				break;

			case Character::Type::Archer:
				temp = new Archer(name, static_cast<Character::Type>(classTypeInt), distanceTravelled, gold, level,
					exp, strength, vitality, dexterity, intelligence,
					hp, stamina, statPoints);
				break;

			case Character::Type::Explorer:
				temp = new Explorer(name, static_cast<Character::Type>(classTypeInt), distanceTravelled, gold, level,
					exp, strength, vitality, dexterity, intelligence,
					hp, stamina, statPoints);
				break;

			default:
				temp = new Character(name, static_cast<Character::Type>(classTypeInt), distanceTravelled, gold, level,
				exp, strength, vitality, dexterity, intelligence,
				hp, stamina, statPoints);
				break;
			}

			//Weapon
			str >>
				itemType >> name >> level >>
				rarity >> buyValue >> sellValue >>
				damageMin >> damageMax;

			Weapon weapon(damageMin, damageMax, name, level, buyValue, sellValue, rarity);

			//Armor head
			str >>
				itemType >> name >> level >>
				rarity >> buyValue >> sellValue >>
				defence >> type;

			Armor armor_head(type, defence, name, level, buyValue, sellValue, rarity);

			//Armor chest
			str >>
				itemType >> name >> level >>
				rarity >> buyValue >> sellValue >>
				defence >> type;

			Armor armor_chest(type, defence, name, level, buyValue, sellValue, rarity);

			//Armor arms
			str >>
				itemType >> name >> level >>
				rarity >> buyValue >> sellValue >>
				defence >> type;

			Armor armor_arms(type, defence, name, level, buyValue, sellValue, rarity);

			//Armor legs
			str >>
				itemType >> name >> level >>
				rarity >> buyValue >> sellValue >>
				defence >> type;

			Armor armor_legs(type, defence, name, level, buyValue, sellValue, rarity);

			temp->setWeapon(weapon);
			temp->setArmorHead(armor_head);
			temp->setArmorChest(armor_chest);
			temp->setArmorArms(armor_arms);
			temp->setArmorLegs(armor_legs);

			//Add Inventory Items
			str.clear();
			line.clear();
			getline(inFile, line);

			str.str(line);

			while (str >>
				itemType >> name >> level >>
				rarity >> buyValue >> sellValue >>
				damageMin >> damageMax)
			{
				temp->addItem(
					Weapon
					(
						damageMin,
						damageMax,
						name,
						level,
						buyValue,
						sellValue,
						rarity
					)
				);
			}

			str.clear();
			line.clear();
			getline(inFile, line);

			str.str(line);

			while (str >>
				itemType >> name >> level >>
				rarity >> buyValue >> sellValue >>
				defence >> type)
			{
				temp->addItem(
					Armor
					(
						type,
						defence,
						name,
						level,
						buyValue,
						sellValue,
						rarity
					)
				);
			}

			this->characters.push_back(temp);
			cout << "Character " << temp->getName() << " loaded!\n";

			str.clear();
		}
	}

	inFile.close();
	cout << endl;

	if (this->characters.size() <= 0)
	{
		throw "ERROR! NO CHARACTERS LOADED OR EMPTY FILE!";
	}
}

void Game::selectCharacter()
{
	system("CLS");

	if (this->characters.size() <= 0)
	{
		cout << "! You can't select a character : there are no saves !" << "\n\n";
		mainMenu();
		return;
	}

	cout << "Select character: " << "\n\n";

	for (size_t i = 0; i < this->characters.size(); i++)
	{
		cout << "Index: " << i+1 << " = " << this->characters[i]->getName() << " Level: " << this->characters[i]->getLevel() << "\n";
	}

	cout << "\n";

	cout << "(0) Back" << "\n\n";

	cout << "Choice: ";

	cin >> this->choice;

	while (cin.fail() || this->choice >= (this->characters.size()+1) || this->choice < 0)
	{
		cout << "Faulty input!" << "\n";
		cin.clear();
		cin.ignore(100, '\n');

		cout << "Select character: " << "\n";
		cin >> this->choice;
	}

	cin.ignore(100, '\n');
	cout << "\n";

	if (this->choice == 0)
	{
		mainMenu();
		return;
	}

	this->activeCharacter = this->choice-1;

	cout << this->characters[this->activeCharacter]->getName() << " is SELECTED!" << "\n\n";

	gui::pausePressKeyClear();
}

void Game::travel()
{
	this->characters[activeCharacter]->travel();

	Event ev;

	if (this->characters[activeCharacter]->getDistTravel() % 6 == 0)
	{
		//ev.bossEncouter(this->characters[activeCharacter], this->bosses);
		ev.bossEncouter(*this->characters[activeCharacter]);
	} 
	else
	{
		ev.generateEvent(*this->characters[activeCharacter], this->enemies);
	}
}

void Game::rest()
{
	int restCost = this->characters[this->activeCharacter]->getHPMax() - this->characters[this->activeCharacter]->getHP();
	cout << "= REST =" << "\n\n";
	cout << "Resting costs you: " << restCost << "\n";
	cout << "Your gold: " << this->characters[this->activeCharacter]->getGold() << "\n";
	cout << "HP: " << this->characters[this->activeCharacter]->getHP() << " / " << this->characters[this->activeCharacter]->getHPMax() << "\n\n";

	if (this->characters[this->activeCharacter]->getGold() < restCost)
	{
		cout << "Not enough money, sorry buddy!" << "\n\n";
	}
	else if (this->characters[this->activeCharacter]->getHP() >= this->characters[this->activeCharacter]->getHPMax())
	{
		cout << "Already at full health buffy!" << "\n\n";
	}
	else
	{
		cout << "\n\n Rest? (0) Yes, (1) No..." << "\n\n";

		cin >> this->choice;

		while (cin.fail() || this->choice < 0 || this->choice > 1)
		{
			cout << "Faulty input!" << "\n";
			cin.clear();
			cin.ignore(100, '\n');

			cout << "\n\n Rest? (0) Yes, (1) No..." << "\n\n";
			cin >> this->choice;
		}

		cin.ignore(100, '\n');
		cout << "\n";

		if (this->choice == 0)
		{
			this->characters[this->activeCharacter]->resetHP();
			this->characters[this->activeCharacter]->payGold(restCost);
			cout << "RESTED!" << "\n\n";
		}
		else
		{
			cout << "Maybe next time!" << "\n\n";
		}

		gui::pausePressKeyClear();
	}
}

//void Game::setBosses(DynamicArray<Boss>& bosses)
//{
//	this->bosses = bosses;
//}
