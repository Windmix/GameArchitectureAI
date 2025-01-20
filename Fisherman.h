#pragma once
#include <memory>
#include "State.h"
class Fisherman
{
	std::shared_ptr<State> currentState;
public:
	Fisherman();
	Fisherman(std::shared_ptr<State> initialState);
	void setCurrentState(std::shared_ptr<State> state);
	void update();
};