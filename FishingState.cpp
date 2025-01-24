#include "FishingState.h"
#include "RestingState.h"
#include "MarketState.h"
#include "LemonadeStandState.h"

FishingState::FishingState()
{

}

std::shared_ptr<FishingState> FishingState::instance()
{
	static std::shared_ptr<FishingState> fishingState = std::make_shared<FishingState>();
	return fishingState;
}

void FishingState::handle(std::shared_ptr<Fisherman> SPfisherman)
{
	SPfisherman->addFishCarried(1);
	SPfisherman->IncreaseFatigue(3);
	std::cout << "\n[name]: " << SPfisherman->getName() << "\n[ID]: " << SPfisherman->getEntityID() << 
		"\n[Money] " << SPfisherman->getMoneyInBank() << " $\n[fish]: " << SPfisherman->getFishCarried() <<
		" ~ caught a fish!\n" << std::endl;

	if (SPfisherman->isFishingBagFull())
	{

		SPfisherman->setCurrentState(MarketState::instance());
	}
	if (SPfisherman->isThirsty())
	{
		SPfisherman->setCurrentState(LemonadeStandState::instance());
	}
	if (SPfisherman->isFatigue())
	{
		SPfisherman->setCurrentState(RestingState::instance());
	}
	if (SPfisherman->isDying())
	{
		std::cout << "\n[name]: " << SPfisherman->getName() << "\n[ID]: " << SPfisherman->getEntityID() << "*DEAD*\n";
	}
	
}

void FishingState::enterState(std::shared_ptr<Fisherman> SPfisherman)
{
	if (SPfisherman->getCurrentLocation() != Fisherman::locationType::pond)
	{
		std::cout << "\n[name]: " << SPfisherman->getName() << "\n[ID]: " << SPfisherman->getEntityID() << "\n" <<
		"walking to the pond\n" << std::endl;

		SPfisherman->setCurrentLocation(Fisherman::locationType::pond);
	}
	

}

void FishingState::exitState(std::shared_ptr<Fisherman> SPfisherman)
{

	if (SPfisherman->getCurrentLocation() == Fisherman::locationType::pond)
	{
		std::cout << "\n[name]: " << SPfisherman->getName() << "\n[ID]: " << SPfisherman->getEntityID() << "\n" <<
			"I got enough fishes, time to go!\n" << std::endl;
		
	}
	if (SPfisherman->getCurrentLocation() != Fisherman::locationType::pond)
	{
		std::cout << "\n[name]: " << SPfisherman->getName() << "\n[ID]: " << SPfisherman->getEntityID() << "\n" <<
			"Time to get away here whatever I am doing!\n" << std::endl;
	}
	
}
