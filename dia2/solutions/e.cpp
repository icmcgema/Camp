#include <bits/stdc++.h>

#define mp make_pair
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> ii;

const int N = 1000007;

int v[N];
ii seg[4*N]; // first: resposta 
int zeroes[4*N], ones[4*N], lazy[4*N];

void prop(int p, int l, int r) {
	lazy[p] %= 2;
	if(lazy[p]) {
		swap(ones[p], zeroes[p]);
		swap(seg[p].fi, seg[p].se);

		if(l != r) {
			lazy[2*p]++;
			lazy[2*p + 1]++;
		}
		lazy[p] = 0;
	}
}

void build(int p, int l, int r) {
	if(l == r) {
		zeroes[p] = v[l] == 0;
		ones[p] = v[l] == 1;
		seg[p] = mp(1, 1);
	} else {
		build(2*p, l, (l+r)/2);
		build(2*p+1,(l+r)/2 + 1, r);
		zeroes[p] = zeroes[2*p] + zeroes[2*p+1];
		ones[p] = ones[2*p] + ones[2*p+1];
		seg[p].fi = max(seg[2*p].fi + ones[2*p+1], zeroes[2*p] + seg[2*p+1].fi);
		seg[p].se = max(seg[2*p].se + zeroes[2*p+1], ones[2*p] + seg[2*p+1].se);
	}
}

int cnt(int p, int l, int r, int a, int b, int one) {
	prop(p, l, r);
	if(l > b or r < a) return 0;
	if(l >= a and r <= b) return one? ones[p] : zeroes[p];

	return cnt(2*p, l, (l+r)/2, a, b, one) + cnt(2*p+1, (l+r)/2 + 1, r, a, b, one);
}

int lis(int p, int l, int r, int a, int b) {
	prop(p, l, r);

	if(l > b or r < a) return 0;
	if(l >= a and r <= b) return seg[p].fi;

	return max(cnt(2*p, l, (l+r)/2, a, b, 0) + lis(2*p+1, (l+r)/2 + 1, r, a, b), lis(2*p, l, (l+r)/2, a, b) + cnt(2*p+1, (l+r)/2 + 1, r, a, b, 1));
}

void update(int p, int l, int r, int a, int b) {
	prop(p, l, r);
	if(l > b or r < a) return;
	if(l >= a and r <= b) {
		lazy[p]++;
		prop(p, l, r);
	} else {
		update(2*p, l, (l+r)/2, a, b);
		update(2*p+1, (l+r)/2 + 1, r, a, b);
		zeroes[p] = zeroes[2*p] + zeroes[2*p+1];
		ones[p] = ones[2*p] + ones[2*p+1];
		seg[p].fi = max(seg[2*p].fi + ones[2*p+1], zeroes[2*p] + seg[2*p+1].fi);
		seg[p].se = max(seg[2*p].se + zeroes[2*p+1], ones[2*p] + seg[2*p+1].se);
	}
}	



int main() {
	ios::sync_with_stdio(false);

	int n, m;

	cin >> n >> m;

	for(int i = 0; i < n; ++i) {
		char c;
		cin >> c;
		v[i] = c == '4'? 0 : 1;
	}

	build(1, 0, n-1);

	for(int i = 0; i < m; ++i) {
		string op;
		cin >> op;

		if(op == "count") {
			cout << lis(1, 0, n-1, 0, n-1) << endl;
		} else {
			int l, r;
			cin >> l >> r;
			l--, r--;

			update(1, 0, n-1, l, r);
		}
	}

}