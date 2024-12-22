#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent a process
struct Process {
    int pid;           // Process ID
    int arrivalTime;   // Arrival time
    int burstTime;     // Burst time (CPU time)
    int completionTime;
    int waitingTime;
    int turnaroundTime;
};

// Function to calculate the waiting time and turnaround time
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

    vector<Process> processes(n);

    // Input details for each process
    for (int i = 0; i < n; ++i) {
        processes[i].pid = i + 1;  // Process IDs are assigned from 1
        cout << "Enter arrival time for Process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime;
        cout << "Enter burst time for Process " << i + 1 << ": ";
        cin >> processes[i].burstTime;
    }

    // Step 1: Sort processes by arrival time first, then by burst time
    sort(processes.begin() , processes.end(), [](const Process& a, const Process& b) {
        if (a.arrivalTime == b.arrivalTime) {
            return a.burstTime < b.burstTime;  // If arrival times are the same, sort by burst time
        }
        return a.arrivalTime < b.arrivalTime;
    });

    // Step 2: Sort processes by burst time (this is the core of SJF)
    sort(processes.begin() + 1, processes.end(), [](const Process& a, const Process& b) {
        return a.burstTime < b.burstTime;  // Sort by burst time
    });

    // Step 3: Calculate times
    calculateTimes(processes);

    // Step 4: Print the results
    printResults(processes);

    // Step 5: Calculate averages
    calculateAverages(processes);

    return 0;
}



/* ******************* Sample I/O ****************

Enter the number of processes: 4
Enter arrival time for Process 1: 1
Enter burst time for Process 1: 6
Enter arrival time for Process 2: 0
Enter burst time for Process 2: 4
Enter arrival time for Process 3: 2
Enter burst time for Process 3: 2
Enter arrival time for Process 4: 3
Enter burst time for Process 4: 5


PID    Arrival Time   Burst Time   Completion Time   Waiting Time   Turnaround Time
2      0              4            5                 0              4
3      2              2            7                 2              4
4      3              5            12                3              8
1      1              6            18                12             16

Average Waiting Time: 4.75
Average Turnaround Time: 8.0

*/ 