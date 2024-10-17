#include <bits\stdc++.h>
using namespace std;

bool search(int key, vector<int> &frames)
{
    for (int i = 0; i < frames.size(); i++)
    {
        if (frames[i] == key)
        {
            return true;
        }
    }
    return false;
}

int predict(vector<int> &pages, vector<int> &frames, int totalPages, int currentIndex)
{
    int res = -1, farthest = currentIndex; // res for index of page in frame
    for (int i = 0; i < frames.size(); i++)
    {
        int j;
        for (j = currentIndex; j < totalPages; j++)
        {
            if (frames[i] == pages[j])
            {
                if (j > farthest)
                {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        // If a page is never used in the future, return its index
        if (j == totalPages)
        {
            return i;
        }
    }
    return (res == -1) ? 0 : res;
}

void optimalPageReplacement(vector<int> &pages, int totalPages, int frameSize)
{
    vector<int> frames;
    int page_hits = 0;

    for (int i = 0; i < totalPages; i++)
    {
        if (search(pages[i], frames))
        {
            page_hits++;
            continue;
        }
        if (frames.size() < frameSize)
        {
            frames.push_back(pages[i]);
        }
        else
        {
            int j = predict(pages, frames, totalPages, i + 1);
            frames[j] = pages[i];
        }
    }
    cout << "Number of hits: " << page_hits << endl;
    cout << "Number of misses: " << totalPages - page_hits << endl;
}

int main()
{
    int totalPages, frameSize;

    cout << "Enter the number of pages: ";
    cin >> totalPages;

    vector<int> pages(totalPages);
    cout << "Enter the pages (space-separated): ";
    for (int i = 0; i < totalPages; i++)
    {
        cin >> pages[i];
    }

    cout << "Enter the number of frames: ";
    cin >> frameSize;

    optimalPageReplacement(pages, totalPages, frameSize);

    return 0;
}