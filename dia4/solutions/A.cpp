#include <bits/stdc++.h>
using namespace std;
#define INF 1000000000000000LL
#define M 1000000007
#define For(i,a,b) for(int (i)=(a);(i) < (b); ++(i))
#define mp make_pair
#define pb push_back 
#define fi first
#define se second
#define endl "\n"
#define PI acos(-1)
#define EPS 1e-9
#define fastcin ios_base::sync_with_stdio(false);
typedef long long ll;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef pair<int,int> ii;
typedef complex<double> base;

ll gcd (ll a, ll b) {
	if (!b)
		return a;
	else
		return gcd(b, a%b);
}

class Point {
public:
	ll x, y;

	Point () { }

	Point (double x, double y) {
		this->x = x;
		this->y = y;
	}

	/**/
	bool operator == (const Point &b) const {
		return (abs (x - b.x) < EPS and abs (y - b.y) < EPS);
	}

	/**/
	bool operator < (const Point &b) const {
		return ((x < b.x) or ((x == b.x) and y < b.y));
	}

	//Produto vetorial
	ll operator ^ (const Point &b) const {
		return (this->x * b.y) - (this->y * b.x); 
	}

	//Produto escalar
	ll operator * (const Point &b) const {
		return (this->x * b.x) + (this->y * b.y);
	}

	/**/
	Point operator * (double k) {
		return Point (x*k, y*k);
	}

	Point operator / (double k) {
		if (k == 0.0) cout << "Class Point (operador /): divisao por zero" << endl;
		return Point (x/k, y/k);
	}
	
	/**/
	Point operator + (const Point &b) const {
		return Point (x + b.x, y + b.y);
	}

	/**/
	Point operator - (const Point &b) const {
		return Point (x - b.x, y - b.y);
	}

	/**/
	double len () {
		return sqrt (x*x + y*y);
	}

	/*Distancia ponto a ponto*/
	double dpp (const Point &b) {
		return ((*this)-b).len();
	}

	/*Projecao*/
	double proj (Point &b) {
		return ((*this)*b)/(b.len()*b.len());
	}

	Point norm () {
		return Point (x/this->len(), y/this->len());
	}
};

const int N = 100002;
int n;
Point p[N];

bool check(){
	vector<Point> l1, l2;
	l1.pb(p[0]);
	l1.pb(p[1]);

	Point v1 = p[1]-p[0], v2;

	for(int i = 2; i < n; i++){
		v2 = p[i]-p[0];
		if((v1^v2) == 0){
			l1.pb(p[i]);
		}
		else{
			l2.pb(p[i]);
		}
	}

	if(l2.size() <= 2){
		return 1;
	}

	v1 = l2[1] - l2[0];
	for(int i = 2; i < l2.size(); i++){
		v2 = l2[i] - l2[0];
		if((v1^v2) != 0){
			return 0;
		}
	}

	return 1;
}

int main(void){
	scanf("%d", &n);

	for(int i = 0; i < n; i++){
		scanf("%lld%lld", &p[i].x, &p[i].y);
	}

	if(n <= 3){
		printf("YES\n");
		return 0;
	}

	bool ok = check();

	swap(p[1], p[2]);
	ok |= check();

	swap(p[0], p[2]);
	ok |= check();

	if(ok){
		printf("YES\n");
	}
	else{
		printf("NO\n");
	}

	return 0;
}