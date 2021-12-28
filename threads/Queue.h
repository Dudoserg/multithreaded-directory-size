#include <mutex>
#include <condition_variable>
#include <deque>
#include <string>
#include <functional>

typedef std::function<void()> Functor;

class queue
{
private:
    std::mutex              d_mutex;
    std::condition_variable d_condition;
    std::deque<Functor> d_queue;
    std::atomic<bool> isCancel = false;
    bool isWaitMode = false;
public:
    void stop();

    void waitMode();

    void push(Functor const& value);

    void clearQueue();


    bool isCanStop();

    Functor pop();
};