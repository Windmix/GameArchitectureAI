#include "BaseGameEntity.h"

void BaseGameEntity::setID(int value)
{
	if (value <= this->nextValidID)
	{
		value = entityID;
		nextValidID++;
	}
}

BaseGameEntity::BaseGameEntity()
{
	entityID = 0;
	nextValidID = 1;
}

BaseGameEntity::BaseGameEntity(int ID)
{
	setID(ID);
}

void BaseGameEntity::setEntityID(unsigned int ID)
{
	this->entityID = ID;
}

unsigned int BaseGameEntity::getEntityID()
{
	return this->entityID;
}