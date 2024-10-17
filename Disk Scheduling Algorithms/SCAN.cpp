#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int performScanScheduling(vector<int> &reqList, int initialHead, int maxCylinders, string moveDirection)
{
    int totalSeekTime = 0;
    vector<int> leftRequests, rightRequests;

    // Add disk boundaries to the request list based on the direction
    if (moveDirection == "left")
        leftRequests.push_back(0); // Start boundary of the disk
    else if (moveDirection == "right")
        rightRequests.push_back(maxCylinders - 1); // End boundary of the disk

    for (int i = 0; i < reqList.size(); i++)
    {
        if (reqList[i] < initialHead)
            leftRequests.push_back(reqList[i]);
        else if (reqList[i] > initialHead)
            rightRequests.push_back(reqList[i]);
    }

    // Sort the requests in ascending order
    sort(leftRequests.begin(), leftRequests.end());
    sort(rightRequests.begin(), rightRequests.end());

    // Print the sequence of serviced requests
    cout << "Request service sequence: " << initialHead;

    // Move the head in the specified direction (left or right)
    if (moveDirection == "left")
    {
        // Service requests to the left first (in decreasing order), then to the right
        for (int i = leftRequests.size() - 1; i >= 0; i--)
        {
            totalSeekTime += abs(initialHead - leftRequests[i]);
            initialHead = leftRequests[i];
            cout << " -> " << initialHead;
        }
        for (int i = 0; i < rightRequests.size(); i++)
        {
            totalSeekTime += abs(initialHead - rightRequests[i]);
            initialHead = rightRequests[i];
            cout << " -> " << initialHead;
        }
    }
    else if (moveDirection == "right")
    {
        // Service requests to the right first (in increasing order), then to the left
        for (int i = 0; i < rightRequests.size(); i++)
        {
            totalSeekTime += abs(initialHead - rightRequests[i]);
            initialHead = rightRequests[i];
            cout << " -> " << initialHead;
        }
        for (int i = leftRequests.size() - 1; i >= 0; i--)
        {
            totalSeekTime += abs(initialHead - leftRequests[i]);
            initialHead = leftRequests[i];
            cout << " -> " << initialHead;
        }
    }

    cout << endl;
    return totalSeekTime;
}

int main()
{
    int requestCount, initialHead, totalCylinders;
    string headDirection;

    cout << "Enter the number of disk requests: ";
    cin >> requestCount;

    vector<int> diskRequests(requestCount);

    cout << "Enter the disk requests (space-separated): ";
    for (int i = 0; i < requestCount; i++)
    {
        cin >> diskRequests[i];
    }

    cout << "Enter the initial head position: ";
    cin >> initialHead;

    cout << "Enter the total disk size: ";
    cin >> totalCylinders;

    cout << "Enter the head movement direction (left/right): ";
    cin >> headDirection;

    int totalSeekTime = performScanScheduling(diskRequests, initialHead, totalCylinders, headDirection);

    cout << "Total Seek Time: " << totalSeekTime << endl;

    return 0;
}
