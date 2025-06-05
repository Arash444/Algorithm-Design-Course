#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxn = 10 + 1, maxk = 2e6 + 10;
int mat[maxn][maxn], a[maxn];
ll dp[maxk];

inline void update(int i, int id, int x, int y) {
	id ^= (a[x] << (2 * x));
	if (a[y] == 1) id ^= (3 << (2 * y));
	dp[i] += dp[id];
}

int main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		mat[u][v] = mat[v][u] = 1;
	}
	vector <pair <int, int>> num;
	for (int i = 0; i < (1 << (2 * n)); i++) {
		int x = 0;
		for (int j = 0; j < n; j++) {
			if ((i >> (2 * j)) % 4) x++;
		}
		num.push_back({ x, i });
	}
	sort(num.begin(), num.end());
	ll ans = 0;
	for (pair <int, int> pr : num) {
		int i = pr.second;
		for (int j = 0; j < n; j++) {
			a[j] = (i >> (2 * j)) % 4;
		}
		int x = 0, y = 0, z = 0;
		for (int j = 0; j < n; j++) {
			if (a[j] == 1) x++;
			else if (a[j] == 2) y++;
			else if (a[j] == 3) z++;
		}
		if (x + y + z < 2) continue;
		if (x + y + z == 2) {
			if (y + z < 2) continue;
			vector <int> v;
			for (int j = 0; j < n; j++) {
				if (a[j]) v.push_back(j);
			}
			if (mat[v[0]][v[1]]) dp[i] = 1;
		}
		if (z) {
			int ind;
			for (int j = 0; j < n; j++) {
				if (a[j] == 3) {
					ind = j;
					break;
				}
			}
			for (int j = 0; j < n; j++) {
				if (mat[ind][j] && a[j] && a[j] != 3) {
					update(i, i, ind, j);
				}
			}
			if (x + y + z == n && !y && z == k) ans += dp[i];
			continue;
		}
		int id = i;
		for (int j = 0; j < n; j++) {
			if (a[j] == 2) {
				for (int k = 0; k < n; k++) {
					if (mat[j][k] && a[k]) {
						update(i, id, j, k);
					}
				}
				id ^= (3 << (2 * j));
				a[j] = 1;
			}
		}
	}
	cout << ans;
	return 0;
}
