#include "TimeManager.h"


TimeManager::TimeManager()
{
	setCurrentTime(std::chrono::system_clock::now());
	setDuration(getCurrentTime().time_since_epoch());
	setMilliseconds(std::chrono::duration_cast<std::chrono::milliseconds>(getDuration()).count());
	setPrevousTime(getCurrentTime());

	float timer = 0.0f;
	float realTime = 0.0f;

}

void TimeManager::setCurrentTime(std::chrono::system_clock::time_point currentTime)
{
	this->currentTime = currentTime;
}

std::chrono::system_clock::time_point TimeManager::getCurrentTime()
{
	return this->currentTime;
}

void TimeManager::setPrevousTime(std::chrono::system_clock::time_point previousTime)
{
	this->previousTime = previousTime;
}

std::chrono::system_clock::time_point TimeManager::getPreviousTime()
{
	return this->previousTime;
}

void TimeManager::setDuration(std::chrono::system_clock::duration duration)
{
	this->duration = duration;
}

std::chrono::system_clock::duration TimeManager::getDuration()
{
	return this->duration;
}

std::chrono::duration<double> TimeManager::getDeltaTime()
{
	 auto deltaTime = getCurrentTime() - getPreviousTime();
	return deltaTime;
}

void TimeManager::setMilliseconds(long long miliseconds)
{
	this->milliseconds = miliseconds;
}

long long TimeManager::getTimeMilliseconds()
{
	return this->milliseconds;
}

void TimeManager::clockInGame::updateTime(float realTimeSeconds)
{
	// Each real second equals 24 in-game minutes
	float inGameMinutes = realTimeSeconds * 24.0f;  // 1 real second = 24 min
	min += inGameMinutes;
	days = min / scaleFactor;

	if(min >= 1440.0f)  // 1 in-game day = 1440 minutes
	{
		min = 0.0f;
		days += 1.0f;
	}

	std::cout << "min: " << "[" << std::fixed << std::setprecision(1) << min * 1000000*5*2 << "] " << " days: " << "[" << std::fixed << std::setprecision(1) << days * 1000000*5*2 << "]" << std::endl;
}
