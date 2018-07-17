#include <bits/stdc++.h>

#define fi first
#define se second

const int N = 200007;

using namespace std;
typedef pair<int, int> ii;

struct query {
	int i, j, k, id;

	bool operator< (query q) const {
		return k < q.k;
	}
};

int seg[4*30007];
query queries[N];
int ans[N];

/* 
	Segtree de soma
	Queremos que os valores maiores do que K sejam 1, e os menores ou iguais 0
*/

void build(int p, int l, int r) {
	if(l == r) {
		seg[p] = 1;
	} else {
		build(2*p, l, (l+r)/2);
		build(2*p + 1, (l+r)/2 + 1, r);
		seg[p] = seg[2*p] + seg[2*p+1];
	}
}

void update(int p, int l, int r, int pos, int val) {
	if(r < pos or l > pos) return;
	if(l == r) {
		seg[p] = val;
	} else {
		update(2*p, l, (l+r)/2, pos, val);
		update(2*p+1, (l+r)/2 + 1, r, pos, val);
		seg[p] = seg[2*p] + seg[2*p+1];
	}
}

int query(int p, int l, int r, int a, int b) {
	if(r < a or l > b) return 0;
	if(l >= a and r <= b) return seg[p];

	return query(2*p, l, (l+r)/2, a, b) + query(2*p + 1, (l+r)/2 + 1, r, a, b);
}

int main() {
	vector<ii> aux; // vetor auxiliar para ordenar crescentemente as posicoes dos elementos pelos seus valores

	int n;
	int l, r, k, a;
	scanf("%d", &n);

	for(int i = 0; i < n; ++i) {
		scanf("%d", &a);
		aux.emplace_back(a, i);
	}

	sort(aux.begin(), aux.end()); 

	int q;
	scanf("%d", &q);

	for(int i = 0; i < q; ++i) {
		scanf("%d %d %d", &l, &r, &k);
		queries[i] = {l-1, r-1, k, i};
	}

	
	sort(queries, queries + q); // ordena as queries crescentemente pelo k

	build(1, 0, n-1); // constroi a segtree de soma

	int p = 0; // ponteiro atual do vetor de posicoes dos elementos
	for(int i = 0; i < q; ++i) {
		// Quero fazer a query (i). Pra isso preciso atualizar, pra 0, todos os elementos cujos valores sao menores ou iguais a K
		while(p < aux.size() and aux[p].fi <= queries[i].k) {
			update(1, 0, n-1, aux[p].se, 0);
			++p;
		}

		// responde a query
		ans[queries[i].id] = query(1, 0, n-1, queries[i].i, queries[i].j);
	}


	for(int i = 0; i < q; ++i) printf("%d\n", ans[i]); 

}
