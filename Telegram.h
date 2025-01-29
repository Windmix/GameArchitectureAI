#pragma once
#include <string>
class Telegram
{
private:
	int idSender;
	int idReceiver;
	std::string message;
public:
	int getIdSender();
	void setIdSender(int id);

	int getIdReceiver();
	void setIdReceiver(int id);

	std::string getMessage() const { return message; }
	void setMessage(const std::string& msg) { message = msg; }
};