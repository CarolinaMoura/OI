/*
La gran función
*/
#include <bits/stdc++.h>

#define ll long long
#define all(x) x.begin(),x.end()
#define sz(x) x.size()

const ll MOD = 1e9 ;
const int MAX = 1e6 ;

using namespace std ;

int K ;
ll N , ans ;
vector<ll> dp[ 35 ] ;
ll pot[35][55] ;
ll bin[55][55] ;
ll aux[55] , pott[55] ;

void findSum(ll r)
{
	int i ;

	for(i = 29 ; i >= 0 ; i-- )
	{
		if( (1<<i) > r ) continue ;

		if( r == (1<<i) ) 
		{
			for(int j= 0 ; j <= K ; j++ ) 
				aux[j] = dp[i][j] ;

			return ;
		}
		
		break ;
	}

	ll num = r - (1LL<<i)  ;

	findSum(num) ;

	pott[0] = 1LL ;
	for(int i = 1 ; i <= K ; i++ ) pott[i] = ( pott[i-1] * num ) % MOD ;

	for(int k = K ; k > 0 ; k-- )
	{
		for(int j = 0 ; j <= k ; j++ )
		{
			aux[k] += (( (bin[k][j] * pott[j]) % MOD ) * dp[i][k-j] ) % MOD ;
			if( aux[k] >= MOD ) aux[k] -= MOD ;
		}		
	}

	aux[0] = r ;

}

int main()
{
	
	scanf("%lld %d", &N, &K ) ;

	//Easy-peasy
	for( ll i = 1LL ; i <= MAX ; i++ )
	{
		ll pot = 1LL ;
		for(int j = 1 ; j <= K ; j++ ) pot = (pot * i ) % MOD ;
		
		ans += ( pot * (N/i) ) % MOD ;
		if( ans >= MOD ) ans -= MOD ;
	}
	//

	//K-powers of every power of 2
	for(int i = 0, base = 1 ; i <= 29 ; i++ , base += base )
	{
		
		dp[i].resize(K+1) ;
		dp[i][0] = base ;

		pot[i][0] = 1LL ;
		for(int j = 1 ; j <= K ; j++ ) pot[i][j] = (pot[i][j-1] * base) % MOD ;
	}

	//Binomials
	bin[0][0] = bin[1][0] = bin[1][1] = 1 ;
	for(int k = 2 ; k <= K ; k++ )
	{
		bin[k][0] = 1 ;
		for(int i = 1 ; i <= k ; i++ )
		{
			bin[k][i] = bin[k-1][i-1] + bin[k-1][i] ;
			if( bin[k][i] >= MOD ) bin[k][i] -= MOD ;
		}
	}
		
	for(int i = 1 ; i <= K ; i++ ) dp[0][i] = 1 ;

	for(int a = 0 , b = 1 ; b <= 29 ; a++,b++ )
		for(int k = 1 ; k <= K ; k++ )
		{
			for(int j = 0 ; j <= k ; j++ )	
			{
				dp[b][k] += ( ( (bin[k][j] * pot[a][j])%MOD ) * dp[a][k-j] ) % MOD ;
				if( dp[b][k] >= MOD ) dp[b][k] -= MOD ;			
			}

			dp[b][k] += dp[a][k] ;
			if(dp[b][k] >= MOD ) dp[b][k] -= MOD ;

		}


	for(ll l , r , x = N/MAX ; x > 0 ; x-- )
	{		
		l = (N/(x+1) ) + 1 ;
		r = N/x ;

		if( l <= MAX ) l = MAX+1 ;
		if( l > r ) continue ;		

		findSum(r) ;

		ll s = aux[K] ;

		findSum(l-1) ;

		s -= aux[K] ;

		if( s < 0 ) s += MOD ;

		ans += ( s * x ) % MOD ;

		if( ans >= MOD ) ans -= MOD ;

	}

	printf("%lld\n", ans ) ;
}
