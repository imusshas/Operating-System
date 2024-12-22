// Counting semaphore

#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>

using namespace std;

class CountingSemaphore
{
private:
    mutex mtx;
    condition_variable cv;
    int count;

public:
    CountingSemaphore(int initialCount) : count(initialCount) {}

    void acquire()
    {
        cout << "acquire" << count << "\n";
        unique_lock<mutex> lock(mtx);
        while (count <= 0)
        {
            cv.wait(lock);
        }
        count--;
    }

    void release()
    {
        cout << "release" << count << "\n";
        lock_guard<mutex> lock(mtx);
        count++;
        cv.notify_one();
    }
};

CountingSemaphore semaphore(1);

void P0()
{
    semaphore.acquire();
    cout << "Process0 is executing.\n";
    // Critical section
    this_thread::sleep_for(chrono::seconds(1));
    semaphore.release();
    cout << "Process0 is finished.\n";
}

void P1()
{
    semaphore.acquire();
    cout << "Process1 is executing.\n";
    // Critical section
    this_thread::sleep_for(chrono::seconds(1));
    semaphore.release();
    cout << "Process1 is finished.\n";
}

void P2()
{
    semaphore.acquire();
    cout << "Process2 is executing.\n";
    // Critical section
    this_thread::sleep_for(chrono::seconds(1));
    semaphore.release();
    cout << "Process2 is finished.\n";
}

void P3()
{
    semaphore.acquire();
    cout << "Process3 is executing.\n";
    // Critical section
    this_thread::sleep_for(chrono::seconds(1));
    semaphore.release();
    cout << "Process3 is finished.\n";
}

int main()
{
    thread t0(P0);
    thread t1(P1);
    thread t2(P2);
    thread t3(P3);

    t0.join();
    t1.join();
    t2.join();
    t3.join();

    return 0;
}
