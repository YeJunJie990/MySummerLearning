#include<bits/stdc++.h>

using namespace std;

int main() {
    string s = "RBRBB";
    int ans = 0;
    vector<vector<int>> edges = {{2, 5},{1, 5}, {1, 4}, {5, 3}};
    unordered_map<int, unordered_set<int>> neighs;
    for (auto & item : edges) {
        neighs[item[0]].insert(item[1]);
        neighs[item[1]].insert(item[0]);
    }
    
    queue<int> que;
    que.push(1);
    vector<int> w(s.size() + 1, 0);
    w[1] = s[0] == 'R' ? w[1] + 1 : w[1] - 1;
    vector<bool> visited(s.size()+1, false);
    while (!que.empty()) {
        int size = que.size();
        for (int i = 0; i < size; i++) {
            int curnode = que.front();
            que.pop();
            visited[curnode] = true;
            for (auto & n : neighs[curnode]) {
                if (visited[n]) continue;
                w[n] = s[n - 1] == 'R' ? w[curnode] + 1 : w[curnode] - 1;
                que.push(n);
            }
        }
    }
    for (auto & i : w) {
        ans += abs(i);
    }
    cout<<ans<<endl;
    return 0;
}
