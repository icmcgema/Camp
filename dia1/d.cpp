#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second
#define mp make_pair

#define MOD 10007

using namespace std;
const int N = 100310, inf = 0x3f3f3f3f;

typedef pair<int, int> ii;
typedef long long ll;

int n;
vector<int> e[N];
int f[N][2], g[N][2], de[N][2]; // f = menor numero de luzes, g = numero de solucoes otimas, de = matriz de decisao de f

/*
	f[u][l] = menor numero de luzes para a subarvore enraizada em u, com luz acesa em u (se l = 1) e livre escolha caso contrario
	f[u][l] = min{soma de f[v][1] para todos os v's adjacentes a u, 1 + soma de f[v][0] para os v's adjacentes a u}, se l = 0
			= 1 + soma de f[v][0] para os v's adjacentes a u, se l = 1

	g[u][l] = numero de solucoes otimas para a subarvore de u que tem f[u][l] luzes acesas

	Seja X = (produto de g[v][0] para todos os v's adjacentes a u) e Y = (produto de g[v][1] para todos os v's adjacentes a u)
	g[u][l] = X + Y, se tanto acender em u ou nao acender fornecem a melhor solucao
			= X, se acender em u obtem a melhor solucao
			= Y, se nao acender obtem a melhor solucao

	Complexidade: O(N)
*/
int solve(int u, int l, int par) {
	int & st = f[u][l];
	if(st == -1) {
		int a, b;
		
		/* Se eu nao ligar no vert u */
		int s = 0;
		for(int v : e[u]) {
			if(v == par) continue; // nao chamo pro pai

			s += solve(v, 1, u);
		}

		if(l == 0) a = s;
		else a = inf;

		/* Se eu ligar no vert u */
		s = 0;
		for(int v : e[u]) {
			if(v == par) continue; // nao chamo pro pai

			s += solve(v, 0, u);
		}

		b = s + 1;

		if(a < b) de[u][l] = 0; // nao liga
		else if(b < a) de[u][l] = 1; // liga
		else de[u][l] = 2; // tanto faz ligar ou nao

		st = min(a, b);
	}

	return st;
}

int count(int u, int l, int par) {
	int & st = g[u][l];

	if(st == -1) {
		st = 0;

		solve(u, l, par); // tenho que calcular o vetor de decisoes antes

		int tota = 1, totb = 1;
		for(int v : e[u]) {
			if(v == par) continue; // nao chamo pro pai

			tota = (tota * count(v, 1, u))%MOD;
			totb = (totb * count(v, 0, u))%MOD;
		}

		if(de[u][l] == 0) st += tota;
		else if(de[u][l] == 1) st += totb;
		else st += tota + totb;
		st %= MOD;
	}

	return st%MOD;
}

int main() {
	ios::sync_with_stdio(false);

	int t; cin >> t;
	while(t--) {
		memset(f, -1, sizeof f);
		memset(g, -1, sizeof g);
		cin >> n;

		for(int i = 1; i < n; ++i) {
			int u, v;
			cin >> u >> v;

			e[u].pb(v);
			e[v].pb(u);
		}

		cout << solve(1, 0, -1) << " " << count(1, 0, -1) << endl;

		for(int i = 1; i <= n; ++i) e[i].clear(); // Lembrar de liberar os vetores de adjacencias
	}
}