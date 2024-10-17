#include <bits\stdc++.h>
using namespace std;

int cLookDiskScheduling(vector<int> &requests, int head)
{
    int totalSeekTime = 0;
    vector<int> left, right;

    for (int i = 0; i < requests.size(); i++)
    {
        if (requests[i] < head)
            left.push_back(requests[i]);
        else
            right.push_back(requests[i]);
    }

    // Sort the requests in ascending order
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    // Print the service sequence starting from the head
    cout << "Service order: " << head;

    // First service the requests on the right of the head
    for (int i = 0; i < right.size(); i++)
    {
        totalSeekTime += abs(head - right[i]);
        head = right[i];
        cout << " -> " << head;
    }

    // Jump to the leftmost request if there are requests on the left
    if (!left.empty())
    {
        totalSeekTime += abs(head - left[0]);
        head = left[0];
        cout << " -> " << head;

        // Service remaining requests on the left side
        for (int i = 1; i < left.size(); i++)
        {
            totalSeekTime += abs(head - left[i]);
            head = left[i];
            cout << " -> " << head;
        }
    }

    cout << endl;
    return totalSeekTime;
}

int main()
{
    int numRequests, head;

    cout << "Enter the number of disk requests: ";
    cin >> numRequests;

    vector<int> requests(numRequests);

    cout << "Enter the disk requests: ";
    for (int i = 0; i < numRequests; i++)
    {
        cin >> requests[i];
    }

    cout << "Enter the initial head position: ";
    cin >> head;

    int totalSeekTime = cLookDiskScheduling(requests, head);

    cout << "Total Seek Time: " << totalSeekTime << endl;

    return 0;
}
