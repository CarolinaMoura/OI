#include <bits/stdc++.h>
 
#define ll long long
#define all(x) x.begin(),x.end()
#define sz(x) (int)(x.size() )
#define lp(i,a,b) for(int i = a;  i< b ; i++ )
#define pii pair<int,int> 

const int MAXN = 1e5+10 ;
const ll inf = 1e15+10LL ;

using namespace std ;

int N , K ;
int lef[MAXN] , opt[MAXN] ;
ll arr[MAXN];
ll dp[2][MAXN] ;

int main()
{
	scanf("%d %d", &N , &K ) ;
	for(int i = 1 , mx = 0  ; i <= N ; i++ ) 
	{
		scanf("%lld", &arr[i] ) ;
	
		if( arr[i] > mx ) mx = arr[i] ;
		
		dp[0][i] = mx ;

	}

	if( K == 1 ) 
	{
		printf("%lld\n", dp[0][N] ) ;
		return 0 ;
	}

	dp[0][0] = dp[1][0] = inf ;

	int toGet = 0 , toFill = 1 ;
	for(int i = 2 ;  i<= K ; i++ , swap(toGet,toFill) )
	{
		for(int j = 1 ; j <= N ; j++ )
		{
			//if I'm forming my block where I'm the maximum
			lef[j] = j-1 ;
			opt[j] = j-1 ;

			while( lef[j] && arr[j] > arr[ lef[j] ] )
			{
				if( dp[toGet][opt[lef[j]]] < dp[toGet][ opt[j] ] )
					opt[j] = opt[ lef[j] ] ;

				lef[j] = lef[ lef[j] ] ;							
			}

			//if I'm forming my block where I'm not the maximum
			if( lef[j] && dp[toFill][ lef[j] ] < dp[toGet][ opt[j] ] + arr[j] )
				dp[toFill][j] = dp[toFill][lef[j] ] ;

			else dp[toFill][j] = dp[toGet][ opt[j] ]+arr[j] ;

		}
	}

	printf("%lld\n", dp[toGet][N] ) ;
		
}
