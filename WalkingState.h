#pragma once
#include "State.h"
#include "Fisherman.h"

class WalkingState : public State<Fisherman>
{

public:
	static std::shared_ptr<WalkingState> instance();
	void handle(std::shared_ptr<Fisherman> SPfisherman) override;
	void enterState(std::shared_ptr<Fisherman> SPfisherman) override;
	void exitState(std::shared_ptr<Fisherman> SPfisherman) override;

	bool onMessage(std::shared_ptr<Fisherman> SPfisherman, Telegram& telegram) override;
};