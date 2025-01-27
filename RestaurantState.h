#pragma once
#include "State.h"
#include "Fisherman.h"


class RestaurantState : public State<Fisherman>
{
public:
	struct roastedFood
	{
		int roastedChicken = 13;
	};
private:
	int roastedFoodStock;
public:
	RestaurantState();
	
	static std::shared_ptr<RestaurantState> instance();
	void handle(std::shared_ptr<Fisherman> SPfisherman) override;
	void enterState(std::shared_ptr<Fisherman> SPfisherman) override;
	void exitState(std::shared_ptr<Fisherman> SPfisherman) override;


	void setRandomWorkInstance(std::shared_ptr<Fisherman> SPfisherman);
	void refilRoastedFoodStock(float time);
};