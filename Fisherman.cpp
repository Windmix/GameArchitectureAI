#include "Fisherman.h"
#include "state.h"

Fisherman::Fisherman()
{
	//
}

Fisherman::Fisherman(std::shared_ptr<State> initialState)
{
	this->currentState = initialState;
}

void Fisherman::setCurrentState(std::shared_ptr<State> newState)
{
	currentState = newState;
}

void Fisherman::update(std::shared_ptr<Fisherman> fisherman)
{
	this->currentState->handle(fisherman);
}

void Fisherman::setName(std::string newName)
{
	name = newName;
}

std::string Fisherman::getName()
{
	return this->name;
}
