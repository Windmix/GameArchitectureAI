#include "FishingState.h"

void FishingState::handle(std::shared_ptr<Fisherman> fisherman)
{
	std::cout << "Fishing in progress..." << std::endl;
}

void FishingState::enterState(std::shared_ptr<Fisherman> fisherman)
{
	std::cout << fisherman->getName() << " is fishing." << std::endl;

}

void FishingState::exitState(std::shared_ptr<Fisherman> fisherman)
{
	std::cout << fisherman->getName() << " stops fishing." << std::endl;
}
