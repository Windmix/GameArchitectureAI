#pragma once
#include "State.h"
#include "Fisherman.h"

class RestingState : public State<Fisherman>
{
public:

	static std::shared_ptr<RestingState> instance();
	void handle(std::shared_ptr<Fisherman> owner) override;
	void enterState(std::shared_ptr<Fisherman> owner) override;
	void exitState(std::shared_ptr<Fisherman> owner) override;
};