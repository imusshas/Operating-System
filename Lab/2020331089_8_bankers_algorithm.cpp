#include <iostream>
#include <vector>
using namespace std;

// Function to check if the system is in a safe state
bool isSafe(vector<vector<int>> &allocation, vector<vector<int>> &max, vector<vector<int>> &need, vector<int> &available, int P, int R)
{
  vector<bool> finish(P, false);
  vector<int> work = available;

  // Safety sequence
  vector<int> safeSequence;

  while (true)
  {
    bool found = false;
    for (int p = 0; p < P; ++p)
    {
      if (!finish[p])
      {
        bool canAllocate = true;
        for (int r = 0; r < R; ++r)
        {
          if (need[p][r] > work[r])
          {
            canAllocate = false;
            break;
          }
        }
        if (canAllocate)
        {
          for (int r = 0; r < R; ++r)
          {
            work[r] += allocation[p][r];
          }
          finish[p] = true;
          safeSequence.push_back(p);
          found = true;
        }
      }
    }
    if (!found)
      break;
  }

  // Check if all processes are finished
  for (int i = 0; i < P; ++i)
  {
    if (!finish[i])
      return false;
  }

  // Print the safe sequence
  cout << "System is in a safe state.\nSafe sequence is: ";
  for (int i = 0; i < safeSequence.size(); ++i)
  {
    cout << "P" << safeSequence[i];
    if (i != safeSequence.size() - 1)
      cout << " -> ";
  }
  cout << endl;

  return true;
}

// Function to request resources
bool requestResources(vector<vector<int>> &allocation, vector<vector<int>> &max, vector<vector<int>> &need, vector<int> &available, int P, int R, int process, vector<int> request)
{
  for (int r = 0; r < R; ++r)
  {
    if (request[r] > need[process][r])
    {
      cout << "Error: Process has exceeded its maximum claim." << endl;
      return false;
    }
  }

  for (int r = 0; r < R; ++r)
  {
    if (request[r] > available[r])
    {
      cout << "Error: Resources not available." << endl;
      return false;
    }
  }

  // Try to allocate the resources temporarily
  for (int r = 0; r < R; ++r)
  {
    available[r] -= request[r];
    allocation[process][r] += request[r];
    need[process][r] -= request[r];
  }

  // Check if the system is in a safe state
  if (isSafe(allocation, max, need, available, P, R))
  {
    cout << "The resources have been allocated to process P" << process << endl;
    return true;
  }
  else
  {
    // Roll back the allocation
    for (int r = 0; r < R; ++r)
    {
      available[r] += request[r];
      allocation[process][r] -= request[r];
      need[process][r] += request[r];
    }
    cout << "The system is not in a safe state. Request denied." << endl;
    return false;
  }
}

int main()
{
  int P = 5; // Number of processes
  int R = 3; // Number of resources

  vector<vector<int>> allocation = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}};
  vector<vector<int>> max = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}};
  vector<int> available = {3, 3, 2};

  vector<vector<int>> need(P, vector<int>(R));
  for (int i = 0; i < P; ++i)
  {
    for (int j = 0; j < R; ++j)
    {
      need[i][j] = max[i][j] - allocation[i][j];
    }
  }

  if (isSafe(allocation, max, need, available, P, R))
  {
    cout << "Initial state is safe." << endl;
  }
  else
  {
    cout << "Initial state is not safe." << endl;
  }

  // Process P1 requests resources {1, 0, 2}
  vector<int> request = {1, 0, 2};
  requestResources(allocation, max, need, available, P, R, 1, request);

  return 0;
}
