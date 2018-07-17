#include <bits/stdc++.h>

#define fi first
#define se second
#define mp make_pair

const int N = 200007;

using namespace std;
typedef long long ll;
typedef pair<int, int> ii;

struct frog {
	int l;
	ll r;
	int id;
	
	bool operator< (frog f) const {
		return l < f.l;
	}
};

frog frogs[N];
ll seg[4*N], len[N];
int cnt[N], n;

void build(int p, int l, int r) {
	if(l == r) {
		seg[p] = frogs[l].r;
	} else {
		build(2*p, l, (l+r)/2);
		build(2*p + 1, (l+r)/2 + 1, r);
		seg[p] = max(seg[2*p], seg[2*p+1]);
	}
}

void update(int p, int l, int r, int pos, ll val) {
	if(l > pos or r < pos) return;
	if(l == r) {
		seg[p] = val;
	} else {
		update(2*p, l, (l+r)/2, pos, val);
		update(2*p+1, (l+r)/2 + 1, r, pos, val);
		seg[p] = max(seg[2*p], seg[2*p+1]);
	}
}

ll query(int p, int l, int r, int a, int b) {
	if(l > b or r < a) return -1;
	if(l >= a and r <= b) return seg[p];

	return max(query(2*p, l, (l+r)/2, a, b), query(2*p+1, (l+r)/2 + 1, r, a, b));
}

inline int check(int x, int p) {
	return query(1, 0, n-1, 0, p) >= x;
}

int main() {
	int m, x, l;

	scanf("%d %d", &n, &m);

	for(int i = 0; i < n; ++i) {
		scanf("%d %d", &x, &l);

		frogs[i] = {x, x + l, i};
		len[i] = l;
	}

	sort(frogs, frogs + n);

	build(1, 0, n-1);

	multiset<ii> st;
	for(int i = 0; i < m; ++i) {
		scanf("%d %d", &x, &l);
	
		int lo, hi, mi;
		int pos = upper_bound(frogs, frogs + n, frog{x, 0, 0}) - frogs;
		lo = 0, hi = pos;

		if(hi == 0) continue; // todos os caras tem x maior que o x do inseto, entao o inseto nunca vai ser comido
		while(lo < hi) {
			mi = lo + (hi - lo)/2;

			if(check(x, mi) == 0) lo = mi+1;
			else hi = mi;
		}

		if(lo == pos) { // nao achou ninguem que consegue comer o mosquito
			st.insert(mp(x, l));
		} else {
			cnt[frogs[lo].id]++;
			frogs[lo].r += l;

			// come os insetos que tinham sobrado;
			while(1) {
				auto it = st.lower_bound(mp(frogs[lo].l, 0));
				if(it == st.end() or it->fi > frogs[lo].r) break;
				cnt[frogs[lo].id]++;
				frogs[lo].r += it->se;
				st.erase(it);
			}
			update(1, 0, n-1, lo, frogs[lo].r);
		}
	}

	for(int i = 0; i < n; ++i) len[frogs[i].id] = frogs[i].r - frogs[i].l; // atualiza o len

	for(int i = 0; i < n; ++i) printf("%d %lld\n", cnt[i], len[i]);
}
