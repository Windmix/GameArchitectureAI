#include <iostream>
#include "TimeManager.h"
int main()
{
	TimeManager time;

	float realTime = 0.0f;

	while(true)
	{
		time.setCurrentTime(std::chrono::system_clock::now());
		std::chrono::duration<double> deltaTime = time.getDeltaTime();

		time.setPrevousTime(time.getCurrentTime());
		realTime += deltaTime.count();

		//std::cout << "deltaTime is: " << deltaTime.count() * 1000 << " milliseconds" << std::endl;
		//std::cout << "time is: " << std::fixed << std::setprecision(1) << realTime << " seconds" << std::endl;
	}
	return 0;
}