#include "wiring.h"
#include <bits/stdc++.h>
 
#define debug printf
#define lp(i,a,b) for(int i = a ; i < b; i++)
#define pb push_back
#define ff first
#define ss second
#define mk make_pair
#define pii pair<int,int>
#define ll long long 
#define all(x) x.begin(),x.end()
#define sz(x) (int)(x.size())
 
const ll inf = 1e15+10 ;
 
using namespace std ;
 
long long min_total_length(vector<int> r, vector<int> b) 
{
	int n = sz(r) ;
	int m = sz(b) ;
 
	vector< pair<long long,int> > loc(n+m) ;
	for(int i = 0 ; i < n ; i++ ) loc[i] = make_pair( r[i] , 0 ) ;
	for(int i = n ; i < n+m ; i++ ) loc[i] = make_pair(b[i-n] , 1 ) ;
	sort(all(loc)) ;
	
	vector<int> ini(n+m,-1) , fim(n+m,-1) , bestIndex(n+m,-1) ; 
	vector< long long > dp(n+m+1, inf ) , minPrefix(n+m, inf) , s(n+m,0) ;
	vector<long long> meuValor(n+m) ;
 
	for(int i = 0 ; i < sz(loc) ; i++ )
	{
		if(ini[i] == -1) ini[i] = i ;
 
		if( i < sz(loc)-1 && loc[i+1].ss == loc[i].ss ) ini[i+1] = ini[i] ; 
		else for(int j = ini[i] ; j <= i ; j++ ) fim[j] = i ;
 
		s[i] = loc[i].ff ;
		if(i) s[i] += s[i-1] ;
 
	}
 
	dp[n+m] = 0LL ;
 
	for(int i = n+m-1 ; i >= 0 ; i-- )
	{
		if( fim[i] == n+m-1 )
		{
			minPrefix[i] = s[i] - s[ ini[i] ] - (ll)( i - ini[i] ) * loc[ ini[i] ].ff + dp[i+1];
			dp[i] = min( dp[i] , dp[i+1] + loc[i].ff - loc[ini[i]-1].ff) ;
 
			if( i == ini[i] )
				for(int j = i+1 ; j <= fim[i] ; j++ ) minPrefix[j] = min(minPrefix[j] , minPrefix[j-1]) ;
 
			continue ;
		}
 
		int last = min(fim[i]+1 + fim[i] - i , fim[ fim[i]+1 ] ) ;
 
		dp[i] = loc[ fim[i] + 1 ].ff * (fim[i] - i + 1) - ( s[ fim[i] ] - ( (i == 0) ? 0 : s[i-1] ) ) + minPrefix[last] ;
		
 		if( ini[i] ) dp[i] = min(dp[i] , loc[i].ff - loc[ ini[i]-1 ].ff + dp[i+1] ) ;
 
		if(!ini[i] || i != ini[i]) continue ;
 
		minPrefix[i] = dp[i+1] ;
 
		for(int j = i+1 ; j <= fim[i] ; j++ )
			minPrefix[j] = min(minPrefix[j-1], s[j] - s[i] - (ll)(j-i) * loc[i].ff + dp[j+1] );
 
 
	}
 
	return dp[0] ;
}
