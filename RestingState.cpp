#include "RestingState.h"
#include "FishingState.h"

void RestingState::handle(std::shared_ptr<Fisherman> fisherman)
{
	std::cout << fisherman->getName() << " is resting." << std::endl;

	//finish resting
	fisherman->setCurrentState(std::make_shared<FishingState>());
}

void RestingState::enterState(std::shared_ptr<Fisherman> fisherman)
{
	std::cout << fisherman->getName() << " starts resting." << std::endl;
}

void RestingState::exitState(std::shared_ptr<Fisherman> fisherman)
{
	std::cout << fisherman->getName() << " stops resting." << std::endl;
}
