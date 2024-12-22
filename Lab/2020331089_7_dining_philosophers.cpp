#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <chrono>

using namespace std;

const int no_of_philosophers = 10;

// Structure to represent Chopsticks (Mutexes)
struct Chopstick {
    std::mutex mu;
};

// Function to simulate the eating action
void eat(Chopstick &left_chopstick, Chopstick& right_chopstick, int philosopher_number) {
    // Lock the left and right chopstick
    std::unique_lock<std::mutex> lock_left(left_chopstick.mu);  // Lock left chopstick
    std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Optional delay before locking the right chopstick
    
    std::unique_lock<std::mutex> lock_right(right_chopstick.mu);  // Lock right chopstick

    // Simulate eating
    cout << "Philosopher " << philosopher_number << " is eating" << endl;

    // Simulate eating time
    std::chrono::milliseconds timeout(1500);
    std::this_thread::sleep_for(timeout);

    // cout << "Philosopher " << philosopher_number << " has finished eating" << endl;
    cout << "Philosopher " << philosopher_number << " is reading" << endl;
}

int main() {
    vector<Chopstick> chp(no_of_philosophers);  // Create chopsticks for the philosophers

    vector<thread> philosophers(no_of_philosophers);  // Create philosopher threads

    // Create philosophers and assign them the task of eating
    for (int i = 0; i < no_of_philosophers; ++i) {
        if(i == 0 ) {
            philosophers[i] = std::thread(eat, std::ref(chp[(i + 1) % no_of_philosophers]), std::ref(chp[i]), i + 1);
        } else {
            // Philosopher i will use chopsticks i and (i+1)%no_of_philosophers
            philosophers[i] = std::thread(eat, std::ref(chp[i]), std::ref(chp[(i + 1) % no_of_philosophers]), i + 1);
        }
    }

    // Join all the philosopher threads
    for (auto& ph : philosophers) {
        ph.join();
    }

    return 0;
}
