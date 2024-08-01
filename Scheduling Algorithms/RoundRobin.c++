#include <bits/stdc++.h>
using namespace std;

typedef struct
{
    string processId;
    int at;
    int bt;
    int ct = -1;
    int tat = -1;
    int wt = -1;
    int original_bt;

} Process;

int main()
{
    int n;
    int timeQuantum;

    cout << "Enter the number of processes: ";
    cin >> n;
    cout << endl;
    vector<Process> processes(n);

    // User input for time quantum
    cout << "Enter your time quantum: ";
    cin >> timeQuantum;
    cout << endl;

    // User input
    for (int i = 0; i < processes.size(); i++)
    {
        cout << "Enter Process Id, Arrival time and Burst time and priority respectively: ";
        cin >> processes[i].processId >> processes[i].at >> processes[i].bt;
        processes[i].original_bt = processes[i].bt;
        cout << endl;
    }

    // Sort on the basis of arrival time
    sort(processes.begin(), processes.end(), [](const auto &a, const auto &b)
         { return a.at < b.at; });

    int curTime = 0;
    int completedProcess = 0;
    queue<int> readyQueue;
    set<int> inQueue; // Track indices of processes in the queue

    // Initialize the ready queue with processes that have arrived at the initial time
    for (int i = 0; i < n; i++)
    {
        if (processes[i].at <= curTime)
        {
            readyQueue.push(i);
            inQueue.insert(i);
        }
    }

    while (completedProcess < n)
    {
        if (readyQueue.empty())
        {
            curTime++;
            // Add processes to the ready queue that have arrived by current time
            for (int i = 0; i < n; i++)
            {
                if (processes[i].at == curTime && inQueue.find(i) == inQueue.end())
                {
                    readyQueue.push(i);
                    inQueue.insert(i);
                }
            }
        }
        else
        {
            int idx = readyQueue.front();
            readyQueue.pop();
            inQueue.erase(idx);
            Process &curProcess = processes[idx];

            if (curProcess.bt <= timeQuantum)
            {
                curTime += curProcess.bt;
                curProcess.bt = 0;
                curProcess.ct = curTime;
                completedProcess++;
            }
            else
            {
                curProcess.bt -= timeQuantum;
                curTime += timeQuantum;
            }

            // Add newly arrived processes to the ready queue
            for (int i = 0; i < n; i++)
            {
                if (processes[i].at > curProcess.at && processes[i].at <= curTime && inQueue.find(i) == inQueue.end() && processes[i].bt > 0)
                {
                    readyQueue.push(i);
                    inQueue.insert(i);
                }
            }

            // If the process is not yet completed, re-add it to the ready queue
            if (curProcess.bt > 0)
            {
                readyQueue.push(idx);
                inQueue.insert(idx);
            }
        }
    }

    // Calculating Turn around time

    for (int i = 0; i < n; i++)
    {
        processes[i].tat = processes[i].ct - processes[i].at;
    }

    // Calculating Waiting Time

    for (int i = 0; i < n; i++)
    {
        processes[i].wt = processes[i].tat - processes[i].original_bt;
    }

    // Display process times
    cout << "Process ID\tArrival Time\tBurst Time" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << processes[i].processId << "\t\t" << processes[i].at << "\t\t" << processes[i].bt << endl;
    }
    cout << endl;
    cout << "Completion Time\tTurnaround Time\tWaiting Time" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << processes[i].ct << "\t\t" << processes[i].tat << "\t\t" << processes[i].wt << endl;
    }

    // print average for waiting time and completion time

    double ct_avg = 0;
    double avg = 0;

    for (int i = 0; i < n; i++)
    {
        avg += processes[i].wt;
    }

    avg /= n;

    for (int i = 0; i < n; i++)
    {
        ct_avg += processes[i].ct;
    }

    ct_avg /= n;

    cout << endl;
    cout << "The average of completion time: " << ct_avg << endl;
    cout << "The average of waiting time: " << avg;

    return 0;
}