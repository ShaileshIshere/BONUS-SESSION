#include<bits/stdc++.h>

using namespace std;

// letter tile possibilities - LC(1079)
int solve(vector<int> &freq) {
    int ans = 0;
    for(int i=0; i<26; ++i) {
        // check krlo ke ith index ka character freq m present hai ya nhi
        if(freq[i]) {
            // ek ans nikal giya
            ans++;
            // freq update krow
            freq[i]--;
            // recursion step
            int reccAns = solve(freq);
            ans += reccAns;
            // backtracking step
            freq[i]++;
        }
    }
    return ans;
}
int numTilePossibilities(string tiles) {
    vector<int> freq(26, 0);
    // count freq to characters
    for(auto ch:tiles) 
        freq[ch-'A']++;
    int ans = solve(freq);
    return ans;
}

// Letter Combinations of a Phone Number - LC(17)
void solve(string mapping[], string output, int index, vector<string> &ans, string &digits) {
    // base case
    if(index >= digits.length()) {
        /* output m string ban zugi, then store
        that string in ans array */
        if(output.length() > 0)
            ans.push_back(output);
        return;
    }
    string temp = mapping[digits[index] - '0'];
    for(auto ch:temp) {
        output.push_back(ch);
        // recursion
        solve(mapping, output, index+1, ans, digits);
        // backtracking
        output.pop_back();
    }
}
vector<string> letterCombinations(string digits) {
    string mapping[] = {"","", "abc", "def", "ghi", "jkl", "mno", "pqrs",
                        "tuv", "wxyz"};
    string output = "";
    int index = 0;
    vector<string> ans;
    solve(mapping, output, index, ans, digits);
    return ans;
} 

// remove invalid parentheses - LC(301)
void solve(string &str, unordered_set<string> &ans, int open, int close, int bal, int index, string &output) {
    // base case
    if(index >= str.length()) {
        // valid ans
        if(open == 0 && close == 0 && bal == 0)
            ans.insert(output);
        return;
    }
    // include/exclude
    if(str[index] != '(' && str[index] != ')') {
        // if the current char is an alphabet
        output.push_back(str[index]);
        solve(str, ans, open, close, bal, index+1, output);
        // backtrack
        output.pop_back();
    }
    else {
        // if the current char is a bracket
        // if it's open bracket
        if(str[index] == '(') {
            // either remove this one
            if(open > 0)
                solve(str, ans, open-1, close, bal, index+1, output);
            // or we did not remove this one
            output.push_back('(');
            solve(str, ans, open, close, bal+1, index+1, output);
            output.pop_back();
        }
        // if it's close bracket
        else if(str[index] == ')') {
            // either we have to remove this one
            if(close > 0)
                solve(str, ans, open, close-1, bal, index+1, output);
            // or we do not remove this one
            if(bal > 0) {
                output.push_back(')');
                solve(str, ans, open, close, bal-1, index+1, output);
                output.pop_back();
            }
        } 
    }
}
vector<string> removeInvalidParentheses(string s) {
    unordered_set<string> ans;
    int invalidOpen = 0, invalidClose = 0, index = 0, balance = 0;
    string output = "";
    for(auto ch : s) {
        if(ch == '(') 
            invalidOpen++;
        else if(ch == ')') {
            if(invalidOpen > 0)
                invalidOpen--;
            else 
                invalidClose++;
        }
    }
    solve(s, ans, invalidOpen, invalidClose, balance, index, output);
    return vector<string>(ans.begin(), ans.end());
}

