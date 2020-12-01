#include <bits/stdc++.h>

#define ll long long
#define all(x) x.begin(),x.end()
#define sz(x) (int)(x.size() )

const int MAXN = 110 ;
const int MAXK = 55 ;
const ll inf = 1e15+10LL ;

using namespace std ;

//Let's do iterative (that's the only way I'm productive)

int n , k ;
int tin[MAXN] , tout[MAXN] , father[MAXN] ;
ll qtdTrees[MAXN] ;
ll pref[MAXN] ;
ll dp[MAXN][MAXN][MAXK] ;
vector< pair<int,ll> > adj[MAXN] ;

int currTime ;
void dfs(int x)
{
	tin[x] = tout[x] = ++currTime ;
	for(auto e : adj[x] ) 
	{
		pref[e.first] = pref[x] + e.second ;
		dfs(e.first) ;
		tout[x] = tout[e.first] ;
	}
}

bool isInside(int child , int parent ) { return tin[child] >= tin[parent] && tout[child] <= tout[parent] ; }

int main()
{

	scanf("%d %d", &n, &k ) ;
	for(int i = 1 , d ; i <= n ; i++ )
	{
		scanf("%lld %d %d", &qtdTrees[i], &father[i], &d ) ;
		adj[ father[i] ].push_back(make_pair(i,(ll)d) ) ;
	}

	dfs(0) ;

	vector<int> outDeg(n+1, 0) ;
	for(int i = 0 ; i <= n ; i++ ) outDeg[i] = sz(adj[i] ) ;

	vector<int> fila ;
	for(int i = 1 ; i <= n ; i++ )
		if(outDeg[i] == 0 ) fila.push_back(i) ;

	ll ans = 0LL ;
	for(int i = 1 ; i <= n ; i++ ) ans += qtdTrees[i] * pref[i] ;

	int ini = 0 ;

	while(ini < sz(fila ) )
	{
		int x = fila[ini++] ;

		if(x)
		{
			qtdTrees[ father[x] ] += qtdTrees[x] ;
			if( (--outDeg[ father[x] ] ) == 0 ) fila.push_back(father[x] ) ;
		}

		for(int ancestor = 0 ; ancestor <= n ; ancestor++ )
		{
			if( !isInside(x, ancestor) ) continue ;

			vector<ll> dpAux(k+1, 0) ;

			for(auto e : adj[x] )
				for(int i = k ; i >= 0 ; i-- )
					for(int j = 0 ; j <= i ; j++ )
						dpAux[i] = min(dpAux[i] , dpAux[i-j] + dp[e.first][ancestor][j] ) ;

			for(int i = 1 ; i <= k ; i++ )
				dp[x][ancestor][i] = dpAux[i] ;

			for(int i = 1 ; i <= k ; i++ ) dpAux[i] = 0 ;

			for(auto e : adj[x] )
				for(int i = k ; i>= 0 ; i-- )
					for(int j = 0 ; j <= i ; j++ )
						dpAux[i] = min(dpAux[i], dpAux[i-j] + dp[e.first][x][j] ) ;

			for(int i = 1 ; i <= k ; i++ )
				dp[x][ancestor][i] = min(dp[x][ancestor][i] , dpAux[i-1] - (pref[x] - pref[ancestor] ) * qtdTrees[x] ) ;
			
		}

	}

	ans += dp[0][0][k] ;

	printf("%lld\n", ans ) ;

}
