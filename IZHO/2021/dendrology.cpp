#include <bits/stdc++.h>

#define mkt make_tuple
#define pb push_back
#define sz(x) (int)(x.size() )
#define pii pair<int,int>
#define ll long long
#define mk make_pair
#define lp(i,a,b) for(int i = a ; i < b ; i++ )

const int MAX = 1e5+10 ;

using namespace std ;

int N , Q ;
int magnet[MAX] , sub[MAX] , tin[MAX], tout[MAX] , invTin[MAX] ;
int linearTree[MAX] , iniMagnet[MAX] ;
pair<int,int> edg[MAX] ;
vector<int> adj[MAX] ; 
vector< tuple<int,int,int> > updates[MAX] ;
ll regular[MAX] , changed[MAX] ;                
ll lef[MAX*4] , rig[MAX*4] , tam[MAX*4] ;
ll ans[MAX*4] ;
ll res[MAX] ;

int m(int l, int r) { return (l+r)>>1 ; }

ll getNumber( ll x ){ return ((x*(x-1))/2)+x ; }
ll getAbs(ll x ) { return x < 0 ? -x : x ; }

void build(int pos, int l, int r){

	tam[pos] = r-l+1 ;	
	ans[pos] = getNumber(tam[pos]) ;
	lef[pos] = rig[pos] = -tam[pos] ;

	if( l == r ) return ;

	build(pos<<1 , l , m(l,r) ) ;
	build(pos<<1|1 , m(l,r)+1 , r ) ;
}

void upd(int pos, int l, int r, int id ){
	
	if( l == r ){
		lef[pos] = -lef[pos] ;
		rig[pos] = -rig[pos] ;
		return ;
	}

	if( id <= m(l,r) ) upd(pos<<1 , l , m(l,r) , id ) ;
	else upd(pos<<1|1, m(l,r)+1, r, id ) ;

	lef[pos] = lef[pos<<1 ] ;
	rig[pos] = rig[pos<<1|1] ;			
	ans[pos] = ans[pos<<1] + ans[pos<<1|1] ;

	//sao de cores iguais
	if( (rig[pos<<1] < 0 ) == (lef[pos<<1|1] < 0 ) ){
		ans[pos] += rig[pos<<1]*lef[pos<<1|1] ;
		if( getAbs(rig[pos<<1|1]) == tam[pos<<1|1] ) rig[pos] += rig[pos<<1] ;
		if(getAbs(lef[pos<<1] ) == tam[pos<<1] ) lef[pos] += lef[pos<<1|1] ;
	}

}

int currTime ;
void DFS1(int x){
	
	tin[x] = ++currTime ;
	invTin[tin[x] ] = x ;
	linearTree[tin[x] ] = magnet[x] ;

	sub[x] = 1 ;

	for(auto e : adj[x] ){
		if( sub[e] ) continue ;
		DFS1(e) ;
		sub[x] += sub[e] ;
	}

	tout[x] = currTime ;

}

void DFS2(int x, bool pode_deixar){

	int bc = -1 , pai = 0 ;

	for(auto e : adj[x] ){		
		if( sub[e] < sub[x] && (bc == -1 || sub[bc] < sub[e] ) ) bc = e ;
		if( sub[e] > sub[x] ) pai = e ;
	}

	for(auto e : adj[x] )
		if( sub[e] < sub[x] && bc != e ) DFS2(e, false) ;

	if(bc != -1 ) DFS2(bc, true) ;	

	for(auto e : adj[x] ){
		if( e == pai || e == bc ) continue ;
		for(int i = tin[e] ; i <= tout[e] ; i++ )	
			upd(1,1, N, linearTree[i] ) ;
	}

	upd(1,1,N, iniMagnet[x] ) ;
	
	res[0] += getNumber(N)-ans[1] ;                        
	ll ant = ans[1] ;

	for(auto e : updates[x] ){
		int a = get<0>(e) , b = get<1>(e) , id = get<2>(e) ;
		upd(1,1,N, a) ;
		upd(1,1,N, b) ;
		res[id] += ant-ans[1] ;
		ant = ans[1] ;
	}
	for(int i = sz(updates[x])-1 ; i >= 0 ; i-- ){
		int a = get<0>( updates[x][i] ) ;
		int b = get<1>( updates[x][i] ) ;

		upd(1,1,N,b) ;
		upd(1,1,N,a) ;
	}

	if(!pode_deixar)
		for(int i = tin[x] ; i <= tout[x] ; i++ )
			upd( 1 , 1 , N , linearTree[i] ) ;
}

int main(){
	ios_base::sync_with_stdio(false) ;
	cin.tie(0) ;

	cin >> N >> Q ;
	for(int i = 1 ; i <= N ; i++ ) cin >> iniMagnet[i] , magnet[i] = iniMagnet[i] ;
	for(int i = 1 , a , b ; i < N ; i++ ){
		cin >> a >> b ;
		adj[a].pb(b) ;
		adj[b].pb(a) ;
		edg[i] = make_pair(a,b) ;
	}

	build(1,1,N) ;

	DFS1(1) ;

	for(int i = 1 ; i < N ;i++ )
		if( tin[edg[i].second] < tin[edg[i].first] ) swap(edg[i].first, edg[i].second) ;

	for(int i = 1 , idx ; i <= Q ; i++ ){
		cin >> idx ;
		int u = edg[idx].second ;
		updates[u].push_back( mkt(magnet[u] , magnet[ edg[idx].first ] , i ) ) ;
		swap(magnet[ edg[idx].first], magnet[ edg[idx].second] ) ;
	}

	DFS2(1, true) ;
	
	res[0] += getNumber(N) ;
	for(int i = 1 ; i <= Q ; i++ ) res[i] += res[i-1] ;

	for(int i = 0 ; i <= Q ; i++ ) cout << res[i] <<" " ;
	cout << "\n" ;

}
