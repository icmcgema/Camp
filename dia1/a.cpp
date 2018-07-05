#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second
#define mp make_pair

using namespace std;
const int N = 1000007, inf = 0x3f3f3f3f;

typedef pair<int, int> ii;
typedef long long ll;


int v[N], memo[N][2];
int n;

int solve(int p, int odd) {
	if(p == n) {
		if(odd == 0) return -inf;
		else return 0;
	}

	int & st = memo[p][odd];

	if(st == inf) {
		st = max(v[p] + solve(p+1, (odd + (v[p]%2+2)%2)%2 ), solve(p+1, odd));
	}	

	return st;
}

int main() {
	memset(memo, inf, sizeof memo);
	ios::sync_with_stdio(false);
	
	cin >> n;

	for(int i = 0; i < n; ++i) {
		cin >> v[i];
	}

	cout << solve(0, 0) << endl;
}