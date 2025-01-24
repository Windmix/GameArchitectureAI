#include "MarketState.h"
#include "FishingState.h"
#include "LemonadeStandState.h"
#include "RestingState.h"
#include "WalkingState.h"

std::shared_ptr<MarketState> MarketState::instance()
{
	static std::shared_ptr<MarketState> marketState = std::make_shared<MarketState>();
	return marketState;
}

void MarketState::handle(std::shared_ptr<Fisherman> SPfisherman)
{
	int luckyNumber = 7;
	srand(static_cast<unsigned>(time(0)));

	int randomMultiplier = rand() % luckyNumber;

	SPfisherman->addFishCarried(-1);
	SPfisherman->addMoneyInBank(20 * randomMultiplier);
	SPfisherman->IncreaseFatigue(4);

	std::cout << "\n[" << SPfisherman->getName() << "]\n[ID]: " << SPfisherman->getEntityID() << "\n[fish]:" << SPfisherman->getFishCarried() <<
		"\n~ sold Fish for "<< 20 * randomMultiplier << "$\n[Money] " << SPfisherman->getMoneyInBank() << " $\n" << std::endl;

	if (SPfisherman->getFishCarried() <= 0)
	{
		
		if (!SPfisherman->getIsWalking())
		{
			std::cout << "\n[name]: " << SPfisherman->getName() << "\n[ID]: " << SPfisherman->getEntityID() <<
				"\n[Money] " << SPfisherman->getMoneyInBank() << " $\n[fish]: " << SPfisherman->getFishCarried() <<
				"\n~ I am empty of fishes, going to fish some more in the pond!\n" << std::endl;

			WalkingState::instance()->setDestination(static_cast<int>(Fisherman::locationType::pond));
            SPfisherman->setIsWalking(true); 
            SPfisherman->setCurrentState(WalkingState::instance());
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

void MarketState::enterState(std::shared_ptr<Fisherman> SPfisherman)
{

	if (SPfisherman->getCurrentLocation() != Fisherman::locationType::market)
	{

		std::cout << "\n[" << SPfisherman->getName() << "]\n[ID]: " << SPfisherman->getEntityID() << "\n" << "heading to market to sell fishes~ \n";
		WalkingState::instance()->setDestination(BaseGameEntity::locationType::market);
		SPfisherman->setCurrentState(WalkingState::instance());
	}
	
}

void MarketState::exitState(std::shared_ptr<Fisherman> SPfisherman)
{
	if (SPfisherman->getFishCarried() <= 0)
	{
		std::cout << "\n[" << SPfisherman->getName() << "]\n[ID]: " << SPfisherman->getEntityID() << "]\n" << "That's all fishes sold!\n";
	}
	else
	{
		std::cout << "\n[" << SPfisherman->getName() << "]\n[ID]: " << SPfisherman->getEntityID() << "]\n" << "Something urgent needs to be done!\n";
	}
}
