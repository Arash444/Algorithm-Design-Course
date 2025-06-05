#include <bits/stdc++.h>
using namespace std; 
long long n, m;
long long dp[40][40], Q[40][40];
int main() {
	scanf("%d %d", &n, &m);
	Q[0][0] = 1, dp[1][1] = 1, Q[1][1] = 1;
	for (int i = 2; i <= n; i++) {
		for (int h = 2; h < i; h++) {
			for (int j = 0; j <= i - 1; j++) {
				dp[i][h] += Q[j][min(j, h - 2)] * dp[i - j - 1][h - 1];
				dp[i][h] += dp[j][h - 1] * Q[i - j - 1][min(h - 2, i - j - 1)];
				dp[i][h] += dp[j][h - 1] * dp[i - j - 1][h - 1];
			}
			Q[i][h] = Q[i][h - 1] + dp[i][h];
		}
		dp[i][i] = 1ll << (i - 1);
		Q[i][i] = Q[i][i - 1] + dp[i][i];
	}
	printf("%lld", Q[n][n] - Q[n][m - 1]);
	return 0;
}
