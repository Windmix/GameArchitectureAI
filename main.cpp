#include "main.h"

int main()
{
	
	TimeManager time;
	LemonadeStandState lemonnadeStand;

	bool stopPrint = false;
	bool stopPrint2 = false;

	float tick = 1.0f;
	float timerTick = 0.0f;
	float timerRefilShop = 0.0f;
	static float realTime = 0.0f;

	auto fisherman = std::make_shared<Fisherman>();
	auto fisherman2 = std::make_shared<Fisherman>();

	fisherman->setEntityID(1);
	fisherman2->setEntityID(2);
	fisherman->setName("Gangdam");
	fisherman2->setName("Gandalf");

	while(true) // tick update
	{
		time.setCurrentTime(std::chrono::system_clock::now());
		std::chrono::duration<double> deltaTime = time.getDeltaTime();
		time.setPrevousTime(time.getCurrentTime());

		timerTick += deltaTime.count();
		timerRefilShop += deltaTime.count();
		realTime += deltaTime.count();
		

		if (timerTick >=  tick && timerTick <= tick + 0.1f)
		{
			
			
			if (!fisherman->isDead())
			{
				time.clockInGame.updateTime(deltaTime.count());
				fisherman->update(fisherman);
			}
			if (!fisherman2->isDead())
			{
				time.clockInGame.updateTime(deltaTime.count());
				fisherman2->update(fisherman2);
			}

			if (fisherman->isDead() && !stopPrint)
			{
				time.clockInGame.updateTime(deltaTime.count());
				std::cout << "\n[name]: " << fisherman->getName() << "\n[ID]: " << fisherman->getEntityID() << "\n*DEAD*\n\n\n\n";
				std::cout << "cause of death:\nhunger: " << fisherman->getFood() << "\nwater: " << fisherman->getWater() << "\nfatigue: " << fisherman->getFatigue() << std::endl;
				stopPrint = true;
			}

			if (fisherman2->isDead() && !stopPrint2)
			{
				time.clockInGame.updateTime(deltaTime.count());
				std::cout << "\n[name]: " << fisherman->getName() << "\n[ID]: " << fisherman2->getEntityID() << "\n*DEAD*\n\n\n\n";
				std::cout << "cause of death:\nhunger: " << fisherman2->getFood() << "\nwater: " << fisherman2->getWater() << "\nfatigue: " << fisherman2->getFatigue() << std::endl;
				stopPrint2 = true;
			}
			
			lemonnadeStand.refilLemonadeStock(timerRefilShop);
			

			timerRefilShop = 0.0f;
			timerTick = 0.0f;
		}
		

		//std::cout << "deltaTime is: " << deltaTime.count() * 1000 << " milliseconds" << std::endl;
		//std::cout << "time is: " << std::fixed << std::setprecision(1) << realTime << " seconds" << std::endl;
	}
	return 0;
}