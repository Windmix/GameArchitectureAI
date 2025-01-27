#include "FishingState.h"
#include "RestingState.h"
#include "MarketState.h"
#include "RestaurantState.h"
#include "LemonadeStandState.h"
#include "WalkingState.h"


FishingState::FishingState()
{

}

std::shared_ptr<FishingState> FishingState::instance()
{
	std::shared_ptr<FishingState> fishingState = std::make_shared<FishingState>();
	return fishingState;
}

void FishingState::handle(std::shared_ptr<Fisherman> SPfisherman)
{
	SPfisherman->setCurrentLocation(Fisherman::locationType::pond);

	SPfisherman->addFishCarried(1);
	SPfisherman->IncreaseFatigue(3);
	std::cout << " [name]: " << SPfisherman->getName() << " [ID]: " << SPfisherman->getEntityID() << 
		" [Money] " << SPfisherman->getMoneyInBank() << " $ [fish]: " << SPfisherman->getFishCarried() <<
		"  ~ caught a fish! " << std::endl;

	if (SPfisherman->isFishingBagFull())
	{
		if (!SPfisherman->getIsWalking())
		{

			std::cout << " [name]: " << SPfisherman->getName() << " [ID]: " << SPfisherman->getEntityID() <<
				" [Money] " << SPfisherman->getMoneyInBank() << " $ [fish]: " << SPfisherman->getFishCarried() <<
				" ~ gonna go sell my fishes! " << std::endl;

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
				" ~ I am really thirsty, I will go to the lemonade stand and get a drink! " << std::endl;

			WalkingState::instance()->setDestination(static_cast<int>(Fisherman::locationType::lemonadeStand));
			SPfisherman->setIsWalking(true);
			SPfisherman->setCurrentState(WalkingState::instance());
		}
	}
	if (SPfisherman->isFatigue())
	{
		if (!SPfisherman->getIsWalking()) 
		{
			std::cout << " [name]: " << SPfisherman->getName() << " [ID]: " << SPfisherman->getEntityID() <<
				" [Money] " << SPfisherman->getMoneyInBank() << " $ [fish]: " << SPfisherman->getFishCarried() <<
				" ~ I am EXHAUSTED, I am going to head home and take a nap! " << std::endl;
			WalkingState::instance()->setDestination(static_cast<int>(Fisherman::locationType::house));
			SPfisherman->setIsWalking(true);
			SPfisherman->setCurrentState(WalkingState::instance());
		}
	}
	if (SPfisherman->isHungry())
	{
		if (!SPfisherman->getIsWalking()) 
		{
			std::cout << " [name]: " << SPfisherman->getName() << " [ID]: " << SPfisherman->getEntityID() <<
				" [Money] " << SPfisherman->getMoneyInBank() << " $ [fish]: " << SPfisherman->getFishCarried() <<
				" ~ I am really hungry, I will go to the resturant and get a something to eat! " << std::endl;

			WalkingState::instance()->setDestination(static_cast<int>(Fisherman::locationType::restaurant));
			SPfisherman->setIsWalking(true);  
			SPfisherman->setCurrentState(WalkingState::instance());
		}
	}
}

void FishingState::enterState(std::shared_ptr<Fisherman> SPfisherman)
{
	if (SPfisherman->getCurrentLocation() != Fisherman::locationType::pond)
	{
		std::cout << " [name]: " << SPfisherman->getName() << " [ID]: " << SPfisherman->getEntityID() << " " <<
		"Walking to the pond to fish... " << std::endl;

	}
}

void FishingState::exitState(std::shared_ptr<Fisherman> SPfisherman)
{

	if (SPfisherman->getCurrentLocation() == Fisherman::locationType::pond)
	{
		std::cout << " [name]: " << SPfisherman->getName() << " [ID]: " << SPfisherman->getEntityID() << " " <<
			"Enough fishing for now, heading to the next destination! " << std::endl;
		
	}
	if (SPfisherman->getCurrentLocation() != Fisherman::locationType::pond)
	{
		std::cout << " [name]: " << SPfisherman->getName() << " [ID]: " << SPfisherman->getEntityID() << " " <<
			"Leaving the pond, no more fishing here... " << std::endl;
	}
	
}
