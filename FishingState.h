#pragma once
#include "State.h"
#include "Fisherman.h"


class FishingState : public State<Fisherman>
{
public:
	FishingState();

	static std::shared_ptr<FishingState> instance();
	void handle(std::shared_ptr<Fisherman> SPfisherman) override;
	void enterState(std::shared_ptr<Fisherman> SPfisherman) override;
	void exitState(std::shared_ptr<Fisherman> SPfisherman) override;

	//void setRandomWorkInstance(std::shared_ptr<Fisherman> SPfisherman);
};

