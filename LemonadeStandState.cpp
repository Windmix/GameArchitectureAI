#include "LemonadeStandState.h"
#include "FishingState.h"

LemonadeStandState::LemonadeStandState()
{
	stockOfLemonade = 10;
}

std::shared_ptr<LemonadeStandState> LemonadeStandState::instance()
{
    std::shared_ptr<LemonadeStandState> lemonadeStandState = std::make_shared<LemonadeStandState>();
    return lemonadeStandState;
}

void LemonadeStandState::handle(std::shared_ptr<Fisherman> SPfisherman)
{
	lemonadeDrink lemonadeDrink;

	if (SPfisherman->getMoneyInBank() > 0 && stockOfLemonade > 0)
	{
		stockOfLemonade += -1;
		SPfisherman->addMoneyInBank(-60);

		std::cout << "\n[name]: " << SPfisherman->getName() << "\n[ID]: " << SPfisherman->getEntityID() <<
			"\n[Money] " << SPfisherman->getMoneyInBank() << " $\n[fish]: " << SPfisherman->getFishCarried() <<
			" Drinking some lemonade!!\n" << std::endl;

		SPfisherman->drinkWater(lemonadeDrink.drink);
	}
	if (SPfisherman->getMoneyInBank() <= 0)
	{
		std::cout << "\n[name]: " << SPfisherman->getName() << "\n[ID]: " << SPfisherman->getEntityID() <<
			"\n[Money] " << SPfisherman->getMoneyInBank() << " $\n[fish]: " << SPfisherman->getFishCarried() <<
			"\nDARN IT! I AM OUT OF MONEY!\n" << std::endl;
	}

	if (!SPfisherman->isThirsty())
	{
		SPfisherman->setCurrentState(FishingState::instance());
	}
	if (SPfisherman->isFatigue())
	{
		//go home to bed
	}
}

void LemonadeStandState::enterState(std::shared_ptr<Fisherman> SPfisherman)
{

	if (SPfisherman->getCurrentLocation() != Fisherman::locationType::lemonadeStand)
	{
		std::cout << "\n[name]: " << SPfisherman->getName() << "\n[ID]: " << SPfisherman->getEntityID() << "\n" <<
			"Ooof.. I am so thirsty, time to get a drink! \n" << std::endl;
		SPfisherman->setCurrentLocation(Fisherman::locationType::lemonadeStand);
	}
}

void LemonadeStandState::exitState(std::shared_ptr<Fisherman> SPfisherman)
{

	if (SPfisherman->getCurrentLocation() == Fisherman::locationType::lemonadeStand)
	{
		std::cout << "\n[name]: " << SPfisherman->getName() << "\n[ID]: " << SPfisherman->getEntityID() << "\n" <<
			"That was refreshing!!, time to get to work!\n" << std::endl;

	}
	if (SPfisherman->getCurrentLocation() != Fisherman::locationType::lemonadeStand)
	{
		std::cout << "\n[name]: " << SPfisherman->getName() << "\n[ID]: " << SPfisherman->getEntityID() << "\n" <<
			"Time to get away here whatever I am doing!\n" << std::endl;
	}
}

void LemonadeStandState::refilLemonadeStock(float time)
{
	if (time >= 10.0f)
	{
		stockOfLemonade += 1;
	}
}
