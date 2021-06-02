#include <bits/stdc++.h>

const int MAXN = 35 ;
 
using namespace std ;
 
int N , mask ;
int mat[MAXN][MAXN] ;
unordered_map<int, int> dp ;
 
int solve()
{
	if( mask == 0 ) return 0 ;
	if( dp[mask] ) return dp[mask] ;
 
	int k = __builtin_ctz(mask) ;
	int ans = 0 ;
 
	mask ^= (1<<k) ;
 
	for(int i = k+1 ; i < N ; i++ )
	{
		if( ((1<<i)&mask ) == 0 ) continue ;
 
		mask ^= (1<<i) ;
  
		ans = max(ans, mat[i][k]+solve() ) ;
 
		mask ^= (1<<i) ;
 
	}
 
	mask ^= (1<<k) ;
 
	return dp[mask] = ans ; 
}
 
int main()
{
	scanf("%d", &N ) ;
	for(int i = 0 ; i < N ;i++ )
		for(int j= 0 ; j < N ; j++ ) scanf("%d", &mat[i][j]) ;
 
	mask = (1<<N) - 1 ;
  
	printf("%d\n", solve() ) ;
 
}
