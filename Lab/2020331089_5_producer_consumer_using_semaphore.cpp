#include <iostream>
#include <thread>
#include <mutex>
#include <semaphore.h>
#include <vector>
#include <unistd.h>

using namespace std;

const int BUFFER_SIZE = 5;

// Buffer to hold items, semaphores to manage buffer state
vector<int> buffer(BUFFER_SIZE);
int in = 0;
int out = 0;

// Declare semaphores with more descriptive names to avoid ambiguity
sem_t emptySemaphore;
sem_t fullSemaphore;
mutex mtx;

void produce(int item) {
    sem_wait(&emptySemaphore);  // Wait for an empty slot
    mtx.lock();                  // Lock the mutex to modify the buffer
    buffer[in] = item;
    cout << "Producer Produced item no. : " << item << endl;
    in = (in + 1) % BUFFER_SIZE;
    mtx.unlock();                // Unlock the mutex after modifying the buffer
    sem_post(&fullSemaphore);    // Signal that there's a new item in the buffer
}

void consume() {
    sem_wait(&fullSemaphore);    // Wait for a full slot
    mtx.lock();                  // Lock the mutex to modify the buffer
    int item = buffer[out];
    cout << "Consumer Consumed item no. : " << item << endl;
    out = (out + 1) % BUFFER_SIZE;
    mtx.unlock();                // Unlock the mutex after modifying the buffer
    sem_post(&emptySemaphore);   // Signal that there's an empty slot
}

void producer() {
    for (int i = 0; i < 5; ++i) {
        produce(i);
        sleep(1);  // Simulate time taken to produce an item
    }
}

void consumer() {
    for (int i = 0; i < 5; ++i) {
        consume();
        sleep(2);  // Simulate time taken to consume an item
    }
}

int main() {
    // Initialize semaphores: emptySemaphore starts full, fullSemaphore starts empty
    sem_init(&emptySemaphore, 0, BUFFER_SIZE);
    sem_init(&fullSemaphore, 0, 0);

    // Start producer and consumer threads
    thread producer_thread(producer);
    thread consumer_thread(consumer);

    // Join threads (wait for them to finish)
    producer_thread.join();
    consumer_thread.join();

    // No need to destroy semaphores in modern systems (they are cleaned up automatically)
    return 0;
}
