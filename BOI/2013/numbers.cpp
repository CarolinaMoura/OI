#include <bits/stdc++.h>

#define ll long long
#define all(x) x.begin(),x.end()
#define sz(x) (int)(x.size() )

const int MAX_DIGITS = 25 ;

using namespace std ;

ll dp[MAX_DIGITS][2][15][15] ;

ll solve(string x)
{

	ll tot = 0LL ;

	reverse(all(x));

	for(int i = 0 ; i < 12 ; i++ )
		for(int j = 0 ; j < 12 ; j++ )
			if(i != j ) dp[0][0][i][j] = dp[0][1][i][j] = 1 ;

	for(int i = 1 ; i <= sz(x) ; i++ )
		for(int penultimo = 0 ; penultimo <= 10 ; penultimo++ )
			for(int ultimo = 0 ; ultimo <= 10 ; ultimo++ )
			{
				if( ultimo == penultimo ) continue ;

				dp[i][0][penultimo][ultimo] = dp[i][1][penultimo][ultimo] = 0 ;

				for(int j = 0 ; j < x[i-1]-'0' ; j++ )				
				{
					if( j == ultimo || j == penultimo ) continue ;

					dp[i][0][penultimo][ultimo] += dp[i-1][1][ultimo][j] ;
					dp[i][1][penultimo][ultimo] += dp[i-1][1][ultimo][j] ;
				}

				if( x[i-1]-'0' != ultimo && x[i-1]-'0' != penultimo )
					dp[i][0][penultimo][ultimo] += dp[i-1][0][ultimo][ x[i-1]-'0' ] ;

				for(int j = x[i-1]-'0' ; j <= 9 ; j++ )
					if( j != ultimo && j != penultimo )
						dp[i][1][penultimo][ultimo] += dp[i-1][1][ultimo][j] ;					
				
			}

	for(int i = 1 ; i < sz(x) ; i++ )
		tot += dp[i][1][0][10] ;

	tot += dp[sz(x)][0][0][10] ;

	return tot ;

}

int main()
{

	ios_base::sync_with_stdio(false) ;
	cin.tie(NULL) ;

	string a,b ;
	cin >> a >> b ;

	ll ans = 1LL ;

	for(int i =0 ; i < sz(a) ; i++ )
		for(int j = i+1 ; j < sz(a) ; j++ )
		{
			bool isPalindrome = true ;
			
			for(int l = i , r = j ; l < r ; l++ , r-- )
				isPalindrome &= (a[l] == a[r] ) ;

			if(isPalindrome) ans = 0 ;
		}

	ans += solve(b) - solve(a) ;

	cout << ans << endl ;

}
