#include <bits/stdc++.h>
 
#define ll long long
 
using namespace std ;
 
int N ;
int val[30] ;
ll dp[15][310][11][11] ;
ll aux[310] ;
char str[30] ;
 
bool case1(int a, int b)
{
	if( str[a] == 'x' || str[b] == '-' ) return true ;
	if( str[b] == '/' ) return false ;
	if( str[a] != '?' || str[b] != '?' ) return false ;
	return true ;
}
 
bool case2(int a, int b)
{
	if( str[a] == 'x' || str[b] == '-' ) return false ;
	if( str[b] == '/' ) return true ;
	if(str[b] != '?' ) return false ;
	return true ;
}
 
void solve()
{
	scanf("%d", &N ) ;
	for(int i = 1 ; i <= 2*N + 1 ; i++ ) scanf(" %c" , &str[i] ) ;
	for(int i = 1 ; i<= N ; i++ ) scanf("%d", &val[i] ) ;
 
	for(int a = 1 ; a <= N ; a++ )
		for(int i = 0 ; i <= 300 ; i++ )
			for(int j = 0 ; j <= 10 ; j++ )
				for(int k = 0 ; k <= 10 ; k++ ) dp[a][i][j][k] = 0 ;
 
	for(int i = 0 ; i <= 10 ; i++ )
		for(int j = 0 ; j <= 10 ; j++ ) dp[0][0][i][j] = 1 ;
 
	for(int i = 1 , idx = 1 ; i < N ; i++ , idx += 2 )
	{
		if( case2(idx, idx+1) )
		{
			for(int j = 0 ; j <= 300 ; j++ )
				for(int b = 0 ; b <= 10 ; b++)
				{
					for(int a = 0 ; a < 10 ; a++ )
					{
						if( str[idx] != '?' && a != str[idx]-'0' ) continue ;
						if( j-b-10 <0  ) continue ;
 
						dp[i][j][b][0] += dp[i-1][j-b-10][a][10-a] ;
					}
 
					for(int a = 1 ; a <= 10 ; a++ )
						dp[i][j][b][a] += dp[i][j][b][0] ;
				}
 
		}
 
		for(int j = 0 ; j <= 300 ; j++ ) aux[j] = 0 ;
 
		if( str[idx] != 'x' && str[idx+1] != '/' && str[idx+1] != '-' )
		{
			for(int j = 0 ; j <= 300 ; j++ )
				for(int a = 0 ; a < 10 ; a++ )
					for(int b = 0 ; b < 10-a ; b++ )
					{
						if( str[idx] != '?' && str[idx]-'0' != a ) continue ;
						if( str[idx+1] != '?' && str[idx+1]-'0' != b ) continue ;
						if( j-a-b < 0 ) continue ;
 
						aux[j] += dp[i-1][j-a-b][a][b] ;
					}
		}
 
 
		for(int j = 0 ; j <= 300 ; j++ )
			for(int a = 0 ; a <= 10 ; a++ )
				for(int b = 0 ; b <= 10 ; b++ )
				{
					dp[i][j][a][b] += aux[j] ;
 
					if( case1(idx,idx+1) && j-a-b-10 >= 0) dp[i][j][a][b] += dp[i-1][j-a-b-10][10][a] ;
				}
 
		if( val[i] != -1 )
		{
			for(int j = 0 ; j <= 300 ; j++ )
			{
				if(j == val[i]) continue ;
 
				for(int a = 0 ; a <= 10 ; a++ )
					for(int b = 0 ; b <= 10 ; b++ ) dp[i][j][a][b] = 0 ;
			}
		}
 
	}
 
	int lim_low = (val[N] == -1) ? 0 : val[N] ;
	int lim_up = (val[N] == -1 ) ? 300 : val[N] ;
 
	ll ans = 0;
 
	char x = str[(N<<1)-1] ;
	char y = str[N<<1] ;
	char z = str[ (N<<1)+1 ] ;
 
	vector<char> v = { '0' , '1' , '2' , '3' , '4' , '5' , '6' , '7' ,'8' , '9' , '-' , '/' , 'x'} ;
 
	for(int i = lim_low ; i <= lim_up ; i++ ) 
		for(auto a : v )
			for(auto b : v )
				for(auto c : v )
				{
					if(x != '?' && a != x ) continue ;
					if(y != '?' && y != b) continue ;
					if( z != '?' && z != c ) continue ;
 
					if(a == '/' || a == '-' || b == '-') continue ;
 
					int da , db , dc ;
 
					if(a == 'x') da = 10 ;
					else da = a-'0' ;
 
					if(b == '/')
					{
						if( da == 10 ) continue ;
						db = 10-da ;
					}
					else 
					{
						if(b == 'x') db = 10 ;
						else db = b-'0' ;
 
						if(da != 10 && db+da >= 10 ) continue ;
					}
 
					if( c == '-' )
					{
						if(da+db >= 10) continue ;
						dc = 0 ;
					}
					else 
					{
						if(da+db < 10) continue ;
						
						if(da == 10)
						{
							if(db == 10)
							{
								if( c == '/' ) continue ;
								if(c == 'x') dc = 10 ;
								else dc = c-'0' ;
							}
							else
							{
								if( c == '/' ) dc = 10-db ;
								else
								{
									if ( c == 'x' ) dc = 10 ;
									else dc = c-'0' ;
 
									if(db+dc >= 10) continue ;
								}
							}
						}
						else 
						{
							if( c == '/' ) continue ;
							if(c == 'x') dc = 10 ;
							else dc = c-'0' ;
						}
 
 
					}
 
					if( i-da-db-dc >= 0 )
						ans += dp[N-1][i-da-db-dc][da][db] ;
 
				}
 
	printf("%lld\n" , ans ) ;
}
 
int main()
{
	int T ;
	scanf("%d", &T ) ;
	while(T--) { solve() ; }
}
