#pragma once
#include "State.h"
#include "Fisherman.h"


class FishingState : public State
{
public:
	FishingState();

	static std::shared_ptr< FishingState> instance();
	void handle(std::shared_ptr<Fisherman> SPfisherman) override;
	void enterState(std::shared_ptr<Fisherman> SPfisherman) override;
	void exitState(std::shared_ptr<Fisherman> SPfisherman) override;
};

