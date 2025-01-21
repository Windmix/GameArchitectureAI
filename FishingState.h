#pragma once
#include "State.h"
#include "Fisherman.h"

class FishingState : public State
{
public:
	void handle(std::shared_ptr<Fisherman> fisherman) override;
	void enterState(std::shared_ptr<Fisherman> fisherman) override;
	void exitState(std::shared_ptr<Fisherman> fisherman) override;
};

