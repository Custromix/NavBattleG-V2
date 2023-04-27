#include "Sframework.h"

SMessage::SMessage(SClient* client, std::string message)
{
	receiver = client;
	message_ = message;
}

SMessage::~SMessage()
{
}
