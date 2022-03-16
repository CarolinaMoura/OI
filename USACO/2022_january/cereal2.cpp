#include <bits/stdc++.h>

#define all(x) x.begin(),x.end()
#define lp(i,a,b) for(int i= a ; i < b ; i++)
#define sz(x) (int)x.size()
#define pb push_back
#define pii pair<int,int>
#define mk make_pair
#define ll long long
#define mkt make_tuple

const int MAX = 1e5+10 ;

using namespace std ;

int N , M ;
int matchn[MAX] , matchm[MAX] ,deg[MAX] ;
vector<int> adj[MAX] ;
bool vis[MAX] ;

bool dfs(int x){

	for(auto e : adj[x]){
		if(vis[e]) continue ;
		vis[e] = true ;
		if(!matchm[e] || dfs(matchm[e])){

			matchm[e] = x ;
			matchn[x] = e; 

			return true ;

		}
	}

	return false ;

}

int main(){
	ios_base::sync_with_stdio(false) ;
	cin.tie(0) ;

	cin >> N >> M ;
	for(int i= 1 , x , y ; i <= N ; i++ ){
		cin >> x >> y ;
		adj[i] = {x,y} ;
	}

	bool ok = true ;
	int f = 0;
	while(ok){
		ok = false ;
		lp(i,1,M+1) vis[i] = false ;
		lp(i,1,N+1)
			if(!matchn[i] && dfs(i)){
				ok = true ;
				f++ ;
			}
	}

	for(int i = 1 ; i <= N ; i++ ){

		if(!matchn[i]) continue ;

		int j = adj[i][0] ;
		if(!matchm[j]){
			matchm[ matchn[i] ] = 0 ;
			matchn[i] = j ;
			matchm[j] = i ;
		}

		deg[ matchm[ j ] ]++ ;

	}
	vector<int> fila ;
	int ini = 0 ;

	for(int i = 1 ; i <= N ; i++)
		if(matchn[i] && deg[i] == 0) fila.pb(i) ;

	while(ini < sz(fila)){
		int x = fila[ini++] ;
		if( (--deg[ matchm[ adj[x][0] ] ]) == 0 ) fila.pb( matchm[adj[x][0]] ) ;
	}

	for(int i = 1 ; i <= N ; i++ )
		if(deg[i] && matchn[i]) fila.pb(i) ;

	reverse(all(fila)) ;

	for(int i = 1 ; i <= N ; i++ )
		if(!matchn[i]) fila.pb(i) ;

	cout << N-f << "\n" ;
	for(auto e : fila  )cout << e << "\n" ;

}
