#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

enum class FeedType
{
    PRIMARY,
    SECONDARY
};

class MarketDataFeedHandler
{
    std::atomic<FeedType> currentFeedType{FeedType::PRIMARY};
    std::atomic<int> primaryData{0};
    std::atomic<int> secondaryData{0};
    std::atomic<bool> isRunning{true};

public:
    bool validatePrimaryFeed(int val)
    {
        return val % 5 != 0;
    }
    void primaryLine()
    {
        int value = 0;
        while (isRunning)
        {
            std::cout << "Primary Feed Data: " << value << std::endl;
            if (validatePrimaryFeed(value))
            {
                primaryData = value;
            }
            else
            {
                std::cout << "ERROR: Primary Feed Failed, Switching to Secondary Feed" << std::endl;
                currentFeedType = FeedType::SECONDARY;
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
            value++;
        }
    }

    void secondaryLine()
    {
        int value = 100;
        while (isRunning)
        {
            secondaryData = value;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            value++;
        }
    }

    void dataConsumer()
    {
        while (isRunning)
        {
            if (currentFeedType == FeedType::PRIMARY)
            {
                std::cout << "Consuming Primary Feed Data: " << primaryData << std::endl;
            }
            else
            {
                std::cout << "Consuming Secondary Feed Data: " << secondaryData << std::endl;
                currentFeedType = FeedType::PRIMARY;
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    void stop()
    {
        isRunning = false;
    }
};

int main()
{
    MarketDataFeedHandler handler;
    std::thread primaryThread(&MarketDataFeedHandler::primaryLine, &handler);
    std::thread secondaryThread(&MarketDataFeedHandler::secondaryLine, &handler);
    std::thread consumerThread(&MarketDataFeedHandler::dataConsumer, &handler);
    std::this_thread::sleep_for(std::chrono::seconds(15));
    handler.stop();
    primaryThread.join();
    secondaryThread.join();
    consumerThread.join();
    return 0;
}
