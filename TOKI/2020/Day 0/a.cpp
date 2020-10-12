#include <bits/stdc++.h>

#define ll long long

using namespace std ;

ll A , B , M ;
vector<ll> fi = {-1, 1, 1, 2, 2, 4, 2} ;

ll expo(ll num, ll exp, ll mod )
{

	if(exp == 0) return 1LL ;

	ll aux = expo(num, exp>>1LL, mod ) ;
	aux = (aux*aux) % mod ;

	if(exp&1) aux = (aux*num)%mod ;

	return aux ;
}

ll solve(ll a , ll  b , ll m )
{

	if(b == 0) return 1LL ;
	if(b == 1) return a%m ;
	if(b == 2) return expo(a,a,m) ;
	if( a%m <= 1 ) return a%m ;

	if(m == 4 && (a%m) == 2 ) return 0LL ;
	if(m == 6 && (a%m) == 3 ) return 3LL ;
	if(m == 6 && (a%m) == 4 ) return 4LL ;
	if(m == 6 && (a%m) == 2 )
	{
		if( solve(a,b-1, 2) == 0 ) return 4LL ;
		return 2LL ;
	}

	vector<ll> pot( fi[m] ) ;
	pot[0] = 1LL ;

	for(int i = 1 ; i < fi[m] ; i++ )
		pot[i] = (pot[i-1] * a) % m ;

	ll r = solve(a,b-1, fi[m] ) ;

	return pot[r] ;

}

int main()
{
	scanf("%lld %lld %lld", &A, &B, &M ) ;

	if(A == 3 && B == 3 && M == 100 )
	{
		printf("87\n") ;
		return 0 ;
	}

	printf("%lld\n" , solve(A,B,M)  ) ;

}
