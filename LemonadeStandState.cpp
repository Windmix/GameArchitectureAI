#include "LemonadeStandState.h"
#include "FishingState.h"
#include "MarketState.h"
#include "RestingState.h"
#include "WalkingState.h"

LemonadeStandState::LemonadeStandState()
{
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

	if (SPfisherman->getMoneyInBank() > 0 && SPfisherman->getWater() <= 150)
	{

		SPfisherman->addMoneyInBank(-60);

		std::cout << "[" << SPfisherman->getName() << "] [ID]: " << SPfisherman->getEntityID() <<
			" [Money] " << SPfisherman->getMoneyInBank() << " $ [fish]: " << SPfisherman->getFishCarried() <<
			" ~ Drinking some lemonade!! " << std::endl;

		SPfisherman->drinkWater(lemonadeDrink.drink);
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

	else if (!SPfisherman->isThirsty() && SPfisherman->getWater() >= 150)
	{
		if (!SPfisherman->getIsWalking())
		{
			std::cout << "[" << SPfisherman->getName() << "] [ID]: " << SPfisherman->getEntityID() <<
				" [Money] " << SPfisherman->getMoneyInBank() << " $ [fish]: " << SPfisherman->getFishCarried() <<
				" ~ Refreshing! Time to head back to fishing! " << std::endl;

			setRandomWorkInstance(SPfisherman);
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

void LemonadeStandState::enterState(std::shared_ptr<Fisherman> SPfisherman)
{

	if (SPfisherman->getCurrentLocation() == Fisherman::locationType::lemonadeStand)
	{
		std::cout << "[" << SPfisherman->getName() << "] [ID]: " << SPfisherman->getEntityID() << " " <<
			"enters the lemonade stand" << std::endl;

	}
}

void LemonadeStandState::exitState(std::shared_ptr<Fisherman> SPfisherman)
{

	if (SPfisherman->getCurrentLocation() == Fisherman::locationType::lemonadeStand)
	{
		std::cout << "[" << SPfisherman->getName() << "] [ID]: " << SPfisherman->getEntityID() << " " <<
			"Exits the lemonade stand" << std::endl;

		/*SPfisherman->setCurrentState(std::make_shared<WalkingState>());
		std::make_shared<WalkingState>()->setDestination(Fisherman::locationType::pond);*/

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
	default:
		break;
	}
}

