#include "FishingState.h"
#include "RestingState.h"
#include "MarketState.h"
#include "RestaurantState.h"
#include "LemonadeStandState.h"
#include "WalkingState.h"
#include "EntityManager.h"
#include "MessageDispatcher.h"


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
	SPfisherman->SetisAvailableForSocializing(true);

	int randomFish = 1+rand() % 4;

	SPfisherman->addFishCarried(randomFish);
	SPfisherman->IncreaseFatigue(3);
	SPfisherman->addSocialStatus(-2);
	std::cout << "[" << SPfisherman->getName() << "] [ID]: " << SPfisherman->getEntityID() << 
		" [Money] " << SPfisherman->getMoneyInBank() << " $ [fish]: " << SPfisherman->getFishCarried() <<
		"  ~ caught a fish! " << std::endl;

	if (SPfisherman->isFishingBagFull())
	{
		if (!SPfisherman->getIsWalking())
		{

			std::cout << "[" << SPfisherman->getName() << "] [ID]: " << SPfisherman->getEntityID() <<
				" [Money] " << SPfisherman->getMoneyInBank() << " $ [fish]: " << SPfisherman->getFishCarried() <<
				" ~ gonna go sell my fishes! " << std::endl;

			SPfisherman->SetisAvailableForSocializing(false);
			SPfisherman->setDestination(Fisherman::locationType::market);
            SPfisherman->setIsWalking(true); 
            SPfisherman->setCurrentState(std::make_shared<WalkingState>());
		}
	}
	else if(SPfisherman->getSocialStatus() <= 30)
	{

		std::cout << "[" << SPfisherman->getName() << "] [ID]: " << SPfisherman->getEntityID()
			<< " ~ I feel lonely... Anyone wants to hang out?" << std::endl;

		// Send a message to ALL fishermen
		for (auto& entityPair : Entity_Manager->getAllEntities())
		{
			auto fisherman = std::dynamic_pointer_cast<Fisherman>(entityPair.second);

			if (fisherman && fisherman->getEntityID() != SPfisherman->getEntityID()) // oposite
			{
				MessageDispatcher::instance()->DispatchMessage(0, SPfisherman->getEntityID(), fisherman->getEntityID(), MessageType::msg_socializeResponseCall, nullptr);


			}
		}
		
	}
	else if (SPfisherman->isThirsty())
	{
		if (!SPfisherman->getIsWalking())
		{
			std::cout << "[" << SPfisherman->getName() << "] [ID]: " << SPfisherman->getEntityID() <<
				" [Money] " << SPfisherman->getMoneyInBank() << " $ [fish]: " << SPfisherman->getFishCarried() <<
				" ~ I am really thirsty, I will go to the lemonade stand and get a drink! " << std::endl;
			SPfisherman->SetisAvailableForSocializing(false);
			SPfisherman->setDestination(Fisherman::locationType::lemonadeStand);
			SPfisherman->setIsWalking(true);
			SPfisherman->setCurrentState(std::make_shared<WalkingState>());
		}
	}
	else if (SPfisherman->isFatigue())
	{
		if (!SPfisherman->getIsWalking()) 
		{
			std::cout << "[" << SPfisherman->getName() << "] [ID]: " << SPfisherman->getEntityID() <<
				" [Money] " << SPfisherman->getMoneyInBank() << " $ [fish]: " << SPfisherman->getFishCarried() <<
				" ~ I am EXHAUSTED, I am going to head home and take a nap! " << std::endl;
			SPfisherman->SetisAvailableForSocializing(false);
			SPfisherman->setDestination(Fisherman::locationType::house);
			SPfisherman->setIsWalking(true);
			SPfisherman->setCurrentState(std::make_shared<WalkingState>());
		}
	}
	else if (SPfisherman->isHungry())
	{
		if (!SPfisherman->getIsWalking()) 
		{
			std::cout << "[" << SPfisherman->getName() << "] [ID]: " << SPfisherman->getEntityID() <<
				" [Money] " << SPfisherman->getMoneyInBank() << " $ [fish]: " << SPfisherman->getFishCarried() <<
				" ~ I am really hungry, I will go to the resturant and get a something to eat! " << std::endl;
			SPfisherman->SetisAvailableForSocializing(false);
			SPfisherman->setDestination(Fisherman::locationType::restaurant);
			SPfisherman->setIsWalking(true);  
			SPfisherman->setCurrentState(std::make_shared<WalkingState>());
		}
	}
}

void FishingState::enterState(std::shared_ptr<Fisherman> SPfisherman)
{
	if (SPfisherman->getCurrentLocation() == Fisherman::locationType::pond)
	{
		std::cout << "[" << SPfisherman->getName() << "] [ID]: " << SPfisherman->getEntityID() << " " <<
			"enters the pond" << std::endl;
	}

}

void FishingState::exitState(std::shared_ptr<Fisherman> SPfisherman)
{

	if (SPfisherman->getCurrentLocation() == Fisherman::locationType::pond)
	{
		std::cout << "[" << SPfisherman->getName() << "] [ID]: " << SPfisherman->getEntityID() << " " <<
			"exits the pond" << std::endl;
		
	}
	
}

bool FishingState::onMessage(std::shared_ptr<Fisherman> SPfisherman, Telegram& telegram)
{
	switch (telegram.getMessage())
	{
	case MessageType::msg_socializeResponseCall:
	{
		SPfisherman->handleMessage(telegram);
		return true;
	}
	default:
		break;
	}
	return false;
}
