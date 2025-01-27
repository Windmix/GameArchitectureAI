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

private:
	std::string name;

	std::shared_ptr<State<Fisherman>> currentState;
	std::shared_ptr<State<Fisherman>> previousState;
	std::shared_ptr<State<Fisherman>> globalState;

	locationType currentLocation;
	

	unsigned int fishCarried;
	int moneyInBank;
	int water = 200;
	int food = 200;
	int fatigue = 200;

	bool isWalking;
private:
	std::shared_ptr<State<Fisherman>> randomInstanceGenerator(int num);
public:
	Fisherman();


	// ID and update
	void update(std::shared_ptr<Fisherman> fisherman) override;
	void setName(std::string newName);
	std::string getName();

	// location and state
	void setCurrentLocation(locationType location);
	locationType getCurrentLocation();

	void setCurrentState(std::shared_ptr< State<Fisherman>> newtate);
	std::shared_ptr< State<Fisherman>> getCurrentState();
	void RevertToPrevousState();

	//Inventory Stuff
	void addFishCarried(unsigned int fish);
	unsigned int getFishCarried();

	void eatFood(unsigned int food);
	int getFood();

	void addMoneyInBank(int money);
	int getMoneyInBank();

	void drinkWater(unsigned int water);
	unsigned int getWater();

	void IncreaseFatigue(int fatigueLevel);
	void ResetFatigue(int val);
	unsigned int getFatigue();

	//conditions
	bool isFishingBagFull();
	bool isThirsty();
	bool isHungry();
	bool isFatigue();
	bool isDead();

	void setIsWalking(bool walking);
	bool getIsWalking();
};