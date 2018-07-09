#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define For(i,a,b) for(int (i)=(a);(i) < (b); ++(i))

struct point{
	ll x, y;
	int id;

	point() {}

	point(ll x, ll y){
		this->x = x;
		this->y = y;
	}

	bool operator<(const point& b) const{
		if(x == b.x) return y < b.y;
		return x < b.x;
	}

	point operator-(const point& b) const{
		return point(x-b.x, y-b.y);
	}
};

point p[8];

ll dist(point a, point b){
	return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y); 
}

ll dot(point a, point b){
	return a.x*b.x + a.y*b.y;
}

bool is_sqr(point p[]){
	ll len1 = dist(p[0], p[1]);
	ll len2 = dist(p[1], p[2]);
	ll len3 = dist(p[2], p[3]);
	ll len4 = dist(p[3], p[0]);

	if(len1 != len2 or len1 != len3 or len1 != len4) return 0;
	if(dot(p[1]-p[0], p[2]-p[1]) != 0) return 0;
	if(dot(p[2]-p[1], p[3]-p[2]) != 0) return 0;
	if(dot(p[3]-p[2], p[0]-p[3]) != 0) return 0;
	if(dot(p[0]-p[3], p[1]-p[0]) != 0) return 0;
	return 1;
}

bool is_rec(point p[]){
	ll len1 = dist(p[0], p[1]);
	ll len2 = dist(p[1], p[2]);
	ll len3 = dist(p[2], p[3]);
	ll len4 = dist(p[3], p[0]);

	if(len1 != len3 or len2 != len4) return 0;
	if(dot(p[1]-p[0], p[2]-p[1]) != 0) return 0;
	if(dot(p[2]-p[1], p[3]-p[2]) != 0) return 0;
	if(dot(p[3]-p[2], p[0]-p[3]) != 0) return 0;
	if(dot(p[0]-p[3], p[1]-p[0]) != 0) return 0;
	return 1;
}

int main(void){
	ios_base::sync_with_stdio(false);
	
	For(i,0,8){
		cin >> p[i].x >> p[i].y;
		p[i].id = i+1;
	}

	sort(p, p+8);
	bool res = 0;
	do{
		if(is_sqr(p) and is_rec(p+4)){
			res = 1;
			break;
		}
	
	}while(next_permutation(p, p+8));
	
	if(res){
		cout << "YES" << endl;
		For(i,0,4){
			cout << p[i].id << " ";
		}
		cout << endl;
		For(i,4,8){
			cout << p[i].id << " ";
		}
		cout << endl;
	}
	else{
		cout << "NO" << endl;
	}

	return 0;
}