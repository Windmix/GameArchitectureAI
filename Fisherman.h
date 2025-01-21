#pragma once
#include <string>
#include <memory>

// Forward declare State
class State;

class Fisherman
{
	unsigned int entity;
	std::string name;
	std::shared_ptr<State> currentState;

public:

	Fisherman();
	Fisherman(std::shared_ptr<State> initialState);

	void setCurrentState(std::shared_ptr<State> newtate);
	void update(std::shared_ptr<Fisherman> fisherman);
	
	void setName(std::string newName);
	std::string getName();
};