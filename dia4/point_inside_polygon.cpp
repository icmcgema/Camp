#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Point{
    ll x, y;
    
    Point() {}
    
    Point(ll x, ll y){
        this->x = x;
        this->y = y;
    }
    
    Point operator+(Point p2) const{
        return Point(x + p2.x, y + p2.y);
    }
    
    Point operator-(Point p2) const{
        return Point(x - p2.x, y - p2.y);
    }
    
    Point operator*(ll c) const{
        return Point(x * c, y * c);
    }
    
    ll operator*(Point p) const{
        return x*p.x + y*p.y;
    }
    
    ll operator^(Point p) const{
        return x*p.y - y*p.x;
    }
};

bool inside_triangle(Point a, Point b, Point c, Point q){
    Point u = b-a;
    Point v = c-b;
    Point w = a-c;
    
    ll cross1 = (q-a)^u;
    ll cross2 = (q-b)^v;
    ll cross3 = (q-c)^w;
    
    if(cross1 >= 0 and cross2 >= 0 and cross3 >= 0)
        return 1;
    if(cross1 <= 0 and cross2 <= 0 and cross3 <= 0)
        return 1;
    return 0;
}

bool binsearch(vector<Point>& poly, Point p){
    int l = 1, r = int(poly.size())-1;
    
    while(l < r){
        int mid = (l+r)/2;
        
        Point u = poly[mid] - poly[0]; // lado
        Point v = p-poly[0]; // origem -> p
        
        ll cross = u^v;
        
        u = poly[mid+1] - poly[0];
        ll cross2 = u^v;
        
        if(cross >= 0 and cross2 <= 0){
            return inside_triangle(poly[0], poly[mid], poly[mid+1], p);
        }
        else if(cross > 0 and cross2 > 0){ // os cortes dependem se os pontos estiverem ordenados em sentido horário ou anti-horário
            l = mid+1;
        }
        else{
            r = mid;
        }
    }
    
    return 0;
}