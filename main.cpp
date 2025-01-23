#include "main.h"

int main()
{
	
	TimeManager time;

	float timer = 0.0f;
	static float realTime = 0.0f;

	auto fisherman = std::make_shared<Fisherman>();
	fisherman->setEntityID(1);
	fisherman->setName("Gangdam");
	fisherman->setCurrentState(FishingState::instance());
	while(true)
	{
		time.setCurrentTime(std::chrono::system_clock::now());
		std::chrono::duration<double> deltaTime = time.getDeltaTime();
		time.setPrevousTime(time.getCurrentTime());
		timer += deltaTime.count();
		realTime += deltaTime.count();
		

		if (timer >= 1.0f && timer <= 1.1f)
		{
			time.clockInGame.updateTime(deltaTime.count());
			
			fisherman->update(fisherman);
			timer = 0.0f;
		
		}
		

		//std::cout << "deltaTime is: " << deltaTime.count() * 1000 << " milliseconds" << std::endl;
		//std::cout << "time is: " << std::fixed << std::setprecision(1) << realTime << " seconds" << std::endl;
	}
	return 0;
}