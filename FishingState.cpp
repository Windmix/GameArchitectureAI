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
	std::cout << "\n[name]: " << SPfisherman->getName() << "\n[ID]: " << SPfisherman->getEntityID() << 
		"\n[Money] " << SPfisherman->getMoneyInBank() << " $\n[fish]: " << SPfisherman->getFishCarried() <<
		"\n ~ caught a fish!\n" << std::endl;

	if (SPfisherman->isFishingBagFull())
	{
		if (!SPfisherman->getIsWalking())
		{

			std::cout << "\n[name]: " << SPfisherman->getName() << "\n[ID]: " << SPfisherman->getEntityID() <<
				"\n[Money] " << SPfisherman->getMoneyInBank() << " $\n[fish]: " << SPfisherman->getFishCarried() <<
				" ~ gonna go sell my fishes!\n" << std::endl;

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
				"\n~ I am really thirsty, I will go to the lemonade stand and get a drink!\n" << std::endl;

			WalkingState::instance()->setDestination(static_cast<int>(Fisherman::locationType::lemonadeStand));
			SPfisherman->setIsWalking(true);
			SPfisherman->setCurrentState(WalkingState::instance());
		}
	}
	if (SPfisherman->isFatigue())
	{
		if (!SPfisherman->getIsWalking()) 
		{
			std::cout << "\n[name]: " << SPfisherman->getName() << "\n[ID]: " << SPfisherman->getEntityID() <<
				"\n[Money] " << SPfisherman->getMoneyInBank() << " $\n[fish]: " << SPfisherman->getFishCarried() <<
				"\n~ I am EXHAUSTED, I going to head home and take a nap!\n" << std::endl;
			WalkingState::instance()->setDestination(static_cast<int>(Fisherman::locationType::house));
			SPfisherman->setIsWalking(true);
			SPfisherman->setCurrentState(WalkingState::instance());
		}
	}
	if (SPfisherman->isHungry())
	{
		if (!SPfisherman->getIsWalking()) 
		{
			std::cout << "\n[name]: " << SPfisherman->getName() << "\n[ID]: " << SPfisherman->getEntityID() <<
				"\n[Money] " << SPfisherman->getMoneyInBank() << " $\n[fish]: " << SPfisherman->getFishCarried() <<
				"\n~ I am really hungry, I will go to the resturant and get a something to eat!\n" << std::endl;

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
		std::cout << "\n[name]: " << SPfisherman->getName() << "\n[ID]: " << SPfisherman->getEntityID() << "\n" <<
		"Walking to the pond to fish...\n" << std::endl;

	}
}

void FishingState::exitState(std::shared_ptr<Fisherman> SPfisherman)
{

	if (SPfisherman->getCurrentLocation() == Fisherman::locationType::pond)
	{
		std::cout << "\n[name]: " << SPfisherman->getName() << "\n[ID]: " << SPfisherman->getEntityID() << "\n" <<
			"Enough fishing for now, heading to the next destination!\n" << std::endl;
		
	}
	if (SPfisherman->getCurrentLocation() != Fisherman::locationType::pond)
	{
		std::cout << "\n[name]: " << SPfisherman->getName() << "\n[ID]: " << SPfisherman->getEntityID() << "\n" <<
			"Leaving the pond, no more fishing here...\n" << std::endl;
	}
	
}
