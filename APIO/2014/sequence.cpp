#include <bits/stdc++.h>
 
#define debug printf
#define lp(i,a,b) for(int i = a ; i < b ; i++ )
#define ff first
#define ss second
#define pb push_back
#define mk make_pair
#define ll long long
#define sz size()
#define pii pair<int,int>
#define all(x) x.begin(),x.end()
#define tiii tuple<int,int,int>
#define mkt make_tuple
 
const int MAXN = 1e5+10 , MAXK = 210 ;
 
using namespace std ;
 
int n , k , mid , opt ;
int a[MAXN] ;
int myOpt[MAXK][MAXN] ;
ll val , cur ;
ll sufSum[MAXN] ;
ll dp[2][MAXN] ;
 
 
void calcDp(int l , int r , int optmin , int optmax, int am, int mod )
{
 
	if( r < l ) return ;
 
	val = 0;
	mid = (l+r)>>1 ;
	opt = mid+1 ;
 
	lp(i,max(optmin-1,mid)+1,optmax+1)
	{
		cur = dp[!mod][i] + (sufSum[mid] - sufSum[i])*sufSum[i] ;
		if( cur > val ) val = cur, opt = i ;
	}
 
	dp[mod][mid] = val ;
	myOpt[am][mid] = opt ;
 
	calcDp(l,mid-1, optmin, opt , am, mod ) ;
	calcDp(mid+1, r, opt, optmax, am, mod ) ;
 
}
 
char c ;
void read(int &num )
{
	num = 0 ;
	c = getchar() ;
	for(; (c>47 && c<58);c=getchar())
		num = num*10 + c - 48 ;
}
 
int main()
{
	read(n) , read(k) ;
	lp(i,1,n+1)read(a[i]) ;
 
	for(int i = n ; i > 0 ; i-- ) sufSum[i] = sufSum[i+1] + a[i] ;
	lp(i,1,k+1) calcDp(1,n - i,1,n-i+1,i, i%2 ) ;
 
	printf("%lld\n", dp[k%2][1] ) ;
 
	int cur = 1 ;
	for(int i = k ; i > 0 ; i-- )
	{
		cur= myOpt[i][cur] ;
		printf("%d " , cur-1 ) ;
	}
 
	printf("\n") ;
 
}
