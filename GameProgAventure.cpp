#include"Game.h"

int main()
{
	srand(time(NULL));

	Game* game = Game::getInstance();
	game->initGame();
	game->mainMenu();

	while (game->getPlaying())
	{
		game->update();
	}

	return 0;
}