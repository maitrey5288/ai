#include<iostream>
#include<bits/stdc++.h>
using namespace std;

bool isSafe(int row, int col, vector<string>&board, int n){
    int duprow=row;
    int dupcol=col;

    //north west
    while(row>=0 && col>=0){
        if(board[row][col]=='Q') return false;
        row--; col--;
    }

    //west
    row=duprow;
    col=dupcol;
    while(col>=0){
        if(board[row][col]=='Q') return false;
        col--;
    }

    //south west
    row=duprow;
    col=dupcol;
    while(row<n && col>=0){
        if(board[row][col]=='Q') return false;
        row++; col--;
    }

    return true;
}

void solve(int col, int n, vector<string> &board, vector<vector<string>> &ans){
    if(col==n){
        ans.push_back(board);
        return;
    }

    for(int row=0; row<n; row++){
        if(isSafe(row, col, board, n)){
            board[row][col]='Q';
            solve(col+1, n, board, ans);
            board[row][col]='.';
        }
    }
}

vector<vector<string>> solveNQueens(int n){

    vector<vector<string>>ans;
    vector<string>board(n);
    string s(n, '.');

    for(int i=0; i<n; i++){
        board[i]=s;
    }
    solve(0, n, board, ans);
    return ans;

}

int main(){
    int n;
    cout<<"Enter n=\n";
    cin>>n;
    vector<vector<string>>ans=solveNQueens(n);
    for(int i=0; i<ans.size(); i++){
        cout<<"Solution "<<i+1<<"\n";
        for(int j=0; j<ans[0].size(); j++){
            cout<<ans[i][j]<<endl;
        }
        cout<<endl;
    }
    return 0;
}