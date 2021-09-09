#include <bits/stdc++.h>

#define debug 
#define ll long long

const ll MOD = 1e9+7 ;
const int MAX = 3010 ;

using namespace std ;

int N ;
ll dp[2][MAX][2] ;
pair<int,int> v[MAX*2] ;

ll m(ll x) { return x%MOD ; }

int main()
{
	scanf("%d", &N ) ;
	for(int i = 0 , x = 1 ; i < 2 ; i++ )
		for(int j = 0 ;j < N ; j++ , x++ ) 
		{
			scanf("%d", &v[x].first) ;
			v[x].second = i ;
		}
		
	sort(v+1, v+2*N+1 ) ;
	
	int toGet = 0 , toFill = 1 ;
	
	for(int i = 1 ; i <= 2*N ; i++ ) debug("%d %d\n" , v[i].first, v[i].second ) ;
	
	dp[0][0][0] = 1 ;
	for(int i = 1 ; i <= 2*N ; i++, swap(toGet, toFill) )
	{
		for(int j = 0 ; j <= i ; j++ )
		{
			if( v[i].second == 0 ) //vaca
			{
				//caso 0: todas as vacas menores ou iguais a mim precisam ser colocadas para parear
				if(j-1>=0) dp[toFill][j][0] = dp[toGet][j-1][0] ;
				else dp[toFill][j][0] = 0 ;
				
				//caso 1: posso escolher me colocar ou nao
				dp[toFill][j][1] = m(dp[toGet][j][0]+dp[toGet][j][1]) ;
				if(j-1 >= 0 ) dp[toFill][j][1] = m( dp[toFill][j][1] + dp[toGet][j-1][1] ) ;				
			}
			else //celeiro
			{
				//caso 0
				dp[toFill][j][0] = dp[toGet][j][0] ;
				dp[toFill][j][0] = m( dp[toFill][j][0] + m(dp[toGet][j+1][0]*(j+1)) ) ;
				
				//caso 1: sou obrigada a parear com alguem
				dp[toFill][j][1] = m(dp[toGet][j+1][1] * (j+1) ) ;
			}
		}
	}
		
	printf("%lld\n", m(dp[toGet][0][0]+dp[toGet][0][1]) ) ;
}
