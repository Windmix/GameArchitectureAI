#pragma once
#include <iostream>
#include <memory>

// Forward declare State

template <class entityType>
class State
{
public:
	virtual void handle(std::shared_ptr<entityType> owner) = 0;
	virtual void enterState(std::shared_ptr<entityType> owner) = 0;
	virtual void exitState(std::shared_ptr<entityType> owner) = 0;
};