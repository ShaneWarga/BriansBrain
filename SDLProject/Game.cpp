#include "Game.h"

#define WindowWidth 1280
#define WindowHeight 720
#define CellSize 4

Game::Game() {
	mWindow = nullptr;
	mRenderer = nullptr;
	mTicksCount = 0; 
	mIsRunning = true;
	playerPositionX = 0;
	playerPositionY = 0;
}

int get2DIndex(int x, int y, int division=1) {
	int coord =  x + (division * y);
	return coord;
}

void Game::CreateObjects() {
	for (int j = 0; j < WindowHeight /CellSize; j++) {
		for (int i = 0; i < WindowWidth/ CellSize; i++) {
			std::unique_ptr<Vector2> initPos = std::unique_ptr<Vector2>(new Vector2());
			initPos.get()->x = i * CellSize;
			initPos.get()->y = j * CellSize;
			std::shared_ptr<GameObject> cell = std::shared_ptr<GameObject>(new Cell(std::move(initPos), CellSize));
			cell->SetColorData(0, 0, 0, 255);
			cell->SetRenderer(mRenderer);
			gameObjects.push_back(std::move(cell));
		}
	}
	std::shared_ptr<GameObject> currentCell;
	for (int i = 0; i < WindowWidth / CellSize; i++) {
		for (int j = 0; j < WindowHeight / CellSize; i++) {
			try {
				currentCell = gameObjects.at(get2DIndex(i, j, WindowWidth / CellSize));
			}
			catch (const std::out_of_range& oor) { return; }
			try {
				currentCell->neighbors.push_back(gameObjects.at(size_t(get2DIndex(i - 1, j, WindowWidth/ CellSize))));
			}
			catch (const std::out_of_range& oor) {}
			try {
				currentCell->neighbors.push_back(gameObjects.at(size_t(get2DIndex(i + 1, j, WindowWidth/ CellSize))));
			}catch(const std::out_of_range& oor){}
			try {
				currentCell->neighbors.push_back(gameObjects.at(size_t(get2DIndex(i, j+1, WindowWidth/ CellSize))));
			}
			catch (const std::out_of_range& oor) {}
			try {
				currentCell->neighbors.push_back(gameObjects.at(size_t(get2DIndex(i, j-1, WindowWidth/ CellSize))));
			}
			catch (const std::out_of_range& oor) {}
			try {
				currentCell->neighbors.push_back(gameObjects.at(size_t(get2DIndex(i + 1, j+1, WindowWidth/ CellSize))));
			}
			catch (const std::out_of_range& oor) {}
			try {
				currentCell->neighbors.push_back(gameObjects.at(size_t(get2DIndex(i + 1, j-1, WindowWidth/ CellSize))));
			}
			catch (const std::out_of_range& oor) {}
			try {
				currentCell->neighbors.push_back(gameObjects.at(size_t(get2DIndex(i - 1, j+1, WindowWidth/ CellSize))));
			}
			catch (const std::out_of_range& oor) {}
			try {
				currentCell->neighbors.push_back(gameObjects.at(size_t(get2DIndex(i -1, j-1, WindowWidth/ CellSize))));
			}
			catch (const std::out_of_range& oor) {}

		}
	}

}

void updatePositions(std::vector<std::unique_ptr<GameObject>>* objects, RenderQueue* renderer) {
	for (auto i = objects->begin(); i < objects->end(); i++) {
		Vector2 position;
		position.x = i->get()->GetPosition()->x + 50;
		position.y = i->get()->GetPosition()->y - 50;
		i->get()->SetPosition(position);
		renderer->Push(i->get());
	}
}

void updateColors(std::vector<std::shared_ptr<GameObject>>* objects, RenderQueue* renderer) {
	srand(time(NULL));
	for (auto i = objects->begin(); i < objects->end(); i++) {
		i->get()->Update();
		renderer->Push(i->get());
	}
}

