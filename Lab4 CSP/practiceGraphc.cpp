#include<iostream>
#include<vector>
using namespace std;

bool graphColouring(int N, int m, vector<vector<int>>&graph){
    vector<int>color(N,0);

    if(solve(0, color, N, m, graph)){
        cout<<"Vertex colors"<<endl;
        
    }
} 

int main(){

    int N, m, edges;
    cout<<"Enter number of nodes= "<<endl;
    cin>>N;
    cout<<"Enter number of colors= "<<endl;
    cin>>m;
    cout<<"Enter number of edges= "<<endl;
    cin>>edges;
    
    vector<vector<int>>graph;
    graph.resize(N);

    for(int i=0; i<edges; i++){
        int node1, node2;
        cout<<"Enter vertices of edge= "<<endl;
        cin>>node1>>node2;
        node1--; node2--;

        graph[node1].push_back(node2);
        graph[node2].push_back(node1);
    }
    cout<<(graphColoring(N, m, graph)? "Yes": "No");
    return 0;
}