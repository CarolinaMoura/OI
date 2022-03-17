#include <bits/stdc++.h>

#define all(x) x.begin(),x.end()
#define lp(i,a,b) for(int i= a ; i < b ; i++)

const int MAXN = 10010 ;

using namespace std ;

int N , M ;
int cnt[MAXN] ;
int val[2][MAXN] ;
vector<int> adj[MAXN] ;

inline int getVal(int x){
	if(cnt[x] == 0 ) return 0 ;
	return cnt[x] > 0 ? 1 : -1 ;
}

inline void interpret(int x){
	if( x == 0 ) cout << "1/2\n" ;
	else if ( x == 1 ) cout << "1\n" ;
	else cout << "0\n" ;
}

void solve(int *v , int k){

	lp(i,0,N) cnt[i] = 0 , v[i] = k ;

	v[0] = -1 ;
	cnt[0] = -1 ;

	v[1] = 1 ;
	cnt[1] = 1 ;

 	lp(i,0,N)
		for(auto e : adj[i]) cnt[e] += v[i] ;

	priority_queue< pair<int,int> , vector<pair<int,int> >, greater<pair<int,int> > > fila ;

	lp(i,2,N) fila.push(make_pair( k*cnt[i] , i )) ;

	while(!fila.empty()){

		int x = fila.top().second ;
		int valCnt = fila.top().first ;

		fila.pop() ;

		if( getVal(x) == v[x] ) continue ;

		for(auto e : adj[x] ) cnt[e] -= v[x] ;
		v[x] = getVal(x) ;
		for(auto e : adj[x] ){
			cnt[e] += v[x] ;
			fila.push(make_pair(k*cnt[e] , e )) ;
 		}
	}

}

int main(){
	ios_base::sync_with_stdio(false) ;
	cin.tie(0) ;

	cin >> N ;

	for(int i = 2 , K  ; i< N ; i++ ){
		cin >> K ;
		for(int j = 0 , x ; j < K ; j++ ){
			cin >> x ;
			adj[x].push_back(i) ;
		}
	}

	solve(val[0] , 1 ) ;
	solve(val[1] , -1 ) ;

	for(int i = 0 ; i < N ; i++ ){
		if(val[0][i] != val[1][i]) cout <<"?\n" ;
		else interpret(val[0][i]) ;
	}
}
