#include <bits/stdc++.h>

#define ll long long
#define sz(x) (int)(x.size() )
#define all(x) x.begin(),x.end()

const int MAXN = 1e5+10 ;

using namespace std ;

int N , M ;
int deg[MAXN] ;
ll c[MAXN] , val[MAXN] ;
vector< pair<int,int> > cycle ;
vector< pair<int,int> > adj[MAXN] ;

void dfs(int x)
{
	deg[x]= 0 ;
	cycle.push_back( make_pair(x,0) ) ;

	for(auto e : adj[x] )
	{
		if(!deg[e.first] ) continue ;

		cycle.back().second = e.second ;
		dfs(e.first) ;
		
	}

}

int main()
{
	scanf("%d %d", &N , &M ) ;

	for(int i = 1 ; i <= N ; i++ ) scanf("%lld", &c[i] ) ;

	if( M > N )
	{
		printf("0\n") ;
		return 0 ;
	}

	for(int i = 1 , u , v ; i <= M ; i++ )
	{
		scanf("%d %d", &u, &v ) ;

		adj[u].push_back(make_pair(v,i) ) ;
		adj[v].push_back(make_pair(u,i) ) ;

		deg[u]++ ;
		deg[v]++ ;

	}

	vector<int> fila ;
	int ini = 0 ;

	for(int i = 1 ; i <= N ; i++ )
		if( deg[i] == 1 ) fila.push_back(i) ;

	while( ini < sz(fila) )
	{
		int x = fila[ini++] ;
		int parent = -1 ;

		for(auto e : adj[x] )
		{
			if(deg[e.first] > 0 ) 
			{
				parent = e.first ;
				continue ;
			}

			val[e.second] = c[e.first]<<1LL ;
			c[x] -= c[e.first] ;	

		}

		if( parent != -1 && (--deg[parent] ) == 1 ) fila.push_back(parent) ;
		deg[x] = 0 ;

	}

	for(int i = 1 ; i<= N ; i++ )
		for(auto e : adj[i] )
		{
			if(deg[e.first] || !deg[i] ) continue ;

			val[e.second] = c[e.first]<<1LL ;
			c[i] -= c[e.first] ;

		}

	for(int i = 1 ; i <= N ; i++ )
		if(deg[i] ) dfs(i) ;

	if( sz(cycle) )
	{
		for(auto e : adj[ cycle.back().first ] )
		if(e.first == cycle[0].first ) cycle.back().second = e.second ;

		if( !(sz(cycle)&1) )
		{
			printf("0\n") ;
			return 0 ;
		}

		ll cteFactor= -c[ cycle[0].first ] ;
		for(int i = 1 ; i < sz(cycle) ; i += 2 ) cteFactor -= c[ cycle[i].first ] ;
		for(int i = 2 ; i < sz(cycle) ; i += 2 ) cteFactor += c[ cycle[i].first ] ;

		val[ cycle[0].second ] = -cteFactor ;

		for(int i = 1 ; i < sz(cycle) ; i++ )
		{
			c[ cycle[i].first ] -= val[ cycle[i-1].second ]>>1LL ;
			val[ cycle[i].second ] = c[ cycle[i].first ]<<1LL ;
		}

	}

	for(int i = 1 ; i <= M ; i++ ) printf("%lld\n", val[i] ) ;

}
