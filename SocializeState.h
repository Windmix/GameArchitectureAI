#pragma once
#include "State.h"
#include "Fisherman.h"
class SocializeState :public State<Fisherman>
{
public:
	static std::shared_ptr<SocializeState> instance();
	void handle(std::shared_ptr<Fisherman> SPfisherman) override;
	void enterState(std::shared_ptr<Fisherman> SPfisherman) override;
	void exitState(std::shared_ptr<Fisherman> SPfisherman) override;

	bool onMessage(std::shared_ptr<Fisherman> SPfisherman, Telegram& telegram) override;
};