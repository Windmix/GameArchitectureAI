#include "Fisherman.h"
#include "state.h"
#include "cassert"

Fisherman::Fisherman()
{
	this->setEntityID(0);
	this->name = "unnamed";
	this->currentState = nullptr;
	this->fatigue = 0;
	this->thirst = 0;
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
void Fisherman::setCurrentState(std::shared_ptr<State> newState)
{
	std::shared_ptr<Fisherman> fisherman = std::make_shared<Fisherman>();
	assert(currentState && newState);
	currentState->exitState(fisherman);
	currentState = newState;
	currentState->enterState(fisherman);
}

std::shared_ptr<State> Fisherman::getCurrentState()
{
	return this->currentState;
}

void Fisherman::update(std::shared_ptr<Fisherman> fisherman)
{
	thirst += 1;
	//this->currentState->enterState(fisherman);
	//this->currentState->exitState(fisherman);
	this->currentState->handle(fisherman);

	
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

void Fisherman::setMoneyInBank(int money)
{
	this->moneyInBank = money;
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


