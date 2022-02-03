#include <bits/stdc++.h>
 
#define mk make_pair
 
const int MAX = 510 ;
 
using namespace std ;
 
int N , M ;
int dsu[MAX][MAX] , dist[MAX*MAX] ;
vector< pair<int,int> > adj[MAX*MAX] ;
 
int main(){
	ios_base::sync_with_stdio(false) ;
	
	cin >> N >> M ;
 
	for(int i = 0 , c = 0  ; i <= N ; i++ )
		for(int j = 0 ; j <= M ; j++ , c++ ) 
			dsu[i][j] = c ;
 
	vector< pair<int,int> > g[2] ;
 
	for(int i= 0 ; i < N ; i++ )
		for(int j = 0 ; j < M ; j++ ){
			char c ;
			cin >> c ;
			g[1].push_back( make_pair(dsu[i+1][j], dsu[i][j+1] ) ) ;
			g[0].push_back( make_pair( dsu[i][j] , dsu[i+1][j+1] ) ) ;
			if(c == '/' ) swap(g[0].back() , g[1].back() ) ;
		}	
 
	for(int i = 0 ; i < 2 ; i++ ){
		for(auto e : g[i] ){
			adj[e.first].push_back(mk(e.second,i) ) ;
			adj[e.second].push_back(mk(e.first,i) ) ;
		}
	}
 
	int S = dsu[0][0] , T = dsu[N][M] ;
 
	priority_queue< pair<int,int> , vector<pair<int,int> > , greater< pair<int,int> > > fila ;
 
	for(int i= 1 ; i <= T ; i++ ) dist[i] = MAX*MAX ;
	fila.push( make_pair(0, S) ) ;
 
	
	while(!fila.empty() ){
		int x = fila.top().second ;
		int d = fila.top().first ;
 
		fila.pop() ;
 
		if( d != dist[x] ) continue ;
 
		for(auto e : adj[x] ){
			int newd = d + e.second ;
			if( dist[e.first] <= newd ) continue ;
			fila.push( make_pair(dist[e.first] = newd , e.first ) ) ;
		}
	}
 
	if(dist[T] >= MAX*MAX ) cout << "NO SOLUTION\n" ;
	else cout << dist[T] << "\n" ;
}
