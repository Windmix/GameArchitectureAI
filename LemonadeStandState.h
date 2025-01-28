#pragma once
#include "State.h"
#include "Fisherman.h"
class LemonadeStandState : public State<Fisherman>
{
public:
	struct lemonadeDrink
	{
		int drink = 60;
	};
public:
	LemonadeStandState();
	static std::shared_ptr<LemonadeStandState> instance();
	void handle(std::shared_ptr<Fisherman> SPfisherman) override;
	void enterState(std::shared_ptr<Fisherman> SPfisherman) override;
	void exitState(std::shared_ptr<Fisherman> SPfisherman) override;

	void setRandomWorkInstance(std::shared_ptr<Fisherman> SPfisherman);
};