#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#define INF 1000000001
#define KAPA 2000001
using namespace std;

long long int K, T, Ts, Cs, Tf, Cf;
long long int dist[KAPA];
vector <pair<long long int, long long int> > cars;
long long int get_minc(long long int first, long long int last);

int main() {    // Total Complexity: O(KlogK + (N+K)logN)
    long long int N, D;
    long long int min_capacity;
    long long int min_price;

    /* Input Problem Data */
    scanf("%lld %lld %lld %lld", &N, &K, &D, &T);
    for(long long int i = 0; i < N; ++i) {
        long long int price, capacity;
        scanf("%lld %lld", &price, &capacity);
        cars.push_back(make_pair(capacity, price));
    }
    for(long long int i = 0; i < K; ++i) 
        scanf("%lld", &dist[i]);
    dist[K] = D;
    scanf("%lld %lld %lld %lld", &Ts, &Cs, &Tf, &Cf); 

    /* Preprocess Data - cost: O(KlogK + NlogN) */
    sort(dist, dist + K);    // sort distances
    for(long long int i = K; i > 0; --i)              // transform them into consecutive distances
        dist[i] -= dist [i-1];
    sort(cars.begin(), cars.end());         // sort cars according to their fuel capacity
    
    /* Problem Solution - cost: O(KlogN + N) */
    if((min_capacity = get_minc(0, N-1)) != INF) {
        min_price = INF;
        for(const auto& car: cars)
            if(car.first >= min_capacity && car.second < min_price)
                min_price = car.second;
        printf("%d\n", min_price);
    }
    else
        printf("%d\n", -1);
}

long long int get_minc(long long int first, long long int last) { // Returns the minimum capacity needed
    long long int mid = (first+last)/2;
    double time = 0;
    bool able = true;

    if(first <= last) {
        for(long long int i = 0; i < K+1; ++i) {
            if(cars[mid].first - dist[i]*Cs >= 0) {  // scenario 1: dist[i] can be covered
                double x = min( (double) dist[i], ( (double) (cars[mid].first - dist[i]*Cs) )/( (double) Cf - Cs));
                double y = ( (double) dist[i])-x;
                time += x*Tf + y*Ts;
            }
            else {  // scenario 2: car is unable to cover dist[i]
                able = false;
                break;
            }
        }
        if(able && time <= T)
            return min(cars[mid].first, get_minc(first, mid-1));
        else
            return get_minc(mid+1, last);
    }
    return INF;
}  