#include<bits/stdc++.h>

using namespace std;

// Minimum Size Subarray Sum - LC(209)
int minSubArrayLen(int target, vector<int>& nums) {
    int start = 0, end = 0, sum = 0, len = INT_MAX;
    while(end < nums.size()) {
        sum += nums[end];
        // now access the remaining elements
        while(sum >= target) {
            /*it's a valid ans, now we've to minimize
            the size of window*/
            len = min(len, end - start + 1);
            sum -= nums[start];
            ++start;
        }
        ++end;
    }
    return len != INT_MAX ? len : 0;
}

// Two sum - LC(1)
vector<int> twoSum(vector<int>& nums, int target) {
    int start = 0, end = nums.size() - 1; 
    vector<pair<int, int>> record;
    vector<int> ans;
    for(int i = 0; i < nums.size(); ++i)
        record.push_back({nums[i], i});
        
    sort(record.begin(), record.end()); 
    while(start < end) {
        if(record[start].first + record[end].first == target) {
            ans.push_back(record[start].second);
            ans.push_back(record[end].second);
            break; // Found the pair, no need to continue
        } 
        else if(record[start].first + record[end].first > target)
            --end;
        else
            ++start;
    }
    return ans;
}

// Binary Subarrays With Sum - LC(930)
int numSubarraysWithSum(vector<int>& nums, int goal) {
    int start=0, end=0, sum=0, prefixZero=0, count=0;
    while(end < nums.size()) {
        sum += nums[end];
        while(start < end && (sum > goal || nums[start] == 0)) {
            if(nums[start] == 1)
                prefixZero = 0;
            else
                prefixZero += 1;
            sum -= nums[start];
            ++start;
        }
        if(sum == goal)
            count += prefixZero + 1;
        ++end;
    }
    return count;
}

// Minimum Window Substring - LC(76)
string minWindow(string s, string t) {
    int len1 = s.length();
    int len2 = t.length();
    if (len2 > len1)
        return "";
    int start = 0;
    // valid case
    int ansIndex = -1;
    int ansLen = INT_MAX;
    unordered_map<char, int> sMap, tMap;
    
    // store frequencies of pattern string
    for (char ch : t)
        tMap[ch]++;
    
    // sliding window
    int count = 0;
    for (int i = 0; i < s.length(); ++i) {
        char ch = s[i];
        // update frequency in sMap
        sMap[ch]++;
        // valid case
        if (sMap[ch] <= tMap[ch])
            count++;
        if (count == len2) {
            // window found which has all the characters, now minimize
            while (sMap[s[start]] > tMap[s[start]] || tMap[s[start]] == 0) {
                if (sMap[s[start]] > tMap[s[start]])
                    sMap[s[start]]--;
                start++;
            }
            // find answer
            int windowLen = i - start + 1;
            if (windowLen < ansLen) {
                ansLen = windowLen;
                ansIndex = start;
            }
        }
    }
    if (ansIndex == -1)
        return "";
    else 
        return s.substr(ansIndex, ansLen);
}

int main() {

    vector<int> nums = {2, 3, 1, 2, 4, 3};
    int target = 7;
    int minLength = minSubArrayLen(target, nums);
    cout << "Minimum length of subarray with sum greater than or equal to " << target << " is: " << minLength << endl;

    vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    vector<int> result = twoSum(nums, target);
    if(result.size() == 2)
        cout << "Indices: " << result[0] << ", " << result[1] << endl;
    else
        cout << "No valid pair found." << endl;

    vector<int> test1 = {1, 0, 1, 0, 1};
    int goal1 = 2;
    cout << "Test Case 1: " << numSubarraysWithSum(test1, goal1) << " (Expected: 4)" << endl;
    vector<int> test2 = {0, 0, 0, 0, 0};
    int goal2 = 0;
    cout << "Test Case 2: " << numSubarraysWithSum(test2, goal2) << " (Expected: 15)" << endl;
    vector<int> test3 = {0, 1, 0, 1, 0};
    int goal3 = 2;
    cout << "Test Case 3: " << numSubarraysWithSum(test3, goal3) << " (Expected: 3)" << endl;

    string s = "ADOBECODEBANC";
    string t = "ABC";
    string result = minWindow(s, t);
    cout << "Minimum window substring is: " << result << endl;
     
    return 0;
}