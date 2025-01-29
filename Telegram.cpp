#include "Telegram.h"

int Telegram::getIdSender()
{
	return this->idSender;
}

void Telegram::setIdSender(int id)
{
	this->idSender = id;
}

int Telegram::getIdReceiver()
{
	return this->idReceiver;
}

void Telegram::setIdReceiver(int id)
{
	this->idReceiver = id;
}
