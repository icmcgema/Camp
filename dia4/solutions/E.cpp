#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long

struct Point {
	ll x, y;
	int label;

	Point() {}

	Point(ll _x, ll _y, int la){
		x = _x;
		y = _y;
		label = la;
	}

	bool operator <(const Point &p) const {
		if(x == p.x) return y < p.y;
		return x < p.x;
	}
};

ll cross(const Point &O, const Point &A, const Point &B)
{
	return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

vector<Point> convex_hull(vector<Point> P)
{
	int n = P.size(), k = 0;
	vector<Point> H(2*n);

	sort(P.begin(), P.end());

	// Lower hull
	for (int i = 0; i < n; ++i) {
		while (k >= 2 && cross(H[k-2], H[k-1], P[i]) < 0) k--;
		H[k++] = P[i];
	}

	// Upper hull
	for (int i = n-2, t = k+1; i >= 0; i--) {
		while (k >= t && cross(H[k-2], H[k-1], P[i]) < 0) k--;
		H[k++] = P[i];
	}

	H.resize(k-1);
	return H;
}

int n, m;
vector<Point> p;

int main(void){
	scanf("%d", &n);

	ll x, y;
	for(int i = 0; i < n; i++){
		scanf("%lld%lld", &x, &y);
		p.pb(Point(x,y,0));
	}

	scanf("%d", &m);
	for(int i = 0; i < m; i++){
		scanf("%lld%lld", &x, &y);
		p.pb(Point(x,y,1));
	}

	vector<Point> hull = convex_hull(p);

	for(int i = 0; i < hull.size(); i++){
		if(hull[i].label == 1){
			printf("NO\n");
			return 0;
		}
	}

	printf("YES\n");

	return 0;
}