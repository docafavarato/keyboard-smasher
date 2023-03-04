#include <iostream>
#include "Game.h"

int main() {
	std::srand(time(NULL));
	Game game;

	while (game.running()) {
		game.update();

		game.render();
	}

	return 0;
}