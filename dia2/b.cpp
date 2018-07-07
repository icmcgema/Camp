#include <bits/stdc++.h>

const int N = 100007;
using namespace std;
typedef long long ll;

ll v[N];
ll seg[N*4], lazy[N*4];

/*
	Implementacao de uma seg tree de soma, com lazy update
*/

void build(int p, int l, int r) {
	lazy[p] = 0;
	if(l == r) {
		seg[p] = v[l];
	} else {
		int m = (l+r)/2;
		build(2*p, l, m);
		build(2*p+1, m+1, r);
		seg[p] = seg[2*p] + seg[2*p + 1];
	}
}

void prop(int p, int l, int r) {
	if(lazy[p]) {
		seg[p] += lazy[p] * ll(r - l + 1);
		if(l < r) {
			lazy[2*p] += lazy[p];
			lazy[2*p+1] += lazy[p];
		}

		lazy[p] = 0;
	}
}

ll query(int p, int l, int r, int a, int b) {
	if(r < a or l > b) return 0;
	prop(p, l, r);
	if(l >= a and r <= b) return seg[p];
	int m = (l + r)/2;
	return query(2*p, l, m, a, b) + query(2*p + 1, m+1, r, a, b);
}

void update(int p, int l, int r, int a, int b, ll v) {
	prop(p, l, r);
	if(r < a or l > b) return;
	if(l >= a and r <= b) {
		lazy[p] += v;
		prop(p, l, r);
		return;
	}

	int m = (l + r)/2;
	update(2*p, l, m, a, b, v);
	update(2*p + 1, m+1, r, a, b, v);
	seg[p] = seg[2*p] + seg[2*p+1];
}


int main() {
	ios::sync_with_stdio(false);
	int t; cin >> t;

	while(t--) {
		int n, c;
		cin >> n >> c;

		for(int i = 1; i <= n; ++i) {
			v[i] = 0;
		}

		build(1, 1, n);
		while(c--) {
			int op; cin >> op;

			if(op == 0) {
				int a, b, val;
				cin >> a >> b >> val;

				update(1, 1, n, a, b, val);
			} else {
				int a, b;
				cin >> a >> b;
				cout << query(1, 1, n, a, b) << endl;
			}
		}
	}

	return 0;
}