#pragma once
#include <chrono>
#include <iomanip>
#include <iostream>
#include <memory>

class TimeManager
{
private:
    // Get the current time
    std::chrono::system_clock::time_point currentTime;
    std::chrono::system_clock::time_point previousTime;

    std::chrono::system_clock::duration duration;
    long long milliseconds;

    // Singleton instance

public:
    TimeManager();

    struct clockInGame
    {
        double min;
        double days;
        double scaleFactor = 1440.0f;
        void updateTime(double realTimeSeconds);
        clockInGame();
    };

    double tick = 1.0;
    double timerTick = 0.0f;
    double realTime;
    clockInGame clockInGame;

    // Singleton access method
    static std::shared_ptr<TimeManager> getInstance();

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