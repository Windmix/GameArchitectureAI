#include "State.h"

void State::enterState(std::shared_ptr<Fisherman> fisherman)
{
	std::cout << "Entering state." << std::endl;
}

void State::exitState(std::shared_ptr<Fisherman> fisherman)
{
	std::cout << "Exiting state." << std::endl;
}
