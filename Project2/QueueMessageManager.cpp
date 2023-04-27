#include "Sframework.h"

QueueMessageManager::QueueMessageManager()
{
}

QueueMessageManager::~QueueMessageManager()
{
}

void QueueMessageManager::EnqueueMessage(const std::string& message, SClient* client)
{
    std::lock_guard<std::mutex> lock(mutex_);
    SMessage* smessage = new SMessage(client, message);
    messages_.push(*smessage);
}

bool QueueMessageManager:: IsEmpty() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    return messages_.empty();
}

SMessage QueueMessageManager::DequeueMessage()
{
    std::lock_guard<std::mutex> lock(mutex_);
    SMessage message = messages_.front();
    messages_.pop();
    return message;
}


