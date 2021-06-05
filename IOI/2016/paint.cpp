#include "paint.h"
#include <bits/stdc++.h>
 
#define all(x) x.begin(),x.end()
#define sz(x) (int)(x.size() )
#define ll long long
 
const int MAXN = 2e5+10 ;
const int MAXK = 110 ;
const ll MOD = 1e9+7 ;
 
using namespace std ;
 
int N , K ;
int sv_black[MAXN] , sv_white[MAXN] ;
string s ;
vector<int> c ;
ll dp[MAXN][MAXK] , dpPref[MAXN][MAXK], dpSuf[MAXN][MAXK] ;
 
int getBlack(int l, int r ) { return sv_black[r] - sv_black[l-1] ; }
int getWhite(int l, int r ) { return sv_white[r] - sv_white[l-1] ; }
 
void calc()
{
	dp[0][0] = 1 ;
 
	for(int i = 1 ; i <= N ; i++ )
	{
		dp[i][0] = (getBlack(1,i) == 0 ) ;
 
		for(int j = 1 ; j <= K ; j++ )
		{
			dp[i][j] = dp[i-1][j] * ( s[i] != 'X' ) ;
		
			if( i-c[j] < 0 || getWhite(i-c[j]+1, i) ) continue ;
			if( i-c[j] > 0 && s[i-c[j]] == 'X' ) continue ;
 
			if( i-c[j] == 0 ) dp[i][j] += (j == 1 ) ;
			else dp[i][j] += dp[i-c[j]-1][j-1] ;
 
			if( dp[i][j] >= MOD ) dp[i][j] -= MOD ;
		}
	}
}
 
void calc_sv()
{
	for(int i = 1 ; i <= N ; i++ )
	{
		sv_black[i] = ( s[i] == 'X' ) ;
		sv_white[i] = ( s[i] == '_' ) ;
 
		sv_black[i] += sv_black[i-1] ;
		sv_white[i] += sv_white[i-1] ;
	}
 
}
 
string solve_puzzle(string _s, vector<int> _c) 
{
	s = _s ;
	c = _c ;
 
	N = sz(s) ;	
	K = sz(c) ;
 
	c.insert(c.begin() , 0 ) ;
	c.push_back(0) ;
	s.insert( s.begin() , '.' ) ;
	s.push_back('.') ;
 
	calc_sv() ;
	calc() ;
 
	for(int i = 0 ; i <= N ; i++ )
		for(int j = 0 ; j <= K ; j++ )
		{
			dpPref[i][j] = dp[i][j] ;
			dp[i][j] = 0 ;
		}
 
	reverse( all(c) ) ;
	reverse( all(s) ) ;
 
	calc_sv() ;
	calc() ;
 
	for(int i = 0 , j = N+1 ; i <= N ; i++ , j-- )
		for(int a = 0 , b = K+1 ; a <= K ; a++ , b-- )
			dpSuf[j][b] = dp[i][a] ;
 
	reverse( all(c) ) ;
	reverse( all(s) ) ;
	
	for(int i = 1 ; i <= N ; i++ )
	{
		if( s[i] == 'X' ) continue ;
 
		ll qtd_as_white = 0 , temp ;
 
		for(int j = 0 ; j <= K ; j++ )
		{
			temp = dpPref[i-1][j] * dpSuf[i+1][j+1] ;
			temp %= MOD ;
 
			qtd_as_white += temp ;							
			if( qtd_as_white >= MOD ) qtd_as_white -= MOD ;
		}			
 
		if( qtd_as_white == dpPref[N][K] ) s[i] = '_' ;
		else if( qtd_as_white == 0 ) s[i] = 'X' ;
		else s[i] = '?' ; 
 
	}
 
	string ans ;
	for(int i = 1 ; i<= N ; i++ ) ans.push_back(s[i] ) ;
 
	return ans ;
}
