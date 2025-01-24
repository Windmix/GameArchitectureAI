#include "RestingState.h"
#include "FishingState.h"
#include "MarketState.h"
#include "LemonadeStandState.h"
#include "WalkingState.h"

std::shared_ptr<RestingState> RestingState::instance()
{
	static std::shared_ptr<RestingState> restingState = std::make_shared<RestingState>();
	return restingState;
}

void RestingState::handle(std::shared_ptr<Fisherman> SPfisherman)
{
	SPfisherman->setCurrentLocation(Fisherman::locationType::house);

	SPfisherman->IncreaseFatigue(-10);
	SPfisherman->eatFood(1); //to componsate the usage of food while sleep
	SPfisherman->drinkWater(2); // to componsate the usage of water while sleep

	std::cout << "\n[name]: " << SPfisherman->getName() << "\n[ID]: " << SPfisherman->getEntityID() <<
		"\n[Money] " << SPfisherman->getMoneyInBank() << " $\n[fish]: " << SPfisherman->getFishCarried() <<
		"\nZzzZzzzZz\n" << std::endl;

	if (SPfisherman->isFishingBagFull())
	{

		if (!SPfisherman->getIsWalking())
		{

			std::cout << "\n[name]: " << SPfisherman->getName() << "\n[ID]: " << SPfisherman->getEntityID() <<
				"\n[Money] " << SPfisherman->getMoneyInBank() << " $\n[fish]: " << SPfisherman->getFishCarried() <<
				" ~ uugghh.. gonna go sell my fishes\n" << std::endl;

			WalkingState::instance()->setDestination(static_cast<int>(Fisherman::locationType::market));
			SPfisherman->setIsWalking(true);
			SPfisherman->setCurrentState(WalkingState::instance());
		}
	}
	if (SPfisherman->isThirsty())
	{
		if (!SPfisherman->getIsWalking())
		{
			std::cout << "\n[name]: " << SPfisherman->getName() << "\n[ID]: " << SPfisherman->getEntityID() <<
				"\n[Money] " << SPfisherman->getMoneyInBank() << " $\n[fish]: " << SPfisherman->getFishCarried() <<
				"\n~ gghh.. I am really thirsty, I will go to the lemonade stand and get a drink\n" << std::endl;

			WalkingState::instance()->setDestination(static_cast<int>(Fisherman::locationType::lemonadeStand));
			SPfisherman->setIsWalking(true);
			SPfisherman->setCurrentState(WalkingState::instance());
		}
	}
	if (SPfisherman->getFatigue() <= 5)
	{
		if (!SPfisherman->getIsWalking())
		{
			std::cout << "\n[name]: " << SPfisherman->getName() << "\n[ID]: " << SPfisherman->getEntityID() <<
				"\n[Money] " << SPfisherman->getMoneyInBank() << " $\n[fish]: " << SPfisherman->getFishCarried() <<
				"\n~ I am fully RESTED!, time to get to work!\n" << std::endl;
			WalkingState::instance()->setDestination(static_cast<int>(Fisherman::locationType::pond));
			SPfisherman->setIsWalking(true);
			SPfisherman->setCurrentState(WalkingState::instance());
		}
	}

}

void RestingState::enterState(std::shared_ptr<Fisherman> SPfisherman)
{

	std::cout << "\n[name]: " << SPfisherman->getName() << "\narrived into house" << std::endl;

	if (SPfisherman->getCurrentLocation() != Fisherman::locationType::house)
	{
		WalkingState::instance()->setDestination(static_cast<int>(Fisherman::locationType::house));
		std::cout << "\n[name]: " << SPfisherman->getName() << "\nNice to get some sleep" << std::endl;
		
	}
	
}


void RestingState::exitState(std::shared_ptr<Fisherman> SPfisherman)
{
	std::cout << "\n[name]: " << SPfisherman->getName() << "\nFully rested now, time to head to work!" << std::endl;
}