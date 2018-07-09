#include <bits/stdc++.h>

const int N = 100007;
using namespace std;
typedef long long ll;

int v[N];
int seg[4*N];

/*
	Solucao:
	Segtree de produto!
	Normalizar os valores da entrada, ou seja, tornar todo mundo -1, 0 ou 1.
*/

void build(int p, int l, int r) {
	if(l == r) {
		seg[p] = v[l];
	} else {
		int m = (l+r)/2;
		build(2*p, l, m);
		build(2*p+1, m+1, r);
		seg[p] = seg[2*p] * seg[2*p + 1];
	}
}

int query(int p, int l, int r, int a, int b) {
	if(r < a or l > b) return 1;
	if(l >= a and r <= b) return seg[p];
	int m = (l+r)/2;
	return query(2*p, l, m, a, b) * query(2*p+1, m+1, r, a, b);
}

void update(int p, int l, int r, int pos, int val) {
	if(r < pos or l > pos) return;
	if(l == r) { // l = r = pos
		seg[p] = val;
	} else {
		int m =  (l + r)/2;
		update(2*p, l, m, pos, val);
		update(2*p + 1, m+1, r, pos, val);
		seg[p] = seg[2*p] * seg[2*p + 1];
	}
}


int main() {
	ios::sync_with_stdio(false);
	int n;

	while(cin >> n) {
		int k;

		cin >> k;
		for(int i = 1; i <= n; ++i) {
			cin >> v[i];
			if(v[i]) v[i] = v[i]/abs(v[i]); // transforma em 1 ou -1
		}

		build(1, 1, n);
		while(k--) {
			char op;
			cin >> op;

			if(op == 'C') {
				int p, val;
				cin >> p >> val;
				if(val) val = val/abs(val);
				update(1, 1, n, p, val);
			} else {
				int l, r;
				cin >> l >> r;
				int ret = query(1, 1, n, l, r);
				if(ret == 1) cout << "+";
				else if(ret == -1) cout << "-";
				else cout << "0";
			}
		}

		cout << "\n";
	}

	return 0;
}