#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

#define inf 0x3f3f3f3f

int n;
int v[57]; 
int f[57][57]; 

/*
	f[i][j] = melhor resposta para cortar o segmento de v[i] a v[j]
	f[i][j] = min{f[i][k] + f[k][r] + v[r] - v[l]}, para todo k entre i e j
	Base: f[i][j] = 0 se j = i + 1

	Complexidade: O(n^3)
*/
int solve(int l, int r) {
	if (r - l <= 1) return 0;

	if (f[l][r] != -1) return f[l][r]; 

	int ret = inf;

	for (int i = l+1; i < r; i++) {
		ret = min(ret, v[r] - v[l] + solve(l, i) + solve(i, r));
	}

	return f[l][r] = ret;
}

int main() {
	int l;
	while(scanf("%d %d", &l, &n) == 2 && l) {
		v[0] = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d", v + i);
		}
		v[n+1] = l;

		memset(f, -1, sizeof f);
		printf("The minimum cutting is %d.\n", solve(0, n+1));
	}

	return 0;
}