#include "WalkingState.h"
#include "MarketState.h"
#include "RestaurantState.h"
#include "LemonadeStandState.h"
#include "FishingState.h"
#include "RestingState.h" 
#include "FishSouvenirShopState.h"
#include "SocializeState.h"

std::shared_ptr<WalkingState> WalkingState::instance()
{
	static std::shared_ptr< WalkingState> walkingState = std::make_shared< WalkingState>();
	return walkingState;
}

void WalkingState::handle(std::shared_ptr<Fisherman> SPfisherman)
{
	
	std::cout << "["<< SPfisherman->getName() << "] [ID]: " << SPfisherman->getEntityID() << "  currently walking.. distance: " << SPfisherman->getTicks() <<" | 3"  <<" distantUnits" << std::endl;
	
	if (SPfisherman->getTicks() == 3)
	{
		if (SPfisherman->getDestination() == Fisherman::locationType::fishingSouvenirShop)
		{
			if (SPfisherman->GetisAvailableForSocializing() && SPfisherman->getHasAgreed())
			{
				SPfisherman->setCurrentLocation(SPfisherman->getDestination());
				SPfisherman->setCurrentState(SocializeState::instance());
				SPfisherman->setHasAgreed(false);
				SPfisherman->setIsWalking(false);
				SPfisherman->setTicks(0);
			}
			else
			{
				SPfisherman->setCurrentLocation(SPfisherman->getDestination());
				SPfisherman->setCurrentState(FishSouvenirShopState::instance());
				SPfisherman->addSocialStatus(-2);
				SPfisherman->setIsWalking(false);
				SPfisherman->setTicks(0);
			}
			
		}
		else if (SPfisherman->getDestination() == Fisherman::locationType::market)
		{
			if (SPfisherman->GetisAvailableForSocializing() && SPfisherman->getHasAgreed())
			{
				SPfisherman->setCurrentLocation(SPfisherman->getDestination());
				SPfisherman->setCurrentState(SocializeState::instance());
				SPfisherman->setHasAgreed(false);
				SPfisherman->setIsWalking(false);
				SPfisherman->setTicks(0);
			}
			else
			{
				SPfisherman->setCurrentLocation(SPfisherman->getDestination());
				SPfisherman->setCurrentState(MarketState::instance());
				SPfisherman->addSocialStatus(-2);
				SPfisherman->setHasAgreed(false);
				SPfisherman->setIsWalking(false);
				SPfisherman->setTicks(0);
			}
			
		}
		else if (SPfisherman->getDestination() == Fisherman::locationType::lemonadeStand)
		{
			if (SPfisherman->GetisAvailableForSocializing() && SPfisherman->getHasAgreed())
			{
				SPfisherman->setCurrentLocation(SPfisherman->getDestination());
				SPfisherman->setCurrentState(SocializeState::instance());
				SPfisherman->addSocialStatus(-2);
				SPfisherman->setHasAgreed(false);
				SPfisherman->setIsWalking(false);
				SPfisherman->setTicks(0);
			}
			else
			{
				SPfisherman->setCurrentLocation(SPfisherman->getDestination());
				SPfisherman->setCurrentState(LemonadeStandState::instance());
				SPfisherman->setIsWalking(false);
				SPfisherman->setTicks(0);
			}
		}
		else if (SPfisherman->getDestination() == Fisherman::locationType::restaurant)
		{
			if (SPfisherman->GetisAvailableForSocializing() && SPfisherman->getHasAgreed())
			{
				SPfisherman->setCurrentLocation(SPfisherman->getDestination());
				SPfisherman->setCurrentState(SocializeState::instance());
				SPfisherman->addSocialStatus(-2);
				SPfisherman->setHasAgreed(false);
				SPfisherman->setIsWalking(false);
				SPfisherman->setTicks(0);
			}
			else
			{
				SPfisherman->setCurrentLocation(SPfisherman->getDestination());
				SPfisherman->setCurrentState(RestaurantState::instance());
				SPfisherman->setIsWalking(false);
				SPfisherman->setTicks(0);
			}
			
		}
		else if (SPfisherman->getDestination() == Fisherman::locationType::pond)
		{
			if (SPfisherman->GetisAvailableForSocializing() && SPfisherman->getHasAgreed())
			{
				SPfisherman->setCurrentLocation(SPfisherman->getDestination());
				SPfisherman->setCurrentState(SocializeState::instance());
				SPfisherman->addSocialStatus(-2);
				SPfisherman->setHasAgreed(false);
				SPfisherman->setIsWalking(false);
				SPfisherman->setTicks(0);
			}
			else
			{
				SPfisherman->setCurrentLocation(SPfisherman->getDestination());
				SPfisherman->setCurrentState(FishingState::instance());
				SPfisherman->setIsWalking(false);
				SPfisherman->setTicks(0);
			}
			
		}
		else if (SPfisherman->getDestination() == Fisherman::locationType::house)
		{
			if (SPfisherman->GetisAvailableForSocializing() && SPfisherman->getHasAgreed())
			{
				SPfisherman->setCurrentLocation(SPfisherman->getDestination());
				SPfisherman->setCurrentState(SocializeState::instance());
				SPfisherman->addSocialStatus(-2);
				SPfisherman->setHasAgreed(false);
				SPfisherman->setIsWalking(false);
				SPfisherman->setTicks(0);
			}
			else
			{
				SPfisherman->setCurrentLocation(SPfisherman->getDestination());
				SPfisherman->setCurrentState(RestingState::instance());
				SPfisherman->setIsWalking(false);
				SPfisherman->setTicks(0);
			}
			
		}
	}
	if (SPfisherman->getTicks() > 3)
	{
		SPfisherman->setTicks(0);
	}
	else
	{
		SPfisherman->addTicks(1);
	}
}

void WalkingState::enterState(std::shared_ptr<Fisherman> SPfisherman)
{
	std::cout << "[" << SPfisherman->getName() << "] [ID]: " << SPfisherman->getEntityID() <<
		" Begin to walk..\n " << std::endl;
	
}

void WalkingState::exitState(std::shared_ptr<Fisherman> SPfisherman)
{
	std::cout << "[" << SPfisherman->getName() << "] [ID]: " << SPfisherman->getEntityID() <<
		" stop walking..\n " << std::endl;
}

bool WalkingState::onMessage(std::shared_ptr<Fisherman> SPfisherman, Telegram& telegram)
{
	return false;
}
