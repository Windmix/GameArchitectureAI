#include "Fisherman.h"
#include "state.h"
#include "FishingState.h"
#include "RestaurantState.h"
#include "LemonadeStandState.h"
#include "RestingState.h"
#include "FishSouvenirShopState.h"
#include "WalkingState.h"
#include "cassert"

#include <cstdlib> 
#include <ctime>

std::shared_ptr<State<Fisherman>> Fisherman::randomInstanceGenerator(int num)
{
	srand(static_cast<unsigned>(time(0)));

	int randomStateIndex = rand() % num;

	std::shared_ptr<State<Fisherman>> randomState;
	switch (randomStateIndex)
	{
	case 0:
		return randomState = FishingState::instance();
	case 1:
		return randomState = RestaurantState::instance();
	case 2:
		return randomState = LemonadeStandState::instance();
	case 3: 
		return randomState = RestingState::instance();
	case 4:
		return randomState = FishSouvenirShopState::instance();


	default:
		break;
	}

}

Fisherman::Fisherman()
{
	this->setEntityID(0);
	this->name = "unnamed";
	this->currentState = randomInstanceGenerator(5);
	this->fatigue = 0;
	this->water = 200;
	this->food = 200;
	this->moneyInBank = 200;
	this->fishCarried = 0;
	this->isWalking = false;
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
	
	//currentState->exitState(shared_from_this());
	currentState = newState;
	//currentState->enterState(shared_from_this());
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
	
	water -= 3;
	food -= 1;
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

void Fisherman::eatFood(unsigned int food)
{
	this->food += food;
}

int Fisherman::getFood()
{
	return this->food;
}

void Fisherman::addMoneyInBank(int money)
{
	this->moneyInBank += money;
}

int Fisherman::getMoneyInBank()
{
	return this->moneyInBank;
}

void Fisherman::drinkWater(unsigned int water)
{
	this->water += water;
}

unsigned int Fisherman::getWater()
{
	return this->water;
}

void Fisherman::IncreaseFatigue(int fatigueLevel)
{
	this->fatigue += fatigueLevel;
}

void Fisherman::ResetFatigue(int val)
{
	this->fatigue = val;
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
	return this->water <= 30;
}

bool Fisherman::isHungry()
{
	return this->food <= 30;
}

bool Fisherman::isFatigue()
{
	return this->fatigue >= 70;
}

bool Fisherman::isDead()
{
	if (this->fatigue >= 100 || this->water <= 0 || this->food <= 0)
		return true;
	else
		return false;
}

void Fisherman::setIsWalking(bool walking)
{
	this->isWalking = walking;
}

bool Fisherman::getIsWalking()
{
	return this->isWalking;
}


