#pragma once
#include "Vector2.h"
#include "ColorData.h"
#include "CellStates.h"
#include <SDL.h>
#include <memory>
#include <vector>


class GameObject {
protected: 
	SDL_Renderer* mRenderer;
	std::unique_ptr<ColorData> objectColor;
	std::unique_ptr<Vector2> position;

public:
	virtual void Render() = 0;
	virtual void Update() = 0;
	virtual ~GameObject() = default;
	GameObject& SetRenderer(SDL_Renderer* renderer);
	GameObject& SetColorData(int red, int green, int blue, int alpha);
	void SetPosition(Vector2 pos);
	Vector2* GetPosition();
	std::vector<std::shared_ptr<GameObject>> neighbors;
	std::unique_ptr<CellStates> state;
};