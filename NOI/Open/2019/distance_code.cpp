#include <bits/stdc++.h>

#define lp(i,a,b) for(int i = a ; i < b ; i++ )
#define sz(x) (int)(x.size() )
#define debug printf
#define ll long long
#define pb push_back        
#define all(x) x.begin(),x.end()
#define mk make_pair
#define pii pair<int,int>
#define ff first
#define ss second
#define tiii tuple<int,int,int>

const int MAXN = 1e5+10 ;

using namespace std ;

int T , N ;
int tin[MAXN], tout[MAXN] , prof[MAXN] , A[MAXN] ;
vector<int> adj[MAXN]; 

int dfs1(int x)
{
	int deepest = 0 ;
	vector<pair<int,int> > children ;

	for(auto e : adj[x] )
	{
		if(prof[e] ) continue ;
		
		prof[e] = prof[x]+1 ;
		children.pb( mk(-dfs1(e), e) ) ;
		deepest = max(deepest, -children.back().ff) ;
	}	
	sort(all(children) ) ;
	adj[x].clear(); 
	for(auto e : children ) adj[x].pb(e.ss) ;
	return deepest+1 ;
}

int currTime ;
void dfs2(int x)
{
	tin[x] = ++currTime ;
	for(auto e : adj[x] ) dfs2(e) ;
	tout[x]=++currTime ;	
}

void encode()
{
	for(int i = 1 , a , b ; i< N ; i++ )
	{
		scanf("%d %d", &a, &b ) ;
		adj[a].pb(b) ;
		adj[b].pb(a) ;
	}

	prof[1] = 1 ;
	dfs1(1) ;
	dfs2(1) ;

	//for(int i = 1 ; i <= N ; i++ ) debug("%d -> %d %d\n", i, tin[i], tout[i] ) ;

	vector<int> vec(N) ; iota(all(vec), 1) ;
	sort(all(vec), [&](int a, int b) {
		if( prof[a] != prof[b] ) return prof[a] > prof[b] ;
		return tin[a] < tin[b] ;
	} ) ;

	for(auto e : vec ) printf("%d ", e ) ;
	printf("\n") ;

}

void createEdge(int a, int b)
{	
	printf("%d %d\n", a, b ) ;
}

void decode()
{
	lp(i,1,N) scanf("%d", &A[i] ) ;

	int l_ant = 0 , r_ant = -1 ;

	for(int l = 1 , r = 2 ; l < N ; l = r, r++ )
	{                         	
		while(r < N && (A[r-1]&1) == 0 ) r++ ;

		if(l_ant)
			for(int i = l ; i < r ; i++ )
			{

				createEdge( l_ant++, i ) ;
				while(l_ant <= r_ant && A[l_ant-1] == 2 ) createEdge( l_ant++ , i ) ;
				
				if( l_ant-1 == r_ant ) break ;

				while( A[i]+2 != A[l_ant-1] ) i++ ;
			}

		l_ant = l ;
		r_ant = r-1 ;

	}

	for(int i = l_ant ; i <= r_ant ; i++ ) createEdge(N, i) ;

}

int main()
{
	scanf("%d%d", &T , &N ) ;

	if(T == 1 ) encode() ;
	else decode() ;
}
