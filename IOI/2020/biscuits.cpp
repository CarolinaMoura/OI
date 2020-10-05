#include "biscuits.h"
#include <bits/stdc++.h>

#define lp(i,a,b) for(int i = a; i < b; i++)
#define debug printf
#define ff first
#define ss second
#define sz(x) (int)(x.size()) 
#define all(x) x.begin(),x.end()
#define ll long long
 
using namespace std ;

ll x ;
vector<ll> soma(60,0LL) ;
vector<ll> dp(61, 0LL) ;

ll calc(ll A)
{

	if(A < 0LL ) return 0LL ;
	if(A == 0LL) return 1LL ;

	int i = 0 ;
	for(i = 59 ; i >= 0 ; i-- )
		if((1LL<<i) <= A) break ;

	return dp[i] + calc( min(A,(soma[i]/x)) - (1LL<<i) ) ;

}

long long count_tastiness(long long xx, vector<long long> a ) 
{
	x = xx ;

	while(sz(a) < 60) a.push_back(0LL) ;
	lp(i,0,61) dp[i] = 0LL ;

	dp[0] = 1LL ;

	for(int i = 0 ; i < 60 ; i++ )
	{
		soma[i] = a[i] * (1LL<<i) ;
		if(i) soma[i] += soma[i-1] ;
	}

	for(int i = 1 ; i <= 60 ; i++ )
		dp[i] = calc( (1LL<<i)-1LL ) ;

	return dp[60] ;
}
