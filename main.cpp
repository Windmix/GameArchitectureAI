#include "main.h"
#include "vector"
#include "EntityManager.h"

int main()
{
	auto time = TimeManager::getInstance();
	std::vector<std::shared_ptr<Fisherman>> fishermen;
	std::vector<bool> deadFishermen;
	int rngStats;
	int rngState;

	bool stopPrint = false;
	bool stopPrint2 = false;
	bool stopPrint3 = false;
	bool stopPrint4 = false;

	time->tick = 1.0f;
	time->timerTick = 0.0f;
	time->realTime = 0.0f;

	auto fisherman = std::make_shared<Fisherman>();
	auto fisherman2 = std::make_shared<Fisherman>();
	/*auto fisherman3 = std::make_shared<Fisherman>();
	auto fisherman4 = std::make_shared<Fisherman>();*/

	fisherman->setEntityID(1);
	fisherman->setName("Gangdam");
	fisherman2->setEntityID(2);
	fisherman2->setName("Gandalf");
	//fisherman3->setEntityID(3);
	//fisherman3->setName("Gnyrf");
	//fisherman4->setEntityID(4);
	//fisherman4->setName("Grubb");

	Entity_Manager->registerEntity(fisherman);
	Entity_Manager->registerEntity(fisherman2);
	//Entity_Manager->getEntityFromID()
	//Entity_Manager->registerEntity(fisherman3);
	//Entity_Manager->registerEntity(fisherman4);

	fishermen.push_back(fisherman);
	fishermen.push_back(fisherman2);
	/*fishermen.push_back(fisherman3);
	fishermen.push_back(fisherman4);*/

	for (int i = 0; i < fishermen.size(); i++) // some randomizing stats
	{
		rngStats = rand() % 4;
		rngState = rand() % 6;

		switch (i)
		{
		case 1:
			fisherman = std::make_shared<Fisherman>(rngStats, rngStats,rngStats, rngStats, rngState);
			break;
		case 2:
			fisherman2 = std::make_shared<Fisherman>(rngStats, rngStats, rngStats, rngStats, rngState);
			break;
		default:
			break;
		}
	
	}

	deadFishermen.push_back(stopPrint);
	deadFishermen.push_back(stopPrint2);
	/*deadFishermen.push_back(stopPrint3);
	deadFishermen.push_back(stopPrint4);*/

	while(true) // tick update
	{
		time->setCurrentTime(std::chrono::system_clock::now());
		std::chrono::duration<double> deltaTime = time->getDeltaTime();
		time->setPrevousTime(time->getCurrentTime());

		time->timerTick += deltaTime.count();

		time->realTime += deltaTime.count();
		

		if (time->timerTick >= time->tick && time->timerTick <= time->tick + 0.1f)
		{
			for (int i = 0; i < fishermen.size(); i++)
			{
				if (!fishermen[i]->isDead())
				{
					time->clockInGame.updateTime(deltaTime.count());
					fishermen[i]->update(fishermen[i]);
				}
				else if (fishermen[i]->isDead() && !deadFishermen[i])
				{
					time->clockInGame.updateTime(deltaTime.count());
					std::cout << "\n[name]: " << fishermen[i]->getName() << "\n[ID]: " << fishermen[i]->getEntityID() << "\n\n*DEAD*\n\n";
					std::cout << "cause of death:\nhunger: " << fishermen[i]->getFood() << "\nwater: " << fishermen[i]->getWater() << "\nfatigue: " << fishermen[i]->getFatigue() << std::endl;
					deadFishermen[i] = true;
				}
			}
			time->timerTick = 0.0f;
		}
		
		/*for (int i = 0; i < 3; i++)
		{
			std::cout << rand() % 4 << " " << std::endl;
		}*/

		//std::cout << "deltaTime is: " << deltaTime.count() * 1000 << " milliseconds" << std::endl;
		//std::cout << "time is: " << std::fixed << std::setprecision(1) << realTime << " seconds" << std::endl;
	}
	return 0;
}