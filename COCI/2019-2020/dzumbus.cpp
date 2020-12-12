#include <bits/stdc++.h>
 
#define sz(x) (int)(x.size() )
#define ll long long
 
const int MAXN = 1010 ;
const int inf = 1e9+7 ;
 
using namespace std ;
 
//Don't forget to check during the calculation if you are doing operations with infinity
//We don't want overflow, do we?
 
int N , M , Q ;
int drink[MAXN] , sub[MAXN] ;
int dp0[MAXN][MAXN] , dp1[MAXN][MAXN][2] ;
vector< int > tree[MAXN] ;
bool vis[MAXN] ;
 
void dfs1(int x, int parent )
{
	
	vis[x] = true ;
 
	for(int i = 0 ; i < sz(tree[x] ) ; i++ )
	{
		if( tree[x][i] != parent ) continue ;
 
		swap( tree[x][i], tree[x][ sz(tree[x])-1 ] ) ;
		tree[x].pop_back() ;
 
		break ; 
	}
 
	for(auto e : tree[x] ) dfs1(e, x) ;
 
}
 
void dfs2(int x)
{
 
	//dp0[x][j] means the minimum number of drinks to have j people making exchanges given that x won't be one of them
	//dp1[x][j][0] means the minimum number of drinks to have j people making exchanges given that x will be one of them but their parent won't 
	//dp1[x][j][1] means the minimum number of drinks to have j people making exchanges given that x will be one of them and their parent also will
 
	dp0[x][0] = 0 ;
	dp1[x][1][1] = drink[x] ;
	sub[x] = 1 ;
 
	for(auto e : tree[x] ) 
	{
		dfs2(e) ;
 
		for(int i = sub[x] ; i >= 0 ; i-- )
			for(int j = 1 ; j <= sub[e] ; j++ )
			{
				if( dp0[x][i] + min(dp0[e][j],dp1[e][j][0] ) <= inf )
					dp0[x][i+j] = min( dp0[x][i+j], dp0[x][i] + min(dp0[e][j],dp1[e][j][0]) ) ;
 
				dp1[x][i+j][0] = min( dp1[x][i+j][0], min(dp0[x][i] + dp1[e][j][1], inf) ) ;
				dp1[x][i+j][0] = min( dp1[x][i+j][0] , min(dp1[x][i][0] + min(dp1[e][j][1],dp0[e][j]),inf) ) ;
 
				dp1[x][i+j][1] = min( dp1[x][i+j][1] , min(dp1[x][i][1] + min(dp0[e][j] , dp1[e][j][1] ) , inf ) ) ;
 
			}						
 
		sub[x] += sub[e] ;
	}
 
	for(int i = sub[x] ; i > 0 ; i-- ) dp1[x][i][0] = min( min(dp1[x][i-1][0],dp0[x][i]) + drink[x],  inf ) ;
	dp1[x][0][0] = drink[x] ;
 
	/*printf("About vertex number %d:\n", x) ;
	printf("If I must not give drinks to %d: " , x ) ;
	for(int i = 0 ; i < sub[x] ; i++ ) printf("(%d,%d) ; ", i, dp0[x][i] ) ;
	printf("\nIf I must give drinks to them and I didn't give to my parent: " ) ;
	for(int i = 0 ; i <= sub[x] ; i++ ) printf("(%d,%d) ; ", i, dp1[x][i][0] ) ;
	printf("\nIf I must give drinks to them and I did give to my parent: " ) ;
	for(int i = 0 ; i <= sub[x] ; i++ ) printf("(%d,%d) ; ", i, dp1[x][i][1] ) ;
 
	printf("\n\n") ; */
 
}
 
int main()
{
 
	scanf("%d %d", &N , &M ) ;
	for(int i = 1 ; i <= N ; i++ ) scanf("%d", &drink[i] ) ;
	for(int i = 0 , u,v ; i < M ; i++ )
	{
		scanf("%d %d", &u, &v ) ;
 
		tree[u].push_back(v) ;
		tree[v].push_back(u) ;
	}	
 
	drink[0] = inf ;
 
	for(int i = 0 ; i <= N ; i++ )
		for(int j = 0 ; j <= N ; j++ ) dp0[i][j] = dp1[i][j][0] = dp1[i][j][1] = inf ;
 
	//Getting the connected components
	for(int i = 1 ; i <= N ; i++ )
	{
		if(vis[i] ) continue ;
 
		dfs1(i,-1) ;
		tree[0].push_back(i) ;
	}
 
	dfs2(0) ;
 
	scanf("%d", &Q ) ;
 
	for(int q = 0, x ; q < Q ; q++ )
	{
		scanf("%d", &x ) ;
 
		int l = 2 , r = N , mid , best=0 ;
 
		while( l <= r)
		{
			mid = (l+r)>>1 ;
 
			if( dp0[0][mid] <= x)
			{
				best = mid ;
				l = mid+1 ;
			}
			else r = mid-1 ;
 
		}
 
		printf("%d\n", best ) ;
 
	}
 
}
