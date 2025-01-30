#include "Fisherman.h"
#include "state.h"
#include "FishingState.h"
#include "RestaurantState.h"
#include "LemonadeStandState.h"
#include "RestingState.h"
#include "FishSouvenirShopState.h"
#include "WalkingState.h"
#include "cassert"

#include "MessageDispatcher.h"

void Fisherman::setRandomInstanceGenerator(int num)
{

	int randomStateIndex = rand() % num;

	switch (randomStateIndex)
	{
	case 0:
		setDestination(Fisherman::locationType::market);
		this->currentState = std::make_shared<WalkingState>();;
		break;
	case 1:
		setDestination(Fisherman::locationType::pond);
		this->currentState = std::make_shared<WalkingState>();;
		break;
	case 2:
		setDestination(Fisherman::locationType::fishingSouvenirShop);
		this->currentState = std::make_shared<WalkingState>();
		break;
	case 3: 
		setDestination(Fisherman::locationType::house);
		this->currentState = std::make_shared<WalkingState>();
		break;
	case 4:
		setDestination(Fisherman::locationType::restaurant);
		this->currentState = std::make_shared<WalkingState>();
		break;
	case 5:
		setDestination(Fisherman::locationType::lemonadeStand);
		this->currentState = std::make_shared<WalkingState>();

	default:
		break;
	}

}

void Fisherman::setRandomWorkInstance(int num)
{
	int randomStateIndex = rand() % num;

	switch (randomStateIndex)
	{
	case 0:
		setDestination(Fisherman::locationType::fishingSouvenirShop);
		this->currentState = std::make_shared<WalkingState>();;
		break;
	case 1:
		setDestination(Fisherman::locationType::pond);
		this->currentState = std::make_shared<WalkingState>();;
		break;

	default:
		break;
	}

}

void Fisherman::setRandomFreeTimeInstance(int num)
{
	int randomStateIndex = rand() % num;

	switch (randomStateIndex)
	{
	case 0:
		setDestination(Fisherman::locationType::restaurant);
		this->currentState = std::make_shared<WalkingState>();
		break;
	case 1:
		setDestination(Fisherman::locationType::lemonadeStand);
		this->currentState = std::make_shared<WalkingState>();
		break;
	case 2:
		setDestination(Fisherman::locationType::house);
		this->currentState = std::make_shared<WalkingState>();
	default:
		break;
	}
}

Fisherman::Fisherman()
{

	this->setEntityID(0);
	this->name = "unnamed";
	this->fatigue = 0;
	this->water = 200;
	this->food = 200;
	this->moneyInBank = 200;
	this->fishCarried = 2;
	this->socialStatus = 100;
	this->setRandomInstanceGenerator(4);
	this->isWalking = false;

	//reset ticks
	this->setTicks(0);

}

Fisherman::Fisherman(int pFood, int pWater, int pMoneyInBank, int socialCredits, int randomNumb)
{

	this->fatigue = 0;
	this->water = 100 + 10 * pWater;
	this->food = 100 + 10 * pFood;
	this->moneyInBank = 200 + 10 * pMoneyInBank;
	this->fishCarried = 0;
	this->socialStatus = 30 + 10 * socialCredits;
	this->setRandomInstanceGenerator(randomNumb);

	this->isWalking = false;
}

bool Fisherman::handleMessage(Telegram& msg)
{
	if (GetisAvailableForSocializing())
	{
		std::cout << "[" << this->getName() << "] [ID]: " << this->getEntityID()
			<< " ~ I'm available! Let's meet up at" << std::endl;

		// Send confirmation back to the sender
		MessageDispatcher::instance()->DispatchMessage(0,  // No delay
			this->getEntityID(),
			msg.getIdSender(),
			MessageType::msg_socializeResponse,	
			nullptr);
		return true;
	}
    return false;
}

void Fisherman::setCurrentLocation(locationType location)
{
	this->currentLocation = location;
}
Fisherman::locationType Fisherman::getCurrentLocation()
{
	return this->currentLocation;
}
void Fisherman::setDestination(locationType location)
{
	this->destination = location;
}

Fisherman::locationType Fisherman::getDestination()
{
	return this->destination;
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
	
	water -= 3;
	food -= 1;

	if(fisherman->getCurrentState() == nullptr)
	{
		setRandomInstanceGenerator(6);
	}

	else
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

void Fisherman::addFishCarried(int fish)
{
	this->fishCarried += fish;
}

int Fisherman::getFishCarried()
{
	return this->fishCarried;
}

void Fisherman::addSocialStatus(int socialStatus)
{
	this->socialStatus += socialStatus;
}

int Fisherman::getSocialStatus()
{
	return this->socialStatus;
}

void Fisherman::eatFood(int food)
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

void Fisherman::drinkWater(int water)
{
	this->water += water;
}

int Fisherman::getWater()
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

int Fisherman::getFatigue()
{
	return this->fatigue;
}

bool Fisherman::isFishingBagFull()
{
	return this->fishCarried >= 7;
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
	return this->fatigue >= 150;
}

bool Fisherman::isDead()
{
	if (this->fatigue >= 200 || this->water <= 0 || this->food <= 0)
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

bool Fisherman::GetisAvailableForSocializing()
{
	return this->isAvailable;
}

void Fisherman::SetisAvailableForSocializing(bool Available)
{
	this->isAvailable = Available;
}

void Fisherman::addTicks(int ticks)
{
	this->ticks += ticks;
}

void Fisherman::setTicks(int ticks)
{
	this->ticks = ticks;
}

int Fisherman::getTicks()
{
	return this->ticks;
}


