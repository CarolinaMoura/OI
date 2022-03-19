#include <bits/stdc++.h>

#define ll long long
#define pb push_back
#define lp(i,a,b) for(int i = a ;i < b ; i++)
#define sz(x) (int)(x.size())
#define all(x) x.begin(),x.end()
#define mk make_pair
#define mkt make_tuple

const int MAX = 1e5+10 ;

using namespace std;

int N ;
ll X[MAX] , Y[MAX] ;
int dsu[MAX] ;
vector<pair<ll,int> > vec ;
vector<pair<ll,int> > mat[12] ;
priority_queue< tuple<ll,int,int> > fila ;


int find(int x) { return x = (dsu[x] == x) ? x : find(dsu[x]) ; }
bool join(int x, int y){
	x = find(x) ;
	y = find(y) ;
	if(x == y) return false ;
	if(rand() % 2) swap(x,y );
	dsu[x] = y;
	return true ;
}

ll getDist(int a, int b){

	ll dx = X[a]-X[b] ;
	ll dy = Y[a]-Y[b] ;

	dx *= dx ;
	dy *= dy ;

	return dx+dy ;
}	

void createEdge(int a, int b){
	fila.push( mkt(-getDist(a,b) , a ,b) ) ;
}

int main(){
	ios_base::sync_with_stdio(false) ;
	cin.tie(0) ;

	cin >> N ;
	for(int i = 1 ; i <= N ; i++ ){
		cin >> X[i] >> Y[i] ;
		vec.pb(mk(X[i] , i)) ;
	}

	sort(all(vec)) ;

	for(auto e : vec ) mat[Y[e.second]].pb(e);

	for(int i = 1 ; i <= N ; i++ ){

		for(int j = 0 ; j <= 10 ; j++ ){

			auto it = upper_bound(all(mat[j]) , mk(X[i] , i)) ;
		
			if( it != mat[j].end() && it->second == i) it++ ;
			if(it != mat[j].end()) createEdge(it->second , i) ;

			it =lower_bound(all(mat[j]) , mk(X[i] , i)) ;
			if(it != mat[j].begin() ){
				it-- ;
				createEdge(it->second , i) ;
			}

		}

	}


	iota(dsu+1, dsu+1+N,1) ;

	ll ans = 0 ;
	while(!fila.empty()){

		ll d = get<0>(fila.top() ) ;
		int a = get<1>(fila.top()) ;
		int b = get<2>(fila.top()) ;

		fila.pop() ;

		if(join(a,b)) ans -= d ;

	}

	cout << ans << "\n" ;

}


