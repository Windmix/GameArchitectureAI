#include "RestaurantState.h"
#include "MarketState.h"
#include "LemonadeStandState.h"
#include "RestingState.h"
#include "FishingState.h"
#include "WalkingState.h"

RestaurantState::RestaurantState()
{
	roastedFoodStock = 10;
}

std::shared_ptr<RestaurantState> RestaurantState::instance()
{
	static std::shared_ptr<RestaurantState> restaurantState = std::make_shared<RestaurantState>();
    return restaurantState;
}

void RestaurantState::handle(std::shared_ptr<Fisherman> SPfisherman)
{
	SPfisherman->IncreaseFatigue(2);

	if (SPfisherman->getMoneyInBank() > 0 && roastedFoodStock > 0)
	{
		SPfisherman->eatFood(33);

		roastedFoodStock += -1;
		SPfisherman->addMoneyInBank(-40);

		std::cout << "\n[name]: " << SPfisherman->getName() << "\n[ID]: " << SPfisherman->getEntityID() <<
			"\n[Money] " << SPfisherman->getMoneyInBank() << " $\n[fish]: " << SPfisherman->getFishCarried() <<
			"\n~ Eating some delicious roasted chicken\n" << std::endl;
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

	if (SPfisherman->isThirsty())
	{
		if (!SPfisherman->getIsWalking())
		{
			std::cout << "\n[name]: " << SPfisherman->getName() << "\n[ID]: " << SPfisherman->getEntityID() <<
				"\n[Money] " << SPfisherman->getMoneyInBank() << " $\n[fish]: " << SPfisherman->getFishCarried() <<
				"\n~ I am really thirsty, I will go to the lemonade stand and get a drink!\n" << std::endl;

			WalkingState::instance()->setDestination(static_cast<int>(Fisherman::locationType::lemonadeStand));
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
	if (!SPfisherman->isHungry() && SPfisherman->getFood() >= 90)
	{
		std::cout << "\n[name]: " << SPfisherman->getName() << "\n[ID]: " << SPfisherman->getEntityID() <<
			"\n[Money] " << SPfisherman->getMoneyInBank() << " $\n[fish]: " << SPfisherman->getFishCarried() <<
			"\n~ I am so full, heading back to fish!\n" << std::endl;

		WalkingState::instance()->setDestination(static_cast<int>(Fisherman::locationType::pond));
		SPfisherman->setIsWalking(true);
		SPfisherman->setCurrentState(WalkingState::instance());
	}
}

void RestaurantState::enterState(std::shared_ptr<Fisherman> SPfisherman)
{

	if (SPfisherman->getCurrentLocation() != Fisherman::locationType::restaurant)
	{
		std::cout << "\n[name]: " << SPfisherman->getName() << "\n[ID]: " << SPfisherman->getEntityID() << "\n" <<
			"Ooof.. I am so hungry, time get something to eat! \n" << std::endl;
		SPfisherman->setCurrentLocation(Fisherman::locationType::restaurant);
	}
}

void RestaurantState::exitState(std::shared_ptr<Fisherman> SPfisherman)
{

	if (SPfisherman->getCurrentLocation() == Fisherman::locationType::restaurant)
	{
		std::cout << "\n[name]: " << SPfisherman->getName() << "\n[ID]: " << SPfisherman->getEntityID() << "\n" <<
			"That was so delicious!!, time to get to work!\n" << std::endl;

	}
	if (SPfisherman->getCurrentLocation() != Fisherman::locationType::restaurant)
	{
		std::cout << "\n[name]: " << SPfisherman->getName() << "\n[ID]: " << SPfisherman->getEntityID() << "\n" <<
			"Time to get away here whatever I am doing!\n" << std::endl;
	}
}

void RestaurantState::refilRoastedFoodStock(float time)
{
	if (time >= 10.0f)
	{
		this->roastedFoodStock += 1;
	}
	
}
