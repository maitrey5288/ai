#include<bits/stdc++.h>
#include<algorithm>
using namespace std;

map<string, map<string,int>> graph={
    {"A", {{"B", 2}, {"C", 4}}},
    {"B", {{"A", 4}, {"D", 3}, {"E", 1}}},
    {"C", {{"A", 2}, {"F", 5}}},
    {"D", {{"B", 3}, {"G", 7}}},
    {"E", {{"B", 1}, {"G", 2}}},
    {"F", {{"C", 4}, {"G", 1}}},
    {"G", {{"D",7}, {"E", 1}, {"F", 1}}}
};

map<string, int>heuristic={
    {"A", 6}, {"B", 4}, {"C", 3}, {"D", 4}, {"E",2}, {"F", 1}, {"G", 0}
};

vector<string> bfs(const string &start, const string &goal){
    priority_queue< pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
    map<string, string>cameFrom;

    pq.push({heuristic[start], start});
    cameFrom[start]="";

    while(!pq.empty()){
        string current=pq.top().second;
        pq.pop();

        if(current == goal){
            vector<string>path;
            while(current != ""){
                path.push_back(current);
                current= cameFrom[current];
            }
            reverse(path.begin(), path.end());
            return path;
        }

        for(const auto &neighbour: graph[current]){
            string next=neighbour.first;

            if(cameFrom.find(next)==cameFrom.end()){
                cameFrom[next]=current;
                int priority=heuristic[next];
                pq.push({priority, next});
            }
        }
    }
    return {};
}

int main(){
    string start="A";
    string goal="G";
    vector<string>path= bfs(start, goal);
    if(!path.empty()){
        cout<<"Path from "<<start<<"to "<<goal<<":\n";
        for(const auto &city: path){
            cout<<city<<"->";
        }
        cout<<"Goal";
    }
    else{
        cout<<"No solution\n";
    }
    return 0;
}