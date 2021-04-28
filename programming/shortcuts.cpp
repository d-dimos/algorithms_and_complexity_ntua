#include <iostream>
#include <vector>
#include <set>
using namespace std;

#define iipair pair<int, int>
#define mp make_pair
#define X first
#define Y second
#define Nmax 1001
#define INF 1000000001

vector< vector<iipair> > neigh(Nmax);
vector< vector<int> > dist(Nmax);
vector< vector<bool> > visited(Nmax); 
set< pair<int, iipair> > queue;
int N, M, s, t, B;

// a modified version of Dijkstra
void Dijkstra() {
    while (!queue.empty()) {
        pair<int, iipair> front = *queue.begin();
        queue.erase(queue.begin());

        int u = front.Y.X;   // current vertex
        int ud = front.X;    // vertex distance from s
        int sc = front.Y.Y;  // shortcuts used
        visited[sc][u] = true;

        for (auto n:neigh[u]) {
            int v = n.first;
            int l = n.second;

            // for current number of shortcuts
            if (!visited[sc][v] && dist[sc][v] > dist[sc][u] + l) {
                if (dist[sc][v] != INF)
                    queue.erase(queue.find( mp(dist[sc][v], mp(v, sc)) ));
                
                dist[sc][v] = dist[sc][u] + l;
                queue.insert( mp(dist[sc][v], mp(v, sc)) );
            }

            // for next number of shortcuts
            if (sc+1 < N && !visited[sc+1][v] && dist[sc+1][v] > dist[sc][u]) {
                
                if (dist[sc+1][v] != INF)
                    queue.erase(queue.find( mp(dist[sc+1][v], mp(v, sc+1)) ));
                
                dist[sc+1][v] = dist[sc][u];
                queue.insert( mp(dist[sc+1][v], mp(v, sc+1)) );
            }
        }
    }
}

int main() {
    scanf("%d%d%d%d%d", &N, &M, &s, &t, &B);
    for (int i = 1; i <= M; i++) {
        int u, v, l;
        scanf("%d%d%d", &u, &v, &l);
        neigh[u].push_back( mp(v,l) );
    }
    
    for (int i = 0; i <= N; i++)
        for (int j = 0; j <= N; j++) {
            dist[i].push_back(INF);
            visited[i].push_back(false);
        }

    dist[0][s] = 0;
    queue.insert( mp(0, mp(s,0)) );
    Dijkstra();
    
    for (int j = 0; j <= N; j++) {
        if (dist[j][t] <= B) {
            cout << j << endl;
            return 0;
        }    
    }
}