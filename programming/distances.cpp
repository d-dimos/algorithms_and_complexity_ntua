#include <stdio.h>
#include <vector>
#include <algorithm>
#include <math.h>
#include <iostream>

#define mp std::make_pair
#define pb push_back
#define X first
#define Y second
#define N_max 100005
#define uint unsigned long
#define ulli unsigned long long

typedef std::pair<uint, uint> int_pair;
typedef std::pair<uint, int_pair> edge;

uint N, M, MST_E = 0;
uint parent[N_max], height[N_max];
std::vector<edge> input_edges;
std::vector<edge> MST_edges;
std::vector< std::pair<uint, uint> > adj[N_max];
std::vector<ulli> freq(2*N_max, 0);

uint find(int v) {
    if(parent[v] == v)
        return v;
    return parent[v] = find(parent[v]);
}

void Union(int u, int v) {
    u = find(u);
    v = find(v);
    if(height[u] > height[v])
        parent[v] = u;
    else {
        parent[u] = v;
        if(height[u] == height[v])
            height[v]++;
    }
}

void initialize() {
    for(int i = 1; i <= N; i++) {
        parent[i] = i;
        height[i] = 0;
  }
}

void Kruskal() {
    uint e = 0;
    uint i = 0;

    sort(input_edges.begin(), input_edges.end());
    initialize();
    
    while (e < N-1 && i < M)  {
        edge next_edge = input_edges[i++];
        uint src = find(next_edge.Y.X);
        uint dst = find(next_edge.Y.Y);
        if (src != dst) {
            MST_edges.pb(next_edge);
            Union(src, dst);
            e++;
        } 
    }
}

uint DFS(uint v, uint parent) {
    uint set = 0;
    uint returned = 0;
    for(auto i : adj[v]) {
        uint neigh  = i.X;
        uint weight = i.Y;
        if(neigh != parent) {
            returned = DFS(neigh, v);
            set += returned;
            ulli times = returned * ( (MST_E+1) - returned );
            freq[weight] = times;
        }
    }
    return 1 + set;
}

int main() {
    
    scanf("%lu %lu", &N, &M);
    for(uint i = 1; i <= M; ++i) {
        uint v1, v2, w;
        scanf("%lu %lu %lu", &v1, &v2, &w);
        input_edges.pb( mp(w, mp(v1, v2)) );
    }
    Kruskal();

    std::vector<edge>().swap(input_edges);
    uint start = MST_edges[0].Y.X;

    for(auto i : MST_edges) {
        MST_E++;
        uint v1 = i.Y.X;
        uint v2 = i.Y.Y;
        uint weight = i.X;

        adj[v1].pb(mp(v2,weight));
        adj[v2].pb(mp(v1,weight));
    }
    std::vector<edge>().swap(MST_edges);
    DFS(start, 0);

    for(int i = 0; i < 2*N_max; i++)
        if(freq[i] != 0) {
            freq[i+1] += freq[i]/2 ;
            freq[i] = freq[i]%2;
        }
    std::reverse(freq.begin(), freq.end());

    uint iter = 0;
    while(freq[iter++] == 0 && iter < 2*N_max);

    for(uint i = iter-1; i < 2*N_max; i++)
        printf("%llu",freq[i]);
    printf("\n");
}