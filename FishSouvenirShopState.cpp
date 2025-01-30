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
	SPfisherman->IncreaseFatigue(1);

	std::cout << "[" << SPfisherman->getName() << "] [ID]: " << SPfisherman->getEntityID() << " [fish]:" << SPfisherman->getFishCarried() <<
		" ~ sold "<< item <<" for " << price << "$ [Money] " << SPfisherman->getMoneyInBank() << " $ " << std::endl;

	if (SPfisherman->getMoneyInBank() >= 1000)
	{
		if (!SPfisherman->getIsWalking())
		{
			std::cout << "[" << SPfisherman->getName() << "] [ID]: " << SPfisherman->getEntityID() <<
				" [Money] " << SPfisherman->getMoneyInBank() << " $ [fish]: " << SPfisherman->getFishCarried() <<
				" ~ I'm rich, done working here! " << std::endl;

			SPfisherman->setIsWalking(true);
			SPfisherman->setRandomFreeTimeInstance(3);
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

void FishSouvenirShopState::enterState(std::shared_ptr<Fisherman> SPfisherman)
{
	std::cout << "[" << SPfisherman->getName() << "] enters the souvenirshop" << std::endl;
}

void FishSouvenirShopState::exitState(std::shared_ptr<Fisherman> SPfisherman)
{
	std::cout << "[" << SPfisherman->getName() << "] exits the souvenirshop" << std::endl;
}

bool FishSouvenirShopState::onMessage(std::shared_ptr<Fisherman> SPfisherman, Telegram& telegram)
{
	return false;
}

void FishSouvenirShopState::randomizerSetSouvenirs()
{
	int luckyNumber = 6;

	int randomIndex = rand() % luckyNumber;

	auto it = fishingSouvenir.begin();
	std::advance(it, randomIndex);

	item = it->first;
	price = it->second;
}
