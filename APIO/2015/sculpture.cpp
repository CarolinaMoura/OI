#include <bits/stdc++.h>

#define ll long long
#define all(x) x.begin(),x.end()

const int MAX = 2010 ;
const int LOG = 43 ;

using namespace std ;

int n , a , b ;
ll arr[MAX] ;

void solve1()
{

	vector<int> dp(n+1) ;

	long long mask = 0 ;

	for(int i = LOG-1 ; i >= 0 ; i-- )
	{
		dp[0] = 0 ;

		for(int j = 1 ; j <= n ; j++ )
		{
			ll curSum = 0LL ;
			dp[j] = n+1 ;

			for(int g = j ; g > 0 ; g-- )
			{
				curSum += arr[g] ;

				ll newMask = curSum >> i ;
				newMask <<= i ;

				if( (newMask|mask) == mask )				
					dp[j] = min(dp[j] , dp[g-1] + 1 ) ;
			}

		}

		if(dp[n] > b ) mask |= (1LL<<i) ;

	}
	
	printf("%lld\n", mask ) ;

}

void solveGeneral()
{
	
	vector< vector<bool> > dp(b+1, vector<bool>(n+1) ) ;

	ll mask= 0LL ;
	
	for(int i = 38 ; i >= 0 ; i-- )
	{

		for(int j = 1 ; j <= n ; j++ ) dp[0][j] = false ;
		dp[0][0] = true ;

		for(int qtdGroups = 1 ;qtdGroups <= b ; qtdGroups++ )
		{
			for(int j = 1 ; j <= n ; j++ ) 
			{
				dp[qtdGroups][j] = false ;

				ll curSum = 0LL ;

				for(int g = j ; g > 0 && !dp[qtdGroups][j] ; g-- )
				{
					curSum += arr[g] ;

					ll newMask = curSum >> i ;
					newMask <<= i ;

					if( (newMask|mask) == mask )
						dp[qtdGroups][j] = dp[qtdGroups-1][g-1] ;

				}

			}
		}

		bool ok = false ;
		for(int j = a ; j <= b ; j++ ) ok |= dp[j][n] ;

		if(!ok) mask |= (1LL<<i) ;

	}
		
	printf("%lld\n", mask ) ;


}

int main()
{
	
	scanf("%d %d %d", &n, &a, &b ) ;
	for(int i= 1 ; i <= n ;i++ ) scanf("%lld", &arr[i] ) ;

	if(a == 1 ) solve1() ;
	else solveGeneral() ;

}
