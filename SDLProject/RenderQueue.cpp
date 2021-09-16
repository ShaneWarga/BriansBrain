#include "RenderQueue.h"

RenderQueue::RenderQueue(SDL_Renderer* renderer) { mRenderer = renderer; }
RenderQueue::~RenderQueue() {}

void RenderQueue::Push(GameObject* object) {
	renderQueue.push(object);
}

void RenderQueue::RenderOne() {
	SDL_RenderClear(mRenderer);
	renderQueue.front()->Render();
	renderQueue.pop();
	SDL_RenderPresent(mRenderer);
}

void RenderQueue::RenderAll() {
	while (!renderQueue.empty()) {
		renderQueue.front()->Render();
		renderQueue.pop();
	}
	SDL_RenderPresent(mRenderer);
	renderQueue = std::queue<GameObject*>();
}

void RenderQueue::Clear() {
	while (!renderQueue.empty()) {
		renderQueue.pop();
	}
}