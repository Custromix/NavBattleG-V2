#pragma once
class QueueMessageManager
{
public:

    QueueMessageManager();
    ~QueueMessageManager();

    void EnqueueMessage(const std::string& message);
    
    bool IsEmpty() const;

    std::string DequeueMessage();


private:
    std::queue<std::string> messages_;
    mutable std::mutex mutex_;

};

