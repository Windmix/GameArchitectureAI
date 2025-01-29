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
	SPfisherman->setDestination(Fisherman::locationType::house);

	SPfisherman->IncreaseFatigue(-30);
	SPfisherman->eatFood(1); //to componsate the usage of food while sleep
	SPfisherman->drinkWater(2); // to componsate the usage of water while sleep

	std::cout << "[" << SPfisherman->getName()<< "] [ID]: " << SPfisherman->getEntityID()<<" [Money] " << SPfisherman->getMoneyInBank()<< " $ [fish]: " << SPfisherman->getFishCarried() <<" [fatigue]: " << SPfisherman->getFatigue() <<" ZzzZzzzZz " << std::endl;

	if (SPfisherman->getFatigue() == NULL) // reset fatigue on if fisherman starts on home and sleep 
	{
		SPfisherman->ResetFatigue(0);
	}

	else if (SPfisherman->getMoneyInBank() <= 0)
	{
		if (!SPfisherman->getIsWalking())
		{
			std::cout << "[" << SPfisherman->getName() << "] [ID]: " << SPfisherman->getEntityID() <<
				" [Money] " << SPfisherman->getMoneyInBank() << " $ [fish]: " << SPfisherman->getFishCarried() <<
				" ~ uugghh.. gonna gotta work " << std::endl;


			SPfisherman->setIsWalking(true);
			SPfisherman->setRandomWorkInstance(1);
		}
		
	}

	else if (SPfisherman->isThirsty())
	{
		if (!SPfisherman->getIsWalking())
		{
			std::cout << "[" << SPfisherman->getName() << "] [ID]: " << SPfisherman->getEntityID() <<
				" [Money] " << SPfisherman->getMoneyInBank() << " $ [fish]: " << SPfisherman->getFishCarried() <<
				" ~ gghh.. I am really thirsty, I will go to the lemonade stand and get a drink " << std::endl;

			SPfisherman->setDestination(Fisherman::locationType::lemonadeStand);
			SPfisherman->setIsWalking(true);
			SPfisherman->setCurrentState(std::make_shared<WalkingState>());
		}
	}
	else if (SPfisherman->getFatigue() < 10)
	{
		if(!SPfisherman->getIsWalking())
		{
			std::cout << "[" << SPfisherman->getName() << "] [ID]: " << SPfisherman->getEntityID() <<
				" [Money] " << SPfisherman->getMoneyInBank() << " $ [fish]: " << SPfisherman->getFishCarried() <<
				" ~ I am fully RESTED!, time to get to work! " << std::endl;
			setRandomWorkInstance(SPfisherman);
		}
	}

}

void RestingState::enterState(std::shared_ptr<Fisherman> SPfisherman)
{

	std::cout << "[" << SPfisherman->getName() << "] enter the house" << std::endl;
	
}


void RestingState::exitState(std::shared_ptr<Fisherman> SPfisherman)
{
	std::cout << "[" << SPfisherman->getName() << "] exits the house" << std::endl;
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
		SPfisherman->setDestination(Fisherman::locationType::pond);
		SPfisherman->setIsWalking(true);
		SPfisherman->setCurrentState(std::make_shared<WalkingState>());
		break;
	}
	case 1:
	{
		SPfisherman->setDestination(Fisherman::locationType::fishingSouvenirShop);
		SPfisherman->setIsWalking(true);
		SPfisherman->setCurrentState(std::make_shared<WalkingState>());
		break;
	}
	case 2:
	{
		SPfisherman->setDestination(Fisherman::locationType::pond);
		SPfisherman->setIsWalking(true);
		SPfisherman->setCurrentState(std::make_shared<WalkingState>());
		break;
	}
	case 3:
	{
		SPfisherman->setDestination(Fisherman::locationType::fishingSouvenirShop);
		SPfisherman->setIsWalking(true);
		SPfisherman->setCurrentState(std::make_shared<WalkingState>());
		break;
	}
	case 4:
		SPfisherman->setDestination(Fisherman::locationType::fishingSouvenirShop);
		SPfisherman->setIsWalking(true);
		SPfisherman->setCurrentState(std::make_shared<WalkingState>());

	default:
		break;
	}
}
