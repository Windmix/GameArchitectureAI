#include "MarketState.h"
#include "FishingState.h"
#include "LemonadeStandState.h"
#include "RestingState.h"

std::shared_ptr<MarketState> MarketState::instance()
{
	std::shared_ptr<MarketState> marketState = std::make_shared<MarketState>();
	return marketState;
}

void MarketState::handle(std::shared_ptr<Fisherman> SPfisherman)
{
	SPfisherman->addFishCarried(-1);
	SPfisherman->addMoneyInBank(20);
	SPfisherman->IncreaseFatigue(4);

	if (SPfisherman->getFishCarried() <= 0)
	{
		SPfisherman->setCurrentState(FishingState::instance());
	}
	std::cout << "\n[" << SPfisherman->getName() <<"]\n[ID]: " << SPfisherman->getEntityID() << "\n[fish:" << SPfisherman->getFishCarried() <<
		"] ~ sold Fish for 50$" << "\n[Money] " <<SPfisherman->getMoneyInBank() <<" $\n" << std::endl;

	if (SPfisherman->isThirsty())
	{
		SPfisherman->setCurrentState(LemonadeStandState::instance());
	}
	if (SPfisherman->isFatigue())
	{
		SPfisherman->setCurrentState(RestingState::instance());
	}

}

void MarketState::enterState(std::shared_ptr<Fisherman> SPfisherman)
{

	if (SPfisherman->getCurrentLocation() != Fisherman::locationType::market)
	{
		std::cout << "\n[" << SPfisherman->getName() << "]\n[ID]: " << SPfisherman->getEntityID() << "\n" << "aye, it's time for selling fishes babe~ \n";
		SPfisherman->setCurrentLocation(Fisherman::locationType::market);
	}
	
}

void MarketState::exitState(std::shared_ptr<Fisherman> SPfisherman)
{
	std::cout << "\n[" << SPfisherman->getName() << "]\n[ID]: " << SPfisherman->getEntityID() << "]\n" << "That's all fishes sold, Time to head back fishin'!\n";
}
