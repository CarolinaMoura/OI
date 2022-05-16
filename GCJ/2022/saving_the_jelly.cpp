#include <bits/stdc++.h>

#define ff first
#define ss second
#define lp(i,a,b) for(int i = a ; i < b ;i++ ) 
#define pb push_back
#define ll long long
#define all(x) x.begin(),x.end()
#define sz(x) (int)x.size()
#define pii pair<int,int>
#define mk make_pair

const int MAXN = 1010 ;

using namespace std ;

int N ;
int matchn[MAXN] , matchm[MAXN] ;
ll X[MAXN] , Y[MAXN] ,cx[MAXN] , cy[MAXN] ;
int lista[MAXN] ;
vector<int> adj[MAXN] ;
bool vis[MAXN] ;
int ptr[MAXN] ;

bool dfs(int x){
	for(auto e : adj[x]){
		if(vis[e]) continue ;
		vis[e] = true ;
		if(matchm[e] == -1 || (dfs(matchm[e]))){
			matchm[e] = x ;
			matchn[x] = e ;
			return true ;
		}
	}
	return false ;
}

ll getDist(ll x, ll y, ll a, ll b ){
	x = x - a ;
	y = y-b ;
	x*= x ;
	y *= y ;
	return x+y ;
}

void solve(){
	cin >> N ;

	for(int i= 0 ;i <= N ; i++ ){
		matchn[i] = matchm[i] = -1 ;
		adj[i].clear() ;
	}

	lp(i,0,N) cin >>cx[i] >> cy[i] ;
	for(int i = 0 ; i <= N ; i++ ){
		cin >> X[i] >> Y[i] ;
	}

	iota(lista,lista+N+1 , 0 ) ;

	lp(i,0,N){
		
		sort(lista, lista+1+N , [&](int a, int b){
			ll da = getDist(X[a],Y[a] ,cx[i] , cy[i]) ;
			ll db = getDist(X[b],Y[b] ,cx[i] , cy[i]) ;
			if(da != db) return da < db;
			return a > b ;
		} ) ;

		lp(j,0,N+1){
			if(lista[j] == 0 ) break ;
			adj[i].push_back(lista[j] ) ;
		}
	}

	int f = 0 ;
	bool ok = true ;
	while(ok){
		ok = false ;
		lp(i,0,N+1) vis[i] = false ;
		lp(i,0,N)
			if(matchn[i] == -1 && dfs(i)){
				f++ ;
				ok = true ;
			}
	}

	if(f < N){
		cout << "IMPOSSIBLE\n" ;
		return ;
	}

	vector<pair<int,int> >ans ;

	lp(i,0,N) ptr[i] = 0 ;
	while(f){
		lp(i,0,N){
			if(matchn[i] == -1 ) continue ;
			while( matchm[ adj[i][ptr[i]] ] == -1 ) ptr[i]++ ;
			if(matchm[adj[i][ptr[i]]] == i){
				ans.push_back(make_pair(i,matchn[i])) ;
				matchm[matchn[i]] = -1 ;
				matchn[i] = -1 ;
				f-- ;
			}
		}
	}

	cout << "POSSIBLE\n" ;
	for(auto &e : ans ) cout << e.first+1 << " " << e.second+1 << "\n" ;

}

int main(){
	ios_base::sync_with_stdio(false) ; 
	cin.tie(0);

	int T = 1 ;
	cin >>T ;
	for(int i = 1 ; i <= T ; i++ ) {
		cout << "Case #" << i<<": " ; solve() ;
	}

}
