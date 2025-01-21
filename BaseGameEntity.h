#pragma once
#include<memory>
class Fisherman;

class BaseGameEntity
{
private:
	unsigned int entityID;
	unsigned int nextValidID;

	void setID(int value);

public:
	BaseGameEntity();
	BaseGameEntity(int ID);

	virtual void update(std::shared_ptr<Fisherman> fisherman) = 0;

	void setEntityID(unsigned int ID);
	unsigned int getEntityID();
};