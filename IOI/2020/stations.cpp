#include "stations.h"
#include <bits/stdc++.h>
 
#define lp(i,a,b) for(int i = a; i < b;  i++)
#define debug //printf
#define ff first
#define ss second
#define mk make_pair
#define ll long long
#define pii pair<int,int>
#define all(x) x.begin(),x.end()
#define sz(x) (int)(x.size())
 
const int MAXN = 1010 ;
 
using namespace std ;
 
int tin[MAXN] , tout[MAXN] ;
vector<int> adj[MAXN] ;
 
int currTime = -1 ;
void dfs(int x, int father)
{
	tin[x] = tout[x] = ++currTime ;
	for(auto e :adj[x])
	{
		if(e == father) continue ;
 
		dfs(e,x) ;
 
		tout[x] = ++currTime ;
 
	}
 
	if( (tin[x]&1) != (tout[x]&1) ) tout[x] = ++currTime ;
 
}
 
std::vector<int> label(int n, int k, std::vector<int> u, std::vector<int> v) {
	
	for(int i = 0 ; i < n ; i++ ) adj[i].clear() ;
	currTime = -1 ;
 
	for(int i = 0 ; i <n-1 ; i++ )
	{
		adj[ u[i] ].push_back(v[i]) ;
		adj[v[i]].push_back(u[i]) ;
	}
 
	dfs(0,-1) ;
 
 
	vector<int> labels(n) ;
 
	map<int,int> mp ;
 
	for(int i = 0 ; i < n ; i++ )
	{
		if(tin[i]&1) labels[i] = tin[i] ;
		else labels[i] = tout[i] ;
 
		mp[labels[i]] = 0 ;
	}
 
	int Key = 0 ;
	for(auto &e : mp ) e.ss = Key++ ;
 
	lp(i,0,n) labels[i] = mp[labels[i]] ;
 
 
	return labels ;
 
}
 
int find_next_station(int s, int t, std::vector<int> c) {
	
	for(auto e: c ) 
		if(e == t) return t ;
 
	bool sOdd = ( s < c[0] ) ;
 
	if( !sOdd )
	{
		//ou seja, tenho os tin's
 
		if(t > s ) return c[0] ;
 
		for(int  i = sz(c) - 1 ; i>= 0 ; i-- )
			if( c[i] < t ) return c[i] ;
 
		return c[0] ;
 
	}
	else 
	{
		//tenho os tout's
 
		if( t < s ) return c[ sz(c)-1 ] ;
 
		for(int i = 0 ; i < sz(c) ; i++ )
			if( c[i] > t ) return c[i] ;
 
		return c[ sz(c)-1 ] ;
 
	}
 
}
