#include<iostream>
#include<vector>
using namespace std;
vector<int>board={0,2,2,2,2,2,2,2,2,2};

void displayBoard(){
    cout<<endl;

    for(int i=1; i<=9; i++){
        if(board[i]==2) cout<<"_";
        else if(board[i]==3) cout<<"X";
        else cout<<"O";

        if(i%3==0) cout<<endl;
        else cout<<" | ";
    }

    cout<<endl;
}

int posswin(int p){
    int pos;
    for(int i=1; i<=9; i+=3){
        pos=i;
        if(board[pos]*board[pos+1]*board[pos+2]==p*p*2){
            if(board[pos]==2) return pos;
            if(board[pos+1]==2) return pos+1;
            if(board[pos+2]==2) return pos+2;
        }
    }

    for(int i=1; i<=3; i++){
        pos=i;
        if(board[pos]*board[pos+3]*board[pos+6]==p*p*2){
            if(board[pos]==2) return pos;
            if(board[pos+3]==2) return pos+3;
            if(board[pos+6]==2) return pos+6;
        }
    }

    pos=1;
    if(board[pos]*board[pos+4]*board[pos+8]==p*p*2){
        if(board[pos]==2) return pos;
        if(board[pos+4]==2) return pos+4;
        if(board[pos+8]==2) return pos+8;
    }

    pos=3;
    if(board[pos]*board[pos+2]*board[pos+4]==p*p*2){
        if(board[pos]==2) return pos;
        if(board[pos+4]==2) return pos+2;
        if(board[pos+8]==2) return pos+4;
    }

    return 0;
}

bool checkWin(int player){
    for(int i=1; i<=9; i+=3){
        if(board[i]==player && board[i+1]==player && board[i+2]==player){
            return true;
        }
    }

    for(int i=1; i<=3; i++){
        if(board[i]==player && board[i+3]==player && board[i+6]==player){
            return true;
        }
    }

    if(board[1]==player && board[5]==player && board[9]==player) return true;
    if(board[3]==player && board[5]==player && board[7]==player) return true;

    return false;
}

void makeMove(int player){
    if(board[5]==2){
        board[5]=player;
        return;
    }

    int winningMove=posswin(player);
    if(winningMove!=0 && board[winningMove]==2){
        board[winningMove]=player;
        return;
    }

    int blockingMove=posswin(player==3?5:3);
    if(blockingMove!=0 && board[blockingMove]==2){
        board[blockingMove]=player;
        return;
    }

    vector<int>corners={1,3,7,9};
    for(int i=0; i<4; i++){
        if(board[corners[i]]==2){
            board[corners[i]]=player;
            return;
        }
    }

    for(int i=1; i<=9; i++){
        if(board[i]==2){
            board[i]=player;
            return;
        }
    }
}

bool gameOver(){
    if(checkWin(3)){
        displayBoard();
        cout<<"You win\n";
        return true;
    }
    if(checkWin(5)){
        displayBoard();
        cout<<"Computer wins\n";
        return true;
    }
    for(int i=1; i<=9; i++){
        if(board[i]==2) return false;
    }
    displayBoard();
    cout<<"Draw\n";
    return true;
}

int main(){

    cout<<"Welcome to TIc Tac Toe"<<endl;

    while(true){
        displayBoard();
        int playerMove;
        cout<<"Enter your move= \n";
        cin>>playerMove;
        if(playerMove<1 || playerMove>9 || board[playerMove]!=2){
        cout<<"Invalid move, try again\n";
        continue;
        }
        board[playerMove]=3;
        if(gameOver()){
            cout<<"Game Over\n";
            break;
        }
        makeMove(5);
        if(gameOver()){
            cout<<"Game Over]\n";
            break;
        }
    }
    return 0;
}