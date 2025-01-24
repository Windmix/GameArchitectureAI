#include "RestingState.h"
#include "FishingState.h"
#include "MarketState.h"
#include "LemonadeStandState.h"

std::shared_ptr<RestingState> RestingState::instance()
{
	std::shared_ptr<RestingState> restingState = std::make_shared<RestingState>();
	return restingState;
}

void RestingState::handle(std::shared_ptr<Fisherman> owner)
{

	owner->IncreaseFatigue(-10);
	owner->drinkWater(2); // to componsate the usage of water while sleep

	std::cout << "\n[name]: " << owner->getName() << "\n[ID]: " << owner->getEntityID() <<
		"\n[Money] " << owner->getMoneyInBank() << " $\n[fish]: " << owner->getFishCarried() <<
		"\nZzzZzzzZz\n" << std::endl;

	if (owner->isFishingBagFull())
	{

		owner->setCurrentState(MarketState::instance());
	}
	if (owner->isThirsty())
	{
		owner->setCurrentState(LemonadeStandState::instance());
	}
	if (owner->getFatigue() <= 5)
	{
		owner->setCurrentState(FishingState::instance());
	}

}

void RestingState::enterState(std::shared_ptr<Fisherman> owner)
{

	std::cout << "\n[name]: " << owner->getName() << "arrived into house" << std::endl;

	if (owner->getCurrentLocation() != Fisherman::locationType::house)
	{
		std::cout << "\n[name]: " << owner->getName() << "Nice to get some sleep" << std::endl;
	}
	
}


void RestingState::exitState(std::shared_ptr<Fisherman> owner)
{
	std::cout << "\n[name]: " << owner->getName() << "Fully rested now, time to head to work!" << std::endl;
}