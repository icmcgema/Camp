#include <bits/stdc++.h>

#define pb push_back

using namespace std;
typedef long long ll;

const int N = 100007;

int v[N];
ll seg[4*N];

void build(int p, int l, int r) {
	if(l == r) {
		seg[p] = 0;
	} else {
		build(2*p, l, (l+r)/2);
		build(2*p+1, (l+r)/2+1, r);
		seg[p] = seg[2*p] + seg[2*p+1];
	}
}

ll query(int p, int l, int r, int a, int b) {
	if(l > b or r < a) return 0;
	if(l >= a and r <= b) return seg[p];

	return query(2*p, l, (l+r)/2, a, b) + query(2*p+1, (l+r)/2 + 1, r, a, b);
}

void update(int p, int l, int r, int pos, ll val) {
	if(l > pos or r < pos) return;
	if(l == r) {
		seg[p] = val;
	} else {
		update(2*p, l, (l+r)/2, pos, val);
		update(2*p+1, (l+r)/2+1, r, pos, val);
		seg[p] = seg[2*p] + seg[2*p+1];
	}
}

int main() {
	int n, K;
	scanf("%d %d", &n, &K);

	for(int i = 1; i <= n; ++i) {
		scanf("%d", v + i);
	}

	vector<ll> res, resp1;
	for(int i = 1; i <= n; ++i) {
		res.pb(1);
	}

	for(int k = 1; k <= K; ++k) {
		// calcula numero de subsequencias crescentes que formo com k+1 elementos terminando em pos. 
		// Entao a resposta vai ser a soma de f(K, p) para todo 1 <= p <= n

		build(1, 1, n);
		for(int i = 1; i <= n; ++i) {
			ll ans = query(1, 1, n, 1, v[i]-1);
			resp1.pb(ans);
			update(1, 1, n, v[i], res[i-1]);
		}

		res = resp1;
		resp1.clear();
	}

	ll ans = 0;
	for(int i = 0; i < res.size(); ++i) ans += res[i];

	printf("%lld\n", ans);
}