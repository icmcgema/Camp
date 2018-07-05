#include <bits/stdc++.h>

using namespace std;
const int N = 1000007, inf = 0x3f3f3f3f;

int v[N], f[N][2], n;

/*
	f[p][odd] = soma da subsequencia que da a maior soma impar (se odd = 1) ou par (se odd = 0) para o sufixo p...n-1

	f[p][odd] = max(f[p+1][x] + v[p], f[p+1][odd]), em que x = !odd se v[p] for impar e odd se v[p] for par
	f[n][odd] = -inf, se odd = 1 ou 0, se odd = 0

	Solucao melhor:
	Pegue todos os elementos positivos, e se a soma for par, a melhor subsequencia eh a gerada 
	tirando-se um elemento impar positivo do conjunto (o menor deles) ou adicionando um elemento 
	impar negativo ao conjunto (o menor em valor absoluto)

	Complexidade: O(n)
*/
int solve(int p, int odd) {
	if(p == n)
		return odd? 0 : -inf;

	int & st = f[p][odd];

	if(st == inf) {
		st = max(v[p] + solve(p+1, v[p]%2? !odd : odd), solve(p+1, odd));
	}	

	return st;
}

int main() {
	ios::sync_with_stdio(false);
	
	memset(f, inf, sizeof f);
	cin >> n;

	for(int i = 0; i < n; ++i) {
		cin >> v[i];
	}

	cout << solve(0, 0) << endl;
}