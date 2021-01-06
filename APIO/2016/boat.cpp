#include <bits/stdc++.h>

#define debug printf
#define all(x) x.begin(),x.end()
#define ll long long
#define sz(x) x.size() 

const int MAXN = 1010 ;
const ll MOD = 1e9+7 ;

using namespace std ;

/* Quick description of the solution because I'm dumb and disorganized */

//dp[i][j] represents the possibilities given that I only have the boats [1;i] and the intervals [1;j]
//and is guaranteed that boat number i is going to be chosen
//For this problem, I had to come up with a little lemma (don't know if it is a well-known fact)
//(I don't do Math olympiads :P)
//Link to the "proof": https://pasteboard.co/JIrUdPL.jpg
//To find C(x+y, y) quickly, I did a trick: 
//C(x+y,y) = C(x+y-1,y-1) * (x+y)/y
//Because the inverses of 1, 2, ..., y are easily calculated in O(N)

int N , M ;
int A[MAXN] , B[MAXN] ;
int val[MAXN] ;
ll inv[MAXN] ;
ll dp[MAXN][MAXN] ;

int main()
{

	vector<int> compression ;
	inv[1] = 1 ;

	scanf("%d", &N ) ;
	for(int i = 1 ; i <= N ; i++ ) 
	{
		scanf("%d %d", &A[i], &B[i] ) ;

		compression.push_back(A[i]) ;
		compression.push_back( ++B[i] ) ;		 

		if( i > 1 )
		{
			inv[i] = ( (-MOD/i)*inv[MOD%i] ) % MOD ;
			if(inv[i] < 0 ) inv[i] += MOD ;
		}

	}

	sort(all(compression) ) ;
	compression.erase( unique(all(compression) ) , compression.end() ) ;

	M = sz(compression) ;

	for(int i = 0 ; i < M-1 ; i++ ) val[i+1] = compression[i+1] - compression[i] ;
	for(int i= 1 ; i <= N ; i++ ) 
	{
		A[i] = lower_bound(all(compression) , A[i] ) - compression.begin() +1 ;
		B[i] = lower_bound(all(compression) , B[i] ) - compression.begin() + 1 ;
	}

	for(int j = 0 ; j < M ; j++ ) dp[0][j] = 1LL ;
	ll ans = 0LL ;

	for(int i = 1; i <= N ; i++ )
	{

		for(int j = A[i] ; j < B[i] ; j++ )
		{			

			//In the beginning, cnt is C(val[j]+0, 0+1)
			ll cnt = val[j] , y = 1 ;
			ll x = val[j] ;	

			for(int person = i-1 ; person >= 0 ; person-- )
			{
				dp[i][j] += (cnt * dp[person][j-1] ) % MOD ;
				if( dp[i][j] >= MOD ) dp[i][j] -= MOD ;

				if( A[person] <= j && B[person] > j )
				{
					++x , ++y ;					
					cnt = ( ( cnt * x ) % MOD * inv[y] ) % MOD ; 
				}

			}
				
			
		}

		for(int j = 1 ; j < M ; j++ ) 
		{
			dp[i][j] += dp[i][j-1] ;
			if( dp[i][j] >= MOD ) dp[i][j] -= MOD ;
		}

		ans += dp[i][M-1] ;
		if(ans >= MOD ) ans -= MOD ;
		
	}

	
	printf("%lld\n", ans ) ;

}
