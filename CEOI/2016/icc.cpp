#include "icc.h"
#include <bits/stdc++.h>
 
#define sz(x) (int)(x.size())
#define ll long long
#define ff first
#define ss second
 
const int MAX = 110 ;
 
using namespace std ;
 
int N ;
int dsu[MAX] ;
vector<int> a , b ;
 
int find(int x) { return dsu[x] = (x == dsu[x]) ? x : find(dsu[x]) ; }
void join(int x, int y)
{
	x = find(x) ;
	y = find(y) ;
 
	if(x == y) return ;
 
	if( x < y ) dsu[y] = x ;
	else dsu[x] = y ;
}
 
bool ask()
{
	if( !sz(a) || !sz(b) ) return false ;
 
	int A[ sz(a) ] ;
	int B[sz(b)] ;
 
	for(int i = 0 ; i < sz(a) ; i++ ) A[i] = a[i]+1 ;
	for(int i = 0 ; i < sz(b) ; i++ ) B[i] = b[i]+1 ;
 
	return query( sz(a) , sz(b) , A , B ) ;
 
}
 
void solve()
{
	vector< vector<int> > vec ;
 
	for(int i = 0 ; i < N ; i++ )
	{
		if(i != find(i)) continue ;
 
		vec.push_back(vector<int>()) ;
 
		for(int j = 0 ; j < N ; j++ )
			if( find(j) == i ) vec.back().push_back(j) ;
	}
 
	int H = sz(vec) , x = 0 ;
 
	for(int i = 0 ; (1<<i) < H ; i++ )
	{
		a.clear() ;
		b.clear() ;
 
		for(int j = 0 ; j < H ; j++ )
		{
			if( j&(1<<i) ) a.insert(a.end() , vec[j].begin() , vec[j].end() ) ;
			else b.insert( b.end() , vec[j].begin() , vec[j].end() ) ;
		}
 
		if( ask() ) x ^= (1<<i) ;
	}
 
	vector< pair<int,int> > pairs ;
 
	for(int i = 0 ; i < H ; i++ )
		if( (i^x) < H && i < (i^x) ) pairs.push_back( make_pair(i, i^x) ) ;
 
	while( sz(pairs) > 1 )
	{
 
		a.clear() ;
		b.clear() ;
 
		for(int i = 0 ; i < sz(pairs)/2 ; i++ ) 
		{
			a.insert( a.end() , vec[ pairs[i].first ].begin() , vec[ pairs[i].first ].end() ) ;
			b.insert( b.end() , vec[ pairs[i].second ].begin() , vec[ pairs[i].second ].end() ) ;
		}
 
		if( ask() ) pairs = vector<pair<int,int> >( pairs.begin() , pairs.begin()+sz(pairs)/2 ) ;
		else pairs = vector<pair<int,int> >( pairs.begin()+sz(pairs)/2 , pairs.end() ) ;
 
	}
 
	vector<int> c = vector<int>( vec[ pairs[0].first ].begin() , vec[ pairs[0].first ].end() ) ;
	vector<int> d = vector<int>( vec[pairs[0].second].begin()  , vec[pairs[0].second].end() ) ;
 
	while( true )
	{
		if( sz(c) < sz(d) ) swap(c,d) ;
		if( sz(c) == 1 )
		{
			setRoad(c[0]+1, d[0]+1) ;
			join(c[0] , d[0]) ;
			return ;
		}
 
		a.clear() ;
		b.clear() ;
 
		a = vector<int>( c.begin() ,c.begin()+sz(c)/2 ) ;
		b = d ;
 
		if(ask()) c = a ;
		else c = vector<int>( c.begin()+sz(c)/2 , c.end() ) ;
	}
 
}
 
void run(int n)
{
	N = n ;
 
	for(int i = 0 ; i < N ; i++  ) dsu[i] = i ;
	for(int i = 0 ; i < N-1 ; i++ ) solve() ;
}
