#pragma once
#include "State.h"
#include "Fisherman.h"

class WalkingState : public State<Fisherman>
{
private:
	int ticks;
	int destination;
	
public:
	Fisherman::locationType locationName;
	
	static std::shared_ptr<WalkingState> instance();
	void handle(std::shared_ptr<Fisherman> SPfisherman) override;
	void enterState(std::shared_ptr<Fisherman> SPfisherman) override;
	void exitState(std::shared_ptr<Fisherman> SPfisherman) override;
	void setDestination(int destinationValue);
	int getDestination();
	int getTicks();
	
	
};