#include <bits/stdc++.h>

#define lp(i,a,b) for(int i = a ; i < b ; i++ )
#define ll long long

const int MAXN = 1510 ;

using namespace std ;

int n , m ,k ;
ll ans ;
ll suffixColumn[MAXN][MAXN] , suffixRow[MAXN][MAXN] , val[MAXN][MAXN] ;
ll sub[MAXN][MAXN] , aux[MAXN][MAXN] ;
pair<int,int> rotation[MAXN][MAXN] ;

ll getRectangle(int rMin ,int rMax, int cMin,int cMax)
{
	if( rMin < 1 || rMax > n || cMin < 1 || cMax > m ) 
		return 0 ;

	return sub[rMax][cMax] - sub[rMin-1][cMax] - sub[rMax][cMin-1] + sub[rMin-1][cMin-1] ;
}

void solve()
{

	vector<ll> backwards(n+2,0);

	for(int i = n ; i > 0 ; i-- )
	{
		backwards[i] = backwards[i+1] ;
		if( i+k-1 <= n ) backwards[i] = max(backwards[i] , suffixRow[i+k-1][1] ) ;
	}

	ll curUpper = 0 ;

	for(int i = 2 ; i <= n ; i++ )
	{
		curUpper = max(curUpper, suffixRow[i-1][1] ) ;
		
		ll curMiddle = 0 ;

		for(int j = i+1 ; j <= n ; j++ )
		{
			if(j-k >= i)
				curMiddle = max(curMiddle, suffixRow[j-1][1] ) ;

			ans = max(ans, curUpper + curMiddle + backwards[j] ) ;
			
		}

	}

	curUpper = 0 ;

	for(int i = 2 ; i <= n ; i++ )
	{
		curUpper = max(curUpper, suffixRow[i-1][1] ) ;

		if(i + k - 1 > n ) break ;

		for(int j = n ; j > 0 ; j-- )
		{
			backwards[j] = backwards[j+1] ;
			if(j+k-1 <= n )
				backwards[j] = max(backwards[j], suffixColumn[j+k-1][i+k-1] ) ; 
		}

		ll curMiddle = 0 ;

		for(int j = 2 ; j <= n ; j++ )
		{
			curMiddle = max(curMiddle, suffixColumn[j-1][i+k-1] ) ;
			ans = max(ans, curUpper+curMiddle+backwards[j]) ;				
		}

	}     

}

int main()
{
	scanf("%d %d %d", &n, &m , &k ) ;

	for(int i = 1 ; i <= n ; i++ )
		for(int j = 1 ; j <= m ; j++ ) scanf("%lld", &val[i][j] ) ;

  	n = max(n,m) ;
  	m = max(n,m) ;

	
	for(int i = 1 ; i <= n ; i++ )
		for(int j= 1 ; j <= n ; j++ )
			rotation[i][j] = make_pair(j,n-i+1) ;

	/*for(int i= 1 ; i <= n ; i++ , printf("\n") ) 
		for(int j = 1 ; j <= n ; j++ ) printf("%d ", sub[i][j] ) , aux[rotation[i][j].first][ rotation[i][j].second] = sub[i][j] ;

	for(int i = 1 ; i <= n ; i++ , printf("\n") ) 
		for(int j = 1 ; j <= n ; j++ ) printf("%d ", aux[i][j] ) ; */

	for(int g = 0 ; g < 4 ; g++ )
	{

		for(int i =1 ; i <= n ; i++ )
  			for(int j = 1 ; j <= n ; j++ )
  				sub[i][j] = val[i][j] + sub[i-1][j] + sub[i][j-1] - sub[i-1][j-1] ;

		for(int i = 1 ; i <= n ; i++ )
			for(int j = m ; j > 0 ; j-- ) 
				suffixRow[i][j] = max(suffixRow[i][j+1], getRectangle(i-k+1, i, j-k+1, j) ) ;

		for(int i = 1 ; i <= m ; i++ )	
			for(int j= n ; j > 0 ; j-- )
				suffixColumn[i][j] = max(suffixColumn[i][j+1], getRectangle( j-k+1, j, i-k+1, i ) ) ;

		solve() ;

		for(int i = 1 ; i <= n ; i++ )
			for(int j = 1 ; j <= n ; j++ )
				aux[ rotation[i][j].first ][ rotation[i][j].second ] = val[i][j] ;

		for(int i = 1; i <= n ; i++ )
			for(int j = 1 ; j <= n ; j++ ) val[i][j] = aux[i][j] ;		 

	}

	printf("%lld\n", ans ) ;

}
