#include<bits/stdc++.h>
using namespace std;

typedef vector<vector<int>> Board;
enum Action {up, down, LEFT, RIGHT};

Board apply_actions(const Board &state, Action action){
    Board newState=state;
    int er=-1, ec=-1;
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(state[i][j]==0){
                er=i;
                ec=j;
            }
        }
    }

    if(action==up) swap(newState[er][ec], newState[er-1][ec]);
    if(action==down) swap(newState[er][ec], newState[er+1][ec]);
    if(action==LEFT) swap(newState[er][ec], newState[er][ec-1]);
    if(action==RIGHT) swap(newState[er][ec], newState[er][ec+1]);

    return newState;
}

void print_board(const Board &state){
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            cout<<state[i][j]<<" ";
        }
        cout<<endl;
    }
}

vector<Action> get_actions(const Board &state){

    vector<Action> valid_actions;
    int er=-1, ec=-1;
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(state[i][j]==0){
                er=i;
                ec=j;
            }
        }
    }

    if(er>0) valid_actions.push_back(up);
    if(er<2) valid_actions.push_back(down);
    if(ec>0) valid_actions.push_back(LEFT);
    if(ec<2) valid_actions.push_back(RIGHT); 

    return valid_actions;
}

bool is_goal(const Board &state, const Board &goal){
    return state==goal;
}

bool dfs(const Board &current, const Board &goal, stack<Action>&path, set<Board>&visited){
    if(is_goal(current, goal)){
        return true;
    }
    
    visited.insert(current);
    vector<Action> validActions = get_actions(current);

    for(Action action: validActions){
        Board next= apply_actions(current, action);

        if(visited.find(next)==visited.end()){
            path.push(action);
            print_board(next);

            if(dfs(next, goal, path, visited)){
                return true;
            }
            path.pop();
        }
    }
    return false;
}

Board get_input(){
    Board matrix(3, vector<int>(3)); 
    cout<<"Enter 3*3 configuration=\n";
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            cin>>matrix[i][j];
        }
    }
    return matrix;
}

int main(){
    
    cout<<"Initial State:\n";
    Board initial_state = get_input();

    cout<<"Goal State:\n";
    Board goal_state= get_input();

    stack<Action>path;
    set<Board>visited;

    bool solution= dfs(initial_state, goal_state, path, visited);
    if(solution){
        cout<<"Solution found\n";
    }
    else{
        cout<<"No solution found\n";
    }


    return 0;
}