#include "MarketState.h"
#include "FishingState.h"
#include "LemonadeStandState.h"
#include "RestingState.h"
#include "WalkingState.h"
#include "EntityManager.h"
#include "MessageDispatcher.h"

std::shared_ptr<MarketState> MarketState::instance()
{
	static std::shared_ptr<MarketState> marketState = std::make_shared<MarketState>();
	return marketState;
}

void MarketState::handle(std::shared_ptr<Fisherman> SPfisherman)
{
	int luckyNumber = 7;

	int randomMultiplier =rand() % luckyNumber;

	SPfisherman->addFishCarried(-1);
	SPfisherman->addMoneyInBank(10 + 20 * randomMultiplier);
	SPfisherman->IncreaseFatigue(4);
	SPfisherman->addSocialStatus(-2);
	SPfisherman->SetisAvailableForSocializing(true);
	std::cout << "[" << SPfisherman->getName() << "] [ID]: " << SPfisherman->getEntityID() << " [fish]:" << SPfisherman->getFishCarried() <<
		" ~ sold Fish for "<< 10 + 20 * randomMultiplier << "$ [Money] " << SPfisherman->getMoneyInBank() << " $ " << std::endl;

	if (SPfisherman->getFishCarried() <= 0)
	{
		
		if (!SPfisherman->getIsWalking())
		{
			std::cout << "[" << SPfisherman->getName() << "] [ID]: " << SPfisherman->getEntityID() <<
				" [Money] " << SPfisherman->getMoneyInBank() << " $ [fish]: " << SPfisherman->getFishCarried() <<
				" ~ I am empty of fishes, going to fish some more in the pond! " << std::endl;

			SPfisherman->setRandomWorkInstance(1);
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
				" ~ I am EXHAUSTED, I going to head home and take a nap! " << std::endl;

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

			SPfisherman->setDestination(Fisherman::locationType::restaurant);
			SPfisherman->setIsWalking(true);
			SPfisherman->setCurrentState(std::make_shared<WalkingState>());
		}
	}

}

void MarketState::enterState(std::shared_ptr<Fisherman> SPfisherman)
{

	if (SPfisherman->getCurrentLocation() == Fisherman::locationType::market)
	{

		std::cout << "[" << SPfisherman->getName() << "] [ID]: " << SPfisherman->getEntityID() << " " << " enters the Market" << std::endl;
	
	}
	
}

void MarketState::exitState(std::shared_ptr<Fisherman> SPfisherman)
{
	if (SPfisherman->getCurrentLocation() == Fisherman::locationType::market)
	{

		std::cout << "[" << SPfisherman->getName() << "] [ID]: " << SPfisherman->getEntityID() << " " << " exits the Market" << std::endl;;

	}
}

bool MarketState::onMessage(std::shared_ptr<Fisherman> SPfisherman, Telegram& telegram)
{
	return false;
}
