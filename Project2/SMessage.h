#pragma once
class SMessage
{
public:
	SMessage(SClient* client, std::string message);
	~SMessage();

	SClient* GetClient() { return receiver; }
	std::string GetSMessage() { return message_; }

private :

	SClient* receiver;
	std::string message_;
};

