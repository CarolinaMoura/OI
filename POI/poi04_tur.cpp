#include <bits/stdc++.h>

#define all(x) x.begin(),x.end()
#define lp(i,a,b) for(int i= a ; i < b ; i++)
#define sz(x) (int)x.size()
#define pb push_back
#define pii pair<int,int>
#define mk make_pair
#define ll long long
#define mkt make_tuple

const int MAXN = 1e5+10 ;

using namespace std ;

int N ;
int comp[MAXN] ;
bool vis[MAXN] ;
vector<int> adj[MAXN] , revAdj[MAXN] ;
vector<int> List ;

set<int> s ;
void bfs(int x){

	vector<int>fila = {x} ;
	int ini = 0 ;

	while(ini < sz(fila)){

		int y = fila[ini++] ;
		int ptr0 =0  , ptr1 = 0 ;
		auto it = s.begin() ;

		while(it != s.end() ){

			while(ptr0 < sz(adj[y]) && adj[y][ptr0] < *it ){
				ptr0++ ;
			}
			while(ptr1 < sz(revAdj[y]) && revAdj[y][ptr1] < *it ){
				ptr1++ ;
			}
			if((ptr0 == sz(adj[y]) || adj[y][ptr0] != *it) && (ptr1 == sz(revAdj[y]) || revAdj[y][ptr1] != *it)){
				fila.pb(*it) ;
				it = s.erase(it) ;
			}
			else it++ ;

		}
	}

	for(int i = 1 ; i < sz(fila) ; i++ ){
		adj[fila[0]].pb(fila[i]) ;
		adj[fila[i]].pb(fila[0] ) ;
		revAdj[fila[0]].pb(fila[i]) ;
		revAdj[fila[i]].pb(fila[0]) ;
	}

}

void dfs1(int x){
	vis[x] = true ;
	for(auto e : adj[x]){
		if(!vis[e]) dfs1(e); 
	}
	List.pb(x) ;
}

void dfs2(int x){
	vis[x] =true ;
	for(auto e : revAdj[x]){
		if(!vis[e]){
			comp[e] = comp[x];
			dfs2(e); 
		}
	}
}

int main(){
	

	ios_base::sync_with_stdio(false) ;
	cin.tie(0) ;

	cin >> N ;
	for(int i = 1 , K ; i <= N ; i++ ){
		cin >> K ;
		for(int j =1 , x ; j <= K ; j++ ){
			cin >> x ;
			adj[i].push_back(x) ;
			revAdj[x].push_back(i) ;
		}
	}

	lp(i,1,N+1) sort(all(revAdj[i])) ;

	for(int i = 1 ; i <= N ; i++  )s.insert(i) ;

	for(int i = 1 ;i <= N ; i++ ){
		if(s.find(i) != s.end()){
			s.erase(i) ;
			bfs(i); 
		}
	}

	lp(i,1,N+1)
		if(!vis[i] ) dfs1(i) ;

	reverse(all(List)) ;
	lp(i,1,N+1 ) vis[i] = false ;

	int c = 0 ;
	for(auto e : List ){

		if(vis[e]) continue ;
		comp[e] = ++c ;
		dfs2(e) ;

	}

	vector<int> ans ;

	for(int i = 1 ;i <= N ; i++ ){
		if(comp[i] == 1){
			ans.pb(i) ;
		}
	}

	cout << sz(ans) << " " ;
	for(auto e : ans ) cout << e << " " ;
	cout << "\n" ;

}
