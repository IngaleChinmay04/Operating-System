#include <bits\stdc++.h>
using namespace std;

typedef struct
{
    string processId;
    int at;
    int bt;
    int ct = -2;
    int tat = -2;
    int wt = -2;
    int priority;
} Process;

int main()
{

    int n;
    cout << "Enter The no of Processes.:" << endl;
    cin >> n;

    vector<Process> processes(n);

    for (int i = 0; i < processes.size(); i++)
    {
        cout << "Enter Process Id, Arrival time and Burst time and priority respectively: ";
        cin >> processes[i].processId >> processes[i].at >> processes[i].bt >> processes[i].priority;
        cout << endl;
    }

    sort(processes.begin(), processes.end(), [](const auto &a, const auto &b)
         { return a.at < b.at; });

    int currTime = 0;
    currTime = processes[0].at;

    currTime += processes[0].bt;
    processes[0].ct = currTime;
    processes[0].priority = -1;

    int p = n - 1;

    while (p > 0)
    {
        int currentProcessIndex = -1;
        int currentPriority = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            if (processes[i].at <= currTime && processes[i].priority != -1 && processes[i].ct == -2)
            {
                if (processes[i].priority < currentPriority)
                {
                    currentProcessIndex = i;
                    currentPriority = processes[i].priority;
                }
            }
        }
        if (currentProcessIndex != -1)
        {

            currTime += processes[currentProcessIndex].bt;
            processes[currentProcessIndex].ct = currTime;
            processes[currentProcessIndex].priority = -1;
            p--;
        }
        else
        {
            currTime++;
        }
    }

    for (int i = 0; i < n; i++)
    {
        processes[i].tat = processes[i].ct - processes[i].at;
    }

    for (int i = 0; i < n; i++)
    {
        processes[i].wt = processes[i].tat - processes[i].bt;
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
