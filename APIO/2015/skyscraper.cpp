#include <bits/stdc++.h>

#define pii pair<int,int>
#define all(x) x.begin(),x.end()
#define sz(x) (int)(x.size() )

const int MAX = 30010;
const int SQ = 173 ;

using namespace std ;

int n , m ;
int b[MAX] , p[MAX] ;
vector<int> content[MAX] ;
vector<int> noName[SQ+5][SQ+5] ;

vector<int> dijkstra(int S)
{	

	vector<int> dist(n) ;
	for(int i = 0 ; i < n ; i++ ) dist[i] = MAX*MAX ;
	dist[ b[S] ] = 0 ;

	priority_queue< pii , vector<pii> , greater<pii> > fila ;
	fila.push(make_pair(0, b[S] ) ) ;

	while(!fila.empty() )
	{
		int d = fila.top().first ;
		int curr = fila.top().second ;

		fila.pop() ;

		if( d != dist[curr] ) continue ;

		for(auto e : content[curr] )
		{
			if( p[e] >= SQ )
			{
				for(int i = b[e] - p[e], w = 1 ; i >= 0 ; i-= p[e] , w++ )
					if( d + w < dist[i] )
					{
						dist[i] = d + w ;
						fila.push(make_pair(d+w, i) ) ;
					}

			  for(int i = b[e] + p[e] , w = 1 ; i < n ; i+= p[e] , w++ )
			  	if( d + w < dist[i] )
			  	{
			  		dist[i] = d + w ;
			  		fila.push(make_pair(d+w, i) ) ;
			  	} 

			}
			else 
			{
				int firstDim =  b[e] % p[e]  ;
				int secondDim = p[e] ;


				int x = lower_bound(all(noName[firstDim][secondDim]), b[e]) - noName[firstDim][secondDim].begin() ;

				int limLow = (x == 0) ? -1 : noName[firstDim][secondDim][x-1] ;
				int limUp = (x == sz(noName[firstDim][secondDim])-1 ) ? -1 : noName[firstDim][secondDim][x+1] ;

				for(int i = curr - p[e] , w = 1 ; i >= 0 ; i -= p[e] , w++ )
				{
					if(d + w < dist[i] )
					{
						dist[i] = d + w ;
						fila.push(make_pair(d+w, i) ) ;
					}
					if( i == limLow ) break ;
				}
				for(int i = b[e] + p[e] , w = 1 ; i < n  ; i += p[e] , w++ )
				{
					if(d + w < dist[i] )
					{
						dist[i] = d + w ;
						fila.push(make_pair(d+w, i) ) ;
					}

					if( i == limUp ) break ;

				}
			}
		}

	}

	return dist ;

}

int main()
{

	scanf("%d%d", &n, &m ) ;
	for(int i = 0 ; i < m ; i++ ) 
	{
		scanf("%d %d", &b[i] , &p[i] ) ;
	
		content[ b[i] ].push_back(i) ;

		if( p[i] < SQ ) noName[ b[i] % p[i] ][ p[i] ].push_back( b[i] ) ;

	}

	for(int i = 0 ; i < SQ ; i++ )
		for(int j = 0 ; j < SQ; j++ ) 
		{
			sort(all(noName[i][j]) );
			noName[i][j].erase( unique(all(noName[i][j])) , noName[i][j].end() ) ;
		}

	vector<int> dist = dijkstra(0) ;

	if(dist[ b[1] ] == MAX*MAX ) dist[ b[1] ] = -1 ;

	printf("%d\n", dist[ b[1] ] ) ;
}
