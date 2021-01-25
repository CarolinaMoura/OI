#include <bits/stdc++.h>
 
#define eps 0.000000001
#define debug printf
#define ll long long
#define all(x) x.begin(),x.end()
#define sz(x) (int)(x.size())
 
const int MAXN = 110 ;
const int MAXK = 1010 ;
const ll inf = 1e15+10LL ;
 
using namespace std ;
 
int N , M , K ;
ll buying[MAXN][MAXK] , selling[MAXN][MAXK] ;
ll dist[MAXN][MAXN ] , cost[MAXN][MAXN] ;
ll dCheap[MAXN][MAXN] ;
 
bool test(ll val)
{
	for(int i = 1 ; i <= N ; i++ )
		for(int j = 1 ; j <= N ; j++ )
		{
			dCheap[i][j] = inf ;
 
			if( dist[i][j] <= (inf/val) )
				dCheap[i][j] = dist[i][j] * val - cost[i][j] ;
		}
	
	for(int i = 1 ; i <= N ; i++ )
		for(int j = 1 ; j <= N ; j++ )
			for(int g = 1 ; g <= N ; g++ ) 
				dCheap[i][j] = min( dCheap[i][j] , dCheap[i][g] + dCheap[g][j] ) ;
 
	for(int i = 1 ; i <= N ; i++ )
		for(int j= i+1 ; j<= N ; j++ )
			if( dCheap[i][j] + dCheap[j][i] <= 0 ) return true ; 
	
	return false ;
 
}
 
int main()
{
	scanf("%d %d %d", &N, &M, &K) ;
	for(int i = 1 ; i <= N ; i++ )
		for(int j = 1 ; j <= K ; j++ ) scanf("%lld %lld", &buying[i][j], &selling[i][j] ) ;
	
	for(int i = 1 ; i <= N ; i++ )
		for(int j = i+1 ; j <= N ; j++ ) dist[i][j] = dist[j][i] = inf ;
 
	for(int i = 1 ,u,v,t ; i <= M ; i++ )
	{
		scanf("%d %d %d", &u, &v, &t ) ;
		dist[u][v] = (ll)t ;
	}
 
	for(int i = 1 ; i <= N ; i++ )
		for(int j= 1 ; j <= N ; j++ )
			for(int g = 1 ; g <= N ; g++ )
				dist[j][g] = min(dist[j][g], dist[j][i] + dist[i][g] ) ;
 
	for(int i = 1 ; i<= N ; i++ )
		for(int j = 1 ; j <= N ; j++ )
		{
			ll best = 0;
 
			for(int k = 1 ; k <= K ; k++ )
				if( buying[i][k] != -1 && selling[j][k] != -1 )
					best = max(best, -buying[i][k] + selling[j][k] ) ;
 
			cost[i][j] = best ;
		}
 
	ll l = 1 , r = 1000000000000000LL , mid , best = 0LL ;
 
	while( l <= r )
	{
		mid = (l+r) >> 1 ;
 
		if( test(mid) )
		{
			best = mid ;
			l = mid+1 ;
		}
		else r = mid-1 ;
 
	} 	                           
 
	printf("%lld\n", best ) ; 
 
}
