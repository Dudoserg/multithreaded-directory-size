#include <mutex>
#include <condition_variable>
#include <deque>
#include <string>
#include <functional>

class queue
{
private:
    std::mutex              d_mutex;
    std::condition_variable d_condition;
    typedef std::function<std::string()> Functor;
    std::deque<Functor> d_queue;
    std::atomic<bool> isCancel = false;
    bool isWaitMode = false;
public:
    void stop() {
        isCancel = true;
        d_condition.notify_all();
    }

    void waitMode() {
        isWaitMode = true;
    }

    void push(Functor const& value) {
        if (isWaitMode)
            return;
        {
            std::unique_lock<std::mutex> lock(this->d_mutex);
            d_queue.push_front(value);
        }
        this->d_condition.notify_one();
    }

    void clearQueue() {
        std::unique_lock<std::mutex> lock(this->d_mutex);
        d_queue.clear();
    }


    bool isCanStop() {
        std::unique_lock<std::mutex> lock(this->d_mutex);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        this->d_condition.wait(
            lock, [=] {
                return (this->d_queue.empty());
            }
        );
        return true;
    }

    Functor pop() {
        std::unique_lock<std::mutex> lock(this->d_mutex);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        this->d_condition.wait(
            lock, [=] { 
                return (!this->d_queue.empty()) || isCancel;
            }
        );
        if (d_queue.empty())
            return nullptr;
        Functor rc(std::move(this->d_queue.back()));
        this->d_queue.pop_back();
        return rc;
    }
};