//Brian's Brain
void Game::playerChangeState(int* x, int* y) {
	try {
		std::shared_ptr<GameObject> clickedCell = gameObjects.at(get2DIndex(*x/CellSize, *y/CellSize, WindowWidth / CellSize));
		for (auto neighbors : clickedCell.get()->neighbors) {
			neighbors.get()->state->DEATH = false;
			neighbors.get()->state->STATE_0 = true;
			neighbors.get()->state->STATE_1 = false;
			neighbors.get()->state->STATE_2 = false;
		}
		clickedCell->state->DEATH = false;
		clickedCell->state->STATE_0 = true;
		clickedCell->state->STATE_1 = false;
		clickedCell->state->STATE_2 = false;
	}
	catch (const std::out_of_range& oor) {
		return;
	}
}

//Conway
//void Game::playerChangeState(int* x, int* y) {
//	try {
//		std::shared_ptr<GameObject> clickedCell = gameObjects.at(get2DIndex(*x / CellSize, *y / CellSize, WindowWidth / CellSize));
//		for (auto neighbors : clickedCell.get()->neighbors) {
//			neighbors.get()->state->STATE_1 = true;
//			neighbors.get()->state->STATE_2 = false;
//			neighbors.get()->SetColorData(255, 255, 255, 255);
//		}
//		clickedCell->state->STATE_1 = true;
//		clickedCell->state->STATE_2 = false;
//		clickedCell->SetColorData(255, 255, 255, 255);
//	}
//	catch (const std::out_of_range& oor) {
//		return;
//	}
//}

void Game::wasdMove(SDL_Event* e){
	switch (e->key.keysym.sym)
	{
	case SDLK_w:
		if(playerPositionY - CellSize <= 0){
			return;
		}
		else {
			playerPositionY = playerPositionY - CellSize;
			playerChangeState(&playerPositionX, &playerPositionY);
		}
	case SDLK_a:
		if (playerPositionX - CellSize <= 0) {
			return;
		}
		else {
			playerPositionX = playerPositionX - CellSize;
			playerChangeState(&playerPositionX, &playerPositionY);
		}
	case SDLK_s:
		if (playerPositionY + CellSize >= WindowHeight) {
			return;
		}
		else {
			playerPositionY += CellSize;
			playerChangeState(&playerPositionX, &playerPositionY);
		}
	case SDLK_d:
		if (playerPositionX + CellSize >= WindowWidth) {
			return;
		}
		else {
			playerPositionX += CellSize;
			playerChangeState(&playerPositionX, &playerPositionY);
		}
	default:
		return;
	}
}


void Game::GenerateOutput(double deltaTime) {
	updateCounter++;
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);
	SDL_RenderClear(mRenderer);
	RenderQueue renderObjects(mRenderer);
	if (gameObjects.empty()) { CreateObjects(); };
	if (!gameObjects.empty()) {
		if (true) {
			SDL_Event e;
			while (SDL_PollEvent(&e)) {
				switch (e.type) {
				case SDL_MOUSEBUTTONDOWN:
					int x, y;
					SDL_GetMouseState(&x, &y);
					playerChangeState(&x, &y);
					break;
				case SDL_KEYDOWN:
					wasdMove(&e);
				}


			}
			//updatePosition(&gameObjects, &renderObjects);
			updateColors(&gameObjects, &renderObjects);
			renderObjects.RenderAll();
			SDL_UpdateWindowSurface(mWindow);
			SDL_Delay(100);
			GenerateOutput(deltaTime);
		}else{return;}
	}

}


bool Game::Initialize() {
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	mWindow = SDL_CreateWindow("Cellular Automaton", 100, 100, WindowWidth, WindowHeight, 0);
	if (!mWindow) {
		SDL_Log("Failed to create window %s", SDL_GetError());
		return false;
	}
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer) {
		SDL_Log("Failed to create renderer %s", SDL_GetError());
		return false;
	}

	
	return true;
}


