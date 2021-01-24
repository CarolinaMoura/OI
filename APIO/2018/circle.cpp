/*
Proof of complexity: https://en.wikipedia.org/wiki/Circle_packing_in_a_square
*/
#include <bits/stdc++.h>
 
#define debug printf
#define ll long long
#define sz(x) (int)(x.size() )
#define all(x) x.begin(),x.end()
 
const int MAXN = 3e5+10 ;
 
using namespace std ;
 
struct Circle
{
	ll x , y , r ;
 
	Circle(ll x = 0 , ll y = 0 , ll r = 0 ) : x(x), y(y) , r(r) {}
 
} c[MAXN] ;
 
int N , idx ;
int ans[MAXN] , myBlock[MAXN] ;
ll mn[MAXN] , mx[MAXN] , meaning[MAXN] ;
ll G ;
vector<int> byY , byX ;
vector< pair<ll,int> > v[MAXN] ;
 
bool test(int i, int j )
{
	ll dx = c[i].x - c[j].x ;
	ll dy = c[i].y - c[j].y ;
	ll dr = c[i].r + c[j].r ;
	return dx*dx + dy*dy <= dr * dr ;
}
 
void rescale()
{
	for(int i = 0 ; i <= idx ; i++ ) v[i].clear() ;
	
	idx = -1 ;
 
	for(int e : byX )
	{
		if(ans[e] != -1 ) continue ;
		
		if(idx == -1  || (c[e].x/G) > meaning[idx] )
		{
			myBlock[e] = ++idx ;
			meaning[idx] = (c[e].x/G) ;
			mn[idx] = c[e].x ;
		}
		else myBlock[e] = idx ;		

		mx[idx] = c[e].x ;
	}	
 
	for(int e : byY )
	{
		if(ans[e] != -1 ) continue ;
		v[ myBlock[e] ].push_back(make_pair(c[e].y, e) ) ;
	}
 
	/*debug("Printing rescale with radio %d\n", G) ;
	for(int i= 0 ; i <= idx ; i++ )
	{
		debug("In the x %d: ", meaning[i] ) ;
		for(auto e : v[i] ) debug("%d %d, ", e.first, e.second ) ;
		debug("\n") ;
	} */
 
}
 
int main()
{
 
	scanf("%d", &N ) ;
	for(int i = 0 ; i < N ; i++ ) 
	{
		scanf("%lld %lld %lld", &c[i].x, &c[i].y, &c[i].r) ;
		ans[i] = -1 ;
	}
 
	vector<int> byRadio(N) ; iota(all(byRadio), 0 );
	sort(all(byRadio), [&](int i, int j) 
	{
		if( c[i].r != c[j].r ) return c[i].r > c[j].r ;
		return i< j ;
	} ) ;
 
	byY.resize(N) ; iota(all(byY),0) ;
	sort(all(byY), [&](int i, int j ) { return c[i].y < c[j].y ; } ) ;
 
	byX.resize(N) ; iota(all(byX), 0) ;
	sort(all(byX), [&](int i, int j ) { return c[i].x < c[j].x ; } ) ;
 
	G = c[ byRadio[0] ].r * 2LL + 1 ;
 
	for(auto e : byRadio )
	{
		if( ans[e] != -1 ) continue ;
 
		if( c[e].r*2LL < G )
		{
			G = c[e].r ;
			rescale() ;
		}		
 
		int l = myBlock[e] ; 
		while(l > 0 && c[e].x - mx[l] <= 2LL*c[e].r ) { l-- ; }
 
		int r = myBlock[e] ; 
		while( r < idx && mn[r+1]-c[e].x <= 2LL*c[e].r ) { r++ ; } 

		ll lo = c[e].y-2LL*c[e].r ;
		ll hi = c[e].y+2LL*c[e].r ;
 
		for(int i = l ; i <= r ; i++ )
		{
			int t = lower_bound(all(v[i]), make_pair(lo, -1 ) ) - v[i].begin() ;
			for(; t < sz(v[i]) && v[i][t].first <= hi ; t++ )
			{
				if( ans[ v[i][t].second ] != -1 ) continue ;
				if( test(v[i][t].second, e ) ) ans[ v[i][t].second ] = e ;
			}
		}
 
	}
	
	for(int i = 0 ; i < N ; i++ ) printf("%d ", ans[i]+1 ) ;
	printf("\n") ;	 
}
