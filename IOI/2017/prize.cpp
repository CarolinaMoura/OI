#include "prize.h"
#include <bits/stdc++.h>
 
#define sz(x) (int)(x.size())
#define debug printf
#define lp(i,a,b) for(int i = a ; i < b; i++)
#define pb push_back
#define ff first
#define ss second
#define mk make_pair
#define pii pair<int,int>
#define ll long long 
#define all(x) x.begin(),x.end()
 
const int MAX = 2e5+10 ;
 
using namespace std ;
 
int cte ;
int soma[MAX] ;
int record[MAX][2] ;
bool went[MAX] ;
 
bool isLollipop(int i) { return soma[i] == cte ; }
bool isDiamond(int i) { return soma[i] == 0; }
 
void pergunta(int i)
{
	if(went[i]) return ;
 
	went[i] = true ;
 
	vector<int> a = ask(i) ;
 
	record[i][0] = a[0] ;
	record[i][1]= a[1] ;
	soma[i] = a[0] + a[1] ;
}
 
int find_best(int n) 
{
	if( n <= 5000 )
	{
		for(int i = 0 ; i < n ; i++ )
		{
			pergunta(i) ;
 
			if( isDiamond(i) ) return i ;
		}
	}
	else 
	{
		vector<int> vec(n, 0) ;
		iota(all(vec) , 0 ) ;
 
		srand(time(0)) ;
		random_shuffle(all(vec)) ;
 
		set<int> s ;
 
		for(int i = 0 ; i < 450 ; i++ )
		{
			pergunta( vec[i] ) ;
			s.insert( soma[ vec[i] ] ) ;
 
			if( isDiamond(vec[i]) ) return vec[i] ;
 
			if(sz(vec) == 5 || soma[ vec[i] ] >= 450 ) break ;
		}
 
		cte = *prev( s.end() ) ;
	}
	
	vector<pii> fila(1);
 
	for(int i = 0 ; i < n ; i++ )
	{
		pergunta(i) ;
		
		if( isDiamond(i) ) return i ;
		if( !isLollipop(i) ) continue ;
		
		fila[0].ff = i+1 ;
		break ;
 
	}
	for(int i= n-1 ; i >= 0 ; i-- )
	{
		pergunta(i) ;
 
		if(isDiamond(i)) return i ;
		if( !isLollipop(i) ) continue ;
 
		fila[0].ss = i-1 ;
		break ;
	}
 
	int ptr = 0 ;
	while( ptr < sz(fila) )
	{
		int l = fila[ptr].ff ;
		int r = fila[ptr].ss ;
		ptr++ ;
 
		int mid = (l+r)>>1 ;
 
		pergunta(mid);
 
		//Calculate left interval
		int newR = mid ;
		while( true )
		{
			pergunta(newR) ;
 
			if(isDiamond(newR)) return newR ;
			if( !isLollipop(newR) ) newR-- ;
			else break ;
		}
		
		newR-- ;
 
		if( l <= newR && (record[l-1][1] - record[newR+1][1] > 0 ) ) 
		{
			fila.push_back( make_pair(l,newR) ) ;
		}
 
		//Calculate right interval
		int newL = mid ;
		while( true )
		{
			pergunta(newL) ;
 
			if( isDiamond(newL) ) return newL ;
			if(!isLollipop(newL)) newL++ ;
			else break ;
		}
 
		newL++ ;
 
		if( newL <= r && (record[newL-1][1] - record[r+1][1]) > 0 )
			fila.push_back( make_pair(newL, r) ) ;
	}
 
	return 0;
}
