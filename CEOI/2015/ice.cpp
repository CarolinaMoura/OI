#include <bits/stdc++.h>

#define all(x) x.begin(),x.end()
#define sz(x) (int)(x.size())
#define ll long long

using namespace std ;

bool isOn(int i, int m) { return ((1<<i)&m) != 0 ; }

int main()
{
	int n ;
	ll budget ;

	scanf("%d %lld", &n, &budget ) ;

	vector<ll> vec[2] ;
	vec[0].resize( max(n/2,0) ) ;
	vec[1].resize( max(n - (n/2) , 0) ) ;

	for(int i = 0 ; i < n/2 ; i++ ) scanf("%lld", &vec[0][i]) ;
	for(int i = n/2 , j = 0 ; i < n ; i++, j++ ) scanf("%lld", &vec[1][j]) ;

	vector<ll> ways[2] ;
	long long ans = 0LL ;

	for(int i = 0, qtd ; i < 2 ; i++ )
	{
		qtd = (int)( vec[i].size() ) ;

		for(int j = 0 ; j < (1<<qtd) ; j++ )
		{
			long long mySum = 0 ;

			for(int g = 0 ; g < qtd ; g++ )
				if(isOn(g,j)) mySum += vec[i][g] ;

			ways[i].push_back(mySum) ;

		}

		sort(all(ways[i])) ;

	}

	for(long long mySum : ways[0] ) 
	{

		int l = 0 , r = sz(ways[1])-1 , mid , best = -1 ;

		while( l <= r )
		{
			mid = (l+r)>>1 ;

			if( mySum + ways[1][mid] <= budget )
			{
				best = mid ;
				l = mid+1 ;
			}
			else r = mid-1 ;

		}

		ans += 1LL + (ll)best ;

	}

	printf("%lld\n" , ans ) ;

}
