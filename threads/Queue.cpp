#include "Queue.h"

void queue::stop() {
    isCancel = true;
    d_condition.notify_all();
}

void queue::waitMode() {
    isWaitMode = true;
}

void queue::push(Functor const& value) {
    std::lock_guard<std::mutex> lock(this->d_mutex);

    if (isWaitMode)
        return;
    d_queue.push_front(value);
    this->d_condition.notify_one();
}

void queue::clearQueue() {
    std::lock_guard<std::mutex> lock(this->d_mutex);
    d_queue.clear();
}

bool queue::isCanStop() {
    std::unique_lock<std::mutex> lock(this->d_mutex);

    this->d_condition.wait(
        lock, [=] {
            return (this->d_queue.empty());
        }
    );
    return true;
}

Functor queue::pop() {
    std::unique_lock<std::mutex> lock(this->d_mutex);

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