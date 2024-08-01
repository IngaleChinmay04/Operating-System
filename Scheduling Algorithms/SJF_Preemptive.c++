#include <bits/stdc++.h>
using namespace std;

typedef struct
{
    string processId;
    int at;
    int bt;
    int original_bt;
    int ct = -2;
    int tat = -2;
    int wt = -2;

} Process;

int main()
{

    int n; // for no of processes

    // Asking User the no of processes

    cout << "Enter The no of Processes.:" << endl;
    cin >> n;

    vector<Process> processes(n);

    // Taking input from user.

    for (int i = 0; i < processes.size(); i++)
    {
        cout << "Enter Process Id, Arrival time and Burst time and priority respectively: ";
        cin >> processes[i].processId >> processes[i].at >> processes[i].bt;
        processes[i].original_bt = processes[i].bt;
        cout << endl;
    }
    // finding minimum index of arrival time.
    int j = -1;
    int a = INT_MAX;
    for (int i = 0; i < processes.size(); i++)
    {
        if (processes[i].at < a)
        {
            j = i;
            a = processes[i].at;
        }
    }
    // Incrementing curr Time by 1 and deducting burst time.
    int currTime = 0;
    currTime += 1;
    processes[j].bt -= 1;

    if (processes[j].bt == 0)
    {
        processes[j].ct = currTime;
    }

    int p = n;

    int k = INT_MAX;
    int b = -1;

    // Loop to complete all processes and look at each second which process has arrived and reduce burst time.

    while (p > 0)
    {
        k = INT_MAX;
        for (int i = 0; i < processes.size(); i++)
        {
            if (processes[i].at <= currTime && processes[i].ct == -2)
            {
                if (processes[i].bt < k)
                {
                    b = i;
                    k = processes[i].bt;
                }
            }
        }

        if (b != -1)
        {
            currTime += 1;
            processes[b].bt -= 1;
            if (processes[b].bt == 0)
            {
                processes[b].ct = currTime;
                p--;
            }
        }
        else
        {
            currTime++;
        }
    }
    cout << endl;

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