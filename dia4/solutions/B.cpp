#include <bits/stdc++.h>
using namespace std;

pair <long double, int> p[100005];
int n, x, y, a = 1 , b = 2;

int main(void){
	ios::sync_with_stdio(false);

	cin >> n;

	for(int i = 1; i <= n; i++){
		cin >> x >> y;
		p[i].first = atan2l(y, x);
		p[i].second = i;
	}

	sort(&p[1], &p[n+1]);

	long double minn = 2*acos(-1);
	for(int i = 1; i < n; i++){
		long double ang = p[i+1].first - p[i].first;
		while(ang > acos(-1)) ang -= 2*acos(-1);
		while(ang < -acos(-1)) ang += 2*acos(-1);
		if(ang < 0) ang *= -1;
		if(ang < minn){
			minn = ang;
			a = p[i].second;
			b = p[i+1].second;
		}
	}

	long double ang = p[n].first - p[1].first;
	while(ang > acos(-1)) ang -= 2*acos(-1);
	while(ang < -acos(-1)) ang += 2*acos(-1);
	if(ang < 0) ang *= -1;
	if(ang < minn){
		minn = ang;
		a = p[n].second;
		b = p[1].second;
	}

	cout << a << " " << b << endl;

	return 0;
}