#include <bits/stdc++.h>
 
const int MAXN = 2010 ;
const int MOD = 1e9+7 ;
 
using namespace std ;
 
int N , S , T ;
long long dp[MAXN][MAXN] ;
 
int main()
{
	scanf("%d %d %d", &N , &S, &T ) ;
 
	if( S > T ) swap(S,T) ;
 
	dp[0][1] = 1 ;
 
	for(int i = 1 ; i < N ; i++ )
		for(int j= 1 ; j <= N-i ; j++ )
		{
			long long &ptr = dp[i][j] ;
			long long fat ;
 
			if( i == T || i == S )
			{
				ptr = dp[i-1][j+1] + dp[i-1][j] ;
				if( ptr >= MOD ) ptr -= MOD ;
				continue ;
			}
		
			//creating new component
			fat = (j-1) + ( i > S ) + (i > T ) ;
			ptr = (fat * dp[i-1][j+1] ) % MOD ;
 
			//joining two components
			ptr += (dp[i-1][j-1] * (j-1) ) % MOD ;
			ptr %= MOD ;
 
		}
 
	long long ans = dp[N-1][1] ;
 
	printf("%lld\n", ans ) ;
}
