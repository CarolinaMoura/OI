#include <bits/stdc++.h>
 
#define ll long long
#define sz(x) (int)(x.size())
#define all(x) x.begin(),x.end()
 
const int MAX = 1e6+10 ;
const int MAXN = 1010 ;
 
using namespace std ;
 
char C ;
void read(int &num)
{
	num = 0 ;
	for(C = getchar() ; (C > 47 && C < 58 ) ; C = getchar() )
		num = num*10 + C - 48 ;
}
 
int N , M ;
int minDiff = MAX , lo = -1 , hi = -1 ;
vector<int> trash[MAXN] , adj[MAX] , revAdj[MAX]  ;
int height[MAX] , par[MAX] , comp[MAX] ;
int code[MAXN][MAXN] ;
bool mat[MAXN][MAXN] ;
bool vis[MAX],isOn[MAX] ;
 
vector<int> List ;
void dfs1(int x)
{	
	vis[x] = true ;
	for(auto e : adj[x] )
		if(!vis[e] ) dfs1(e) ;
	List.push_back(x) ;
}
  
void dfs2(int x , int depth )
{
	height[x] = depth ;
	isOn[x] = true ;
 
	for(auto e : adj[x] ) 
	{
		if( isOn[e] && height[x] - height[e] < minDiff )
		{
			minDiff = height[x] - height[e] ;
			lo = x ;
			hi = e ;
		}
		if(height[e]) continue ;
	 
		par[e] = x ;
		dfs2(e,depth+1) ;
 
	}
 
	isOn[x] = false ;
}
 
int main()
{
 
	read(N) ; read(M) ;
	for(int i = 0 , u , v ; i < M ; i++ )
	{
		read(u) ; read(v) ;
		--u ; --v ;
	
		mat[u][v] = mat[v][u] = true ;
 
		trash[u].push_back(v) ;
		trash[v].push_back(u) ;
	}
 
	for(int i = 0 , c = 0 ; i < N ; i++  )
		for(int j = 0 ; j < N ; j++ , c++ ) code[i][j] = c ;
 
	for(int i = 0  ; i < N ; i++ )
		for(int j = 0 ; j < N ; j++ )
		{
			if( i == j || !mat[i][j] ) continue ;
 
			for(auto k : trash[j] )
				if(!mat[i][k] && i != k ) adj[ code[i][j] ].push_back( code[j][k] ) ; 
		}
 
	for(int i = 0 ; i < N ; i++ )
		for(int j= 0 ; j < N ; j++ )
		{
			if( i == j || vis[ code[i][j] ] ) continue ;
			dfs1(code[i][j] ) ;
		}
 
	for(int i = 0 ; i < sz(List) ; i++ )
	{
		if(height[List[i]]) continue ;
		
		dfs2(List[i] ,1 ) ;
 
		if( lo != -1 ) break ;
 
	} 
	
	if( lo == -1 )
	{
		printf("no\n") ;
		return 0 ;
	}
 
	while(lo != par[hi] )
	{
		printf("%d ", (lo%N)+1 ) ;
		lo = par[lo] ;
 
	}
}
