#include "SocializeState.h"
#include "WalkingState.h"

std::shared_ptr<SocializeState> SocializeState::instance()
{
    static std::shared_ptr<SocializeState> socializeState = std::make_shared<SocializeState>();
    return socializeState;
}

void SocializeState::handle(std::shared_ptr<Fisherman> SPfisherman)
{
	SPfisherman->addSocialStatus(30);
	SPfisherman->IncreaseFatigue(2);


	if (SPfisherman->isThirsty())
	{
		if (!SPfisherman->getIsWalking())
		{
			std::cout << "[" << SPfisherman->getName() << "] [ID]: " << SPfisherman->getEntityID() <<
				" [Money] " << SPfisherman->getMoneyInBank() << " $ [fish]: " << SPfisherman->getFishCarried() <<
				" ~ I am really thirsty, I will go to the lemonade stand and get a drink! good bye! " << std::endl;
			SPfisherman->SetisAvailableForSocializing(false);
			SPfisherman->setDestination(Fisherman::locationType::lemonadeStand);
			SPfisherman->setIsWalking(true);
			SPfisherman->setCurrentState(std::make_shared<WalkingState>());
		}

	}
	else if (SPfisherman->isHungry())
	{
		if (!SPfisherman->getIsWalking())
		{
			std::cout << "[" << SPfisherman->getName() << "] [ID]: " << SPfisherman->getEntityID() <<
				" [Money] " << SPfisherman->getMoneyInBank() << " $ [fish]: " << SPfisherman->getFishCarried() <<
				" ~ I am really hungry, I will go to the resturant and get a something to eat! good bye " << std::endl;

			SPfisherman->SetisAvailableForSocializing(false);
			SPfisherman->setDestination(Fisherman::locationType::restaurant);
			SPfisherman->setIsWalking(true);
			SPfisherman->setCurrentState(std::make_shared<WalkingState>());
		}
	}
	else if (SPfisherman->getSocialStatus() >= 200)
	{
		if (!SPfisherman->getIsWalking())
		{
			std::cout << "[" << SPfisherman->getName() << "] [ID]: " << SPfisherman->getEntityID() <<
				" [Money] " << SPfisherman->getMoneyInBank() << " $ [fish]: " << SPfisherman->getFishCarried() <<
				" thanks for today I gotta work, good bye! " << std::endl;

			SPfisherman->SetisAvailableForSocializing(false);
			SPfisherman->setIsWalking(true);
			SPfisherman->setRandomWorkInstance(1);
		}
	}
	std::cout << "[" << SPfisherman->getName() << "] [ID]: " << SPfisherman->getEntityID() <<
		" [Money] " << SPfisherman->getMoneyInBank() << " $ [fish]: " << SPfisherman->getFishCarried() <<
		" bla bla bla bla bla bla..... " << std::endl;
}

void SocializeState::enterState(std::shared_ptr<Fisherman> SPfisherman)
{
    std::cout << "[" << SPfisherman->getName() << "] [ID]: " << SPfisherman->getEntityID() <<
        " enters the " << SPfisherman->getLocationTypeName(SPfisherman->getCurrentLocation()) << std::endl;
}

void SocializeState::exitState(std::shared_ptr<Fisherman> SPfisherman)
{
	std::cout << "[" << SPfisherman->getName() << "] [ID]: " << SPfisherman->getEntityID() <<
		" exits the " << SPfisherman->getLocationTypeName(SPfisherman->getCurrentLocation()) << std::endl;
}

bool SocializeState::onMessage(std::shared_ptr<Fisherman> SPfisherman, Telegram& telegram)
{
    return false;
}
