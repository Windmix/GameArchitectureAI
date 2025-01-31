#pragma once
#include <string>
#include <memory>
#include "BaseGameEntity.h"
#include "State.h"

// Forward declare State
template<class entityType>
class State;



class Fisherman : public BaseGameEntity, public std::enable_shared_from_this<Fisherman>
{
public:

	std::string getLocationTypeName(locationType type);

private:
	std::string name;

	std::shared_ptr<State<Fisherman>> currentState;
	std::shared_ptr<State<Fisherman>> previousState;
	std::shared_ptr<State<Fisherman>> globalState;

	//locations
	locationType previousLocation;
	locationType destination;
	locationType currentLocation;
	
	

	int fishCarried;
	int moneyInBank;
	int water;
	int food;
	int fatigue;
	int socialStatus;

	//inner clock
	int ticks;

	bool isWalking;
	bool isAvailable;
	bool hasAgreed;
private:
	void setRandomInstanceGenerator(int num);
	

public:
	Fisherman();
	Fisherman(int pFood, int pWater, int pMoneyInBank, int socialCredits, int randomNumb);
	
	void handleMessage(Telegram& msg) override;

	void setRandomWorkInstance(int num);
	void setRandomFreeTimeInstance(int num);

	locationType randomLocationGenerator(int num);

	// ID and update
	void update(std::shared_ptr<Fisherman> fisherman) override;
	void setName(std::string newName);
	std::string getName();

	// location and state
	void setCurrentLocation(locationType location);
	locationType getCurrentLocation();
	void setDestination(locationType location);
	locationType getDestination();

	void setCurrentState(std::shared_ptr< State<Fisherman>> newState);
	std::shared_ptr< State<Fisherman>> getCurrentState();
	void RevertToPrevousState();

	//Inventory Stuff
	void addFishCarried(int fish);
	int getFishCarried();
	void addSocialStatus(int socialStatus);
	int getSocialStatus();

	void eatFood(int food);
	int getFood();

	void addMoneyInBank(int money);
	int getMoneyInBank();

	void drinkWater(int water);
	int getWater();

	void IncreaseFatigue(int fatigueLevel);
	void ResetFatigue(int val);
	int getFatigue();

	//conditions
	bool isFishingBagFull();
	bool isThirsty();
	bool isHungry();
	bool isFatigue();
	bool isDead();

	void setIsWalking(bool walking);
	bool getIsWalking();

	bool GetisAvailableForSocializing();
	void SetisAvailableForSocializing(bool Available);
	bool getHasAgreed();
	void setHasAgreed(bool agreed);

	void addTicks(int ticks);
	void setTicks(int ticks);
	int getTicks();
};