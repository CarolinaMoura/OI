#include <bits/stdc++.h>

#define ll long long
#define pb push_back
#define lp(i,a,b) for(int i = a ;i < b ; i++)
#define sz(x) (int)(x.size())
#define all(x) x.begin(),x.end()
#define mk make_pair

const int MAX = 510 ;

using namespace std;

int N ;
bool path[MAX][MAX] ;
vector<int> adj[MAX] , revAdj[MAX] ;


int main(){
	ios_base::sync_with_stdio(false) ;
	cin.tie(0) ;
	
	cin >> N ;
	
	for(int i = 1 ; i <= N ; i++ ){
		for(int j = 1 , x , k = 0 ; j <= N ; j++ ){
			cin >> x; 
			if(k) continue ;
			adj[i].pb(x) ;
			revAdj[x].pb(i) ;
			if( x == i ) k = 1 ;
		}
		path[i][i] = true ;
	}

	vector<pair<int,int> > fila ;
	int ini = 0 ;
	
	for(int i = 1 ; i <= N ; i++ ) fila.pb(mk(i,i)) ;
	
	while(ini < sz(fila)){
		
		int x = fila[ini].first; 
		int y = fila[ini++].second ;
		
		for(auto e : revAdj[x] ){
			if(path[e][y]) continue ;
			path[e][y] = true ;
			fila.pb(mk(e,y)) ;
		}
		
	}
		
	for(int i = 1 ; i<= N ; i++ ){
		for(auto e : adj[i]){
			if(path[e][i]){
				cout << e << "\n" ;
				break ;
			}
		}
	}
}
