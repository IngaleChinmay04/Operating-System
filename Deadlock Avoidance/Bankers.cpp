#include <bits/stdc++.h>
using namespace std;

bool isSafe(vector<vector<int>> &max, vector<vector<int>> &alloc, vector<int> &avail, int process, int numResources)
{
    vector<int> need(numResources);
    for (int i = 0; i < numResources; i++)
    {
        need[i] = max[process][i] - alloc[process][i];
    }
    for (int i = 0; i < numResources; i++)
    {
        if (need[i] > avail[i])
        {
            return false;
        }
    }
    return true;
}

bool bankerAlgorithm(vector<vector<int>> &max, vector<vector<int>> &alloc, vector<int> &avail, int numProcesses, int numResources)
{
    vector<bool> finish(numProcesses, false); // To track completed processes
    vector<int> safeSequence;                 // To store the safe sequence
    int numFinished = 0;                      // Number of processes finished

    while (numFinished < numProcesses)
    {
        bool found = false;
        for (int i = 0; i < numProcesses; i++)
        {
            if (!finish[i] && isSafe(max, alloc, avail, i, numResources))
            {
                for (int j = 0; j < numResources; j++)
                {
                    avail[j] += alloc[i][j];
                }
                // Add the process to the safe sequence
                safeSequence.push_back(i);
                finish[i] = true; // Mark process as finished
                numFinished++;
                found = true;
            }
        }

        // If no process can be allocated, system is in an unsafe state
        if (!found)
        {
            return false;
        }
    }

    // Print the safe sequence
    cout << "Safe Sequence: ";
    for (int i = 0; i < numProcesses; i++)
    {
        cout << "P" << safeSequence[i];
        if (i < safeSequence.size() - 1)
        {
            cout << " -> ";
        }
    }
    cout << endl;
    return true;
}

int main()
{
    int numProcesses;
    int numResources;

    cout << "Enter the number of processes and number of resources separated by spaces: " << endl;
    cin >> numProcesses >> numResources;

    vector<vector<int>> max(numProcesses, vector<int>(numResources));
    vector<vector<int>> alloc(numProcesses, vector<int>(numResources));
    vector<int> avail(numResources);

    cout << "Enter the maximum resources for each process: " << endl;
    for (int i = 0; i < numProcesses; i++)
    {
        for (int j = 0; j < numResources; j++)
        {
            cin >> max[i][j];
        }
    }

    cout << "Enter the allocated resources for each process: " << endl;
    for (int i = 0; i < numProcesses; i++)
    {
        for (int j = 0; j < numResources; j++)
        {
            cin >> alloc[i][j];
        }
    }

    cout << "Enter the available resources: " << endl;
    for (int i = 0; i < numResources; i++)
    {
        cin >> avail[i];
    }

    // Check if the system is in a safe state
    if (bankerAlgorithm(max, alloc, avail, numProcesses, numResources))
    {
        cout << "System is in a safe state." << endl;
    }
    else
    {
        cout << "System is in an unsafe state." << endl;
    }

    return 0;
}
