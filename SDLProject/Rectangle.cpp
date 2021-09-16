#include "Rectangle.h"



Rectangle::Rectangle(std::unique_ptr<Vector2> initialPosition, int width, int height) {
	rectangle.x = initialPosition.get()->x;
	rectangle.y = initialPosition.get()->y;
	rectangle.w = width;
	rectangle.h = height;
	position = std::move(initialPosition);
	objectColor = std::unique_ptr<ColorData>(new ColorData());
}

void Rectangle::Render(){
	SDL_SetRenderDrawColor(mRenderer, objectColor.get()->RED, objectColor.get()->GREEN, objectColor.get()->BLUE, objectColor.get()->ALPHA);
	SDL_RenderFillRect(mRenderer, &rectangle);
}

void Rectangle::Update() {
	rectangle.x = position->x;
	rectangle.y = position->y;
}