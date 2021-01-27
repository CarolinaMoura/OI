#include <bits/stdc++.h>

#define ll long long
#define sz(x) (int)(x.size() )
#define all(x) x.begin(),x.end()

const int MAX = 410 ;
const ll inf = 1e18+10 ;

using namespace std ;

int N , M ;
vector< pair<int,int> > points ;
vector< pair< pair<int,int> ,ll > > adj[MAX][MAX] ;
vector< pair<pair<int,int> , ll > > adj2[MAX*2][MAX*2] ;
ll dist[MAX*2][MAX*2] ;
pair<int,int> parent[MAX][MAX] ;
bool horizontal[MAX*2][MAX*2] , vertical[MAX*2][MAX*2] ;

void dijkstra1()
{
	priority_queue< pair<ll, pair<int,int> >, vector< pair<ll,pair<int,int> > >, greater< pair<ll,pair<int,int> > > > fila ;
	for(int i = 0 ; i <= N ; i++ )
		for(int j = 0 ; j <= M ; j++ ) dist[i][j] = inf ;

	fila.push( make_pair( dist[0][0] = 0 , make_pair(0,0) ) ) ;
	parent[0][0] = make_pair(-1,-1) ;

	while(!fila.empty() )
	{
		pair<int,int> curr = fila.top().second ;
		ll d = fila.top().first ;

		fila.pop() ;

		for( auto e : adj[curr.first][curr.second] )
		{
			auto neigh = e.first ;
			ll dd = d + e.second ;

			if( dist[neigh.first][neigh.second] <= dd ) continue ;
			
			fila.push( make_pair(dist[neigh.first][neigh.second] = dd , neigh ) ) ;
			parent[neigh.first][neigh.second] = curr ;
		}

	}
}

void dijkstra2()
{
	priority_queue< pair<ll, pair<int,int> >, vector< pair<ll,pair<int,int> > >, greater< pair<ll,pair<int,int> > > > fila ;
		
	for(int i= 0 ; i < 2*N+2 ; i++ )
		for(int j = 0 ; j < 2*M+ 2 ; j++ ) dist[i][j] = inf ;

	fila.push( make_pair( dist[0][1] = 0 , make_pair(0,1) ) ) ;

	while(!fila.empty() )
	{
		pair<int,int> curr = fila.top().second ;
		ll d = fila.top().first ;

		fila.pop() ;

		if(curr == make_pair(0,0) ) continue ;

		for(auto e : adj2[curr.first][curr.second ] )
		{
			auto neigh = e.first ;
			ll dd = e.second + d ;

			if( dist[neigh.first][neigh.second] > dd ) 
				fila.push( make_pair(dist[neigh.first][neigh.second] = dd , neigh ) ) ;

		}

	}

}

int main()
{

	scanf("%d %d", &N, &M ) ;
	for(int i = 0 ; i < N ; i++ )
		for(int j= 0 , x ; j < M ; j++ )
		{
			scanf("%d", &x ) ;
			
			if(!x) continue ; 

			points.push_back( make_pair(i,j) ) ;
			points.push_back( make_pair(i+1, j+1) ) ;
			points.push_back( make_pair(i,j+1) ) ;
			points.push_back( make_pair(i+1,j) ) ;

			int n = i<<1 , m = j<<1 ;

			horizontal[n+1][m] = true ;
			horizontal[n+2][m] = true ;
			horizontal[n+1][m+2] = true ;
			horizontal[n+2][m+2] = true ;

			vertical[n][m+1] = true ;
			vertical[n][m+2] = true ;
			vertical[n+2][m+1] = true ;
			vertical[n+2][m+2] = true ;

		}

	sort(all(points) ) ;
	points.erase( unique(all(points) ), points.end() ) ;
	
	for(int i = 0 ; i < N ; i++ )
		for(int j = 0 , w ; j < M+1 ; j++ )
		{
			scanf("%d", &w ) ;
					
			adj[i][j].push_back( make_pair(make_pair(i+1,j) , w ) ) ;
			adj[i+1][j].push_back( make_pair(make_pair(i,j) , w ) ) ;

			int n = i<<1 ;
			int m = j<<1 ;

			adj2[n+1][m].push_back( make_pair(make_pair(n+2,m), w ) ) ;
			adj2[n+2][m].push_back( make_pair(make_pair(n+1, m) , w ) ) ;
			adj2[n+1][m+1].push_back( make_pair(make_pair(n+2,m+1), w ) ) ;
			adj2[n+2][m+1].push_back( make_pair(make_pair(n+1, m+1) , w ) ) ;
		}

	for(int i = 0 ; i < N+1 ; i++ )
		for(int j=0 , w ; j < M ; j++ )
		{           
			scanf("%d", &w ) ;
			adj[i][j].push_back( make_pair( make_pair(i,j+1), w) ) ;
			adj[i][j+1].push_back( make_pair( make_pair(i,j) , w ) ) ;

			int n = i<<1 ;
			int m = j<<1 ;

			adj2[n][m+1].push_back( make_pair(make_pair(n,m+2), w ) ) ;
			adj2[n][m+2].push_back( make_pair(make_pair(n, m+1), w ) );
			adj2[n+1][m+1].push_back(make_pair(make_pair(n+1,m+2), w ) ) ;
			adj2[n+1][m+2].push_back(make_pair(make_pair(n+1,m+1), w ) ) ;

		}

	dijkstra1() ;

	for(auto e : points )
	{
		
		//now I gotta find out what was my path
		auto curr = e ;
		while(true)
		{			
			auto p = parent[curr.first][curr.second ] ;			
			
			if( p == make_pair(-1,-1) ) break ;

			int n = curr.first << 1 ;
			int m = curr.second << 1 ;	  	

	  		if( p == make_pair(curr.first-1,curr.second) )
	  		{
				horizontal[n][m] = true ;
				horizontal[n-1][m] = true ;	  			
	  		}
	  		else if( p == make_pair( curr.first, curr.second-1 ) )
	  		{
	  			vertical[n][m] = true ;
	  			vertical[n][m-1] = true ;
	  		}
	  		else if( p == make_pair(curr.first+1, curr.second ) )
	  		{
	  			horizontal[n+1][m] = true;
				horizontal[n+2][m] = true ;
	  		}
	  		else
	  		{
	  			vertical[n][m+1] = true ;
	  			vertical[n][m+2] = true ;
	  		}

			curr = p ;

		}

	}

	for(int i= 0 ; i < 2*N+2 ; i++ )
		for(int j = 0 ; j < 2*M+1 ; j += 2 )
		{
			if(horizontal[i][j] ) continue ;

			adj2[i][j].push_back( make_pair( make_pair(i,j+1), 0) ) ;
			adj2[i][j+1].push_back( make_pair(make_pair(i,j) , 0 ) ) ;
		}

	for(int i= 0 ; i <2*N+1 ; i += 2 )
		for(int j = 0 ; j < 2*M+2 ; j++ )
		{
			if(vertical[i][j] ) continue ;
			adj2[i][j].push_back(make_pair(make_pair(i+1,j), 0 ) ) ;
			adj2[i+1][j].push_back( make_pair(make_pair(i,j), 0 ) ) ;
		}

	dijkstra2() ;

	printf("%lld\n", dist[1][0] ) ;

}
