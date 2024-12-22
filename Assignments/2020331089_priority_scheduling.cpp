#include <iostream>
#include <chrono>
#include <unistd.h>
#include <algorithm>

using namespace std;

struct Process
{
	int pid;
	double bt;
	int priority;
};

bool comparison(Process a, Process b)
{
	return (a.priority > b.priority);
}

void findWaitingTime(Process proc[], int n, int wt[])
{
	wt[0] = 0;

	for (int i = 1; i < n; i++)
		wt[i] = proc[i - 1].bt + wt[i - 1];
}

void findTurnAroundTime(Process proc[], int n, int wt[], int tat[])
{

	for (int i = 0; i < n; i++)
		tat[i] = proc[i].bt + wt[i];
}

void findavgTime(Process proc[], int n)
{
	int wt[n], tat[n], total_wt = 0, total_tat = 0;

	findWaitingTime(proc, n, wt);

	findTurnAroundTime(proc, n, wt, tat);

	cout << "\nProcesses " << " Burst time " << " Waiting time " << " Turn around time\n";

	for (int i = 0; i < n; i++)
	{
		total_wt = total_wt + wt[i];
		total_tat = total_tat + tat[i];
		cout << "    " << proc[i].pid << "\t    " << proc[i].bt << "\t   " << wt[i] << "\t\t " << tat[i] << "\n";
	}

	cout << "\nAverage waiting time = " << (float)total_wt / (float)n;
	cout << "\nAverage turn around time = " << (float)total_tat / (float)n << "\n";
}

void priorityScheduling(Process proc[], int n)
{
	sort(proc, proc + n, comparison);

	cout << "Order in which processes gets executed \n";
	for (int i = 0; i < n; i++)
		cout << proc[i].pid << " ";

	findavgTime(proc, n);
}

void function_for_process(int n)
{
	for (int i = 1; i < n; i++)
	{
		int a = 1;
		a += 30;
	}
}

int main()
{
	auto start = chrono::high_resolution_clock::now();

	function_for_process(1500000000);

	auto end = chrono::high_resolution_clock::now();

	chrono::duration<double> duration = end - start;

	double p1 = duration.count();
	cout << "Burst time of process p1: " << duration.count() << " seconds\n";

	start = chrono::high_resolution_clock::now();

	function_for_process(1250000000);

	end = chrono::high_resolution_clock::now();

	chrono::duration<double> duration2 = end - start;

	double p2 = duration2.count();
	cout << "Burst time of process p2: " << duration2.count() << " seconds\n";

	start = chrono::high_resolution_clock::now();

	function_for_process(1750000000);

	end = chrono::high_resolution_clock::now();

	chrono::duration<double> duration3 = end - start;

	double p3 = duration3.count();
	cout << "Burst time of process p3: " << duration3.count() << " seconds\n";
	Process proc[] = {{1, p1, 2}, {2, p2, 0}, {3, p3, 1}};
	int n = sizeof proc / sizeof proc[0];
	priorityScheduling(proc, n);

	return 0;
}
