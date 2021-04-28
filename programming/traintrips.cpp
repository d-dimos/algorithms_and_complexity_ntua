#include <stdio.h>
#include <vector>
#include <set>

#define dk_max 10001
#define sj_max 1000000001
#define mp std::make_pair
#define ulong unsigned long
#define iPair std::pair<ulong,int>

int N, dk = dk_max;
ulong Q;
std::vector<ulong> dist, query(dk_max, -1);
std::set<iPair> waiting_room;

void Dijkstra() {
    while(!waiting_room.empty()) {

        iPair head = *waiting_room.begin();
        ulong cur = head.second;
        int d_sum = head.first;
        waiting_room.erase(head);

        for(auto di : dist) {
            int new_node = (cur+di) % dk;
            int new_dist = d_sum + di;

            if(new_dist < query[new_node] || query[new_node] == -1) {
                waiting_room.erase( mp( query[new_node], new_node ) );
                query[new_node] = new_dist;
                waiting_room.insert( mp( query[new_node], new_node ) );
            }
        }
    }
}

int main() {
    scanf("%d %lu", &N, &Q);
    for(int i = 1; i <= N; i++) {
        ulong di;
        scanf("%lu", &di);
        dist.push_back(di);
        if(di < dk)
            dk = di;
    }

    query[0] = 0;
    waiting_room.insert( mp(query[0],0) );
    Dijkstra();
    
    for(int i = 0; i < Q; i++) {
        ulong q;
        scanf("%lu", &q);
        (query[q % dk] > q) ? printf("NO\n") : printf("YES\n");
    }
}
