#include <bits/stdc++.h>

#define pb push_back
#define all(x) x.begin(),x.end()
#define sz(x) (int)(x.size() )
#define lp(i,a,b) for(int i = a ; i < b ; i++ )
#define ll long long

const int MAXN = 5e5+10 ;

using namespace std ;

int n , m , s , p ;
int mySCC[MAXN] , dp[MAXN] , deg[MAXN] , cash[MAXN] ;
int valueSCC[MAXN] ;
vector<int> adj[MAXN], revAdj[MAXN] , graphSCC[MAXN] ;
bool vis[MAXN] , isRestaurant[MAXN] , resSCC[MAXN] ;

vector<int> List ;
int scc ;

void dfs(int x)
{
	vis[x] = true ;

	for(auto e : adj[x] )
		if(!vis[e] ) dfs(e) ;

	List.push_back(x) ;

}

void findSCC(int x)
{
	mySCC[x] = scc ;
	valueSCC[scc] += cash[x] ;
	resSCC[scc] |= isRestaurant[x] ;
	vis[x] = true ;

	for(auto e : revAdj[x] )
		if(!vis[e] ) findSCC(e) ;

}

int main()
{
	
	scanf("%d %d", &n, &m ) ;

	for(int i= 0 , a , b ;i < m ; i++ )
	{
		scanf("%d %d", &a, &b ) ;

		adj[a].push_back(b) ;
		revAdj[b].push_back(a);

	}

	for(int i = 1 ; i <= n ; i++ ) scanf("%d", &cash[i] ) ;

	scanf("%d %d", &s, &p ) ;
	for(int i = 0 , x ; i <p ; i++ ) 
	{
		scanf("%d", &x ) ;
		isRestaurant[x] = true ;
	}

	for(int i= 1 ; i<= n ; i++ )
		if(!vis[i] ) dfs(i) ;

	for(int i = 1 ;i <= n ; i++ ) vis[i] = false ;

	for(int i = n-1 ; i >= 0 ; i-- ) 
		if(!vis[List[i]]) 
		{
			scc++ ;
			findSCC(List[i]) ;
		}

	lp(i,1,n+1)
		for(auto e : adj[i] )
		{
			if(mySCC[e] == mySCC[i] ) continue ;

			graphSCC[ mySCC[e] ].push_back(mySCC[i]) ;
			deg[ mySCC[i] ]++ ;
		}

	vector<int> fila ;
	int ini = 0 ;

	for(int i = 1 ; i <= scc ; i++ )
		if( deg[i] == 0 ) fila.push_back(i) ;
  	
  	memset(dp, -1, sizeof dp ) ;

	while(ini < sz(fila) )
	{
		int x = fila[ini++] ;

		if(resSCC[x] && dp[x] == -1 ) dp[x] = valueSCC[x] ;
		else if( dp[x] != -1 ) dp[x] += valueSCC[x] ;

		for(auto e : graphSCC[x] )
		{
			dp[e] = max(dp[e] , dp[x] ) ;
			if( (--deg[e]) == 0 ) fila.pb(e) ;
		}

	}

	printf("%d\n", dp[ mySCC[s] ] ) ;

}
