#include <bits/stdc++.h>

//Ainda nao consegui submeter

const int MAXN = 35 ;

using namespace std ;

int N , mask ;
int mat[MAXN][MAXN] ;
unordered_map<int, int> dp ;

void solve()
{
	if( dp.find(mask) != dp.end() ) return ;

	int k = __builtin_ctz(mask) ;
	int ans = 0 ;

	mask ^= (1<<k) ;

	for(int i = k+1 ; i < N ; i++ )
	{
		if( ((1<<i)&mask ) == 0 ) continue ;

		mask ^= (1<<i) ;

		solve() ;

		ans = max(ans, mat[i][k]+dp[mask] ) ;

		mask ^= (1<<i) ;

	}

	mask ^= (1<<k) ;

	dp.insert( make_pair(mask, ans) ) ;

}

int main()
{
	scanf("%d", &N ) ;
	for(int i = 0 ; i < N ;i++ )
		for(int j= 0 ; j < N ; j++ ) scanf("%d", &mat[i][j]) ;

	mask = (1<<N) - 1 ;
	dp.insert(make_pair(0,0) ) ;

	solve() ;

	printf("%d\n", dp[mask] ) ;

}
