#include "GameObject.h"


GameObject& GameObject::SetRenderer(SDL_Renderer* renderer) {
	state = std::unique_ptr<CellStates>(new CellStates());
	state.get()->INIT = true;
	state.get()->STATE_0 = false;
	state.get()->STATE_1 = false;
	state.get()->STATE_2 = false;
	state.get()->DEATH = false;
	mRenderer = renderer;
	return *this;
}

GameObject& GameObject::SetColorData(int red, int green, int blue, int alpha) {
	objectColor.get()->RED = red;
	objectColor.get()->GREEN = green;
	objectColor.get()->BLUE = blue;
	objectColor.get()->ALPHA = alpha;
	return *this;
}


void GameObject::SetPosition(Vector2 pos) {
	position.get()->x = pos.x;
	position.get()->y = pos.y;
	Update();
}

Vector2* GameObject::GetPosition() {
	return position.get();
}