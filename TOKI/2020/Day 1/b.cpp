#include <bits/stdc++.h>

#define debug printf
#define sz(x) (int)(x.size())
#define ll long long
#define all(x) x.begin(),x.end()
#define pii pair<int,int>
#define mk make_pair
#define ff first
#define ss second

const int MAXN = 2e5+10 ;
const int inf = 1e9+7 ;

using namespace std ;

struct Seg
{
	int h[MAXN] ;
	int mx[MAXN*4] ;

	Seg() { h[0] = inf ; }

	int m(int l, int r) { return (l+r)>>1 ; }

	void upd(int pos, int l, int r, int k, int val)
	{
		if(l == r)
		{
			h[l] = val ;
			mx[pos] = l ;
			return ;
		}

		if(k <= m(l,r)) upd(pos<<1 , l, m(l,r) , k , val ) ;
		else upd(pos<<1|1 , m(l,r)+1, r, k , val ) ;

		if( h[ mx[pos<<1] ] <= h[ mx[pos<<1|1] ] )
			mx[pos] = mx[pos<<1] ;
		else mx[pos] = mx[pos<<1|1] ;

	}

	int bb(int pos, int l, int r, int beg, int en )
	{

		if(l > en || r < beg) return 0 ;
		if(l >= beg && r <= en ) return mx[pos] ;

		int al = bb(pos<<1 ,l, m(l,r) , beg, en ) ;
		int ar = bb(pos<<1|1 , m(l,r)+1, r, beg, en ) ;

		if( h[al] <= h[ar] ) return al ;
		return ar ;
	}

} seg ;

int n , q , curIdx ;
int ansQueries[MAXN] ;
vector< pair<ll,int> > queries ;
ll cntUniversal ;

void solve(int l, int r, int toSubtract )
{
	if(r < l) return ;

	int menor = seg.bb(1,1,n, l, r) ;

	//debug("%d %d %d %d e %lld\n" , l , r , toSubtract, menor , cntUniversal ) ;

	//todo mundo vai perder seg.a[menor] - toSubtract
	ll cool = (ll)(seg.h[menor]-toSubtract) ;
	while( curIdx < sz(queries) && queries[curIdx].first-cntUniversal <= (ll)(r-l+1) * cool )
	{
		int idx =  queries[curIdx].second  ;
		ansQueries[idx] = ((queries[curIdx].first-cntUniversal)%(r-l+1) ) ;
		if( ansQueries[idx] == 0 ) ansQueries[idx] = r ;
		else ansQueries[idx] = ansQueries[idx]-1 + l ;
		curIdx++ ;
	}

	cntUniversal += (ll)(r-l+1) * cool ;

	seg.upd(1,1,n, menor, inf ) ;

	solve(l,menor-1, toSubtract+cool ) ;
	solve(menor+1, r, toSubtract+cool ) ;
}

int main()
{
	scanf("%d", &n ) ;
	for(int i = 1 ; i <= n ; i++ ) 
	{
		scanf("%d", &seg.h[i] ) ;
		seg.upd(1,1,n, i, seg.h[i]) ;
	}
	scanf("%d", &q ) ;
	for(int i = 1 ; i <= q ; i++ )
	{
		ll x ;
		scanf("%lld", &x ) ;
		queries.push_back( make_pair(x,i) ) ;
	}

	sort(all(queries)) ;
	solve(1,n,0) ;

	for(int i = 1 ; i <= q ; i++ ) printf("%d\n" , ansQueries[i]) ;
}
