#include<bits/stdc++.h>

using namespace std;

int DEFKIN(vector<pair<int, int> > &location, int row, int col) {
    vector<int> xDim, yDim;
    xDim.push_back(0);
    xDim.push_back(col + 1);
    for(int i=0; i<location.size(); ++i)
        xDim.push_back(location[i].first);
    sort(xDim.begin(), xDim.end());
    yDim.push_back(0);
    yDim.push_back(row + 1);
    for(int i=0; i<location.size(); ++i)
        yDim.push_back(location[i].second);
    sort(yDim.begin(), yDim.end());

    vector<int> xAns, yAns;
    for(int i=1; i<xDim.size(); ++i) {
        int diff = xDim[i] - xDim[i-1] - 1;
        xAns.push_back(diff);
    }
    for(int i=1; i<yDim.size(); ++i) {
        int diff = yDim[i] - yDim[i-1] - 1;
        yAns.push_back(diff);
    }

    int maxi = -1;
    for(int i=0; i<xAns.size(); ++i) {
        for(int j=0; j<yAns.size(); ++j) {
            int prod = xAns[i] * yAns[j];
            maxi = max(maxi, prod);
        }
    }
    
    return maxi;
}

// min cost of ropes - GFG
int minCost(int arr[], int n) {
    priority_queue<int, vector<int>, greater<int> > minHeap; 
    for(int i = 0; i < n; ++i)
        minHeap.push(arr[i]);
    int cost = 0;
    while(minHeap.size() > 1) {
        int rope1 = minHeap.top(); minHeap.pop();
        int rope2 = minHeap.top(); minHeap.pop();
        int sum = rope1 + rope2;
        cost += sum;
        minHeap.push(sum);
    }
    return cost;
}

// fractional knapsack - GFG
struct Item{
    int value;
    int weight;
};
double fractionalKnapsack(int W, Item arr[], int n) {
    // Create data related to weight/value ratio
    vector<double> valWtRatio;
    for (int i = 0; i < n; ++i) {
        double ratio = (arr[i].value * 1.0) / arr[i].weight;
        valWtRatio.push_back(ratio);
    }

    // Insert all data into max heap
    priority_queue<pair<double, pair<int, int>>> maxi;
    for (int i = 0; i < n; ++i)
        maxi.push({valWtRatio[i], {arr[i].value, arr[i].weight}});
        
    // Including data into knapsack
    double totalVal = 0;
    while (W != 0 && !maxi.empty()) {
        auto front = maxi.top();
        double ratio = front.first;
        int val = front.second.first;
        int wt = front.second.second;
        maxi.pop();
        if (W >= wt) {
            // Take the whole item
            totalVal += val;
            W -= wt;
        } else {
            // Take a fraction of the item
            totalVal += ratio * W;
            break;
        }
    }
    return totalVal;
}

// N meetings in one room
static bool comp(pair<int, int> a, pair<int, int> b) {
    return a.second < b.second;
}
int maxMeetings(int start[], int end[], int n)
{
    vector<pair<int, int> > time;
    for(int i=0; i<n; ++i)
        time.push_back({start[i], end[i]});
    sort(time.begin(), time.end(), comp);
    
    int count = 1;
    int prevStart = time[0].first;
    int prevEnd = time[0].second;
    for(int i=1; i<n; ++i) {
        int currStart = time[i].first;
        int currEnd = time[i].second;
        if(currStart > prevEnd) {
            count++;
            prevStart = currStart;
            prevEnd = currEnd;
        }
    }
    return count;
}

int main() {

    // int row, col, tower, trow, tcol;
    // cout << "enter [row], [col] or no. of towers : ";
    // cin >> row >> col >> tower;
    // vector<pair<int, int> > location;
    // for(int i=0; i<tower; ++i) {
    //     cout << "enter the coordinated of tower " << i+1 << " : ";
    //     cin >> trow >> tcol;
    //     location.push_back({trow, tcol});
    // }
    // cout << "the area with max unprotected blocks : " << DEFKIN(location, row, col) << endl;

    // int n;
    // cout << "enter [n] : ";
    // cin >> n;
    // int arr[n];
    // for(int i=0; i<n; ++i)
    //     cin >> arr[i];
    // cout << "min cost to connect all ropes : " << minCost(arr, n) << endl;

    // int n, W;
    // cout << "Enter the number of items: ";
    // cin >> n;
    // cout << "Enter the total weight capacity of the knapsack: ";
    // cin >> W;
    // Item arr[n];
    // cout << "Enter value and weight for each item:\n";
    // for (int i = 0; i < n; ++i) {
    //     cin >> arr[i].value >> arr[i].weight;
    // }
    // double maxValue = fractionalKnapsack(W, arr, n);
    // cout << "The maximum value in the knapsack is: " << maxValue << endl;

    // int start[] = {1, 3, 0, 5, 8, 5};
    // int end[] = {2, 4, 6, 7, 9, 9};
    // int n = sizeof(start) / sizeof(start[0]);
    // cout << "Maximum number of meetings that can be conducted: " << maxMeetings(start, end, n) << endl;

    return 0;
}