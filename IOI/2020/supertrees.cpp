#include "supertrees.h"
#include <bits/stdc++.h>
 
#define sz(x) (int)(x.size() )
 
const int MAXN = 1010 ;
 
using namespace std ;
 
int pai[MAXN] ;
 
int find(int x )
{
	if( x == pai[x] ) return x ;
	return pai[x] = find(pai[x] ) ;
}
 
void join(int x, int y )
{
 
	x = find(x) ;
	y = find(y) ;
 
	if(x == y ) return ;
 
	if(rand() % 2 ) pai[x] = y ;
	else pai[y] = x ;
 
}
 
int construct( vector< vector<int> > p ) {
 
	int n = sz(p) ;
 
	for(auto i : p )
		for(auto j : i )
			if( j == 3 ) return 0 ;
 
	vector< vector<int> > componentes(n, vector<int>() ) ;
	vector< vector<int> > graph(n, vector<int>(n,0) ) ;
 
	for(int i  =0  ; i < n ; i++ ) pai[i] = i ;
 
	for(int i = 0 ; i < n ; i++ )
		for(int j = 0 ; j < n ; j++ )
			if(p[i][j] ) join(i,j) ;
 
	for(int i = 0 ; i < n ; i++ )
		componentes[ find(i) ].push_back(i) ;
 
	vector< vector<int> > tree(n, vector<int>() ) ;
 
	for(int i = 0 ; i < n ; i++ ) pai[i] = i ;
 
	for(int i = 0 ; i < n ; i++ )
	{
		for(int j1 : componentes[i] )
			for(int j2 : componentes[i] )
			{
				if( p[j1][j2] == 0 )  return 0 ;
				if(p[j1][j2] == 1 ) join(j1,j2) ; 
			}
 
		vector<int> cycle ;
 
		for(int j : componentes[i] )
		{
			tree[find(j)].push_back(j) ;
			if(find(j) == j ) cycle.push_back(j) ;
		}
 
		if(sz(cycle) == 2 ) return  0 ;
		if(sz(cycle) == 1 ) continue ;
 
		for(int j = 0 , nxt = 1 ; j < sz(cycle) ; j++ , nxt++ )
		{
			if(nxt == sz(cycle) ) nxt = 0 ;
 
			graph[ cycle[j] ][ cycle[nxt] ]  = graph[ cycle[nxt] ][ cycle[j] ] = 1 ;
 
		}
		
	}
 
	for(int i = 0 ; i < n ; i++ )
	{
 
		if( sz(tree[i]) == 0 ) continue ;
 
	  int rep = tree[i][0] ;
 
	  for(int j = 1 ; j < sz(tree[i] ) ; j++ ) graph[rep][tree[i][j]] = graph[ tree[i][j] ][rep] = 1 ;
 
	}
 
	build(graph) ;
 
	return 1;
}
