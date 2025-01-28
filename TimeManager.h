#pragma once
#include <chrono>
#include <iomanip>
#include <iostream>
class TimeManager
{
private:
	// Get the current time
	std::chrono::system_clock::time_point currentTime;
	std::chrono::system_clock::time_point previousTime;

	std::chrono::system_clock::duration duration;
	long long milliseconds;


public:

	struct clockInGame
	{
		double min = 0.0f;
		double days = 0.0f;
		double scaleFactor = 1440.0f;
		void updateTime(double realTimeSeconds);
	};

	TimeManager::clockInGame clockInGame;

	TimeManager();

	void setCurrentTime(std::chrono::system_clock::time_point currentTime);
	std::chrono::system_clock::time_point getCurrentTime();

	void setPrevousTime(std::chrono::system_clock::time_point previousTime);
	std::chrono::system_clock::time_point getPreviousTime();

	void setDuration(std::chrono::system_clock::duration duration);
	std::chrono::system_clock::duration getDuration();

	std::chrono::duration<double> getDeltaTime();

	void setMilliseconds(long long miliseconds);
	long long getTimeMilliseconds();


};