#include "RestaurantState.h"
#include "MarketState.h"
#include "LemonadeStandState.h"
#include "RestingState.h"
#include "FishingState.h"
#include "WalkingState.h"
#include "EntityManager.h"
#include "MessageDispatcher.h"

RestaurantState::RestaurantState()
{
}

std::shared_ptr<RestaurantState> RestaurantState::instance()
{
	static std::shared_ptr<RestaurantState> restaurantState = std::make_shared<RestaurantState>();
    return restaurantState;
}

void RestaurantState::handle(std::shared_ptr<Fisherman> SPfisherman)
{
	SPfisherman->IncreaseFatigue(1);
	SPfisherman->addSocialStatus(-2);

	if (SPfisherman->getFatigue() > 300) // reset fatigue on if fisherman starts on home and sleep 
	{
		SPfisherman->ResetFatigue(0);
	}

	else if (SPfisherman->getSocialStatus() <= 30)
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
	else if (SPfisherman->getMoneyInBank() > 0 && SPfisherman->getFood() <= 150)
	{
		SPfisherman->eatFood(50);

		SPfisherman->addMoneyInBank(-40);

		std::cout << "[" << SPfisherman->getName() << "] [ID]: " << SPfisherman->getEntityID() <<
			" [Money] " << SPfisherman->getMoneyInBank() << " $ [fish]: " << SPfisherman->getFishCarried() <<
			" ~ Eating some delicious roasted chicken " << std::endl;
		SPfisherman->SetisAvailableForSocializing(true);
	}
	else if (SPfisherman->getMoneyInBank() <= 0)
	{
		std::cout << " [" << SPfisherman->getName() << "] [ID]: " << SPfisherman->getEntityID() <<
			" [Money] " << SPfisherman->getMoneyInBank() << " $ [fish]: " << SPfisherman->getFishCarried() <<
			" ~ DARN IT! I AM OUT OF MONEY!" << std::endl;

		if (!SPfisherman->getIsWalking())
		{
			std::cout << " got to work more ";

		
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
				" ~ I am really thirsty, I will go to the lemonade stand and get a drink! " << std::endl;

			SPfisherman->setCurrentLocation(Fisherman::locationType::lemonadeStand);
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
				" ~ I am EXHAUSTED, I going to head home and take a nap! " << std::endl;

			SPfisherman->setCurrentLocation(Fisherman::locationType::house);
			SPfisherman->setIsWalking(true);
			SPfisherman->setCurrentState(std::make_shared<WalkingState>());
		}
	}
	else if (SPfisherman->getSocialStatus() <= 30)
	{
		std::cout << "[" << SPfisherman->getName() << "] [ID]: " << SPfisherman->getEntityID()
			<< " ~ I feel lonely... Anyone wants to hang out?" << std::endl;

		// Send a message to ALL fishermen
		for (auto& entityPair : Entity_Manager->getAllEntities())
		{
			auto fisherman = std::dynamic_pointer_cast<Fisherman>(entityPair.second);

			if (fisherman && fisherman->getEntityID() != SPfisherman->getEntityID())
			{
				MessageDispatcher::instance()->DispatchMessage(0, SPfisherman->getEntityID(), fisherman->getEntityID(), MessageType::msg_socializeResponseCall, nullptr);
			}
		}
	}
	else if(SPfisherman->getFood() >= 150)
	{
		std::cout << " [" << SPfisherman->getName() << "] [ID]: " << SPfisherman->getEntityID() <<
			" [Money] " << SPfisherman->getMoneyInBank() << " $ [fish]: " << SPfisherman->getFishCarried() <<
			" ~ I am so full, heading back to Work! " << std::endl;

		SPfisherman->setIsWalking(true);
		SPfisherman->setRandomWorkInstance(1);
	}
}

void RestaurantState::enterState(std::shared_ptr<Fisherman> SPfisherman)
{

	if (SPfisherman->getCurrentLocation() != Fisherman::locationType::restaurant)
	{
		std::cout << " [" << SPfisherman->getName() << "] [ID]: " << SPfisherman->getEntityID() << " " <<
			"enters the Restaurant " << std::endl;

	}
}

void RestaurantState::exitState(std::shared_ptr<Fisherman> SPfisherman)
{

	if (SPfisherman->getCurrentLocation() == Fisherman::locationType::restaurant)
	{
		std::cout << "[" << SPfisherman->getName() << "] [ID]: " << SPfisherman->getEntityID() << " " <<
			"Exits the Restaurant " << std::endl;

	}
}

bool RestaurantState::onMessage(std::shared_ptr<Fisherman> SPfisherman, Telegram& telegram)
{
	return false;
}

