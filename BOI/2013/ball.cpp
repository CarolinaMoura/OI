#include <bits/stdc++.h>
 
#define debug printf
#define all(x) x.begin(),x.end()
#define sz(x) (int)(x.size() )
#define ll long long
 
const int MAXN = 1e5+10 ;
const int LOG = 20 ;
 
using namespace std ;
 
int N , Q , root ;
int dp[LOG][MAXN] ;
int tout[MAXN] , lvl[MAXN] , sub[MAXN] ;
bool hasBall[MAXN] ;
vector<int> adj[MAXN] ;
set<pair<int,int > > available;
 
int currTime ;
void dfs1(int x)
{
 
	for(int i = 1 ; i < LOG ; i++ )
		if( dp[i-1][x] != -1 )
			dp[i][x] = dp[i-1][ dp[i-1][x] ] ;
 
	sub[x] = x ;	      	
 
	for(auto e : adj[x] )
	{
		dp[0][e] = x ;
		lvl[e] = lvl[x] + 1 ;
		dfs1(e) ;
		sub[x] = min(sub[x] , sub[e] ) ;
	}
 
}
 
void dfs2(int x)
{
 
	sort(all(adj[x] ), [&](int i, int j ) { return sub[i] < sub[j] ; } ) ;
 
	tout[x] = ++currTime ;
 
	for(auto e : adj[x] )
	{
		dfs2(e) ;
		tout[x] = ++currTime ;
	}
 
	available.insert( make_pair( tout[x] , x ) ) ;
 
}
 
int main()
{
 
	scanf("%d %d", &N, &Q ) ;
	for(int i = 1 , parent ; i <= N ; i++ )
	{
		scanf("%d", &parent ) ;
 
		if( parent == 0 ) root = i ;
		else adj[ parent ].push_back(i) ;
	}
 
	for(int i = 0 ; i < LOG ; i++ )
		for(int j = 1 ; j <= N ; j++ ) dp[i][j] = -1 ;
 
	dfs1(root) ;
	dfs2(root) ;
 
	for(int trash = 0, type , k ; trash < Q ; trash++ )
	{
		scanf("%d %d", &type, &k ) ;
 
		if(type == 1 )
		{
			int resp = -1 ;
			while( k )
			{
				resp = available.begin()->second ;
				hasBall[resp] = true ;
				available.erase( available.begin() ) ;
				k-- ;
			}
 
			printf("%d\n", resp ) ;
 
		}
		else 
		{
			int x = k ;
 
			for(int i = LOG-1 ; i >= 0 ; i-- )
			{
				if( dp[i][x] == -1 ) continue ;
				if( hasBall[ dp[i][x] ] ) x = dp[i][x] ;		
			}
 
			available.insert( make_pair( tout[x], x ) ) ;
			hasBall[x] = false ; 
			printf("%d\n", lvl[k]-lvl[x] ) ;
		}
 
	}
 
}
