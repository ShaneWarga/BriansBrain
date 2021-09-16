#pragma once
#include "GameObject.h"

class Rectangle : public GameObject
{
	SDL_Rect rectangle;

public:
	Rectangle(std::unique_ptr<Vector2> initialPosition, int width, int height);
	void Render() override;
	void Update() override;
};

