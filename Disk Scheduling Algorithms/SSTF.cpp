#include <bits\stdc++.h>
using namespace std;

int calculateSSTF(vector<int> &requests, int head)
{
    int n = requests.size();
    vector<bool> visited(n, false); // To mark serviced requests
    int totalSeekTime = 0;

    // Print initial head position
    cout << "Sequence of request service: " << head;

    for (int i = 0; i < n; i++)
    {
        // Find the closest request to the current head position
        int minDistance = INT_MAX;
        int closestRequestIndex = -1;

        for (int j = 0; j < n; j++)
        {
            if (!visited[j])
            {
                int distance = abs(requests[j] - head);
                if (distance < minDistance)
                {
                    minDistance = distance;
                    closestRequestIndex = j;
                }
            }
        }

        // Move the head to the closest request
        totalSeekTime += minDistance;
        head = requests[closestRequestIndex];
        visited[closestRequestIndex] = true; // Mark this request as serviced

        // Print the request being serviced
        cout << " -> " << head;
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

    cout << "Enter the disk requests (space-separated): ";
    for (int i = 0; i < numRequests; i++)
    {
        cin >> requests[i];
    }

    cout << "Enter the initial head position: ";
    cin >> head;

    int totalSeekTime = calculateSSTF(requests, head);
    cout << "Total Seek Time: " << totalSeekTime << endl;

    return 0;
}
