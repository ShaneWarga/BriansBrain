#include "Game.h"

int main(int argc, char** argv) {
	Game game;
	bool success = game.Initialize();
	game.GenerateOutput(0);
	return 0;
}