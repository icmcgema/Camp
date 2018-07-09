#include <cstdio>
#include <cstdlib>
#include <vector>
#define M 100005

using namespace std;
typedef long long ll;

typedef vector<ll> vll;

vll st(4*M);
vll lazy(4*M);
int n;

void propagate(int p, int l, int r){
	if (lazy[p]) {
		st[p] += ll((r-l+1))*lazy[p];

		if (l != r){
			lazy[p<<1] += lazy[p];
			lazy[p<<1|1] += lazy[p];
		}

		lazy[p] = 0;
	}
}

void update(int p, int l, int r, int a, int b, long long v){
	propagate(p, l, r);
	if (b < l || a > r) return ;
	if (l >= a && r <= b){
		st[p] += ll((r-l+1))*v;

		if (l != r){
			lazy[p<<1] += v;
			lazy[p<<1|1] += v;
		}

		return;
	}

	update(p<<1, l, (l+r)/2, a, b, v);
	update(p<<1|1, (l+r)/2+1, r, a, b, v);
	st[p] = st[p<<1] + st[p<<1|1];
}

ll rsq(int p, int l, int r, int a, int b){
	propagate(p, l, r);
	if (b < l || a > r) return 0;
	if (l >= a && r <= b) return st[p];
	return rsq(p<<1, l, (l+r)/2, a, b ) 
		+ rsq(p<<1|1, (l+r)/2+1, r, a, b );
}

int main(){

	int t;
	scanf("%d", &t );

	while (t--){
		int c;
		scanf("%d%d", &n, &c );
		st.assign( 4*n, 0 );
		lazy.assign( 4*n, 0 );

		for (int i = 0; i<c;i++){
			int o,p,q;
			ll v;
			scanf("%d", &o );
			scanf("%d%d", &p, &q );
			p--;q--;

			if (o == 0){
				scanf("%lld", &v  );
				update( 1, 0, n-1, p,q,(long long )v );
			}
			else{
				printf("%lld\n", rsq(1,0,n-1,p,q ));
			}
		}
	}

	return 0;
}
