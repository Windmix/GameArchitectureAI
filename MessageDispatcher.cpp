#include "MessageDispatcher.h"
#include "BaseGameEntity.h"
#include "EntityManager.h"
#include "TimeManager.h"
#include <iostream>


void MessageDispatcher::discharge(std::shared_ptr<BaseGameEntity> spReceiver, Telegram& msg)
{
    if (!spReceiver)
    {
        std::cerr << "Error: Null receiver in MessageDispatcher::discharge" << std::endl;
        return;
    }
    if (!spReceiver->handleMessage(msg))
    {
        std::cerr << "Warning: Message not handled by receiver with ID " << spReceiver->getEntityID() << std::endl;
    }



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

    Telegram telegram(delay, sender, receiver, msg, ExtraInfo);
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
