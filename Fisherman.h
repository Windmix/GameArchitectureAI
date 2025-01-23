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
	enum locationType
	{
		house,
		pond,
		lemonadeStand,
		market,
	};

private:
	std::string name;

	std::shared_ptr<State<Fisherman>> currentState;
	std::shared_ptr<State<Fisherman>> previousState;
	std::shared_ptr<State<Fisherman>> globalState;

	locationType currentLocation;

	unsigned int fishCarried;
	int moneyInBank;
	unsigned int thirst;
	unsigned int fatigue;

public:
	Fisherman();

	void setCurrentLocation(locationType location);
	locationType getCurrentLocation();

	void setCurrentState(std::shared_ptr< State<Fisherman>> newtate);
	std::shared_ptr< State<Fisherman>> getCurrentState();

	void RevertToPrevousState();

	void update(std::shared_ptr<Fisherman> fisherman) override;
	
	void setName(std::string newName);
	std::string getName();

	void addFishCarried(unsigned int fish);
	unsigned int getFishCarried();

	void addMoneyInBank(int money);
	int getMoneyInBank();

	void IncreaseThirst(unsigned int thirstLevel);
	unsigned int getThirst();

	void IncreaseFatigue(unsigned int fatigueLevel);
	unsigned int getFatigue();

	bool isFishingBagFull();
	bool isThirsty();
	bool isFatigue();
};