#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;

#define newp make_pair
#define push push_back
#define INF 100001
#define X first
#define Y second

typedef pair<int, int> int_pair;
typedef pair<int, int_pair> edge;

int N, M;
int max_narrow_portal;
int c[INF+1];
int parent[INF+1], height[INF+1];
vector<edge> edges;

int find(int v);    // returns representative element
void Union(int u, int v);   // unites two disjoint vertex sets
void initialize();
int binary_search(int start, int end);
void create_unions(int pivot);



int main() {

    /* Input Data */
    scanf("%d %d", &N, &M);
    for(int i = 1; i <= N; ++i) {
        int Morty;
        scanf("%d", &Morty);
        c[Morty] = i;
    }
    for(int i = 0; i < M; ++i) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        edges.push( newp(w, newp(u, v)) );
    }

    /* Preprocess Data - O(MlogM) */
    sort(edges.begin(), edges.end());

    /* Calculate Result */
    max_narrow_portal = binary_search(0, N-1);
    printf("%d\n", max_narrow_portal);
}


 
int find(int v) {
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
        if(height[u] == height[v]) height[v]++;
    }
}

void initialize() {
    for(int i = 1; i <= N; i++) {
        parent[i] = i;
        height[i] = 0;
  }
}

int binary_search(int start, int end) {
    int mid = (start+end)/2;           

    if(start <= end) {
        //cout << "\nExamining edge: " << mid+1 << " with weight: " << edges[mid].X <<endl;
        initialize();
        create_unions(mid);
        for(int i = 1; i <= N; ++i) {
            if(find(i) != find(c[i])) { //cout << " The unions created cannot connect: " << i << " and " << c[i] << ". They have rep: " << find(i) << " and " << find(c[i]) << endl;
                return binary_search(start, mid-1); }
        }
        return max(edges[mid].X, binary_search(mid+1,end));
    }
    return -1;
}

void create_unions(int pivot) {
    for(int i = pivot; i < edges.size(); ++i)
        if(find( edges[i].Y.X ) != find( edges[i].Y.Y )) {
            //printf("Creating edge between: %d and %d\n", edges[i].Y.X, edges[i].Y.Y);
            Union(edges[i].Y.X, edges[i].Y.Y);
        }
}