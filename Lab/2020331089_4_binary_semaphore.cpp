// Binary semaphore

#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>

using namespace std;

class BinarySemaphore
{
private:
    mutex mtx;
    condition_variable cv;
    bool flag;

public:
    BinarySemaphore() : flag(false) {}

    void acquire()
    {
        unique_lock<mutex> lock(mtx);
        while (flag)
        {
            cv.wait(lock);
        }
        flag = true;
    }

    void release()
    {
        lock_guard<mutex> lock(mtx);
        flag = false;
        cv.notify_one();
    }
};

BinarySemaphore semaphore;

void P0()
{
    semaphore.acquire();
    cout << "Process0 is executing.\n";
    // Critical section
    this_thread::sleep_for(chrono::seconds(2));
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
