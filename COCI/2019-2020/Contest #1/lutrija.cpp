#include <bits/stdc++.h>
 
#define sz(x) (int)(x.size() )
#define ll long long
 
using namespace std ;
 
bool isPrime(ll x)
{
	if(x <= 1LL ) return false ;
 
	for(ll i = 2 ; i*i <= x ; i++ )
		if( x%i == 0 ) return false ;
	
	return true ;
}
 
void giveAns(vector<ll> &ans )
{
	if(sz(ans) == 1 ) printf("-1\n" ) ;
	else
	{
		printf("%d\n", sz(ans) ) ;
		for(auto e : ans ) printf("%lld ", e ) ;
		printf("\n") ;
	}
	exit(0) ;
}
 
void solve( ll B , vector<ll> &ans )
{
	if(B == 2)
	{
		ans.push_back(2) ;
		ans.push_back(5) ;
		ans.push_back(2) ;
 
		giveAns(ans) ;
	}
 
	if( isPrime(B-2) )
	{
		ans.push_back( 2 ) ;
		ans.push_back( B ) ;
		
		giveAns(ans) ;	
	}
	if( isPrime(B+2) )
	{	
		ans.push_back(2) ;
		ans.push_back(B+2) ;	
		ans.push_back(B) ;
 
		giveAns(ans) ;
	}
 
	ans = {-1} ;
 
	giveAns(ans) ;
}
 
int main()
{
 
	ll A , B ;	
	scanf("%lld %lld", &A, &B) ;
 
	vector<ll> ans ;
 
	if(A == 3 )
	{
		ans.push_back(3) ;
		A = 5 ;	
	} 
 
	if(A == 5 )
	{
		ans.push_back(5) ;
		A = 7 ;
	}
 
	if( A == 2 ) solve( B, ans) ;
 
	if( isPrime(A-2) ) 
	{
		ans.push_back(A) ;
		solve(B, ans) ;
	}
	if( isPrime(A+2) )
	{
		ans.push_back(A) ;
		ans.push_back(A+2) ;
		solve(B, ans) ;
	}
 
	ans = {-1} ;
 
	giveAns(ans) ;
 
}
