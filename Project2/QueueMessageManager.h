#pragma once
class QueueMessageManager
{
public:

    QueueMessageManager();
    ~QueueMessageManager();

    void EnqueueMessage(const std::string& message, SClient* client);
    
    bool IsEmpty() const;

    SMessage DequeueMessage();


private:
    std::queue<SMessage> messages_;
    mutable std::mutex mutex_;

};

