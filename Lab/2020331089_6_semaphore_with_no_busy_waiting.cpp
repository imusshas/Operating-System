#include <mutex>
#include <condition_variable>
#include <iostream>
#include <thread>

class Semaphore {
private:
    std::mutex mutex_;
    std::condition_variable condition_;
    int count_;

public:
    Semaphore(int count = 0) : count_(count) {}

    void notify() {
        std::unique_lock<std::mutex> lock(mutex_);
        ++count_;
        condition_.notify_one();
    }

    void wait() {
        std::unique_lock<std::mutex> lock(mutex_);
        condition_.wait(lock, [this] { return count_ > 0; });
        --count_;
    }
};

Semaphore sem(3);

void worker(int id) {
    sem.wait();
    std::cout << "Process " << id << " is working." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Process " << id << " is done." << std::endl;
    sem.notify();
}

int main() {
    std::thread t1(worker, 1);
    std::thread t2(worker, 2);
    std::thread t3(worker, 3);
    std::thread t4(worker, 4);
    std::thread t5(worker, 5);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    return 0;
}
