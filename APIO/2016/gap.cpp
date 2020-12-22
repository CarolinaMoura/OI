#include "gap.h"
#include <bits/stdc++.h>

#define all(x) x.begin(),x.end()
#define sz(x) (int)(x.size() )
#define ll long long 

const ll MAX = 1e18 ;

using namespace std ;

long long findGap(int T, int N)
{
	
	if( T == 1 || N <= 7 )
	{
		vector<ll> a(N) ;

		MinMax(0LL,MAX, &a[0] , &a[N-1] ) ;

		for(int l = 1 , r = N-2 ; l <= r ; l++ , r-- )
			MinMax(a[l-1]+1, a[r+1]-1, &a[l], &a[r] ) ;
		
		ll resp = -1LL ;

		for(int i = 0 ; i < N-1 ; i++ ) resp = max(resp, a[i+1]-a[i] ) ;

		return resp ; 

	}

	ll smallest, biggest, mn, mx ;

	MinMax(0, MAX, &smallest, &biggest ) ;

	ll d = (biggest-smallest-1)/(N-1) ;

	vector<ll> vec(1, smallest) ;

	int cnt = 0 ;

	for(ll l = smallest+1 ; l < biggest ; l += d+1 )
	{
		MinMax(l, min(l+d, biggest-1) , &mn, &mx) ;
		
		cnt++ ;

		if(mn == -1 ) continue ;

		vec.push_back(mn) ;
		vec.push_back(mx) ;

	}

	vec.push_back(biggest) ;

	d = 0LL ;

	for(int i = 0 ; i < vec.size() - 1 ; i++ ) d = max(d, vec[i+1]-vec[i] ) ;
    	return d ;

}
