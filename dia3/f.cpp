#include <bits/stdc++.h>

#define pb push_back
using namespace std;
const int inf = 0x3f3f3f3f, N = 1000000;

/* 
	Solucao:
	Horacio consegue "ver um elefante" na posicao j do muro dos ursos, se e somente se,
	a sequencia de diferencas do muro de horacio {b1 - b0, b2 - b1, b3 - b2, ..., b(m-1) - b(m-2)} for igual
	a sequencia de diferencas do muro dos ursos a partir da posicao j {a(j+1) - aj, a(j+2) - a(j+1), ..., a(j+m-1) - a(j+m-2)}

	Por causa disso, podemos construir um vetor de diferencas do array A e um vetor de diferencas para o B, e fazer string matching nesses
	caras, usando phi function
*/

int phi[N];

/* Esse Phi eh meio diferente pq eh zero based */
void calc_phi(vector<int> & v) {
	phi[0] = 0;

	for(int i = 1; i < v.size(); ++i) {
		int j = phi[i-1];

		while(j and v[i] != v[j]) j = phi[j-1];
		if(v[i] == v[j]) phi[i] = j+1;
		else phi[i] = 0;
	}
}

int main() {
	ios::sync_with_stdio(false);
	int n, w, prev;

	scanf("%d %d", &n, &w);

	if(w > n) return 0 * printf("0\n"); // se o meu padrao for maior que n, nao tem nenhum match
	if(w == 1) return 0 * printf("%d\n", n); // se eu nao fizer isso, o meu padrao vai ser um vetor vazio

	/* Monta o vetor de diferencas dos ursos */
	vector<int> ursos;
	scanf("%d", &prev);
	for(int i = 1; i < n; ++i) {
		int a;
		scanf("%d", &a);
		ursos.pb(a - prev);
		prev = a;
	}

	/* Monta o vetor de diferencas do horacio */
	vector<int> horacio;
	scanf("%d", &prev);
	for(int i = 1; i < w; ++i) {
		int a;
		scanf("%d", &a);
		horacio.pb(a - prev);
		prev = a;
	}

	horacio.pb(inf); // inf eh o separador
	horacio.insert(horacio.end(), ursos.begin(), ursos.end()); // funcao pra concatenar o vetor horacio com o ursos

	calc_phi(horacio);

	int tot = 0;
	for(int i = 0; i < horacio.size(); ++i) tot += phi[i] == (w-1); // conta o numero de matchs

	printf("%d\n", tot);

}