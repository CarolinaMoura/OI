#include <bits/stdc++.h>

#define all(x) x.begin(),x.end()
#define lp(i,a,b) for(int i= a ; i < b ; i++)
#define sz(x) (int)x.size()
#define pb push_back
#define pii pair<int,int>
#define mk make_pair
#define ll long long
#define mkt make_tuple

const int MAXN = 10010 ;
const int inf = 1e9+10 ;

using namespace std ;

int N , M ;
int cor[MAXN] ,dist[MAXN] , edg[MAXN] ;
vector<pii> adj[MAXN] ;

void dijkstra(){

	for(int i=2 ; i <= N ; i++ ) dist[i] = inf ;

	priority_queue< pair<int,int> , vector<pair<int,int> > , greater<pair<int,int> > > fila ;
	fila.push(mk(0,1)) ;
	cor[1] = -1 ;

	while(!fila.empty()){

		int x = fila.top().second ;
		int d = fila.top().first ;

		fila.pop() ;

		if(d != dist[x]) continue ;

		for(auto e : adj[x]){

			int vis = e.first; 
			int newDist = d+e.second ;

			if(vis == 1 )continue ;

			if( newDist < dist[vis] ){
				cor[vis]=(cor[x] == -1 ? vis : cor[x]) ;
				fila.push(mk(dist[vis] = newDist, vis)) ;
			}

		}

	}

	for(int i = 2 ; i<= N+N ; i++ ) dist[i] = inf ;

	fila.push(mk(0,1)) ;

	while(!fila.empty()){
		
		int x = fila.top().second ;
		int d = fila.top().first ;

		fila.pop() ;

		if(d != dist[x]) continue ;

		int p = x > N ? (x-N) : x ;

		for(auto e : adj[p]){

			int vis= e.first; 
			int newDist = d+e.second ;

			if( vis == 1  ) continue ;

			int color = (x == 1 ? vis : cor[x] ) ;

			if(color != cor[vis]){

				if( newDist < dist[vis+N] ){
					fila.push(mk(dist[vis+N] = newDist, vis+N) ) ;
				}
				cor[vis+N] = color ;

			}
			else{

				if(newDist < dist[vis]){
					fila.push(mk(dist[vis] = newDist , vis)) ;
				}

			}

		}

	}

}

int main(){
	ios_base::sync_with_stdio(false) ;
	cin.tie(0) ;

	cin >> N >> M ;
	lp(i,1,N+1) edg[i] = inf ;
	for(int i = 1 , a ,b , c , d ; i <= M ; i++ ){
		cin >> a >>b >> c >> d ;
		adj[a].pb(mk(b,c)) ;
		adj[b].pb(mk(a,d)) ;
		if(a > b ){
			swap(a,b) ;
			swap(c,d) ;
		}
		if(a == 1) edg[b] = min(edg[b], d ) ;
	}

	dijkstra() ;

	int ans = inf ;

	for(int i = 2 ; i <= N ; i++ ){

		if(cor[i] != i) ans = min(ans, dist[i]+edg[i]) ;
		else ans = min(ans, dist[i+N]+edg[i] ) ;

	}

	cout << ans << "\n" ;
}
