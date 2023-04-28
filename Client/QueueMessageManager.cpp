#include "framework.h"

QueueMessageManager::QueueMessageManager()
{
}

QueueMessageManager::~QueueMessageManager()
{
}

void QueueMessageManager::EnqueueMessage(const std::string& message)
{
    std::lock_guard<std::mutex> lock(mutex_);
    messages_.push(message);
}

bool QueueMessageManager:: IsEmpty() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    return messages_.empty();
}

std::string QueueMessageManager::DequeueMessage()
{
    std::lock_guard<std::mutex> lock(mutex_);
    std::string message = messages_.front();
    messages_.pop();
    return message;
}


