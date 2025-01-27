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

	if (SPfisherman->getFatigue() > 300) // reset fatigue on if fisherman starts on home and sleep 
	{
		SPfisherman->ResetFatigue(0);
	}

	if (SPfisherman->getMoneyInBank() > 0 && roastedFoodStock > 0)
	{
		SPfisherman->eatFood(33);

		roastedFoodStock += -1;
		SPfisherman->addMoneyInBank(-40);

		std::cout << " [name]: " << SPfisherman->getName() << " [ID]: " << SPfisherman->getEntityID() <<
			" [Money] " << SPfisherman->getMoneyInBank() << " $ [fish]: " << SPfisherman->getFishCarried() <<
			" ~ Eating some delicious roasted chicken " << std::endl;
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
			SPfisherman->setCurrentState(WalkingState::instance());;
		}
	}

	if (SPfisherman->isThirsty())
	{
		if (!SPfisherman->getIsWalking())
		{
			std::cout << " [name]: " << SPfisherman->getName() << " [ID]: " << SPfisherman->getEntityID() <<
				" [Money] " << SPfisherman->getMoneyInBank() << " $ [fish]: " << SPfisherman->getFishCarried() <<
				" ~ I am really thirsty, I will go to the lemonade stand and get a drink! " << std::endl;

			WalkingState::instance()->setDestination(static_cast<int>(Fisherman::locationType::lemonadeStand));
			SPfisherman->setIsWalking(true);
			SPfisherman->setCurrentState(WalkingState::instance());
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
	if (!SPfisherman->isHungry() && SPfisherman->getFood() >= 100)
	{
		std::cout << " [name]: " << SPfisherman->getName() << " [ID]: " << SPfisherman->getEntityID() <<
			" [Money] " << SPfisherman->getMoneyInBank() << " $ [fish]: " << SPfisherman->getFishCarried() <<
			" ~ I am so full, heading back to fish! " << std::endl;

		WalkingState::instance()->setDestination(static_cast<int>(Fisherman::locationType::pond));
		SPfisherman->setIsWalking(true);
		SPfisherman->setCurrentState(WalkingState::instance());
	}
}

void RestaurantState::enterState(std::shared_ptr<Fisherman> SPfisherman)
{

	if (SPfisherman->getCurrentLocation() != Fisherman::locationType::restaurant)
	{
		std::cout << " [name]: " << SPfisherman->getName() << " [ID]: " << SPfisherman->getEntityID() << " " <<
			"Ooof.. I am so hungry, time get something to eat!  " << std::endl;
		SPfisherman->setCurrentLocation(Fisherman::locationType::restaurant);
	}
}

void RestaurantState::exitState(std::shared_ptr<Fisherman> SPfisherman)
{

	if (SPfisherman->getCurrentLocation() == Fisherman::locationType::restaurant)
	{
		std::cout << " [name]: " << SPfisherman->getName() << " [ID]: " << SPfisherman->getEntityID() << " " <<
			"That was so delicious!!, time to get to work! " << std::endl;

	}
	if (SPfisherman->getCurrentLocation() != Fisherman::locationType::restaurant)
	{
		std::cout << " [name]: " << SPfisherman->getName() << " [ID]: " << SPfisherman->getEntityID() << " " <<
			"Time to get away here whatever I am doing! " << std::endl;
	}
}

void RestaurantState::setRandomWorkInstance(std::shared_ptr<Fisherman> SPfisherman)
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

void RestaurantState::refilRoastedFoodStock(float time)
{
	if (time >= 10.0f)
	{
		this->roastedFoodStock += 1;
	}
	
}
