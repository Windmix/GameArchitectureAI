#pragma once
#include <chrono>
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