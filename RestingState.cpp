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

	std::cout << "[name]: " << SPfisherman->getName()
		<< " [ID]: " << SPfisherman->getEntityID()
		<<" [Money] " << SPfisherman->getMoneyInBank()
		<< " $ [fish]: " << SPfisherman->getFishCarried() 
		<<" [fatigue]: " << SPfisherman->getFatigue() 
		<<" ZzzZzzzZz ";

	if (SPfisherman->getFatigue() > 300) // reset fatigue on if fisherman starts on home and sleep 
	{
		SPfisherman->ResetFatigue(0);
	}

	if (SPfisherman->isFishingBagFull())
	{

		if (!SPfisherman->getIsWalking())
		{

			std::cout << " [name]: " << SPfisherman->getName() << " [ID]: " << SPfisherman->getEntityID() <<
				" [Money] " << SPfisherman->getMoneyInBank() << " $ [fish]: " << SPfisherman->getFishCarried() <<
				" ~ uugghh.. gonna go sell my fishes " << std::endl;

			WalkingState::instance()->setDestination(static_cast<int>(Fisherman::locationType::market));
			SPfisherman->setIsWalking(true);
			SPfisherman->setCurrentState(WalkingState::instance());
		}
	}
	if (SPfisherman->isThirsty())
	{
		if (!SPfisherman->getIsWalking())
		{
			std::cout << " [name]: " << SPfisherman->getName() << " [ID]: " << SPfisherman->getEntityID() <<
				" [Money] " << SPfisherman->getMoneyInBank() << " $ [fish]: " << SPfisherman->getFishCarried() <<
				" ~ gghh.. I am really thirsty, I will go to the lemonade stand and get a drink " << std::endl;

			WalkingState::instance()->setDestination(static_cast<int>(Fisherman::locationType::lemonadeStand));
			SPfisherman->setIsWalking(true);
			SPfisherman->setCurrentState(WalkingState::instance());
		}
	}
	if (SPfisherman->getFatigue() < 5)
	{
		if (!SPfisherman->getIsWalking())
		{
			std::cout << " [name]: " << SPfisherman->getName() << " [ID]: " << SPfisherman->getEntityID() <<
				" [Money] " << SPfisherman->getMoneyInBank() << " $ [fish]: " << SPfisherman->getFishCarried() <<
				" ~ I am fully RESTED!, time to get to work! " << std::endl;
			setRandomWorkInstance(SPfisherman);
		}
	}

}

void RestingState::enterState(std::shared_ptr<Fisherman> SPfisherman)
{

	std::cout << " [name]: " << SPfisherman->getName() << " arrived into house" << std::endl;

	if (SPfisherman->getCurrentLocation() != Fisherman::locationType::house)
	{
		WalkingState::instance()->setDestination(static_cast<int>(Fisherman::locationType::house));
		std::cout << " [name]: " << SPfisherman->getName() << " Nice to get some sleep" << std::endl;
		
	}
	
}


void RestingState::exitState(std::shared_ptr<Fisherman> SPfisherman)
{
	std::cout << " [name]: " << SPfisherman->getName() << " Fully rested now, time to head to work!" << std::endl;
}

void RestingState::setRandomWorkInstance(std::shared_ptr<Fisherman> SPfisherman)
{
	int interval = 5; // between 0,4
	srand(static_cast<unsigned>(time(0)));

	int randomDice = rand() % interval;

	switch (randomDice)
	{
	case 0:
	{
		WalkingState::instance()->setDestination(static_cast<int>(Fisherman::locationType::pond));
		SPfisherman->setIsWalking(true);
		SPfisherman->setCurrentState(WalkingState::instance());
		break;
	}
	case 1:
	{
		WalkingState::instance()->setDestination(static_cast<int>(Fisherman::locationType::fishingSouvenirShop));
		SPfisherman->setIsWalking(true);
		SPfisherman->setCurrentState(WalkingState::instance());
		break;
	}
	case 2:
	{
		WalkingState::instance()->setDestination(static_cast<int>(Fisherman::locationType::pond));
		SPfisherman->setIsWalking(true);
		SPfisherman->setCurrentState(WalkingState::instance());
		break;
	}
	case 3:
	{
		WalkingState::instance()->setDestination(static_cast<int>(Fisherman::locationType::fishingSouvenirShop));
		SPfisherman->setIsWalking(true);
		SPfisherman->setCurrentState(WalkingState::instance());
		break;
	}
	case 4:
		WalkingState::instance()->setDestination(static_cast<int>(Fisherman::locationType::fishingSouvenirShop));
		SPfisherman->setIsWalking(true);
		SPfisherman->setCurrentState(WalkingState::instance());

	default:
		break;
	}
}
