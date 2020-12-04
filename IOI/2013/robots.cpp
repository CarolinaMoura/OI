#include <bits/stdc++.h>

#pragma GCC optimize ("O3")

#define debug 
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

const int MAXT = 1e6+10 , MAXN = 5e4+10 ;

using namespace std ;

int a , b ,t , Key ;
int x[MAXN] , y[MAXN] , xx[MAXT] , yy[MAXT] , idx[MAXT] ;
map<int,int> mp ;
priority_queue<int> fila ;

bool cmp(int i , int j) { return xx[i] < xx[j] ; }


bool isPossible( int toTest ) 
{

	while( !fila.empty() ) fila.pop() ;

	int myPointer = 1 ;

	lp(i,1,a+1)
	{

		while( myPointer <= t && xx[ idx[myPointer] ] < x[i] )
		{
			fila.push(yy[ idx[myPointer] ]) ;
			myPointer ++ ;
		}

		for(int i = 1 ; i <= toTest ; i++ )
		{
			if( fila.empty() ) break ;
			fila.pop() ;
		}

	}

	lp(i,myPointer,t+1 ) fila.push(yy[ idx[myPointer] ]) ;

	lp(i,1,b+1)
		for(int j = 1 ; j <= toTest; j ++ )
		{
			if( fila.empty() || fila.top() >= y[i] ) break ;
			fila.pop() ;
		}

	return fila.empty() ;

}	

int main()
{

	scanf("%d%d%d", &a, &b, &t ) ;
	lp(i,1,a+1) scanf("%d", &x[i]) ;
	lp(i,1,b+1) 
	{
		scanf("%d", &y[i]) ;
		mp[ y[i] ] = 0 ;
	}
	lp(i,1,t+1)
	{
		scanf("%d%d", &xx[i], &yy[i]) ;
		mp[ yy[i] ] = 0 ;
	}

	sort( x+1, x+1+a ) ;
	sort(y+1, y+1+b ) ;
	reverse(y+1, y+1+b ) ;
	iota(idx+1, idx+1+t,1) ;
	sort(idx+1, idx+1+t, cmp ) ;
	for(auto &p : mp ) p.ss = ++ Key;

	lp(i,1,b+1) y[i] = mp[ y[i] ] ;
	lp(i,1,t+1) yy[i] = mp[ yy[i] ] ;

	int l = 1 , r = t , mid , best = -1 ;

	while( l <= r )
	{
		mid = (l+r)>>1 ;

		if( isPossible(mid) )
		{
			best = mid ;
			r = mid - 1 ;
		}
		else l = mid+1 ;

	}

	printf("%d\n" , best ) ;

}
