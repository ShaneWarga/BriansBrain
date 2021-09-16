#pragma once
#include <SDL.h>
#include "GameObject.h"
#include"Rectangle.h"
#include "RenderQueue.h"
#include "Circle.h"
#include "Cell.h"
#include <vector>
#include <memory>
#include <time.h>
#include <stdexcept>
class Game
{
private:
	// void ProcessInput();
	// void UpdateGame();
	// void Shutdown();

	std::vector<std::shared_ptr<GameObject>> gameObjects;
	int updateCounter = 0;
	int playerPositionX;
	int playerPositionY;

public:
	SDL_Window* mWindow;
	bool mIsRunning;
	SDL_Renderer* mRenderer;
	Uint32 mTicksCount;
	Game();
	void GenerateOutput(double deltaTime);
	bool Initialize();
	void CreateObjects();
	void playerChangeState(int* x, int* y);
	void wasdMove(SDL_Event* e);
};

