#include "LemonadeStandState.h"
#include "FishingState.h"
#include "MarketState.h"
#include "RestingState.h"
#include "WalkingState.h"

LemonadeStandState::LemonadeStandState()
{
	stockOfLemonade = 10;
}

std::shared_ptr<LemonadeStandState> LemonadeStandState::instance()
{
	static std::shared_ptr<LemonadeStandState> lemonadeStandState = std::make_shared<LemonadeStandState>();
    return lemonadeStandState;
}

void LemonadeStandState::handle(std::shared_ptr<Fisherman> SPfisherman)
{
	SPfisherman->setCurrentLocation(Fisherman::locationType::lemonadeStand);

	lemonadeDrink lemonadeDrink;

	if (SPfisherman->getMoneyInBank() > 0 && stockOfLemonade > 0)
	{

		SPfisherman->addMoneyInBank(-60);

		std::cout << " [name]: " << SPfisherman->getName() << " [ID]: " << SPfisherman->getEntityID() <<
			" [Money] " << SPfisherman->getMoneyInBank() << " $ [fish]: " << SPfisherman->getFishCarried() <<
			" ~ Drinking some lemonade!! " << std::endl;

		SPfisherman->drinkWater(lemonadeDrink.drink);
	}
	if (stockOfLemonade <= 0)
	{
		std::cout << " [name]: " << SPfisherman->getName() << " [ID]: " << SPfisherman->getEntityID() <<
			" [Money] " << SPfisherman->getMoneyInBank() << " $ [fish]: " << SPfisherman->getFishCarried() <<
			" ~ What the f, the lemonade stock is empty, I guess I go back fishing! " << std::endl;

		WalkingState::instance()->setDestination(static_cast<int>(Fisherman::locationType::pond));
		SPfisherman->setIsWalking(true);
		SPfisherman->setCurrentState(WalkingState::instance());
	}
	if (SPfisherman->getMoneyInBank() <= 0)
	{
		std::cout << " [name]: " << SPfisherman->getName() << " [ID]: " << SPfisherman->getEntityID() <<
			" [Money] " << SPfisherman->getMoneyInBank() << " $ [fish]: " << SPfisherman->getFishCarried() <<
			" ~ DARN IT! I AM OUT OF MONEY!" << std::endl;

		if (SPfisherman->getFishCarried() <= 0 && !SPfisherman->getIsWalking())
		{
			std::cout << " got to work more ";

			WalkingState::instance()->setDestination(static_cast<int>(Fisherman::locationType::pond));
			SPfisherman->setIsWalking(true);
			SPfisherman->setCurrentState(WalkingState::instance());
		}
		
		else
		{
			std::cout << " got to sell the fishes I have ";
			WalkingState::instance()->setDestination(static_cast<int>(Fisherman::locationType::market));
			SPfisherman->setIsWalking(true);
			SPfisherman->setCurrentState(WalkingState::instance());
		}
	}

	if (!SPfisherman->isThirsty() && SPfisherman->getWater() >= 100)
	{
		if (!SPfisherman->getIsWalking())
		{
			std::cout << " [name]: " << SPfisherman->getName() << " [ID]: " << SPfisherman->getEntityID() <<
				" [Money] " << SPfisherman->getMoneyInBank() << " $ [fish]: " << SPfisherman->getFishCarried() <<
				" ~ Refreshing! Time to head back to fishing! " << std::endl;

			setRandomWorkInstance(SPfisherman);
		}
	}
	if (SPfisherman->isFatigue())
	{
		if (!SPfisherman->getIsWalking())
		{
			std::cout << " [name]: " << SPfisherman->getName() << " [ID]: " << SPfisherman->getEntityID() <<
				" [Money] " << SPfisherman->getMoneyInBank() << " $ [fish]: " << SPfisherman->getFishCarried() <<
				" ~ I am EXHAUSTED, I going to head home and take a nap! " << std::endl;

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

void LemonadeStandState::enterState(std::shared_ptr<Fisherman> SPfisherman)
{

	if (SPfisherman->getCurrentLocation() != Fisherman::locationType::lemonadeStand)
	{
		std::cout << " [name]: " << SPfisherman->getName() << " [ID]: " << SPfisherman->getEntityID() << " " <<
			"Ooof.. I am so thirsty, time to get a drink!  " << std::endl;

		SPfisherman->setCurrentState(WalkingState::instance());
		WalkingState::instance()->setDestination(Fisherman::locationType::lemonadeStand);
	}
}

void LemonadeStandState::exitState(std::shared_ptr<Fisherman> SPfisherman)
{

	if (SPfisherman->getCurrentLocation() == Fisherman::locationType::lemonadeStand)
	{
		std::cout << " [name]: " << SPfisherman->getName() << " [ID]: " << SPfisherman->getEntityID() << " " <<
			"That was refreshing!!, time to get to work! " << std::endl;

		/*SPfisherman->setCurrentState(WalkingState::instance());
		WalkingState::instance()->setDestination(Fisherman::locationType::pond);*/

	}
}

void LemonadeStandState::setRandomWorkInstance(std::shared_ptr<Fisherman> SPfisherman)
{
	int interval = 1; // between 0,1
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
	default:
		break;
	}
}

void LemonadeStandState::refilLemonadeStock(float time)
{
	if (time >= 10.0f)
	{
		stockOfLemonade += 1;
	}
}
