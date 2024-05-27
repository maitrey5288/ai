#include<iostream>
#include<limits>
using namespace std;
struct Move{
    int row, col;
};
char human='X', computer='O';

bool movesLeft(char board[3][3]){
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(board[i][j]=='_') return true;
        }
    }
    return false;
}

int evaluate(char board[3][3], int depth){

    for(int row=0; row<3; row++){
        if(board[row][0]==board[row][1] && board[row][1]==board[row][2]){
            if(board[row][0]==human) return -10 + depth;
            else if(board[row][0]==computer) return 10 - depth;
        }
    }

    for(int col=0; col<3; col++){
        if(board[0][col]==board[1][col] && board[1][col]==board[2][col]){
            if(board[0][col]==human) return -10 + depth;
            else if(board[0][col]==computer) return 10 + depth;
        }
    }

    if(board[0][0]== board[1][1] && board[1][1]==board[2][2]){
        if(board[0][0]==human) return -10 + depth;
        else if(board[0][0]==computer) return 10 +depth;
    }

    if(board[0][2]==board[1][1] && board[1][1]==board[2][0]){
        if(board[0][2]==human) return -10 +depth;
        else if(board[0][2]==computer) return 10 - depth;
    }
    return 0;
}

int minimax(char board[3][3], int depth, bool isMax){
    int score=evaluate(board, depth);
    if(score==10 || score==-10) return score;
    if(!movesLeft(board)) return 0;

    if(isMax){
        int best= -numeric_limits<int>::max();
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                if(board[i][j]=='_'){
                    board[i][j]=computer;
                    int best= max(best, minimax(board, depth+1, !isMax));
                    board[i][j]='_';
                }
            }
        }
        return best;
    }
    else{
        int best= numeric_limits<int>::max();
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                if(board[i][j]=='_'){
                    board[i][j]=human;
                    int best= min(best, minimax(board, depth+1, !isMax));
                    board[i][j]='_';
                }
            }
        }
        return best;
    }
}

bool checkWin(char player, char board[3][3]){

    for(int i=0; i<3; i++){
        if((board[i][0]==player && board[i][1]==player && board[i][2]==player) || 
           (board[0][i]==player && board[1][i]==player && board[2][i]==player)) return true;
    }

    if((board[0][0]==player && board[1][1]==player && board[2][2]==player) || 
       (board[0][2]==player && board[1][1]==player && board[2][0]==player)) return true;
    
    return false;
}

Move findBestMove(char board[3][3]){
    Move bestMove;
    bestMove.row=-1;
    bestMove.col=-1;
    int bestScore= -numeric_limits<int>::max();

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(board[i][j]=='_'){
                board[i][j]=computer;
                int score=minimax(board, 0, false);
                board[i][j]='_';

                if(score>bestScore){
                    bestScore=score;
                    bestMove.row=i;
                    bestMove.col=j;
                }
            }
        }
    }
    return bestMove;
}

void printBoard(char board[3][3]){

    for(int i=0; i<3; i++){
        cout<<" | ";
        for(int j=0; j<3; j++){
            cout<<board[i][j]<<" | ";
        }
        cout<<endl<<"--------------"<<endl;
    }
}


int main(){
    char board[3][3]={
        {'_','_','_'},
        {'_','_','_'},
        {'_','_','_'}
    };
    printBoard(board);
    int flag=0;

    while(movesLeft(board)){

        if(flag==0){
            Move computerMove=findBestMove(board);
            board[computerMove.row][computerMove.col]=computer;
            printBoard(board);
            if(checkWin(computer, board)){
            cout<<"Computer Wins\n";
            break;
            }
            if(!movesLeft(board)){
            break;
            }
        }

        int hrow, hcol;
        cout<<"Enter your move= \n";
        cin>>hrow>>hcol;

        if(!cin || hrow < 0 || hrow > 2 || hcol < 0 || hcol > 2 || board[hrow][hcol]!= '_'){
        cout<<"Invalid Move, play again\n";
            flag=1;
            continue;

        }
        board[hrow][hcol]=human;
        printBoard(board);
        if(checkWin(human, board)){
            cout<<"You Win\n";
            break;
        }
        flag=0;   

    }

    if(!checkWin(human,board) && !checkWin(computer,board)){
        cout<<"Draw\n";
    }

    return 0;
}