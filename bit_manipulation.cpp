#include<bits/stdc++.h>

using namespace std;

void getBit(int n, int i) {
    int op1 = 1 << i;
    int op2 = op1 & n;
    if(op2) 
        cout << i << "th bit is 1" << endl;
    else 
        cout << i << "th bit is 0" << endl;
}

void setBit(int n, int i) {
    int op1 = 1 << i;
    int op2 = op1 | n;
    if(op2) 
        cout << i << "th bit is 1" << endl;
    else 
        cout << i << "th bit is 0" << endl;
}

void clearBit(int &n, int i) {
    int op1 = ~(1 << i);
    int op2 = op1 & n;
    cout << "after clearing bit : " << op2 << endl;
}

void updateBit(int n, int i, int target) {
    // step 1: clear ith bit
    clearBit(n, i);

    // step 2: create mask
    int mask = target << i;

    // step 3: update n by performing (OR)
    n |= mask;
    cout << "after updating bit by " << target << " is : " << n << endl;
}

void clearLastIthBits(int n, int i) {
    int mask = (-1 << i);
    int ans = n & mask;
    cout << "after clearing the last " << i << " bits : " << ans << endl;
}

bool isPowerofTwo(long long n){
    // 1st way (faster)
    // Handle edge case where n is 0
    if (n <= 0) return false;
    // A power of two has only one bit set, so we can use a bitwise AND
    // with n-1 to check if it's a power of two.
    return (n & (n - 1)) == 0;
    
    // 2nd way
    int count=0;
    while(n != 0) {
        long long lastBit = n & 1;
        if(lastBit) {
            count++;
        }
        n = n >> 1;
    }
    if(count == 1)
        return true;
    else
        return false;
}

int countSetBits(int n) {
    int count = 0;
    while(n != 0) {
        count++;
        n = n & (n-1);
    }
    return count;
}

void clearBitsInRange(int n, int i, int j) {
    int mask1 = (-1 << (i+1));
    int mask2 = ~(-1 << j);
    int finalMask = mask1 | mask2;
    n = n & finalMask;
    cout << "updated no : " << n << endl;
}

int main() {

    int n, i, target, start, end;
    cin >> n;
    cin >> i;
    getBit(n, i);
    setBit(n, i);
    clearBit(n, i);
    cin >> target;
    updateBit(n, i, target);
    clearLastIthBits(n, i);
    cout << "no. of set bits in " << n << " : " << countSetBits(n) << endl;
    cin >> start >> end;
    clearBitsInRange(n, start, end);

    return 0;
}