// N-Queens - LC(51)
// Global variables to keep track of which rows and diagonals are already occupied
unordered_map<int, bool> rowCheck;
unordered_map<int, bool> upperLeftDiagonalCheck;
unordered_map<int, bool> bottomLeftDiagonalCheck;
// Function to store a valid solution into the 'ans' vector
void storeSolution(vector<vector<char>> &board, int n, vector<vector<string>> &ans) {
    vector<string> temp;
    for (int i = 0; i < n; i++) {
        string output = "";
        for (int j = 0; j < n; j++) {
            output.push_back(board[i][j]);
        }
        temp.push_back(output);
    }
    ans.push_back(temp);
}
// Function to check if it's safe to place a queen at a given position
bool isSafe(int row, int col, vector<vector<char>> &board, int n) {
    // Check if this row is already occupied
    if (rowCheck[row])
        return false;
    // Check if the upper left diagonal is already occupied
    if (upperLeftDiagonalCheck[n - 1 + col - row])
        return false;
    // Check if the bottom left diagonal is already occupied
    if (bottomLeftDiagonalCheck[row + col])
        return false;
    return true;
}
// Recursive function to solve the N-Queens problem
void solve(vector<vector<char>> &board, vector<vector<string>> &ans, int n, int col) {
    // Base case: If all columns are processed, a valid solution is found
    if (col >= n) {
        storeSolution(board, n, ans);
        return;
    }
    // Try placing the queen in each row of the current column
    for (int row = 0; row < n; row++) {
        if (isSafe(row, col, board, n)) {
            // Place the queen
            board[row][col] = 'Q';
            // Mark the row and diagonals as occupied
            rowCheck[row] = true;
            upperLeftDiagonalCheck[n - 1 + col - row] = true;
            bottomLeftDiagonalCheck[row + col] = true;
            // Recur for the next column
            solve(board, ans, n, col + 1);
            // Backtrack: Remove the queen and mark the row and diagonals as unoccupied
            board[row][col] = '.';
            rowCheck[row] = false;
            upperLeftDiagonalCheck[n - 1 + col - row] = false;
            bottomLeftDiagonalCheck[row + col] = false;
        }
    }
}
// Function to solve N-Queens problem for given N
vector<vector<string>> solveNQueens(int n) {
    vector<vector<string>> ans;
    vector<vector<char>> board(n, vector<char>(n, '.')); // Initialize the board with empty cells
    int col = 0; // Start solving from the first column
    solve(board, ans, n, col);
    return ans;
}

// sudoku solver - LC(37)
bool isSafe(int row, int col, vector<vector<char>>& board, char value) {
    int n = board.size();
    for(int i=0; i<n; i++) {
        //row check
        if(board[row][i] == value)
            return false;
        
        //col check
        if(board[i][col] == value) 
            return false;

        //3*3 box check
        if(board[3*(row/3)+(i/3)][3*(col/3)+(i%3)] == value) 
            return false;
    }
    return true;
}
bool solve(vector<vector<char>>& board) {
    int n = board.size();
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            //check for empty cell
            if(board[i][j] == '.') {
                //try to fill with values ranging from 1 to 9
                for(char val = '1'; val<='9'; val++) {
                    //check for safety
                    if(isSafe(i,j, board, val)) {
                        //insert
                        board[i][j] = val;
                        //recursion sambal lega
                        bool remainingBoardSolution = solve(board);
                        if(remainingBoardSolution == true) {
                            return true;
                        }
                        else {
                            //backtrack
                            board[i][j] = '.';
                        }
                    }
                }
                //if 1 se 9 tak koi bhi value se solution
                //nahi nikla ,current cell pr, 
                //that means piche kahin pr galti h , 
                //go back by returning false
                return false;
            }
        }
    }
    //all cells filled 
    return true;
}
void solveSudoku(vector<vector<char>>& board) {
    solve(board);
}

int main() {

    // string tiles;
    // cout << "Enter the tiles: ";
    // cin >> tiles;
    // int result = numTilePossibilities(tiles);
    // cout << "Number of tile possibilities: " << result << endl;

    // string digits;
    // cout << "Enter a string of digits (2-9): ";
    // cin >> digits;
    // vector<string> result = letterCombinations(digits);
    // if (result.empty()) {
    //     cout << "No letter combinations possible for the input." << endl;
    // } else {
    //     cout << "Letter combinations for " << digits << " are:" << endl;
    //     for (string s : result) {
    //         cout << s << " ";
    //     }
    //     cout << endl;
    // }

    // string input;
    // cout << "Enter a string: ";
    // cin >> input;
    // vector<string> result = removeInvalidParentheses(input);
    // cout << "Valid expressions after removing invalid parentheses:" << endl;
    // for (const string& s : result)
    //     cout << s << endl;

    int n;
    cout << "Enter the number of queens (N): ";
    cin >> n;
    vector<vector<string>> solutions = solveNQueens(n);
    // Display the solutions
    int solutionCount = solutions.size();
    if (solutionCount == 0) 
        cout << "No solutions found for N = " << n << endl;
    else {
        cout << "Found " << solutionCount << " solutions for N = " << n << ":" << endl;
        for (int i = 0; i < solutionCount; i++) {
            cout << "Solution " << i + 1 << ":" << endl;
            for (const string &row : solutions[i])
                cout << row << endl;
            cout << endl;
        }
    }
     
    return 0;
}