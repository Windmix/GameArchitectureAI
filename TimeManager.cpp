#include "TimeManager.h"


TimeManager::TimeManager()
{
	setCurrentTime(std::chrono::system_clock::now());
	setDuration(getCurrentTime().time_since_epoch());
	setMilliseconds(std::chrono::duration_cast<std::chrono::milliseconds>(getDuration()).count());
	setPrevousTime(getCurrentTime());
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
