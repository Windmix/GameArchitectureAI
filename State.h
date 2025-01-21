#pragma once
#include <iostream>
#include <memory>

// Forward declare State
class Fisherman;

class State
{
public:
	virtual void handle(std::shared_ptr<Fisherman> SPfisherman) = 0;
	virtual void enterState(std::shared_ptr<Fisherman> SPfisherman) = 0;
	virtual void exitState(std::shared_ptr<Fisherman> SPfisherman) = 0;
};