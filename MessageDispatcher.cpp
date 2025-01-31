#include "MessageDispatcher.h"
#include "BaseGameEntity.h"
#include "EntityManager.h"
#include "TimeManager.h"
#include <iostream>


// Remove the processed message from the priority queue
void MessageDispatcher::discharge(std::shared_ptr<BaseGameEntity> spReceiver, Telegram& msg)
{
    if (!spReceiver)
    {
        std::cerr << "Error: Null receiver in MessageDispatcher::discharge" << std::endl;
        return;
    }
    spReceiver->handleMessage(msg);

    // Remove the processed message from the priority queue
    std::priority_queue<Telegram, std::vector<Telegram>, TelegramComparator> tempQ;
    while (!priorityQ.empty())
    {
        Telegram topMsg = priorityQ.top();
        priorityQ.pop();
        if (topMsg.getIdReceiver() != msg.getIdReceiver())
        {
            tempQ.push(topMsg);
        }
    }
    priorityQ = tempQ;
}
    
std::shared_ptr<MessageDispatcher> MessageDispatcher::instance()
{
    static std::shared_ptr<MessageDispatcher> messageDispatcher = std::make_shared<MessageDispatcher>();
    return messageDispatcher;
}

void MessageDispatcher::DispatchMessage(int delay, int sender, int receiver, MessageType msg, std::shared_ptr<void> ExtraInfo)
{
    std::shared_ptr<BaseGameEntity> SPreceiver = Entity_Manager->getEntityFromID(receiver);
    auto time = TimeManager::getInstance();

    Telegram telegram(delay, sender, receiver, msg, ExtraInfo); // save information
    if (delay <= 0.0f)
    {
        discharge(SPreceiver, telegram);
    }
    else
    {
        int currentDay = time->clockInGame.days;
        telegram.setDispatchTime(currentDay + delay);
        priorityQ.push(telegram);
    }
}

std::priority_queue<Telegram, std::vector<Telegram>, TelegramComparator> MessageDispatcher::getPriorityQ()
{
    return this->priorityQ;
}

void MessageDispatcher::setPriorityQ(std::priority_queue<Telegram, std::vector<Telegram>, TelegramComparator> PriorityQ)
{
    this->priorityQ = PriorityQ;
}

void MessageDispatcher::dispatchDelayedMessages()
{
    auto time = TimeManager::getInstance();
    int currentDay = time->clockInGame.days;

    while (!priorityQ.empty())
    {
        Telegram telegram = priorityQ.top();  // Get the earliest message
        if (telegram.getDispatchTime() > currentDay)  // Not ready to dispatch yet
        {
            break;
        }
        std::shared_ptr<BaseGameEntity> SPreceiver = Entity_Manager->getEntityFromID(telegram.getIdReceiver());
        discharge(SPreceiver, telegram);

        priorityQ.pop();  // Remove the processed message
    }
}
