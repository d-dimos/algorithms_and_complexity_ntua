#include <stdio.h>
#include <algorithm>
#define N_max 2501
#define infinity 200000000
using namespace std;

int N, K, reaction[N_max+1][N_max+1], energy[N_max+1][N_max+1], dp[N_max+1][N_max+1], best_cut[N_max+1][N_max+1];
void solution(int k, int left, int right, int best_left, int best_right);   // Break problem into smaller problems
void find_partial(int i, int k, int left, int right);                       // Find solution for smaller t-margins

int main() {
    /* Input */
    scanf("%d%d", &N, &K);
    for(int i = 1; i <= N; i++)
        for(int j = i+1; j <= N; j++)
            scanf("%d", &reaction[i][j]);
    /* Calculate possible reaction energies: O(N^2) */ 
    for(int i = 1; i <= N; ++i)
        energy[i][i] = 0;
    for(int j = 1; j <= N; ++j) 
        for(int i = 1; i <= N-j; ++i) {
            energy[i][i+j] = energy[i][i+j-1] + energy[i+1][i+j] + reaction[i][i+j];
            if(i+1 < i+j-1)
                energy[i][i+j] -= energy[i+1][i+j-1];
        }
    /* Divide and Conquer solution: O(K*N*logN) */ 
    for(int i = 1; i <= N; ++i) {
        dp[i][i] = 0;
        dp[i][1] = energy[1][i];
        best_cut[i][1] = 0;
    } 
    for(int k = 2; k <= K; ++k)
        solution(k, 0, N, 0, N);
    printf("%d\n", dp[N][K]);
}

void solution(int k, int left, int right, int best_left, int best_right) {
  if(left > right)
    return;
  int mid = (left + right)/2;
  find_partial(mid, k, best_left, best_right);
  solution(k, left, mid-1, best_left, best_cut[mid][k]);
  solution(k, mid+1, right, best_cut[mid][k], best_right);
}

void find_partial(int i, int k, int left, int right) {
    dp[i][k] = infinity;
    for(int t = left; t <= right; t++) {
        int temp = dp[t][k-1] + energy[t+1][i];
        if(temp < dp[i][k]) {
            dp[i][k] = temp;
            best_cut[i][k] = t;
        }
    }
}