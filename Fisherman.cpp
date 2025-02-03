#include "Fisherman.h"
#include "state.h"
#include "FishingState.h"
#include "RestaurantState.h"
#include "LemonadeStandState.h"
#include "RestingState.h"
#include "FishSouvenirShopState.h"
#include "WalkingState.h"
#include "cassert"
#include "string"
#include "Telegram.h"
#include "TimeManager.h"

#include "MessageDispatcher.h"

std::string Fisherman::getLocationTypeName(locationType type)
{
	{
		static const std::map<locationType, std::string> locationTypeNames =
		{
			{locationType::house, "Home"},
			{locationType::fishingSouvenirShop, "fishingSouvenirShop"},
			{locationType::restaurant, "restaurant"},
			{locationType::lemonadeStand, "lemonadeStand"},
			{locationType::market, "market"},
			{locationType::pond, "pond" }
		};
		auto iteration = locationTypeNames.find(type);
		if (iteration != locationTypeNames.end())
		{
			return iteration->second;
		}
		return "does not exist";
	}
}

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

void Fisherman::setRandomWorkInstance(int num) // random work, put in number for the intvall
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

void Fisherman::setRandomFreeTimeInstance(int num) // random bn  , put in number for the intvall
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

BaseGameEntity::locationType Fisherman::randomLocationGenerator(int num)
{

	int randomDice = rand() % num;
	switch (randomDice)
	{
	case 0:
		return locationType::fishingSouvenirShop;
	case 1:
		return locationType::house;
	case 2:
		return locationType::lemonadeStand;
	case 3:
		return locationType::market;
	case 4:
		return locationType::restaurant;
	case 5:
		return locationType::pond;
	default:
		return BaseGameEntity::locationType();
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
	this->socialStatus = 10;
	this->setRandomInstanceGenerator(4);
	this->isWalking = false;
	this->hasAgreed = false;

	//reset ticks
	this->setTicks(0);

}

Fisherman::Fisherman(int pFood, int pWater, int pMoneyInBank, int socialCredits, int randomNumb)
{

	this->fatigue = 0;
	this->water = 120 + 10 * pWater;
	this->food = 100 + 10 * pFood;
	this->moneyInBank = 200 + 10 * pMoneyInBank;
	this->fishCarried = 0;
	this->socialStatus = 30 + 10 * socialCredits;
	this->currentState = FishingState::instance();
	setRandomInstanceGenerator(randomNumb);

	this->isWalking = false;
	this->hasAgreed = false;
}

void Fisherman::handleMessage(Telegram& msg)
{
	auto globaltime = TimeManager::getInstance(); 
	switch (msg.getMessage())
	{
	case MessageType::msg_socializeResponseCall:
	{
		if (GetisAvailableForSocializing())
		{
			std::cout << "[" << this->getName() << "] [ID]: " << this->getEntityID()
				<< " ~ I'm available!" << std::endl;

			
			// Send confirmation back to the sender
			MessageDispatcher::instance()->DispatchMessage(0, this->getEntityID(), msg.getIdSender(), MessageType::msg_socializeResponseAccept, nullptr);

			
			break;
		}
		else
		{
			std::cout << "[" << this->getName() << "] [ID]: " << this->getEntityID() << " ~ No sorry I am busy right now" << std::endl;

			// Send deny back to the sender
			MessageDispatcher::instance()->DispatchMessage(0, this->getEntityID(), msg.getIdSender(), MessageType::msg_socializeResponseDeny, nullptr);
			break;
			
		}
	}
	case MessageType::msg_socializeResponseDeny:
	{
		if (!GetisAvailableForSocializing())
		{
			// Send confirmation back to the sender
			std::cout << "[" << this->getName() << "] [ID]: " << this->getEntityID() << " ~ ok, understandable" << std::endl;
			break;
		}

	}
	case MessageType::msg_socializeResponseAccept:
	{
		if (GetisAvailableForSocializing())
		{
			globalDestination = randomLocationGenerator(globaltime->realTime);
			
			this->setDestination(globalDestination);
			std::cout << "[" << this->getName() << "] [ID]: " << this->getEntityID()
				<< " ~ Great! Meeting up at " << getLocationTypeName(this->getDestination()) << std::endl;
			MessageDispatcher::instance()->DispatchMessage(0, this->getEntityID(), msg.getIdSender(), MessageType::msg_socializeResponseUnderStood, nullptr);

			
			this->setHasAgreed(true);
			this->setIsWalking(true);
			this->setCurrentState(std::make_shared<WalkingState>());
			break;
		}
		
	}
	case MessageType::msg_socializeResponseUnderStood:
		if (GetisAvailableForSocializing())
		{
			std::cout << "[" << this->getName() << "] [ID]: " << this->getEntityID()
				<< " ~ ok understood" << std::endl;

			this->setDestination(globalDestination);
			this->setHasAgreed(true);
			this->setIsWalking(true);
			this->setCurrentState(std::make_shared<WalkingState>());
			break;
		}
		
	}
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
	socialStatus -= 2;
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

bool Fisherman::getHasAgreed()
{
	return this->hasAgreed;
}

void Fisherman::setHasAgreed(bool agreed)
{
	this->hasAgreed = agreed;
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


