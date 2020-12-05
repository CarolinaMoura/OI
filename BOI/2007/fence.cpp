#include <bits/stdc++.h>

#define debug 
#define all(x) x.begin(),x.end()
#define ll long long
#define sz(x) (int)(x.size())

const int MAXN = 210 ;
const ll inf = 1e17+10LL ;

using namespace std ;

int n , toSum ;
int keyX , keyY ;
int dx[4] = {0,-1,0,1} , dy[4] = {1,0,-1,0} ;
vector< pair<int,int> > adj[MAXN*MAXN*2] ;

int getIndex(int x, int y, int par )
{
	//"par" stands for "parity"
	return x * keyY + y + par * toSum ;
}
tuple<int,int,int> vertex(int code)
{
	int par = 0 ;
	int x , y ;

	if(code >= toSum ) par = 1 , code -= toSum ;

	y = code % keyY ;
	x = code/keyY ;

	return make_tuple(x,y,par) ;
}

bool valid(int i, int j) { return 0 <= min(i,j) && i < keyX && j < keyY ; }

ll dijkstra(int s, int t)
{
	
	vector<ll> dist(toSum*2+5, inf ) ;
	dist[s] = 0 ;

	priority_queue< pair<ll,int> , vector< pair<ll,int> > , greater< pair<ll,int> > >fila ;
	fila.push(make_pair(0,s) ) ;

	while(!fila.empty() )
	{
		int x = fila.top().second ;
		ll d = fila.top().first ;

		fila.pop() ;

		if( d != dist[x] ) continue ;
		if( x == t ) return d ;

		auto p = vertex(x) ;

		for(auto e : adj[x] )
		{
			
			int viz = e.first ;
			ll dd = d + (ll)e.second ;

			if( dd >= dist[viz] ) continue ;

			fila.push(make_pair(dist[viz] = dd, viz) ) ;

		}
	}

	return inf ;

}

int main()
{
	scanf("%d", &n ) ;

	vector<pair<int,int> > bottomLeft(n) , topRight(n) ;
	vector<int> compressX, compressY ;

	for(int i = 0 ; i < n ; i++ )
	{
		scanf("%d %d", &bottomLeft[i].first, &bottomLeft[i].second ) ;
		scanf("%d %d", &topRight[i].first, &topRight[i].second ) ;

		compressX.push_back(bottomLeft[i].first);
		compressX.push_back( topRight[i].first ) ;

		compressY.push_back( bottomLeft[i].second ) ;
		compressY.push_back( topRight[i].second ) ;
	}

	sort(all(compressX)) ; 
	sort(all(compressY)) ;

	compressX.erase(unique(all(compressX)) , compressX.end() ) ;
	compressY.erase( unique(all(compressY)) , compressY.end() ) ;

	keyX = sz(compressX) ;
	keyY = sz(compressY) ;

	vector< vector<bool>  > allowedHorizontal( keyX, vector<bool>(keyY, true ) ) ;
	vector< vector<bool>  > allowedVertical( keyX, vector<bool>(keyY, true ) ) ;

	for(int i = 0 ; i < n ; i++ )
	{
		bottomLeft[i].first = lower_bound(all(compressX), bottomLeft[i].first ) - compressX.begin() ;
		bottomLeft[i].second = lower_bound(all(compressY), bottomLeft[i].second ) - compressY.begin() ;
		topRight[i].first = lower_bound(all(compressX), topRight[i].first ) - compressX.begin() ;
		topRight[i].second = lower_bound(all(compressY), topRight[i].second ) - compressY.begin() ;

		for(int z = bottomLeft[i].first + 1 ; z < topRight[i].first ; z++ )
			for(int j = bottomLeft[i].second ; j < topRight[i].second ; j++ )
				allowedVertical[z][j] = false ;

		for(int z = bottomLeft[i].first ; z < topRight[i].first ; z++ )
			for(int j = bottomLeft[i].second+1 ; j < topRight[i].second  ; j++ )
				allowedHorizontal[z][j] = false ; 

	}

	toSum = keyX * keyY ;
	
	int X = bottomLeft[0].first ;
	int Y = topRight[0].second ;

	auto isSpecial = [&](int x, int y ) { return x == X && y >= Y ; } ;

	for(int x = 0 ; x < keyX ; x++ )
		for(int y = 0 ; y < keyY ; y++ )
		{

			if( valid(x+1, y) && allowedHorizontal[x][y] ) 
			{

				if( isSpecial(x,y) )
				{
					adj[ getIndex(x,y,0) ].push_back( make_pair( getIndex(x+1,y,1), compressX[x+1] - compressX[x] )  ) ;
					adj[ getIndex(x,y,1) ].push_back( make_pair(getIndex(x+1,y,0), compressX[x+1] - compressX[x]) ) ;
				}
				else 
				{
					adj[ getIndex(x,y,0) ].push_back(make_pair( getIndex(x+1,y,0 ), compressX[x+1] - compressX[x] ) ) ;
					adj[ getIndex(x,y,1) ].push_back(make_pair( getIndex(x+1,y,1 ) , compressX[x+1] - compressX[x] ) ) ;
				}

			}
			if(valid(x,y-1) && allowedVertical[x][y-1] )
			{
				adj[ getIndex(x,y,0) ].push_back( make_pair(getIndex(x,y-1,0 ), compressY[y] - compressY[y-1]) ) ;
				adj[ getIndex(x,y,1) ].push_back( make_pair(getIndex(x,y-1,1 ), compressY[y] - compressY[y-1]) ) ;
			}
			if( valid(x-1, y) && allowedHorizontal[x-1][y] ) 
			{

				if(isSpecial(x-1,y) )
				{
					adj[ getIndex(x,y,0) ].push_back( make_pair(getIndex(x-1,y,1), compressX[x] - compressX[x-1] ) ) ;
					adj[ getIndex(x,y,1) ].push_back( make_pair(getIndex(x-1,y,0), compressX[x] - compressX[x-1] ) ) ;
				}
				else 
				{
					adj[ getIndex(x,y,0) ].push_back( make_pair(getIndex(x-1,y,0), compressX[x] - compressX[x-1] ) ) ;
					adj[ getIndex(x,y,1) ].push_back( make_pair(getIndex(x-1,y,1), compressX[x] - compressX[x-1] ) ) ;
				}

			}
			if( valid(x, y+1) && allowedVertical[x][y] )
			{
				adj[ getIndex(x,y,0) ].push_back( make_pair(getIndex(x,y+1,0 ), compressY[y+1] - compressY[y]) ) ;
				adj[ getIndex(x,y,1) ].push_back( make_pair(getIndex(x,y+1,1 ), compressY[y+1] - compressY[y]) ) ;
			}

		}
		   
	ll ans = inf ;

	for(int i = 0 ; i < keyX ; i++ )
		for(int j = 0 ; j < keyY ; j++ )
			if(isSpecial(i,j) ) ans = min(ans, dijkstra( getIndex(i,j,0) , getIndex(i,j,1 ) ) ) ;  


	printf("%lld\n", ans ) ;			

}                        
