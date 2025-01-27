#include "WalkingState.h"
#include "MarketState.h"
#include "RestaurantState.h"
#include "LemonadeStandState.h"
#include "FishingState.h"
#include "RestingState.h" 
#include "FishSouvenirShopState.h"

std::shared_ptr<WalkingState> WalkingState::instance()
{
	static std::shared_ptr< WalkingState> walkingState = std::make_shared< WalkingState>();
	return walkingState;
}



void WalkingState::handle(std::shared_ptr<Fisherman> SPfisherman)
{
	ticks++;
	std::cout << "\n[name]: " << SPfisherman->getName() << "\n[ID]: " << SPfisherman->getEntityID() << "\n walking.. distance: " << ticks <<" | " << destination <<" distantUnits" << std::endl;
	
	switch (ticks)
	{

	case 1:
		if (ticks == destination)
		{
			SPfisherman->setCurrentLocation(Fisherman::fishingSouvenirShop);
			SPfisherman->setCurrentState(FishSouvenirShopState::instance());
			SPfisherman->setIsWalking(false);
			ticks = 0;
		}
	case 2:
		if (ticks == destination)
		{
			SPfisherman->setCurrentLocation(Fisherman::market);
			SPfisherman->setCurrentState(MarketState::instance());
			SPfisherman->setIsWalking(false);
			ticks = 0;
		}
		break;
	case 3:
		if (ticks == destination)
		{
			SPfisherman->setCurrentLocation(Fisherman::lemonadeStand);
			SPfisherman->setCurrentState(LemonadeStandState::instance());
			SPfisherman->setIsWalking(false);
			ticks = 0;
		}
			
		break;
	case 4:
		if (ticks == destination)
		{
			SPfisherman->setCurrentLocation(Fisherman::restaurant);
			SPfisherman->setCurrentState(RestaurantState::instance());
			SPfisherman->setIsWalking(false);
			ticks = 0;
		}
		break;
	case 5:
		if (ticks == destination)
		{
			SPfisherman->setCurrentLocation(Fisherman::pond);
			SPfisherman->setCurrentState(FishingState::instance());
			SPfisherman->setIsWalking(false);
			ticks = 0;
		}
		break;
	case 6:
		if (ticks == destination)

		{
			SPfisherman->setCurrentLocation(Fisherman::house);
			SPfisherman->setCurrentState(RestingState::instance());
			SPfisherman->setIsWalking(false);
			ticks = 0;
		}
		break;

	default:
		break;

	}
}

void WalkingState::enterState(std::shared_ptr<Fisherman> SPfisherman)
{
	std::cout << "\n[name]: " << SPfisherman->getName() << "\n[ID]: " << SPfisherman->getEntityID() <<
		"\n Begin to walk.." << std::endl;
	ticks = 0;
	
}

void WalkingState::exitState(std::shared_ptr<Fisherman> SPfisherman)
{
	std::cout << "\n[name]: " << SPfisherman->getName() << "\n[ID]: " << SPfisherman->getEntityID() <<
		"\n stop walking.." << std::endl;
}

void WalkingState::setDestination(int destinationValue)
{
	this->destination = destinationValue;
}

int WalkingState::getDestination()
{
	return this->destination;
}

int WalkingState::getTicks()
{
	return this->ticks;
}
