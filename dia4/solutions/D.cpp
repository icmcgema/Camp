#include <bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f
#define M 1000000007
#define For(i,a,b) for(int (i)=(a);(i) < (b); ++(i))
#define mp make_pair
#define pb push_back 
#define fi first
#define se second
#define endl "\n"
#define PI acos(-1)
#define fastcin ios_base::sync_with_stdio(false);
typedef long long ll;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef pair<int,int> ii;
typedef complex<double> base;

struct Point{
	int x, y;

	Point () {}

	Point(int x_, int y_){
		x = x_;
		y = y_;
	}

	Point operator-(const Point& b) const{
		return Point(x-b.x, y-b.y);
	}

	int operator^(const Point& b) const{
		return x*b.y - y*b.x;
	}
};

int n, m, k;
vector<Point> q1, q2;

int is_inside(vector<Point>& poly, Point p){
	int pos = 0, neg = 0;
	for(int i = 0; i < poly.size(); i++){
		Point u = poly[i]-p;
		Point v = poly[(i+1)%poly.size()] - poly[i];
		int cross = u^v;
		if(cross > 0) pos++;
		if(cross < 0) neg++;
	}

	if(pos > 0 and neg > 0) return 0;

	return 1;
}

int main(void){
	int x, y;

	for(int i = 0; i < 4; i++){
		scanf("%d%d", &x, &y);
		q1.emplace_back(2*x, 2*y);
	}

	for(int i = 0; i < 4; i++){
		scanf("%d%d", &x, &y);
		q2.emplace_back(2*x, 2*y);
	}

	int cnt = 0;
	for(int i = 0; i < 4; i++){
		int flag = is_inside(q2, q1[i]);
		// printf("flag = %d\n", flag);
		cnt += flag;
	}

	for(int i = 0; i < 4; i++){
		int flag = is_inside(q1, q2[i]);
		cnt += flag;
	}

	Point center1, center2;
	if(q1[0].x == q1[1].x){
		center1.y = (q1[0].y + q1[1].y)/2;
	}
	else{
		center1.y = (q1[0].y + q1[2].y)/2;
	}

	if(q2[0].x == q2[1].x){
		center2.y = (q2[0].y + q2[1].y)/2;
	}
	else{
		center2.y = (q2[0].y + q2[2].y)/2;
	}

	if(q1[0].y == q1[1].y){
		center1.x = (q1[0].x + q1[1].x)/2;
	}
	else{
		center1.x = (q1[0].x + q1[2].x)/2;
	}

	if(q2[0].y == q2[1].y){
		center2.x = (q2[0].x + q2[1].x)/2;
	}
	else{
		center2.x = (q2[0].x + q2[2].x)/2;
	}

	cnt += is_inside(q2, center1);
	cnt += is_inside(q1, center2);

	if(cnt > 0){
		printf("YES\n");
	}
	else{
		printf("NO\n");
	}

	return 0;
}