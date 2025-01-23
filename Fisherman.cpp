#include "Fisherman.h"
#include "state.h"
#include "FishingState.h"
#include "cassert"

Fisherman::Fisherman()
{
	this->setEntityID(0);
	this->name = "unnamed";
	this->currentState =FishingState::instance();
	this->fatigue = 0;
	this->thirst = 100;
	this->moneyInBank = 0;
	this->fishCarried = 0;
}
void Fisherman::setCurrentLocation(locationType location)
{
	this->currentLocation = location;
}
Fisherman::locationType Fisherman::getCurrentLocation()
{
	return this->currentLocation;
}
void Fisherman::setCurrentState(std::shared_ptr< State<Fisherman>> newState)
{

	assert(currentState && newState);
	currentState->exitState(shared_from_this());
	currentState = newState;
	currentState->enterState(shared_from_this());
	
	
}

std::shared_ptr< State<Fisherman>> Fisherman::getCurrentState()
{
	return this->currentState;
}

void Fisherman::RevertToPrevousState()
{
	std::shared_ptr<State<Fisherman>> tempstate = currentState;
	currentState = previousState;
	previousState = tempstate;
}

void Fisherman::update(std::shared_ptr<Fisherman> fisherman)
{
	thirst -= 1;
	if (currentState)
	{
		this->currentState->handle(shared_from_this());
	}
	

	
}

void Fisherman::setName(std::string newName)
{
	name = newName;
}

std::string Fisherman::getName()
{
	return this->name;
}

void Fisherman::addFishCarried(unsigned int fish)
{
	this->fishCarried += fish;
}

unsigned int Fisherman::getFishCarried()
{
	return this->fishCarried;
}

void Fisherman::addMoneyInBank(int money)
{
	this->moneyInBank += money;
}

int Fisherman::getMoneyInBank()
{
	return this->moneyInBank;
}

void Fisherman::IncreaseThirst(unsigned int thirstLevel)
{
	this->thirst += thirstLevel;
}

unsigned int Fisherman::getThirst()
{
	return this->thirst;
}

void Fisherman::IncreaseFatigue(unsigned int fatigueLevel)
{
	this->fatigue += fatigueLevel;
}

unsigned int Fisherman::getFatigue()
{
	return this->fatigue;
}

bool Fisherman::isFishingBagFull()
{
	return this->fishCarried >= 10;
}

bool Fisherman::isThirsty()
{
	return this->thirst <= 10;
}

bool Fisherman::isFatigue()
{
	return this->fatigue >= 100;
}


