#include <bits\stdc++.h>
using namespace std;

int LRU(vector<int> &pages, int n, int frameSize)
{
    unordered_set<int> frames; // current frame
    vector<int> recentPages;   // To maintain the order of recently used pages

    int page_faults = 0;

    for (int i = 0; i < n; i++)
    {
        int currentPage = pages[i];

        if (frames.find(currentPage) == frames.end())
        {
            // If memory is full, remove the least recently used page
            if (frames.size() == frameSize)
            {
                int lruPage = recentPages[0];           // Least recently used page is at the front of the vector
                recentPages.erase(recentPages.begin()); // Remove it from the recent pages
                frames.erase(lruPage);                  // Remove it from the frames (memory)
            }

            frames.insert(currentPage);
            page_faults++;
        }
        else
        {
            recentPages.erase(remove(recentPages.begin(), recentPages.end(), currentPage), recentPages.end());
        }

        recentPages.push_back(currentPage);
    }

    return page_faults;
}

int main()
{
    int totalPages, frameSize;

    cout << "Enter the number of pages: ";
    cin >> totalPages;

    vector<int> pages(totalPages);
    cout << "Enter the page references (space-separated): ";
    for (int i = 0; i < totalPages; i++)
    {
        cin >> pages[i];
    }

    cout << "Enter the number of frames (capacity): ";
    cin >> frameSize;

    // Call the LRU page replacement function and print the result
    int page_faults = LRU(pages, totalPages, frameSize);
    cout << "Total number of page faults: " << page_faults << endl;
    cout << "Total number of page hits: " << totalPages - page_faults << endl;

    return 0;
}