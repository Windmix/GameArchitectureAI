#include "main.h"

int main()
{
	TimeManager time;

	float timer = 0.0f;
	float realTime = 0.0f;

	auto fishingState = std::make_shared <FishingState>();
	auto fisherman = std::make_shared<Fisherman>();
	fisherman->setName("Steve");
	fisherman->setEntityID(1);

	while(true)
	{
		time.setCurrentTime(std::chrono::system_clock::now());
		std::chrono::duration<double> deltaTime = time.getDeltaTime();
		time.setPrevousTime(time.getCurrentTime());
		timer += deltaTime.count();
		realTime += deltaTime.count();

		if (timer >= 2.0f && timer <= 2.1f)
		{
			
			fisherman->update(fisherman);
			timer = 0.0f;
		
		}
		

		//std::cout << "deltaTime is: " << deltaTime.count() * 1000 << " milliseconds" << std::endl;
		//std::cout << "time is: " << std::fixed << std::setprecision(1) << realTime << " seconds" << std::endl;
	}
	return 0;
}