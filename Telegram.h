#pragma once
#include <string>
#include <memory>


enum class MessageType
{
	msg_socializeResponseCall,
	msg_socializeResponseAccept,
	msg_socializeResponseDeny,
	msg_socializeResponseUnderStood,
};

class Telegram
{
private:
	int idSender;
	int idReceiver;
	MessageType message;
	int dispatchTime;
	std::shared_ptr<void> extraInfo;

public:

	Telegram();
	Telegram(int delay, int sender, int receiver, MessageType msg, std::shared_ptr<void> ExtraInfo);
	int getIdSender();
	void setIdSender(int id);

	int getIdReceiver();
	void setIdReceiver(int id);

	MessageType getMessage();
	void setMessage(MessageType message);

	int getDispatchTime();
	void setDispatchTime(int disTime);
};