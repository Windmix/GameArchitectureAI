#include "main.h"

int main()
{
	
	TimeManager time;
	LemonadeStandState lemonnadeStand;
	
	
	float tick = 1.0f;
	bool stopPrint = false;
	float timerTick = 0.0f;
	float timerRefilShop = 0.0f;
	static float realTime = 0.0f;

	auto fisherman = std::make_shared<Fisherman>();
	fisherman->setEntityID(1);
	fisherman->setName("Gangdam");

	while(true)
	{
		time.setCurrentTime(std::chrono::system_clock::now());
		std::chrono::duration<double> deltaTime = time.getDeltaTime();
		time.setPrevousTime(time.getCurrentTime());

		timerTick += deltaTime.count();
		timerRefilShop += deltaTime.count();
		realTime += deltaTime.count();
		

		if (timerTick >=  tick && timerTick <= tick + 0.1f)
		{
			
			(timerRefilShop);
			if (!fisherman->isDead())
			{
				time.clockInGame.updateTime(deltaTime.count());
				fisherman->update(fisherman);
			}
			if (fisherman->isDead() && !stopPrint)
			{
				time.clockInGame.updateTime(deltaTime.count());
				std::cout << "\n[name]: " << fisherman->getName() << "\n[ID]: " << fisherman->getEntityID() << "\n*DEAD*\n\n\n\n";
				stopPrint = true;
			}
			
			//lemonnadeStand.refilLemonadeStock(timerRefilShop);
			

			timerRefilShop = 0.0f;
			timerTick = 0.0f;
		}
		

		//std::cout << "deltaTime is: " << deltaTime.count() * 1000 << " milliseconds" << std::endl;
		//std::cout << "time is: " << std::fixed << std::setprecision(1) << realTime << " seconds" << std::endl;
	}
	return 0;
}