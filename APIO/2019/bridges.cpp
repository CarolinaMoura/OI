#include <bits/stdc++.h>
 
#define all(x) x.begin(),x.end()
#define ll long long
#define sz(x) (int)(x.size())
 
const int MAXN = 5e4+10 ;
const int MAXQ = 1e5+10 ;
const int MAXM = 1e5+10 ;
const int perfectQ = 800 ;
 
//NAO ESQUECE DE MUDAR O PERFECTQ PELO AMOR DE DEUS
 
using namespace std ;
 
struct Edge
{
 
	int u , v , weight , tin, tout ;
 
	Edge(int u=0, int v=0, int weight=0, int tin=0, int tout=0) :
	u(u) , v(v) , weight(weight), tin(tin), tout(tout) {}
 
	bool operator < ( Edge other ) const { return weight > other.weight ; }
 
} ;
 
int N , M , Q , cnt ;
int U[MAXM], V[MAXM] , W[MAXM ] ;
int lastChanged[MAXM] , ansQuery[MAXQ] ;
vector<int> adj[MAXN] ;
vector<Edge> edge ;
vector< tuple<int,int,int> > queries ;
bool vis[MAXN] ;
 
//dsu stuff
int pai[MAXN] ;
int componentSize[MAXN] ;
 
int find(int x)
{
	if(x == pai[x] ) return x ;
	return pai[x] = find(pai[x]); 
}
 
void join(int x, int y)
{
	x = find(x) ;
	y= find(y) ;
 
	if(x == y) return ;
 
	if(componentSize[x] > componentSize[y])
		swap(x,y) ;
 
	componentSize[y] += componentSize[x] ;
	pai[x] = y ;
 
}
 
void dfs(int x)
{
	vis[x] =true; 
	cnt += componentSize[x] ;
 
	for(auto e : adj[x])
		if(!vis[e]) dfs(e) ;
}
 
char c ;
void read(int &num)
{
	num = 0 ;
 
	c = getchar() ;
 
	for(; ( c > 47 && c < 58) ; c = getchar() ) 
		num = num*10 + (c - '0') ;
 
}
 
int main()
{
	read(N) , read(M) ;
	for(int i = 1 ; i <= M ; i++ )
	{
		read( U[i] ) ;
		read(V[i] ) ;
		read(W[i]) ;
	}
 
	read(Q) ;
 
	for(int i = 1 ,t , x , y ; i <= Q ; i++ )
	{
 
		read(t) , read(x) , read(y) ;
 
		if(t == 1)
		{
			edge.push_back(Edge( U[x] , V[x] , W[x] , lastChanged[x] , i-1 ) );
			lastChanged[x] = i ;
			W[x] = y ;
		}
		else queries.push_back( make_tuple( y , x , i ) ) ;
 
	}
 
	for(int i = 1 ; i <= M ; i++ ) 
		edge.push_back( Edge( U[i] , V[i] , W[i] , lastChanged[i] , Q+1 ) ) ;
 
	sort(all(edge)) ;
	sort(all(queries), [&](tuple<int,int,int> x, tuple<int,int,int> y) { return get<0>(x) > get<0>(y) ;} ) ;
 
	//for(auto e : edge ) cout << e.u << " " << e.v << " " << e.weight << " " << e.tin << " " << e.tout << endl ;
	//	cout << endl ;
 
	for(int i = 1 ; i <= Q ; i++ ) ansQuery[i] = -1 ;
 
	for(int l = 1 , r = perfectQ ; l <= Q ; l += perfectQ, r += perfectQ )
	{
		if( r > Q ) r = Q ;
 
		for(int i =1  ; i <= N ; i++ )
		{
			pai[i] = i ;
			componentSize[i] = 1 ;
		}
 
		vector<Edge> edgeToCheck , edgeForSure ;
		vector<tuple<int,int,int> > queryNow ;
 
		for(auto e : edge )
		{
			if( e.tin > r || e.tout < l ) continue ;
			if(e.tin <= l && e.tout >= r) edgeForSure.push_back(e) ;
			else edgeToCheck.push_back(e) ;
		}
 
		for(auto e : queries )
			if(get<2>(e) >= l && get<2>(e) <= r) queryNow.push_back(e) ;
 
		int ptrForSure = 0 ;
		int tamForSure = sz(edgeForSure) ;
		int tamToCheck = sz(edgeToCheck ) ;
 
		for(auto e : queryNow )
		{
 
			int t = get<2>(e) ;
			int startNode = get<1>(e ) ;
			int weight = get<0>(e) ;
 
			while( ptrForSure < tamForSure && edgeForSure[ptrForSure].weight >= weight )
			{
				join( edgeForSure[ptrForSure].u , edgeForSure[ptrForSure].v ) ;
				ptrForSure++ ;
			}
 
			for(int i = 0 ; i < tamToCheck ; i++ )
			{
				if( edgeToCheck[i].weight < weight ) break ;
				if( edgeToCheck[i].tin <= t && edgeToCheck[i].tout >= t )
				{
 
					int x = find( edgeToCheck[i].u ) ;
					int y = find(edgeToCheck[i].v ) ;
					
					adj[x].push_back(y) ;
					adj[y].push_back(x) ;
 
				}
			}
 
			startNode = find(startNode) ;
			cnt = 0 ;
 
			dfs(startNode) ;
 
			vis[startNode] = false ;
			ansQuery[ t ] = cnt ;
 
			for(int i = 0 ; i < tamToCheck ; i++ )
			{
				if( edgeToCheck[i].weight < weight ) break ;
				if( edgeToCheck[i].tin <= t && edgeToCheck[i].tout >= t )
				{
					int x = find( edgeToCheck[i].u ) ;
					int y = find(edgeToCheck[i].v ) ;
					
					adj[x].clear() ;
					adj[y].clear() ;
 
					vis[x] = vis[y] = false ;
				}
			}
 
		}
 
	}
 
	for(int i = 1 ; i <= Q ; i++ )
		if(ansQuery[i] > -1 ) printf("%d\n" , ansQuery[i] ) ;
 
}
