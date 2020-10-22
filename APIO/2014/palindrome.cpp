#include <bits/stdc++.h>
 
#define debug 
#define lp(i,a,b) for(int i=a;i<b;i++)
#define pii pair<int,int>
#define ll long long
#define ff first
#define ss second
#define pb push_back
#define mk make_pair
 
const int MAXN = 6e5+1 ;
const int ALF= 35 ;
 
using namespace std ;
 
// ----------------------------------------------------
 
//Call Partial
 
map<string, ll> mapa ;
bool s[110][110] ;
 
void callPartial(char str[])
{
 
	int n = strlen(str) ;
	ll ans = 0 ;
 
	lp(i,0,n) s[i][i] = true ;
	lp(i,0,n-1) s[i][i+1] = ( str[i] == str[i+1] ) ;
 
	lp(i,2, n)
		for(int j = 0 ; j + i < n ; j++ )
			s[j][j+i] = ( s[j+1][j+i-1] && str[j] == str[j+i] ) ;
 
 
	lp( i , 0, n )
		lp(j,0,n)
			if( s[i][j] )
			{
 
				string aux ;
				aux.resize(j-i+1) ;
 
				lp(k,i,j+1)
					aux[k-i] = str[k] ;
 
				if( mapa.find(aux) == mapa.end() )
					mapa.insert( mk(aux , 0) ) ;
 
				ll tot = ++ mapa[aux] ;
 
				ans = max( ans , tot * (j-i+1) ) ;
 
			}
 
 
	printf("%lld\n" , ans ) ;
 
}
 
 
// ----------------------------------------------------
 
struct Trie
{
 
	int nodes ;
	int trie[MAXN][ALF] , lazy[MAXN] , parent[MAXN] ;
	ll ans ;
 
	Trie()
	{
 
		memset(trie, 0, sizeof trie) ;
		memset(lazy,0,sizeof lazy) ;
		parent[0] = 0 ;
		nodes = 0 ;
		ans = 0 ;
 
	}
 
	// The interval becomes [l,r]
	int add( char str[] , int l , int r , int address )
	{
 
		int cur = address ;
 
		for(int i = l ; i <= r ; i++ )
		{
 
			char c = str[i] - 'a' ;
 
			if( trie[cur][c] == 0 )
			{
				trie[cur][c] = ++ nodes ;
				parent[ nodes ] = cur ;
			}
 
			cur = trie[cur][c] ;
 
		}
 
		lazy[cur] ++ ;
 
		return cur ;
 
	}
 
	int goUp( int address, int qtd )
	{
 
 
		lp(i,0,qtd) address = parent[address] ;
 
		return address ;
 
	}
 
 
	ll dfs( int cur , int depth , bool what )
	{
 
 
		ll tempAns = lazy[cur] ;
 
		lp(i,0,30)
			if( trie[cur][i] != 0 )
				tempAns += dfs(trie[cur][i] , depth+1 , what ) ;
 
		ll multiplier = ( what ?  ( depth/2 ) * 2 : ( ( (depth-1)/2 )*2 + 1 ) ) ;
 
		ans = max( ans , tempAns * multiplier ) ;
 
		debug("%d -> %lld %lld\n" , cur , tempAns , multiplier ) ;
 
		return tempAns ;
 
	}
 
 
} ;
 
int n ;
 
int p[MAXN] , myAd[MAXN] ;
 
Trie trie ;
 
char str[MAXN] ;
 
// ----------------------------------------------------
 
void findAns()
{
 
	
	//If I want an odd palindrome
	lp(i,0,27)
		if( trie.trie[0][i] != 0 )
			trie.dfs( trie.trie[0][i] , 1 , 0 ) ;
 
 
	//If I want an even palindrome
	trie.dfs( trie.trie[0][27] , 1 , 1 ) ;
 
 
}
 
void manacher()
{
 
	int center = 0 , right = -1 ;
 
	lp(i,0,n)
	{
 
		int rad= 0 , last = 0 , ant = i ;
 
		if( i <= right )
		{
			rad = min( p[2*center-i] , right - i + 1 ) ;
			last = trie.goUp( myAd[2*center-i] , p[2*center-i] - rad ) ;
			ant = rad + i ;
		}
 
 
		while( i - rad >= 0 && i + rad < n && str[i-rad] == str[i+rad] )
			{ rad ++ ; }
 
		myAd[i] = trie.add(str, ant , i+rad-1 , last ) ;
		p[i] = rad ;
 
		debug("With center %d, we have a ratio of %d and the last I used was %d and it became %d\n\n" , i , rad  , last , myAd[i]) ;
 
		if( i+rad-1 > right )
		{
			center = i ;
			right = i+rad-1 ;
		}
 
	}
 
 
}
 
// ----------------------------------------------------
 
 
int main()
{
 
	char difStr[MAXN] ;
 
	scanf(" %s" , difStr ) ;
 
	if( strlen(difStr) <= 100 ) 
	{
		callPartial(difStr) ;
		return 0 ;
	}
 
	n = strlen(difStr)*2 - 1 ;
 
	lp(i,0,n)
	{
 
		if( i%2 == 0 ) str[i] = difStr[i/2] ;
 
		else str[i] = '|' ;
 
	}
 
	manacher() ;
 
	findAns() ;
 
	printf("%lld\n" , trie.ans ) ;
 
}
