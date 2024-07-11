#include <bits\stdc++.h>
using namespace std;

int main()
{

    int n; // for no of processes

    // Asking User the no of processes

    cout << "Enter The no of Processes.:" << endl;
    cin >> n;

    //  custom datatype
    vector<pair<string, pair<int, int>>> userInput;

    // Taking Input from User
    for (int i = 0; i < n; i++)
    {
        string str;
        int at, bt;

        cout << "Enter the process name, arrival time and burst time respectively: ";
        cin >> str >> at >> bt;
        cout << endl;

        userInput.push_back({str, {at, bt}});
    }

    // Sort on the basis of arrival time

    sort(userInput.begin(), userInput.end(), [](const auto &a, const auto &b)
         { return a.second.first < b.second.first; });

    // Calculate completion time

    vector<int> completionTime;
    completionTime.resize(userInput.size());
    int sum = 0;
    for (int i = 0; i < userInput.size(); i++)
    {
        sum += userInput[i].second.second;
        completionTime[i] = sum;
    }

    // Calculating Turn around time

    vector<int> tat;
    tat.resize(userInput.size());

    for (int i = 0; i < userInput.size(); i++)
    {
        tat[i] = completionTime[i] - userInput[i].second.first;
    }

    // Calculating Waiting Time

    vector<int> waitingTime;
    waitingTime.resize(userInput.size());

    for (int i = 0; i < userInput.size(); i++)
    {
        waitingTime[i] = tat[i] - userInput[i].second.second;
    }

    cout << endl;

    // Display process times
    cout << "Process ID\tArrival Time\tBurst Time" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << userInput[i].first << "\t\t" << userInput[i].second.first << "\t\t" << userInput[i].second.second << endl;
    }
    cout << endl;
    cout << "Completion Time\tTurnaround Time\tWaiting Time" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << completionTime[i] << "\t\t" << tat[i] << "\t\t" << waitingTime[i] << endl;
    }

    // print average for waiting time and completion time

    float ct_avg = accumulate(completionTime.begin(), completionTime.end(), 0.0 / completionTime.size()) / completionTime.size();

    double avg = 0;

    for (int i = 0; i < waitingTime.size(); i++)
    {
        avg += waitingTime[i];
    }

    avg /= waitingTime.size();

    cout << endl;
    cout << "The average of completion time: " << ct_avg << endl;
    cout << "The average of waiting time: " << avg;

    return 0;
}