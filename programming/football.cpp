#include <iostream>
#include <vector>
#include <stack>
using namespace std;

#define Nmax 30001
vector< vector<int> > loses(Nmax);
vector< vector<int> >  wins(Nmax);
vector<bool> visited(Nmax);
stack<int> Stack;
int N, di, t, calc = 0;

void DFSUtil_wins (int v) {
    visited[v] = true;
    for (auto u : wins[v])
        if (!visited[u])
            DFSUtil_wins(u);
    Stack.push(v);
}

void DFSUtil_loses (int v) {
    visited[v] = true;
    for (auto u : loses[v])
        if (!visited[u])
            DFSUtil_loses(u);
}

int DFS () {
    fill(visited.begin(), visited.end(), false);
    for (int i = 1; i <= N; i++)
        if (!visited[i])
            DFSUtil_wins(i);
    return Stack.top();
}

int main () {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &di);
        for (int j = 1; j <= di; j++) {
            scanf("%d", &t);
            loses[i].push_back(t);
            wins[t].push_back(i);
        }
    }
    int start = DFS();
    fill(visited.begin(), visited.end(), false);
    DFSUtil_wins(start);
    for (int i = 1; i <= N; i++) if (!visited[i]) { cout << 0 << endl; return 0; }

    fill(visited.begin(), visited.end(), false);
    DFSUtil_loses(start);
    for (int i = 1; i <= N; i++)
        if (visited[i]) calc++;
    cout << calc << endl;
}