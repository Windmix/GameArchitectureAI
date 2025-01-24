#pragma once
#include<memory>
class Fisherman;

class BaseGameEntity
{
private:
	unsigned int entityID;
	static unsigned int nextValidID;

	void setID(int value);

public:
	//locations
	enum locationType
	{
		house,
		pond,
		lemonadeStand,
		restaurant,
		market,
	};

	BaseGameEntity();

	virtual void update(std::shared_ptr<Fisherman> fisherman) = 0;

	void setEntityID(unsigned int ID);
	unsigned int getEntityID();

	static unsigned int getNextValidID();
};
