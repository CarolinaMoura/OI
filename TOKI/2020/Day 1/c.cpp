/*
Problema super interessante!
*/

#include <bits/stdc++.h>

#define all(x) x.begin(),x.end()
#define ll long long
#define sz(x) (int)(x.size())

const int MAXN = 5e4+10 ;
const int MAXK = 410 ;

using namespace std ;

int n , m , k ;
int a[MAXN] ;
int dp[MAXN][MAXK] , iPoint[MAXN][MAXK] ;
int excluded[MAXN][MAXK] ;
vector<int> freq[MAXN] ;

int main()
{
	scanf("%d%d%d", &n, &m , &k ) ;
	for(int i = 1 ; i <= n ; i++ )
	{
		scanf("%d", &a[i] ) ;
		freq[a[i]].push_back(i) ;
	}

	if(k >= n )
	{
		printf("0\n") ;
		return  0; 
	}

	vector<int> ptr(MAXN,0) ;

	for(int i = 1 ; i <= n ; i++ )
	{
		int recentlyAdded = -1 ;

		if( ptr[a[i]] >= m )
			recentlyAdded = freq[a[i]][ptr[a[i]]-m] ;

		ptr[a[i]]++ ;

		for(int j = 0 ; j <= k ; j++ )
		{
		   if(recentlyAdded == -1 || iPoint[i-1][j] > recentlyAdded )
		   	iPoint[i][j] = iPoint[i-1][j] ;

		   else iPoint[i][j] = ( j == 0 ) ? recentlyAdded : min( recentlyAdded, iPoint[i-1][j-1] ) ;
			
		}

	}

/*	for(int i = 1 ; i <= n ; i++ ,printf("\n") ) 
		for(int j = 0 ; j <= k ; j++ ) printf("%d ", iPoint[i][j] ) ;*/

	for(int i = 1 ; i <= n ; i++ )
	{	
		dp[i][0] = 1 + dp[iPoint[i][0]][0] ;

		for(int j = 1 ; j <= k ; j++ )
		{
			vector<int> pos = {excluded[i-1][j], excluded[i-1][j]+1 , 0, excluded[i-1][j-1]+1 } ;

			dp[i][j] = n+5 ;

			for(auto e : pos )
			{
				if(e > j ) continue ;

				if( dp[i][j] > 1 + dp[iPoint[i][e]][j-e] || (dp[i][j] == 1+dp[iPoint[i][e]][j-e] && e < excluded[i][j] ) )
				{
					dp[i][j] = 1 + dp[iPoint[i][e]][j-e] ;
					excluded[i][j] = e ;
				}	
			}

		}

	}

	printf("%d\n", dp[n][k] ) ;

}
