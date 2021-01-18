#include <bits/stdc++.h>

#define ll long long
#define sz(x) (int)(x.size())
#define all(x) x.begin(),x.end()

const int MAXN = 1e5+10 ;

using namespace std ;

int N , M , R ;
int c[MAXN] , sub[MAXN] ;
vector< int > adj[MAXN] , revAdj[MAXN] ;
bool vis[MAXN] ;
vector< vector<int> > scc(1,vector<int>() ) ;
vector< pair<int,int> > ans ;

vector<int> List ;
void dfs1(int x)
{
	vis[x] = true ;
	for(auto e : adj[x] )
		if(!vis[e] ) dfs1(e) ;
	List.push_back(x) ;	
}

void dfs2(int x )
{
	for(auto e : revAdj[x] )
	{
		if(c[e] ) continue ;
		c[e] = c[x] ;
		scc[ c[e] ].push_back(e) ;
		dfs2(e) ;
	}
}

int dfs3(int x )
{
	sub[x] = sz(scc[c[x]] ) ;
	vis[ c[x] ] = true ;

	int child = -1 ;

	for(int i = 0 ; i < sz(scc[c[x]] ) ; i++ )
		if( scc[c[x] ][i] == x ) swap( scc[ c[x] ][i] , scc[c[x]][0] ) ;

	for(auto e : scc[c[x] ] )
	{
		for(auto j : adj[e] )
		{
			if(vis[ c[j] ] ) continue ;

			int t = dfs3(j) ;

			if( x==R || child != -1 ) ans.push_back(make_pair(t, e ) ) ;
			else child = t ;

			sub[x] += sub[j] ;

		}

		if( child == -1 ) child = x ;
	}

	for(auto e : scc[c[x]] ) sub[e] = sub[x] ;

	return child ;
}

int main()
{
	scanf("%d %d %d", &N, &M , &R ) ;
	for(int i = 0, u , v ; i < M ; i++ )
	{
		scanf("%d %d", &u, &v ) ;
		adj[u].push_back(v) ;
		revAdj[v].push_back(u) ;
	}

	dfs1(R) ;

	for(int i = N-1 , t = 0 ; i >= 0 ; i-- ) 
	{
		if( c[ List[i] ] ) continue ;
		c[ List[i] ] = ++t ;
		scc.push_back( {List[i] } ) ;
		dfs2(List[i] ) ;
	}

	for(int i= 1 ; i <= N ; i++ ) vis[i] = false; 

	dfs3(R) ;

	for(int i = 1 ; i <= N ; i++ ) printf("%d ", sub[i] ) ;
	printf("\n%d\n", sz(ans) ) ;
	for(auto e : ans ) printf("%d %d\n", e.first, e.second ) ;
}
