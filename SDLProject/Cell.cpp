#include "Cell.h"


// USER INPUT CHANGE TO RANDOM STATE ON CLICK
 

Cell::Cell(std::unique_ptr<Vector2> initialPosition, int size) {
	cell = std::unique_ptr<SDL_Rect>(new SDL_Rect());
	objectColor = std::unique_ptr<ColorData>(new ColorData());
	position = std::move(initialPosition);
	cell.get()->x = position.get()->x;
	cell.get()->y = position.get()->y;
	cell.get()->w = size;
	cell.get()->h = size;
}

Cell::~Cell() {
	delete position.get();
	delete objectColor.get();
	delete state.get();
	delete cell.get();
}


void Cell::Render() {
	SDL_SetRenderDrawColor(mRenderer, objectColor.get()->RED, objectColor.get()->GREEN, objectColor.get()->BLUE, objectColor.get()->ALPHA);
	SDL_RenderFillRect(mRenderer, cell.get());
}

bool intPred(int x, int y) {
	return (x > y);
}

//Brian's Brain
void Cell::Update() {

	int nextState = 0 ;
	int stateSum0 = 0;
	int stateSum1 = 0;
	int stateSum2 = 0;
	int stateSumDeath = 0;
	for (int neighborCell = 0; neighborCell < neighbors.size(); neighborCell++){
		GameObject* currentNeighbor = neighbors.at(neighborCell).get();
		CellStates* states = currentNeighbor->state.get();
		if (states->DEATH) {
			stateSumDeath++;
		}
		if (states->STATE_0) {
			stateSum0++;
		}
		if (states->STATE_1) {
			stateSum1++;
		}
		if (states->STATE_2) {
			stateSum2++;
		}
	}
	if (state->DEATH) {
		stateSumDeath++;
	}
	if (state->STATE_0) {
		stateSum0++;
	}
	if (state->STATE_1) {
		stateSum1++;
	}
	if (state->STATE_2) {
		stateSum2++;
	}


	//state_0 = on

	//state_1 = dying 

	//state_Death = off 

	if (state.get()->INIT) {
		nextState = rand() % 4 + 1;
		state.get()->INIT = false;
		if (nextState == 1) {
			state.get()->STATE_0 = true;
			state.get()->INIT = false;
			state.get()->DEATH = false;
			state.get()->STATE_1 = false;
			state.get()->STATE_2 = false;
			this->SetColorData(255, 255, 255, 255);
			return;
		}
		if (nextState == 2) {
			state.get()->STATE_1 = true;
			state.get()->INIT = false;
			state.get()->DEATH = false;
			state.get()->STATE_0 = false;
			state.get()->STATE_2 = false;
			this->SetColorData(0, 0, 255, 255);
			return;
		}
		if (nextState == 3) {
			state.get()->STATE_2 = true;
			state.get()->INIT = false;
			state.get()->DEATH = false;
			state.get()->STATE_0 = false;
			state.get()->STATE_1 = false;
			this->SetColorData(0, 255, 255, 255);
			return;
		}
		if (nextState == 4) {
			state.get()->DEATH = true;
			state.get()->STATE_0 = false;
			state.get()->INIT = false;
			state.get()->STATE_1 = false;
			state.get()->STATE_2 = false;
			this->SetColorData(0, 0, 0, 255);
			return;
		}
	}

	if(state.get()->DEATH && stateSum0 == 2) {
		state.get()->STATE_0 = true;
		state.get()->STATE_1 = false;
		state.get()->DEATH = false;
		this->SetColorData(255, 255, 255, 255);
		return;
	}
	if (state.get()->STATE_0) {
		state.get()->STATE_0 = false;
		state.get()->STATE_1 = true;
		state.get()->DEATH = false;
		this->SetColorData(0, 0, 255, 255);
		return;
	}
	if (state.get()->STATE_1) {
		state.get()->STATE_0 = false;
		state.get()->STATE_1 = false;
		state.get()->STATE_2 = true;
		state.get()->DEATH = false;
		this->SetColorData(0, 255, 255, 255);
		return;
	}
	if (state.get()->STATE_2) {
		state.get()->STATE_0 = false;
		state.get()->STATE_1 = false;
		state.get()->STATE_2 = false;
		state.get()->DEATH = true;
		this->SetColorData(0, 0, 0, 255);
		return;
	}
}



//Conway
//void Cell::Update() {
//	int nextState = 0;
//	int stateSum1 = 0;
//	int stateSum2 = 0;
//	for (int neighborCell = 0; neighborCell < neighbors.size(); neighborCell++) {
//		GameObject* currentNeighbor = neighbors.at(neighborCell).get();
//		CellStates* states = currentNeighbor->state.get();
//		if (states->STATE_1) {
//			stateSum1++;
//		}
//		if (states->STATE_2) {
//			stateSum2++;
//		}
//	}
//	if (state.get()->INIT) {
//		nextState = rand() % 100 + 1;
//		state->INIT = false;
//		if (nextState < 9) {
//			state->STATE_1 = true;
//			state->STATE_2 = false;
//			this->SetColorData(255, 255, 255, 255);
//			return;
//		}
//		else {
//			state->STATE_2 = true;
//			state->STATE_1 = false;
//			this->SetColorData(0, 0, 0, 255);
//			return;
//		}
//	}
//
//	if (state.get()->STATE_1) {
//		if (stateSum1 == 3) {
//			return;
//		}
//		if (stateSum1 < 2) {
//			state.get()->STATE_2 = true;
//			state.get()->STATE_1 = false;
//			this->SetColorData(0, 0, 0, 255);
//			return;
//		}
//		if (stateSum1 > 3) {
//			state.get()->STATE_2 = true;
//			state.get()->STATE_1 = false;
//			this->SetColorData(0, 0, 0, 255);
//			return;
//		}
//
//	}
//	if (state.get()->STATE_2){
//		if (stateSum1 == 3) {
//			state.get()->STATE_1 = true;
//			state.get()->STATE_2 = false;
//			this->SetColorData(255, 255, 255, 255);
//			return;
//		}
//	}
//
//
//	
//}