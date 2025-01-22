#include "Fisherman.h"

Fisherman::Fisherman()
{
	//
}

Fisherman::Fisherman(std::shared_ptr<State> initialState)
{
	this->currentState = initialState;
}

void Fisherman::setCurrentState(std::shared_ptr<State> state)
{
	currentState = state;
}

void Fisherman::update()
{
	this->currentState->handle();
}
