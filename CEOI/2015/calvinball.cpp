#include <bits/stdc++.h>
 
#define ll long long
#define all(x) x.begin(),x.end()
#define sz(x) (int)(x.size())
 
const ll MOD = 1e6+7 ;
const int MAXN = 1e4+10 ;
 
using namespace std ;
 
int seq[MAXN] , pref[MAXN] ;
long long dp[2][MAXN] ;
 
int main()
{
 
	int n ;
	scanf("%d", &n ) ;
	for(int i = 1 ; i <= n ; i++ ) 
	{
		scanf("%d", &seq[i]) ;
		
		pref[i] = seq[i] ;
		if(pref[i-1] > pref[i]) pref[i] = pref[i-1] ;
	}
 
	for(int i = 1 ; i <= n ; i++ ) dp[0][i] = 1 ;
 
	int toFill = 1 ;
	long long ans = 1 ;
 
	for(int tam = 0 ; tam < n ; tam++ , toFill = !toFill )
	{
 
		//idx is the place that gives me a suffix of size tam
		int idx = n - tam ;
		long long toSum = dp[!toFill][ pref[idx-1] ] * (ll)(seq[idx]-1) ;
 
		ans += toSum % MOD ;
 
		if(ans >= MOD) ans -= MOD ;
 
		for(int conhecidos = n ; conhecidos >= 0 ; conhecidos-- )
		{
			ll &ptr = dp[toFill][conhecidos];
 
			ptr = ( (ll)conhecidos * dp[!toFill][conhecidos] ) % MOD ;
			ptr += dp[!toFill][conhecidos+1] ;
 
			if(ptr >= MOD ) ptr -= MOD ;
 
		}
 
	}
 
	printf("%lld\n" , ans ) ;
 
}
