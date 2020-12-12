#include <bits/stdc++.h>
 
#define ll long long
 
using namespace std ;
 
int Q ;
ll L , R ;
 
int main()
{
 
	scanf("%d", &Q ) ;
	
	ll val[9] = {9,1,2,3,4,5,6,7,8} ;
	ll cte = 45 ;
 
	while(Q--)
	{
		scanf("%lld %lld", &L , &R ) ;
 
		ll ans = 0LL ;
 
		if(R - L + 1 <= 1000 )
		{
			for(ll i = L ; i <= R ; i++ ) ans += val[ i%9 ] ;
			printf("%lld\n", ans ) ;
			continue ;				
		}
 
		for(; L % 9 != 0 ; L++ ) ans += val[L%9] ;
		for(; R % 9 != 8 ; R--) ans += val[ R%9 ] ;
 
		ans += cte * ( (R-L+1)/9LL ) ;
 
		printf("%lld\n", ans ) ;
 
	}
 
}
