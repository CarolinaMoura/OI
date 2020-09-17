#include <bits/stdc++.h>

#define all(x) x.begin(),x.end()
#define debug //printf
#define sz(x) (int)(x.size())
#define pii pair<int,int>
#define ff first
#define ss second
#define ll long long

using namespace std ;

int n , m ;
vector<int> height, low , qtdVert , subtree ;
vector<ll> toSubtract ;
vector< vector<int> > biconnected , tree ;
vector<pii> edges ;
vector< vector<pii> > adj ;
vector<bool> seenEdge , isArt , seenVertex , spun ;
ll ans ;

// ------------------ GETTING ARTICULATION POINTS AND BICONNECTED COMPONENTS

stack<int> st ;
void makeComponent(int lastIncluded)
{

	biconnected.push_back( vector<int>() ) ;
	tree.push_back( vector<int>() ) ;
	toSubtract.push_back(0LL) ;
	qtdVert.push_back(0) ;
	subtree.push_back(0) ;
	spun.push_back(false) ;

	while( !st.empty() )
	{
		int onTop = st.top() ;
		st.pop() ;

		biconnected.back().push_back( onTop ) ;

		if(onTop == lastIncluded) return ;

	}

}

void lowlink(int x, bool isFirst = false ) 
{

	bool hasFwd = false ;
	seenVertex[x] = true ;

	for(auto e : adj[x] ) 
	{
		int target = e.ff ;
		int id = e.ss ;

		if( seenEdge[id] ) continue ;

		st.push( id ) ;

		seenEdge[id] = true ;

		if( height[target] != -1 )
		{
			low[x] = min( low[x] , height[target] ) ;
			continue ;
		}

		height[target] = low[target] = height[x] + 1 ;
		
		lowlink( target ) ;

		low[x] = min( low[x] , low[target] ) ;

		if( (isFirst) ? hasFwd : (low[target] >= height[x]) )
		{
			isArt[x] = true ;
			makeComponent(id) ;
		}

		hasFwd = true ;

	}

}
// -----------------------------

void dfsInit(int x, int father )
{

	subtree[x] = qtdVert[x] ;

	for(auto neigh : tree[x] ) 
	{
		if(neigh == father) continue ;

		dfsInit(neigh, x) ;

		subtree[x] += subtree[neigh] ;
	}

}

long long binomial(ll x) { return ((x-1)*x)/2LL ; }

void dfsSpin(int x)
{
	spun[x] = true ;

	if( x >= n )
	{
		//I'm a component
		for(int neigh : tree[x] ) 
			toSubtract[x] += binomial( (ll)subtree[neigh] ) ;

		ans -= toSubtract[x] * (ll)qtdVert[x] ;

	}

	for(int neigh : tree[x])
	{

		if( spun[neigh] ) continue ;

		int mySub = subtree[x] ;
		int yourSub = subtree[neigh] ;

		subtree[x] -= subtree[neigh] ;
		subtree[neigh] = mySub ;

		dfsSpin(neigh) ;

		subtree[x] = mySub ;
		subtree[neigh] = yourSub ;

	}

	if( x < n )
	{
		//I'm an articulation point

		for(int neigh : tree[x])
			toSubtract[x] += toSubtract[neigh] - binomial( (ll) subtree[x] - subtree[neigh] ) ;

		ans -= toSubtract[x] ;
	}

}

int main()
{

	scanf("%d%d", &n , &m ) ;

	adj.resize(n, vector<pii>() ) ;
	seenEdge.resize(m, false) ;
	seenVertex.resize(n, false) ;
	tree.resize(n, vector<int>() ) ;
	height.resize(n, -1) ;
	low.resize(n) ;
	isArt.resize(n, false) ;
	toSubtract.resize(n, 0LL ) ;
	qtdVert.resize(n, 1) ;
	subtree.resize(n, 0) ;
	spun.resize(n, false) ;

	for(int i = 0 , a , b ; i < m ; i++ )
	{
		scanf("%d%d", &a, &b ) ;

		a-- ;
		b-- ;
		
		adj[a].push_back( make_pair(b,i) ) ;
		adj[b].push_back( make_pair(a,i) ) ;
		edges.push_back( make_pair(a,b) ) ;
	}

	for(int i = 0 ; i < n ; i++ )
	{

		if( seenVertex[i] ) continue ;

		int toBegin = sz(biconnected) ;

		height[i] = low[i] = 0 ;
		lowlink(i, true ) ;
		makeComponent(-1) ;

		int toEnd = sz(biconnected) ;

		for(int j = toBegin ; j < toEnd ; j++ )
		{

			debug("Component %d: " , j ) ;

			vector<int> nonArt ;

			for(int e : biconnected[j]) 
			{
				nonArt.push_back( edges[e].ff ) ;
				nonArt.push_back( edges[e].ss ) ;
				debug("(%d %d) and " , edges[e].ff, edges[e].ss ) ;
			}

			debug("\n") ;

			sort(all(nonArt));
			nonArt.erase( unique(all(nonArt)) , nonArt.end() ) ;

			for(int e : nonArt)
			{

				if( isArt[e] ) 
				{
					tree[e].push_back(n + j) ;
					tree[n+j].push_back(e) ;
				}
				else qtdVert[n+j]++ ;
			}

		}

		dfsInit(n+toBegin, -1) ;

		ans += binomial((ll)subtree[n+toBegin]-1) * (ll)subtree[n+toBegin] ;

		dfsSpin(n+toBegin) ;

	}

	printf("%lld\n" , ans*2LL ) ;

}
