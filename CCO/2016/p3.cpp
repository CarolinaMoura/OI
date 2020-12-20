#include <bits/stdc++.h>

#define ll long long
#define all(x) x.begin(),x.end()
#define sz(x) (int)(x.size())

const int MAXN = 1e5+10 ;

using namespace std ;

int S , T , N , M , C ;
int depth[MAXN] , low[MAXN] , deg[MAXN] ;
int U[MAXN], V[MAXN] ;
int edgesComponents[MAXN] , verticesComponents[MAXN] , articulationsComponents[MAXN] ;
vector< pair<int,int> > adj[MAXN] ;
stack<int> st ;
vector<int> myComponents[MAXN] ;
bool ok[5] ;
bool isArt[MAXN] ;

void makeComponent( int lastIncluded )
{

	vector<int> vertices, edges ;
	++C ;

	articulationsComponents[C] = 0 ;

	while( !st.empty() )
	{
		vertices.push_back( U[ st.top() ] ) ;
		vertices.push_back( V[ st.top() ] ) ;

		edges.push_back( st.top() ) ;

		deg[ U[ st.top() ] ]++ ;
		deg[ V[ st.top() ] ]++ ;

		if( st.top() == lastIncluded ) 
		{
			st.pop() ;
			break ;
		}
		
		st.pop() ;

	}	

	int qtdEdges = sz(vertices)>>1 ;
	edgesComponents[C] = qtdEdges ;

	sort(all(vertices) ) ;
	vertices.erase( unique(all(vertices) ) , vertices.end() ) ;

	int qtdVertices = sz(vertices) ;
	verticesComponents[C] = qtdVertices ;

	for(auto e : vertices )	myComponents[e].push_back(C);

	if( qtdEdges >= 5 && qtdEdges > qtdVertices ) ok[0] = true ;
	if( qtdEdges > 3 ) ok[2] = true ;

	if( qtdVertices >= 5 )
	{
		vector<int> deg3 ;

		for(auto e : vertices ) 
		{
			if( deg[e] > 3 ) ok[4] = true ;
			else if( deg[e] == 3 ) deg3.push_back(e) ;
		}

		if( sz(deg3) >= 3 ) ok[4] = true ;
		else if( sz(deg3) == 2 )
		{
			for(auto e : edges )
				if( U[e] != deg3[0] && V[e] != deg3[0] && U[e] != deg3[1] && V[e] != deg3[1] ) ok[4] = true ;
		}	

	}

	for(auto e : vertices ) deg[e] = 0 ;

}

void dfs(int x, int parent )
{	
	bool hasFwd = false ;

	for(auto e : adj[x] )
	{
		int j = e.first ;
		int id = e.second ;

		if( j == parent || depth[j] > depth[x] ) continue ;

		st.push(id) ;

		if( depth[j] != -1 )
		{
			low[x] = min(low[x], depth[j] ) ;
			continue ;
		}

		depth[j] = low[j] = depth[x] + 1 ;

		dfs(j,x) ;

		low[x] = min(low[x], low[j] ) ;

		if( (parent == -1) ? hasFwd : (low[j] >= depth[x]) ) 
		{
			makeComponent(id) ;
			isArt[x] = true ;
		}

		hasFwd = true ;

	}
}

bool solve()
{
	ok[0] = ok[1] = ok[2] = ok[3] = ok[4] = false ;

	scanf("%d %d", &N , &M ) ;
	for(int i = 1 ; i <= N ; i++ ) 
	{
		adj[i].clear() ;
		myComponents[i].clear() ;
		low[i] = depth[i] = -1 ;
		isArt[i] = false ;
	}
	C = 0 ;

	for(int i = 1 ; i <= M ; i++ )
	{
		scanf("%d %d", &U[i], &V[i] ) ;

		adj[ U[i] ].push_back( make_pair(V[i], i) ) ;
		adj[ V[i] ].push_back( make_pair(U[i], i) ) ;
	}                                	

	//Checking subtask 1, subtask 3, and subtask 5
	low[1] = depth[1] = 0 ;
	dfs(1,-1) ;

	if( !st.empty() ) makeComponent(-1) ;

	for(int i = 1 ; i <= N ; i++ )
	{
		if(!isArt[i] ) continue ;
		for(auto e : myComponents[i] ) articulationsComponents[e]++ ;
	}

	for(int i = 1 ; i <= C ; i++ )
	{
		if( edgesComponents[i] >= verticesComponents[i]+1 && articulationsComponents[i] >= 1 && verticesComponents[i] >= 4 ) ok[4] = true ;
		if( articulationsComponents[i] >= 2 && verticesComponents[i] >= 3 ) ok[4] = true ;
	}

	if( S == 0 || S == 2 || S == 4 ) return ok[S] ;
	//


	//Checking subtask 2
	if( S == 1 ) return ( N >= 3 && M != N-1 ) ;
	//


	//Checking subtask 4
	if( S == 3 )
	{
		for(int i = 1 ; i <= N ; i++ ) 
			if( sz(adj[i]) >= 3 ) return true ;
		
		return false ;
	}
	//

}

int main()
{
	scanf("%d %d", &S, &T) ; S-- ;
	while(T--) printf("%s\n", solve() ? "YES" : "NO" ) ;

}
