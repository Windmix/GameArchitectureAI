#pragma once
#include "State.h"
#include "Fisherman.h"
#include <map>

class FishSouvenirShopState : public State<Fisherman>
{
public:
	std::map<std::string, int> fishingSouvenir =
	{
		{"FishingHat",40},
		{"FishingRod",100},
		{"FishingBoots",45},
		{"FishingClothes",120},
		{"FishingBaits",20},
		{"FishingLures",60},
	};

	std::string item;
	int price;

	FishSouvenirShopState();

	static std::shared_ptr<FishSouvenirShopState> instance();
	void handle(std::shared_ptr<Fisherman> SPfisherman) override;
	void enterState(std::shared_ptr<Fisherman> SPfisherman) override;
	void exitState(std::shared_ptr<Fisherman> SPfisherman) override;

	bool onMessage(std::shared_ptr<Fisherman> SPfisherman, Telegram& telegram) override;

	void randomizerSetSouvenirs(); // seller select random items
};
