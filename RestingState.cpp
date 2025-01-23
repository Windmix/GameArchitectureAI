#include "RestingState.h"
#include "FishingState.h"

std::shared_ptr<RestingState> RestingState::instance()
{
	static std::shared_ptr<RestingState> restingState = std::make_shared<RestingState>();
	return restingState;
}

void RestingState::handle(std::shared_ptr<Fisherman> owner)
{
	std::cout << owner->getName() << " is resting." << std::endl;

	//finish resting
	owner->setCurrentState(std::make_shared<FishingState>());
}

void RestingState::enterState(std::shared_ptr<Fisherman> owner)
{
	std::cout << owner->getName() << " starts resting." << std::endl;
}

void RestingState::exitState(std::shared_ptr<Fisherman> owner)
{
	std::cout << owner->getName() << " stops resting." << std::endl;
}
