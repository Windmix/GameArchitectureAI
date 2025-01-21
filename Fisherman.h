#pragma once
#include <string>
#include <memory>
#include "BaseGameEntity.h"

// Forward declare State
class State;

class Fisherman : public BaseGameEntity
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
	std::shared_ptr<State> currentState;
	locationType currentLocation;

	unsigned int fishCarried;
	int moneyInBank;
	unsigned int thirst;
	unsigned int fatigue;

public:
	Fisherman();

	void setCurrentLocation(locationType location);
	locationType getCurrentLocation();

	void setCurrentState(std::shared_ptr<State> newtate);
	std::shared_ptr<State> getCurrentState();
	void update(std::shared_ptr<Fisherman> fisherman) override;
	
	void setName(std::string newName);
	std::string getName();

	void addFishCarried(unsigned int fish);
	unsigned int getFishCarried();

	void setMoneyInBank(int money);
	int getMoneyInBank();

	void IncreaseThirst(unsigned int thirstLevel);
	unsigned int getThirst();

	void IncreaseFatigue(unsigned int fatigueLevel);
	unsigned int getFatigue();

	bool isFishingBagFull();
};