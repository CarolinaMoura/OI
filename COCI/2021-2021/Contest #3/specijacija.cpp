#include <bits/stdc++.h>

#define sz(x) (int)(x.size())
#define debug printf
#define lp(i,a,b) for(int i = a ; i < b; i++)
#define pb push_back
#define ff first
#define ss second
#define mk make_pair
#define pii pair<int,int>
#define ll long long 
#define all(x) x.begin(),x.end()

const int MAXN = 2e5+10 ;
const int LOG =20 ;

using namespace std ;

struct Seg
{
	
	vector<int> e , d , val , sub ;
	
	Seg() 
	{
		e.pb(0) ;
		d.pb(0) ;
		val.pb(0) ;
		sub.pb(0) ;
	}
	
	int m(int l, int r) { return (l+r)>>1 ; }
	int create_and_copy(int pos)
	{
		e.push_back(e[pos]) ;
		d.pb(d[pos]) ;
		val.pb(val[pos]) ;
		sub.pb(sub[pos]) ;
		
		return sz(e)-1 ;
	}
	
	int upd(int pos, int l, int r, int x, int _val , int _sub )
	{
		int newPos = create_and_copy(pos) ;	
		
		if(l == r )
		{
			sub[newPos] = _sub ;
			val[newPos] = _val ;
			return newPos ;
		}
		
		int aux ;
		if(x <= m(l,r))
		{
			aux = upd(e[newPos],l,m(l,r) , x, _val, _sub ) ;
			e[newPos] = aux ;
		}
		else
		{
			aux = upd(d[newPos] , m(l,r)+1, r, x, _val, _sub ) ;
			d[newPos] = aux ;
		}
		
		sub[newPos] = sub[e[newPos]]+sub[d[newPos]] ;
		return newPos ;
	}
	
	pair<int,int> bb(int pos, int l, int r, int x )
	{
		
		if( l == r ) return make_pair( l , val[pos] ) ;
		if( sub[e[pos]] < x ) return bb(d[pos], m(l,r)+1, r, x-sub[e[pos]]) ;
		
		return bb(e[pos] , l , m(l,r) , x ) ;
	}
		
} seg ;

int N , Q , T ;
int rt[MAXN] ;
vector<int> dp[LOG] ;
vector<int> lvl(1,0) ;
ll A[MAXN] , L[MAXN] ;
vector< vector<int> > adj(1, vector<int>() ) ;
vector<ll> resp(1, 0) ;

int create(ll k)
{
	adj.push_back( vector<int>() )	;
	resp.push_back(k) ;

	for(int i = 0 ; i < LOG ; i++ )
		while( sz(dp[i]) != sz(adj) ) dp[i].push_back(-1) ;
		
	lvl.pb(0) ;
	
	return sz(adj)-1 ;
}

ll getRow(ll x) { return upper_bound( L+1, L+2+N , x ) - L - 1 ; }
ll getColumn(ll x) 
{
	int idx = getRow(x) ;
	return x-L[idx]+1 ;
}
void createEdge(int a, int b)
{
	adj[a].pb(b) ;
	adj[b].pb(a) ;
}

int getComponent(ll x )
{
	int r = getRow(x) ;
	int c = getColumn(x) ;
	
	return seg.bb(rt[r],1,N+1, c).second ;
	
}

int getLca(int x, int y)
{
	if(lvl[x] < lvl[y]) swap(x,y) ;
	
	for(int i= LOG-1 ; i >= 0 ; i-- )
		if( dp[i][x] != -1 && lvl[ dp[i][x] ] >= lvl[y] )
			x = dp[i][x] ;
			
	if(x == y ) return y ;
	
	for(int i = LOG-1 ; i >= 0 ; i-- )
		if(dp[i][x] != -1 && dp[i][x] != dp[i][y])
		{
			x= dp[i][x] ;
			y = dp[i][y] ;
		}
		
	return dp[0][x] ;
}

int main()
{
	scanf("%d %d %d", &N, &Q, &T ) ;
	
	for(int i = 1 ; i <= N ; i++ ) scanf("%lld", &A[i]) ;
	
	L[0] = 1 ;
	for(int i = 1 ; i  <= N+1 ; i++ ) L[i] = L[i-1]+i-1 ;
	
	for(int i = 1 ; i <= N+1 ; i++ ) 
	{
		rt[N+1] = seg.upd( rt[N+1] , 1 , N+1, i, i, 1 ) ;
		create( L[N+1]+i-1 ) ;
	}
		
	for(int i = N ; i > 0 ; i-- )
	{
		ll y = getColumn(A[i]) ;
		
		int newId = create(A[i]) ;
		
		rt[i] = rt[i+1] ;
		
		pair<int,int> a = seg.bb( rt[i] , 1 , N+1, y ) ;
		pair<int,int> b = seg.bb(rt[i] , 1 , N+1, y+1 ) ;
				
		rt[i] = seg.upd( rt[i] , 1 , N+1 , b.first, 0, 0 ) ;
		rt[i] = seg.upd( rt[i] , 1 , N+1 , a.first , newId, 1 ) ;
		
		dp[0][a.second] = dp[0][b.second] = newId ;
		
		createEdge(newId, a.second) ;
		createEdge(newId, b.second ) ;
		
	}
	
	for(int j = 1 ; j < LOG ; j++ )
		for(int i = 1 ; i < sz(adj)  ; i++ )
			if( dp[j-1][i] != -1 )
				dp[j][i] = dp[j-1][ dp[j-1][i] ] ;
	
	lvl[sz(adj)-1] = 1 ;
	for(int i = sz(adj)-2 ; i > 0 ; i-- ) 
		lvl[i] = lvl[ dp[0][i] ]+1 ;
	
	ll z = 0 ;
	ll m = (ll)(N+1) ; m *= (ll)(N+2) ; m >>= 1LL ;
	
	while(Q--)
	{
		ll x , y ;
		scanf("%lld %lld", &x, &y ) ;
		
		x = ( (x-1+z*T)%m ) + 1 ;
		y = ( (y-1+z*T)%m ) + 1 ;
		
		if(x < y ) swap(x,y) ;
		
		int idx = getComponent(x) ;
		int idy = getComponent(y) ;
				
		int aux = getLca( idx , idy ) ;
		
		if( aux ==  idy ) z = y ;
		else z = resp[aux] ;
		
		printf("%lld\n" , z ) ;
		
	}
	
}

/*
4 1 0
1 2 5 7
11 4
*/

