#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second
#define mp make_pair

#define MOD 10007

using namespace std;
const int N = 25, inf = 0x3f3f3f3f;

typedef pair<int, int> ii;
typedef long long ll;

int n, m, k;

int a[N];
int c[N][N];

ll f[N][1 << 18];

/*
	f[u][mask] = Maior satisfacao que consigo obter apos comer os pratos de mask e comecando pelo prato u

	f[u][mask] = max{a[u] + c[u][v] + f[v][mask']}, para todos os pratos v que ja nao foram usados, em que
	mask' agora inclui v

	Resposta: max{f[u][0]} para todos os pratos u

	Complexidade: O(n^2 * 2^n)

*/
ll solve(int u, int mask) {
	// __builtin_popcount(x) retorna a quantidade de bits setados em x
	if(__builtin_popcount(mask) == m-1) return a[u];
	ll & st = f[u][mask];

	mask = mask | (1 << (u-1)); // seta o bit referente ao prato u

	if(st == -1) {
		for(int v = 1; v <= n; ++v) {
			if((mask & (1 << (v-1))) == 0) { // checa o se o prato v nao foi usado
				st = max(st, a[u] + c[u][v] + solve(v, mask)); 
			}
		}
	}
	return st;
}

int main() {
	memset(f, -1, sizeof f);
	ios::sync_with_stdio(false);

	cin >> n >> m >> k;
	
	for(int i = 1; i <= n; ++i) cin >> a[i];

	for(int i = 0; i < k; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		c[u][v] = w;
	}

	ll best = 0;
	for(int u = 1; u <= n; ++u) {
		best = max(best, solve(u, 0));
	}

	cout << best << endl;

}