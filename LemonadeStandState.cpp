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
		stockOfLemonade += -1;
		SPfisherman->addMoneyInBank(-60);

		std::cout << "\n[name]: " << SPfisherman->getName() << "\n[ID]: " << SPfisherman->getEntityID() <<
			"\n[Money] " << SPfisherman->getMoneyInBank() << " $\n[fish]: " << SPfisherman->getFishCarried() <<
			"\n~ Drinking some lemonade!!\n" << std::endl;

		SPfisherman->drinkWater(lemonadeDrink.drink);
	}
	if (SPfisherman->getMoneyInBank() <= 0)
	{
		std::cout << "\n[name]: " << SPfisherman->getName() << "\n[ID]: " << SPfisherman->getEntityID() <<
			"\n[Money] " << SPfisherman->getMoneyInBank() << " $\n[fish]: " << SPfisherman->getFishCarried() <<
			"\n~ DARN IT! I AM OUT OF MONEY!" << std::endl;

		if (SPfisherman->getFishCarried() <= 0 && !SPfisherman->getIsWalking())
		{
			std::cout << " got to work more\n";

			WalkingState::instance()->setDestination(static_cast<int>(Fisherman::locationType::pond));
			SPfisherman->setIsWalking(true);
			SPfisherman->setCurrentState(WalkingState::instance());
		}
		else
		{
			std::cout << " got to sell the fishes I have\n";
			WalkingState::instance()->setDestination(static_cast<int>(Fisherman::locationType::market));
			SPfisherman->setIsWalking(true);
			SPfisherman->setCurrentState(WalkingState::instance());;
		}

	}

	if (!SPfisherman->isThirsty() && SPfisherman->getWater() >= 180)
	{
		if (!SPfisherman->getIsWalking())
		{
			std::cout << "\n[name]: " << SPfisherman->getName() << "\n[ID]: " << SPfisherman->getEntityID() <<
				"\n[Money] " << SPfisherman->getMoneyInBank() << " $\n[fish]: " << SPfisherman->getFishCarried() <<
				"\n~ Refreshing! Time to head back to fishing!\n" << std::endl;

			WalkingState::instance()->setDestination(static_cast<int>(Fisherman::locationType::pond));
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

void LemonadeStandState::enterState(std::shared_ptr<Fisherman> SPfisherman)
{

	if (SPfisherman->getCurrentLocation() != Fisherman::locationType::lemonadeStand)
	{
		std::cout << "\n[name]: " << SPfisherman->getName() << "\n[ID]: " << SPfisherman->getEntityID() << "\n" <<
			"Ooof.. I am so thirsty, time to get a drink! \n" << std::endl;

		SPfisherman->setCurrentState(WalkingState::instance());
		WalkingState::instance()->setDestination(Fisherman::locationType::lemonadeStand);
	}
}

void LemonadeStandState::exitState(std::shared_ptr<Fisherman> SPfisherman)
{

	if (SPfisherman->getCurrentLocation() == Fisherman::locationType::lemonadeStand)
	{
		std::cout << "\n[name]: " << SPfisherman->getName() << "\n[ID]: " << SPfisherman->getEntityID() << "\n" <<
			"That was refreshing!!, time to get to work!\n" << std::endl;

		/*SPfisherman->setCurrentState(WalkingState::instance());
		WalkingState::instance()->setDestination(Fisherman::locationType::pond);*/

	}
}

void LemonadeStandState::refilLemonadeStock(float time)
{
	if (time >= 10.0f)
	{
		stockOfLemonade += 1;
	}
}
