#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

// Structure to represent a process
struct Process {
    int pid;           // Process ID
    int arrivalTime;   // Arrival time
    int burstTime;     // Burst time (CPU time)
    int completionTime;
    int waitingTime;
    int turnaroundTime;
    
    // Constructor to initialize process
    Process(int id, int arrival, int burst) : pid(id), arrivalTime(arrival), burstTime(burst), 
                                              completionTime(0), waitingTime(0), turnaroundTime(0) {}
};

// Function to calculate waiting time and turnaround time
void calculateTimes(vector<Process>& processes) {
    int n = processes.size();
    
    // First process starts at its arrival time
    processes[0].completionTime = processes[0].arrivalTime + processes[0].burstTime;
    processes[0].waitingTime = 0;  // No waiting for the first process
    processes[0].turnaroundTime = processes[0].burstTime; // Turnaround time = Burst time for the first process

    // Calculate times for all other processes
    for (int i = 1; i < n; ++i) {
        // Completion time of the current process is the completion time of the previous process + its burst time
        processes[i].completionTime = max(processes[i - 1].completionTime, processes[i].arrivalTime) + processes[i].burstTime;
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
    }
}

// Function to print the results in a table format
void printResults(const vector<Process>& processes) {
    cout << "PID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n";
    for (const auto& p : processes) {
        cout << p.pid << "\t" << p.arrivalTime << "\t\t" << p.burstTime << "\t\t"
             << p.completionTime << "\t\t" << p.waitingTime << "\t\t" << p.turnaroundTime << endl;
    }
}

// Function to calculate average waiting and turnaround times
void calculateAverages(const vector<Process>& processes) {
    int totalWaitingTime = 0, totalTurnaroundTime = 0;
    int n = processes.size();

    for (const auto& p : processes) {
        totalWaitingTime += p.waitingTime;
        totalTurnaroundTime += p.turnaroundTime;
    }

    double avgWaitingTime = (double)totalWaitingTime / n;
    double avgTurnaroundTime = (double)totalTurnaroundTime / n;

    cout << "\nAverage Waiting Time: " << avgWaitingTime << endl;
    cout << "Average Turnaround Time: " << avgTurnaroundTime << endl;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes;
    queue<Process> readyQueue;

    // Input details for each process
    for (int i = 0; i < n; ++i) {
        int arrival, burst;
        cout << "Enter arrival time for Process " << i + 1 << ": ";
        cin >> arrival;
        cout << "Enter burst time for Process " << i + 1 << ": ";
        cin >> burst;
        processes.push_back(Process(i + 1, arrival, burst));  // Process IDs start from 1
    }

    // Step 1: Sort processes by arrival time
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
    });

    // Step 2: Simulate the scheduling process using a queue
    int currentTime = 0;
    int idx = 0;  // Process index to track the next process to be added to the queue

    while (idx < n || !readyQueue.empty()) {
        // Add all processes that have arrived by the current time to the readyQueue
        while (idx < n && processes[idx].arrivalTime <= currentTime) {
            readyQueue.push(processes[idx]);
            idx++;
        }

        if (!readyQueue.empty()) {
            // Get the next process from the queue (FCFS: first-come, first-served)
            Process p = readyQueue.front();
            readyQueue.pop();

            // Set the completion time for the process
            p.completionTime = currentTime + p.burstTime;
            p.turnaroundTime = p.completionTime - p.arrivalTime;
            p.waitingTime = p.turnaroundTime - p.burstTime;

            // Update current time after processing this task
            currentTime = p.completionTime;

            // Store updated process back into the processes list (optional)
            processes[p.pid - 1] = p;
        } else {
            // If the queue is empty, jump to the arrival time of the next process
            currentTime = processes[idx].arrivalTime;
        }
    }

    // Step 3: Calculate times
    // calculateTimes(processes);

    // Step 4: Print the results
    printResults(processes);

    // Step 5: Calculate averages
    calculateAverages(processes);

    return 0;
}



/* *********************** Sample Input Output ***********************

Enter the number of processes: 3
Enter arrival time for Process 1: 0
Enter burst time for Process 1: 4
Enter arrival time for Process 2: 1
Enter burst time for Process 2: 3
Enter arrival time for Process 3: 2
Enter burst time for Process 3: 1

PID    Arrival Time   Burst Time   Completion Time   Waiting Time   Turnaround Time
1      0              4            4                 0              4
2      1              3            7                 3              6
3      2              1            8                 5              6

Average Waiting Time: 2.66667
Average Turnaround Time: 5.33333

*/ 