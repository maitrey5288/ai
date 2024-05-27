#include <bits/stdc++.h>
using namespace std;

bool isSafe(int row, int col, vector<string> board, int n) {
      // store copies of pos(row,col)
      int duprow = row;
      int dupcol = col;

      while (row >= 0 && col >= 0) { //check north west diagonal O(n)
        if (board[row][col] == 'Q')
          return false;
        row--;
        col--;
      }

      col = dupcol;
      row = duprow;
      while (col >= 0) { //check west O(n)
        if (board[row][col] == 'Q')
          return false;
        col--;
      }

      row = duprow;
      col = dupcol;
      while (row < n && col >= 0) { //check south west diagonal O(n)
        if (board[row][col] == 'Q')
          return false;
        row++;
        col--;
      }
      return true;
    }

void solve(int col, vector < string > & board, vector < vector < string >> & ans, int n) {
      
      if (col == n) { //base case- last column=n-1
        ans.push_back(board);
        return;
      }
      
      for (int row = 0; row < n; row++) { //iterate through every row (fill each row) O(n)
        if (isSafe(row, col, board, n)) { //check if position is safe
          board[row][col] = 'Q';
          solve(col + 1, board, ans, n); //recursively check for each column (fill each column)
          board[row][col] = '.'; //while coming back, remove queen
        }
      }

    }

vector<vector<string>> solveNQueens(int n) {
      vector<vector<string>> ans;
      vector<string> board(n);
      string s(n, '.');
      for (int i = 0; i < n; i++) {
        board[i] = s;
      }
      solve(0, board, ans, n);
      return ans;
    }

int main() {
  int n = 4; 
  vector <vector<string>> ans = solveNQueens(n);
  for (int i = 0; i < ans.size(); i++) {
    cout << "Arrangement " << i + 1 << "\n";
    for (int j = 0; j < ans[0].size(); j++) {
      cout << ans[i][j];
      cout << endl;
    }
    cout << endl;
  }
  return 0;
}
