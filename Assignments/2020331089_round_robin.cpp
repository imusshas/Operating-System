#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <numeric> // Add this line for accumulate function
#include <ctime>

using namespace std;

struct Process
{
    int pid;
    int arrival_time;
    double burst_time; // Using double to allow for fractional burst times
    int priority;
};

// Function to simulate a CPU-bound process
double cpuBoundProcess()
{
    clock_t start = clock();
    // Simulate CPU-bound computation
    for (int i = 0; i < 100000000; ++i)
    {
    }
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

// Function to simulate an I/O-bound process
double ioBoundProcess()
{
    clock_t start = clock();
    // Simulate I/O-bound operation
    for (int i = 0; i < 1000000; ++i)
    {
    }
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

// Function to simulate a process with high priority
double highPriorityProcess()
{
    clock_t start = clock();
    // Simulate process with high priority
    for (int i = 0; i < 50000000; ++i)
    {
    }
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

// Function to simulate a process with low priority
double lowPriorityProcess()
{
    clock_t start = clock();
    // Simulate process with low priority
    for (int i = 0; i < 20000000; ++i)
    {
    }
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

// Round Robin Scheduling Algorithm
pair<double, double> roundRobin(vector<Process> &processes, int quantum)
{
    int n = processes.size();
    queue<int> ready_queue;
    double total_time = 0;
    vector<double> remaining_time(n);
    vector<double> waiting_time(n, 0);
    vector<double> turnaround_time(n, 0);
    for (int i = 0; i < n; ++i)
        remaining_time[i] = processes[i].burst_time;

    cout << "Time Quantum: " << quantum << "\n";
    cout << "Round Robin Scheduling:" << "\n";

    while (true)
    {
        bool all_finished = true;
        for (int i = 0; i < n; ++i)
        {
            if (remaining_time[i] > 0)
            {
                all_finished = false;
                if (remaining_time[i] > quantum)
                {
                    cout << "Time: " << total_time << ", Process " << processes[i].pid << " in ready queue" << "\n";
                    total_time += quantum;
                    remaining_time[i] -= quantum;
                    cout << "Time: " << total_time << ", Process " << processes[i].pid << " in running queue" << "\n";
                }
                else
                {
                    cout << "Time: " << total_time << ", Process " << processes[i].pid << " in ready queue" << "\n";
                    total_time += remaining_time[i];
                    waiting_time[i] = total_time - processes[i].burst_time;
                    remaining_time[i] = 0;
                    cout << "Time: " << total_time << ", Process " << processes[i].pid << " completes execution" << "\n";
                }
            }
        }
        if (all_finished)
            break;
    }

    for (int i = 0; i < n; ++i)
        turnaround_time[i] = processes[i].burst_time + waiting_time[i];

    double avg_waiting_time = accumulate(waiting_time.begin(), waiting_time.end(), 0.0) / n;
    double avg_turnaround_time = accumulate(turnaround_time.begin(), turnaround_time.end(), 0.0) / n;

    return {avg_waiting_time, avg_turnaround_time};
}

// Priority Scheduling Algorithm
pair<double, double> priorityScheduling(vector<Process> &processes)
{
    int n = processes.size();
    double total_time = 0;
    vector<double> waiting_time(n, 0);
    vector<double> turnaround_time(n, 0);

    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b)
         { return a.priority < b.priority; });

    for (int i = 0; i < n; ++i)
    {
        total_time += processes[i].burst_time;
        waiting_time[i] = total_time - processes[i].burst_time;
        turnaround_time[i] = total_time;
    }

    double avg_waiting_time = accumulate(waiting_time.begin(), waiting_time.end(), 0.0) / n;
    double avg_turnaround_time = accumulate(turnaround_time.begin(), turnaround_time.end(), 0.0) / n;

    return {avg_waiting_time, avg_turnaround_time};
}
int main()
{
    // Initialize processes
    vector<Process> processes;
    processes.push_back({1, 0, cpuBoundProcess(), 3});
    processes.push_back({2, 0, ioBoundProcess(), 1});
    processes.push_back({3, 0, highPriorityProcess(), 2});
    processes.push_back({4, 0, lowPriorityProcess(), 4});

    int quantum = 2; // Quantum for Round Robin

    // Print burst times of the processes
    cout << "Burst times of the processes:" << "\n";
    for (const auto &process : processes)
    {
        cout << "Process " << process.pid << ": " << process.burst_time << " seconds" << "\n";
    }

    // Run Round Robin Scheduling
    cout << "\nRound Robin Scheduling:" << "\n";
    pair<double, double> rr_results = roundRobin(processes, quantum);
    cout << "Average Waiting Time: " << rr_results.first << " seconds" << "\n";
    cout << "Average Turnaround Time: " << rr_results.second << " seconds" << "\n";

    // Run Priority Scheduling
    cout << "\nPriority Scheduling:" << endl;
    pair<double, double> priority_results = priorityScheduling(processes);
    cout << "Average Waiting Time: " << priority_results.first << " seconds" << "\n";
    cout << "Average Turnaround Time: " << priority_results.second << " seconds" << "\n";

    return 0;
}
