#pragma once
#include "State.h"
#include "Fisherman.h"
class MarketState : public State<Fisherman>
{
public:
	static std::shared_ptr<MarketState> instance();
	void handle(std::shared_ptr<Fisherman> SPfisherman) override;
	void enterState(std::shared_ptr<Fisherman> SPfisherman) override;
	void exitState(std::shared_ptr<Fisherman> SPfisherman) override;
};