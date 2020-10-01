#include "plants.h"
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
 
const int MAX = 2e5+10 ;
const int LOG = 20 ;
const int inf = 1e8+10 ;
 
using namespace std ;
 
struct Seg
{
 
	ll lz[MAX*4] , mn[MAX*4];
	int idx[MAX*4] ;
 
	void clean()
	{
		memset(lz, 0, sizeof lz) ;
		memset(mn, 0, sizeof mn) ;
	}
 
	int m(int l, int r) { return (l+r)>>1 ; }
	void refresh(int pos, int l, int r)
	{
		if(!lz[pos]) return ;
 
		mn[pos] += lz[pos] ;
 
		if(l == r) return (void)(lz[pos] = 0 ) ;
 
		lz[pos<<1] += lz[pos] ;
		lz[pos<<1|1] += lz[pos] ;
 
		lz[pos] = 0 ;
 
	}
 
	void upd(int pos, int l, int r, int beg, int en , int val )
	{
		refresh(pos,l,r) ;
 
		if(l > en || r < beg ) return ;
		if(l >= beg && r <= en)
		{
			lz[pos] += (ll)val ;
			refresh(pos,l,r) ;
			if(l == r) idx[pos] = l ;
			return ;
		}
 
		upd(pos<<1 , l, m(l,r) , beg, en, val ) ;
		upd(pos<<1|1 , m(l,r)+1,r, beg, en, val ) ;
 
		if(mn[pos<<1] <= mn[pos<<1|1])
		{
			idx[pos] = idx[pos<<1] ;
			mn[pos] = mn[pos<<1] ;
		}
		else 
		{
			idx[pos] = idx[pos<<1|1] ;
			mn[pos] = mn[pos<<1|1] ;
		}
 
	}
 
	pii qry(int pos, int l, int r, int beg, int en )
	{
		refresh(pos,l,r) ;
		if( l > en || r < beg ) return mk(inf, -1) ;
		if(l >= beg && r <= en) return mk( mn[pos] , idx[pos] ) ;
 
		pii al = qry(pos<<1 , l, m(l,r) , beg, en ) ;
		pii ar = qry(pos<<1|1 , m(l,r)+1,r, beg, en ) ;
 
		if( al.ff <= ar.ff ) return al ;
		return ar ;
	}
 
} seg ;
 
int n , last , k ;
int dp[2][LOG][MAX] ;
ll dist[2][LOG][MAX] ;
vector<int> h , lef , rig ;
vector<pii> intervalLeft[MAX] , intervalRight[MAX] ;
 
void extract(int x)
{
	while(true)
	{
	
		pii p = mk(inf, -1) ;
		
		for(auto e : intervalLeft[x] ) 
			p = min(p, seg.qry(1,0,n-1, e.ff, e.ss) ) ;
 
		if(p.ff == 0) 
		{
			extract(p.ss) ;
			continue ;
		}
 
		h[x] = last-- ;
		
		seg.upd(1,0,n-1, x , x , inf ) ;
		for(auto e : intervalLeft[x] ) seg.upd(1,0,n-1, e.ff, e.ss, -1) ;
 
		return ;
 
	}
 
}

bool isOn(int m, int i) { return ((1<<i)&m) != 0 ; }
 
int getDist( bool clockwise , int a, int b )
{
	if(a == b) return 0 ;

	if(!clockwise)
	{
		if(b < a) return a - b ;
		return a + n - b ;
	}
 
	if( b > a ) return b-a ;
	return n-a+b ;
}
 
void init(int K, vector<int> r) 
{
	k = K ;
	n = sz(r) ;
	h.resize(n,0) ;
	last = n ;
 
	//Find intervals
	intervalLeft[0].push_back( mk(n-k+1,n-1) ) ;
	lp(i,1,n)
	{
		intervalLeft[i].push_back( mk(max(0,i-k+1) , i-1) ) ;
 
		if( i >= k-1 ) continue ;
		
		int falta = k-1 - i ;
		intervalLeft[i].pb( mk( n-falta , n-1 ) ) ;
 
	}
	intervalRight[n-1].pb( mk( 0 , k-2 ) ) ;
	lp(i,0,n-1)
	{
		intervalRight[i].pb( mk( i+1, min(n-1, i+k-1) ) ) ;
 
		if( i+k-1 <= n-1 ) continue ;
 
		int lef = k-1 - (n-i-1) ;
		intervalRight[i].pb(  mk(0,lef-1)) ;
 
	}
 
	for(int i = 0 ; i < n ; i++ ) 
		seg.upd(1,0,n-1, i , i , r[i] ); 
 
	while(true)
	{
		pii p = seg.qry(1,0,n-1,0,n-1) ;
 
		if(p.ff != 0) break ;
 
		extract(p.ss) ;
 
	}
 
	if(2*k > n ) return ;
 
	seg.clean() ;
 
	vector<int> idx(n) ;
	iota(all(idx) , 0 ) ;
	sort(all(idx), [&](int i, int j){ return h[i] < h[j]; }  ) ;
 
	memset(dp, -1, sizeof dp ) ;
 
	for(auto e : idx )
	{
		pii p = mk(0 , -1 ) ;
		for(auto e : intervalLeft[e] )
			p = min(p , seg.qry(1,0,n-1, e.ff, e.ss) ) ;
 
		dp[0][0][e] = p.ss ;
 
		p = mk(0, -1 ) ;
		for(auto e : intervalRight[e] ) 
			p = min(p, seg.qry(1,0,n-1, e.ff, e.ss) ) ;
 
		dp[1][0][e] = p.ss ;
 
		seg.upd(1,0,n-1,e,e, -h[e] ) ;
 
	}

	lp(i,0,2)
		lp(j,0,n)
			if(dp[i][0][j] != -1)
				dist[i][0][j] = (ll)getDist(i, j , dp[i][0][j] ) ;
 
	lp(i,0,2)
		lp(j,1,LOG)
			lp(g,0,n)
			{
				if(dp[i][j-1][g] == -1) continue ;
				dp[i][j][g] = dp[i][j-1][ dp[i][j-1][g] ] ;
				dist[i][j][g] = dist[i][j-1][g] + dist[i][j-1][ dp[i][j-1][g] ] ;
			}
 
}

 
int compare_plants(int x, int y) 
{
	if( 2*k > n || getDist(false, x, y) < k || getDist(true, x, y) < k)
		return h[x] > h[y] ? 1 : -1 ;
 
	for(int cur : {x,y} )
	for(int type = 0 ; type < 2 ; type++ )
	{
		int filho = cur , _filho ;
		int other = (cur == x ) ? y : x ;
		int d = getDist(type, cur, other) ;
 
		if(h[other] > h[cur]) continue ;
 
		for(int i = LOG-1 ; i >= 0 ; i-- )
		{
 
 
			_filho = dp[type][i][filho] ;
 
			if(_filho == -1 ) continue ;
			if(dist[type][i][filho] > d) continue ;
 
			//cout << filho << " " << type << " " << _filho << " " << h[_filho] << " " << i << " " << dist[type][i][filho] << " "<< d << endl ;
			
			//int distToCur = getDist(type, _filho, cur ) ;
			int distToOther = getDist(type, _filho, other ) ;
  
			if(distToOther < k )
			{
				if(h[other] <= h[_filho]  ) 
					return (cur == x) ? 1 : -1 ;
			}
			else if(h[_filho] > h[other] ) d -= dist[type][i][filho] , filho = _filho  ;
 
		}
 
		if(h[other] <= h[filho] && getDist(type, filho, other) < k ) 
			return (cur == x) ? 1 : -1 ;
 
	}
 
	return 0 ;
 
}
