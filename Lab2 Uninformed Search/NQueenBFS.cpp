#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class NQueens {
private:
    int size;

public:
    NQueens(int size) : size(size) {}

    bool conflict(const vector<pair<int, int>>& queens) {
        for (int i = 1; i < queens.size(); ++i) {
            for (int j = 0; j < i; ++j) {
                int a = queens[i].first;
                int b = queens[i].second;
                int c = queens[j].first;
                int d = queens[j].second;
                if (a == c || b == d || abs(a - c) == abs(b - d)) { 
                    return true;
                }
            }
        }
        return false;
    }

    vector<vector<pair<int, int>>> solveBFS() {
        vector<vector<pair<int, int>>> solutions;
        if (size < 1) {
            return solutions;
        }
        queue<vector<pair<int, int>>> q;
        q.push({});
        
        while (!q.empty()) {
            //cout<<"hi";
            auto solution = q.front();
            //cout<<"size"<<solution.size();
            // for(auto i: solution){
            //     cout<<"g";
            //     cout<<i.first<<"\t";
            //     cout<<i.second<<"\t";
            //     cout<<solution.size()<<"\n";
            // }
            q.pop();
            if (conflict(solution)) {
                continue;
            }
            int row = solution.size();
            cout<<"row="<<row<<endl;
            if (row == size) {
                solutions.push_back(solution);
                continue;
            }
            for (int col = 0; col < size; ++col) {
                vector<pair<int, int>> queens = solution;
                queens.push_back({row, col});
                for(auto i: queens){
                    cout<<i.first<<"\t";
                    cout<<i.second<<endl;
                }
                q.push(queens);
            }
        }
        return solutions;
    }

    void print(const vector<pair<int, int>>& queens) {
        for (int i = 0; i < size; ++i) {
            cout << " ---";
        }
        cout << endl;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                char p = ' ';
                for (auto& queen : queens) {
                    if (queen.first == i && queen.second == j) {
                        p = 'Q';
                        break;
                    }
                }
                cout << "| " << p << " ";
            }
            cout << "|" << endl;
            for (int j = 0; j < size; ++j) {
                cout << " ---";
            }
            cout << endl;
        }
    }
};

int main() {
    int n = 4;
    NQueens nQueens(n);
    vector<vector<pair<int, int>>> solutions = nQueens.solveBFS();
    for (int i = 0; i < solutions.size(); ++i) {
        cout << "Arrangement " << i + 1 << ":\n";
        nQueens.print(solutions[i]);
        cout << endl;
    }
    return 0;
}
