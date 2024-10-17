#include <bits\stdc++.h>
using namespace std;

void pageFaultsAndHits(vector<int> &pages, int n, int frameSize)
{

    unordered_set<int> s; // to know track of current pages.
    queue<int> indexes;   // to implement FIFO

    int page_faults = 0;
    int page_hits = 0;

    for (int i = 0; i < n; i++)
    {

        if (s.find(pages[i]) != s.end())
        {
            page_hits++;
        }
        else
        {
            if (s.size() < frameSize)
            {
                s.insert(pages[i]);
                indexes.push(pages[i]);

                page_faults++;
            }
            else
            {
                int first_page = indexes.front();
                indexes.pop();
                s.erase(first_page);
                s.insert(pages[i]);
                indexes.push(pages[i]);
                page_faults++;
            }
        }
    }

    cout << "Total page faults: " << page_faults << endl;
    cout << "Total page hits: " << page_hits << endl;
}

int main()
{
    int n, frameSize;

    cout << "Enter the number of pages: ";
    cin >> n;

    vector<int> pages(n);

    cout << "Enter the page references: ";
    for (int i = 0; i < n; i++)
    {
        cin >> pages[i];
    }

    cout << "Enter the no of frame size: ";
    cin >> frameSize;

    pageFaultsAndHits(pages, n, frameSize);

    return 0;
}