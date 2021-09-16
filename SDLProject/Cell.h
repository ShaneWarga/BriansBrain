#pragma once
#include "GameObject.h"
#include "CellStates.h"
#include <vector>
class Cell : public GameObject
{
private:
	std::unique_ptr<SDL_Rect> cell;
public:
	Cell(std::unique_ptr<Vector2> initialPosition, int size);
	~Cell();
	void Render() override;
	void Update() override;
};


