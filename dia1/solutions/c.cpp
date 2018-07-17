#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second
#define mp make_pair

using namespace std;
const int N = 10007;
typedef pair<int, int> ii;
typedef long long ll;

const ll inf = 0x3f3f3f3f3f3f3f3f;

int n, v[N];
ll memo[2][N];

/*
	f[tam][l] 	= melhor resposta para o segmento comecando no indice l e de tamanho tam
	f[tam][l] 	= max{v[l] + f[tam-1][l+1], f[tam-1][l] + v[r]}, se tam eh par (jogador A)
				= max(f[tam-1][l+1], f[tam-1][l]), se tam eh impar (jogador B)

	Complexidade: O(N^2), memoria: O(N^2) Memory Limit Exceeded!

	Solucao: como f[tam][l] so depende dos valores calculados para tam-1, podemos calcular f dos menores valores de tam para os maiores,
	usando dois vetores. Desse jeito reduzimos a complexidade de memoria para O(N)
*/
int main() {
	ios::sync_with_stdio(false);

	while(cin >> n) {

		for(int i = 0; i < n; ++i) {
			cin >> v[i];
		}

		for(int tam = 1; tam <= n; ++tam) {
			/*
				memo[0]: vetor correspondente ao tam atual
				memo[1]: vetor correspondente ao tam-1
			*/
			for(int l = 0; l + tam - 1 < n; l++) {
				if(tam == 1) memo[0][l] = 0; // Caso base
				else {
					if(tam % 2 == 0) memo[0][l] = max(memo[1][l+1] + v[l], memo[1][l] + v[l + tam - 1]);
					else memo[0][l] = min(memo[1][l+1], memo[1][l]);
				}

			}

			memcpy(memo[1], memo[0], sizeof memo[1]); // atualiza memo[1] para memo[0]
		}

		cout << memo[0][0] << endl;

	}
}