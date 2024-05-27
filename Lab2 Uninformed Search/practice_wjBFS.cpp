#include<iostream>
#include<bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;

void printPath(map<pii,pii>mp, pii u){
    if(u.first==0 && u.second==0){
        cout<<0<<" "<<0<<endl;
        return;
    }
    printPath(mp, mp[u]);
    cout<<u.first<<" "<<u.second<<endl;
}

void bfs(int a, int b, pii goal){
    map<pii,pii> mp;
    map<pii, int> m;
    queue<pii>q;
    bool isSolvable=false;

    q.push(make_pair(0,0));

    while(!q.empty()){
        auto u = q.front();
        q.pop();

        if(m[u]==1) continue; //dont exoplore visited states
        if(u.first>a || u.second>b || u.first<0 || u.second<0) continue;

        m[{u.first, u.second}]=1;

        if(u.first==goal.first && u.second==goal.second){
            isSolvable=true;
            printPath(mp,u);
            return;
        }

        //completely fill jug 2
        if(m[{u.first, b}] != 1){
            q.push({u.first, b});
            mp[{u.first, b}]=u;
        }

        //completely fill jug 1
        if(m[{a, u.second}] != 1){
            q.push({a, u.second});
            mp[{a, u.second}]=u;
        }

        //transfer jug1->jug2
        int d=b-u.second;
        if(u.first>=d){
            int c=u.first-d;
            if(m[{c,b}] != 1){
                q.push({c,b});
                mp[{c,b}]=u;
            }
        } else{
            int c= u.first + u.second;
            if(m[{0,c}] != 1){
                q.push({0,c});
                mp[{0,c}]=u;
            }
        }

        //transfer jug2->jug1
        d=a-u.first;
        if(u.second>=d){
            int c=u.second-d;
            if(m[{a,c}] != 1){
                q.push({a,c});
                mp[{a,c}]=u;
            }
        } else{
            int c= u.first+u.second;
            if(m[{c,0}] != 1){
                q.push({c,0});
                mp[{c,0}]=u;
            }
        }

        //empty jug 2
        if(m[{u.first,0}] != 1){
            q.push({u.first, 0});
            mp[{u.first,0}]=u;
        }

        //empty jug 1
        if(m[{0, u.second}] != 1){
            q.push({0, u.second});
            mp[{0, u.second}]=u;
        }
    }

    if(!isSolvable){
        cout<<"No solution\n";
    }

}

int main(){
    int jug1, jug2, x, y;
    cout<<"Enter capacity of Jug1=\n";
    cin>>jug1;
    cout<<"Enter capacity of Jug2=\n";
    cin>>jug2;
    cout<<"Enter the goal state=\n";
    cin>>x>>y;

    bfs(jug1, jug2, make_pair(x, y));

    return 0;
}