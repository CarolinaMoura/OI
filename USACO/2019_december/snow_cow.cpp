#include <bits/stdc++.h>

#define ll long long
#define all(x) x.begin(),x.end()
#define sz(x) (int)(x.size() )

const int MAXN = 1e5+10 ;

using namespace std ;

int N , Q ;
int tin[MAXN], tout[MAXN] ;
vector<int> adj[MAXN] ;
ll tree[MAXN*4] , lz[MAXN*4] ;

int m(int l, int r ) {return (l+r)>>1 ; }

void refresh(int pos, int l, int r )
{
	tree[pos] += lz[pos]*(ll)(r-l+1) ;
	if( l == r )return (void)(lz[pos]=0) ;

	lz[pos<<1] += lz[pos] ;
	lz[pos<<1|1] += lz[pos] ;
	lz[pos] = 0 ;
}

ll upd(int pos, int l, int r , int beg, int en, ll val )
{
	refresh(pos,l,r) ;
	if( l > en || r < beg ) return 0 ;
	if(l >= beg && r <= en )
	{
		lz[pos] += val ;
		refresh(pos,l,r) ;
		return tree[pos] ;
	}	

	ll al = upd(pos<<1 , l , m(l,r), beg, en, val ) ;
	ll ar = 	upd(pos<<1|1, m(l,r)+1, r, beg, en, val ) ;
	tree[pos] = tree[pos<<1] + tree[pos<<1|1] ; 
	return al+ar ;
}
struct cmp { bool operator() ( const int &a, const int &b ) const { return tin[a] < tin[b] ; } } ;
set<int, cmp> s[MAXN] ;

int currTime ;
void dfs(int x)
{
	tin[x] = tout[x] = ++currTime ;
	for(auto e : adj[x] )
	{
		if(tin[e]) continue ;
		dfs(e) ;
	}
	tout[x] = currTime ;
}

int main()
{
	freopen("snowcow.in", "r", stdin ) ;	
	freopen("snowcow.out", "w", stdout) ;

	scanf("%d %d", &N , &Q ) ;
	for(int i = 0 ,a , b ; i < N-1 ; i++ )
	{
		scanf("%d %d", &a, &b ) ;
		adj[a].push_back(b) ;
		adj[b].push_back(a) ;
	}
	dfs(1) ;

	//for(int i = 1; i <= N ; i++ ) cout << tin[i] <<" " << tout[i] << endl ;

	while(Q--)
	{
		int op , x , c ;
		scanf("%d %d", &op, &x ) ;

		if( op == 2 ) 
		{
			printf("%lld\n", upd(1,1,N, tin[x], tout[x], 0) ) ;
			continue ;
		}

		scanf("%d", &c ) ;

		auto it = s[c].upper_bound(x) ;
		if(it != s[c].begin() && tout[*(--it)] >= tout[x] ) continue ;

		it = s[c].upper_bound(x) ;
		while( it != s[c].end() && tout[*it] <= tout[x] )
		{
			upd( 1 , 1 , N , tin[*it], tout[*it] , -1 ) ;
			it = s[c].erase(it) ;
		}

		s[c].insert(x) ;
		upd(1,1,N, tin[x] , tout[x] , 1 ) ;

	}
}
