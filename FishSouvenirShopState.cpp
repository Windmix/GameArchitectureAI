#include "FishSouvenirShopState.h"
#include "WalkingState.h"

FishSouvenirShopState::FishSouvenirShopState()
{
	//dog
}

std::shared_ptr<FishSouvenirShopState> FishSouvenirShopState::instance()
{
	std::shared_ptr<FishSouvenirShopState> fishSouvenirShop = std::make_shared<FishSouvenirShopState>();
	return fishSouvenirShop;
}

void FishSouvenirShopState::handle(std::shared_ptr<Fisherman> SPfisherman)
{
	

	randomizerSetSouvenirs();
;
	SPfisherman->addMoneyInBank(price);
	SPfisherman->IncreaseFatigue(2);

	std::cout << "\n[" << SPfisherman->getName() << "]\n[ID]: " << SPfisherman->getEntityID() << "\n[fish]:" << SPfisherman->getFishCarried() <<
		"\n~ sold "<< item <<" for " << price << "$\n[Money] " << SPfisherman->getMoneyInBank() << " $\n" << std::endl;

	if (SPfisherman->getMoneyInBank() >= 1000)
	{
		if (!SPfisherman->getIsWalking())
		{
			std::cout << "\n[name]: " << SPfisherman->getName() << "\n[ID]: " << SPfisherman->getEntityID() <<
				"\n[Money] " << SPfisherman->getMoneyInBank() << " $\n[fish]: " << SPfisherman->getFishCarried() <<
				"\n~ I done working here, going to fish in the pond, yaya!\n" << std::endl;

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

void FishSouvenirShopState::enterState(std::shared_ptr<Fisherman> SPfisherman)
{
}

void FishSouvenirShopState::exitState(std::shared_ptr<Fisherman> SPfisherman)
{

}

void FishSouvenirShopState::randomizerSetSouvenirs()
{
	int luckyNumber = 6;
	srand(static_cast<unsigned>(time(0)));

	int randomizer = rand() % luckyNumber;

	for (const auto& pair : fishingSouvenir)
	{
		switch (randomizer)
		{
		case 0:
			item = pair.first;
			price = pair.second;
			break;
		case 1:
			item = pair.first;
			price = pair.second;
			break;
		case 2:
			item = pair.first;
			price = pair.second;
			break;
		case 3:
			item = pair.first;
			price = pair.second;
			break;
		case 4:
			item = pair.first;
			price = pair.second;
			break;
		case 5:
			item = pair.first;
			price = pair.second;
			break;

		default:
			break;
	}
	
	}
	
}
