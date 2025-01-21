#include "FishingState.h"
#include "RestingState.h"

FishingState::FishingState()
{

}

std::shared_ptr< FishingState> FishingState::instance()
{
	std::shared_ptr<FishingState> fishingState = std::make_shared<FishingState>();
	return fishingState->
}
//make more instances, look at the text you need it
e123e123

void FishingState::handle(std::shared_ptr<Fisherman> SPfisherman)
{
	SPfisherman->addFishCarried(1);
	SPfisherman->IncreaseFatigue(1);
	std::cout << "[name]: " << SPfisherman->getName() << "[ID]: " << SPfisherman->getEntityID() <<
		": catching a fish!" << std::endl;

	if (SPfisherman->isFishingBagFull())
	{
		SPfisherman->setCurrentState(vusut)
	}
	
}

void FishingState::enterState(std::shared_ptr<Fisherman> SPfisherman)
{
	if (SPfisherman->getCurrentLocation() != Fisherman::locationType::pond)
	{
		std::cout << "[name]: " << SPfisherman->getName() << "[ID]: " << SPfisherman->getEntityID() <<
		": walking to the pond" << std::endl;
		SPfisherman->setCurrentLocation(Fisherman::locationType::pond);
	}
	

}

void FishingState::exitState(std::shared_ptr<Fisherman> fisherman)
{
	std::cout << fisherman->getName() << "Exiting fishing state.." << std::endl;
}
