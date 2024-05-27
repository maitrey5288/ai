#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
#include<tuple>
using namespace std;
struct State{
    int missionariesLeft;
    int cannibalsLeft;
    int missionariesRight;
    int cannibalsRight;
    int boat;

    bool operator<(const State &other) const{
        return tie(missionariesLeft, cannibalsLeft, missionariesRight, cannibalsRight, boat) <
               tie(other.missionariesLeft, other.cannibalsLeft, other.missionariesRight, other.cannibalsRight, other.boat);
    }

};

void printState(const State &state){
    cout<<"Left: "<<state.missionariesLeft<<"M "<<state.cannibalsLeft<<"C";
    cout<<"\tRight: "<<state.missionariesRight<<"M "<<state.cannibalsRight<<"R"<<endl;
    cout<<"\tBoat: "<<(state.boat==0? "Left": "Right")<<endl;
}

void move(State &state, int missionaries, int cannibals){
    if(state.boat==0){
        state.missionariesLeft-=missionaries;
        state.cannibalsLeft-=cannibals;
        state.missionariesRight+=missionaries;
        state.cannibalsRight+=cannibals;
    }
    else{
        state.missionariesLeft+=missionaries;
        state.cannibalsLeft+=cannibals;
        state.missionariesRight-=missionaries;
        state.cannibalsRight-=cannibals;
    }
    state.boat=1-state.boat;
}

void unmove(State &state, int missionaries, int cannibals){
    state.boat= 1 - state.boat;
    if(state.boat==0){
        state.missionariesLeft+=missionaries;
        state.cannibalsLeft+=cannibals;
        state.missionariesRight-=missionaries;
        state.cannibalsRight-=cannibals;
    }
    else{
        state.missionariesLeft-=missionaries;
        state.cannibalsLeft-=cannibals;
        state.missionariesRight+=missionaries;
        state.cannibalsRight+=cannibals;
    }
}

bool is_goal(const State &state){
    return state.missionariesLeft==0 && state.cannibalsLeft==0 && state.missionariesRight==3 && state.cannibalsRight==3;
}

bool valid_state(const State &state){
    if(state.missionariesLeft<0 || state.cannibalsLeft<0 || state.missionariesRight<0 || state.cannibalsRight<0) return false;
    if(state.missionariesLeft>0 && state.missionariesLeft<state.cannibalsLeft) return false;
    if(state.missionariesRight>0 && state.missionariesRight<state.cannibalsRight) return false;
    return true;
}

bool dfs(State &state, vector<State> &path, set<State> &visited){
    if(!valid_state(state) || visited.find(state) != visited.end()) return false; //if state if invalid or already explored, base case.

    path.push_back(state);
    visited.insert(state);

    if(is_goal(state)) return true;

    for(int m=0; m<=2; m++){
        for(int c=0; c<=2; c++){
            if(m+c>=1 && m+c<=2){
                move(state, m, c);
                if(dfs(state, path, visited)) return true;
                unmove(state, m, c);
            }
        }
    }

    path.pop_back();
    visited.erase(state);
    return false;
}


int main(){
    State initial_state= {3,3,0,0,0};
    vector<State>path;
    set<State>visited;

    if(dfs(initial_state,path,visited)){
        for(const auto &i: path){
            printState(i);
        }
    }
    else{
        cout<<"No solution found\n";
    }

    return 0;
}