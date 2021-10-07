#include "swaps.h"
#include <bits/stdc++.h>
 
#define sz(x) (int)(x.size() )
#define debug 
 
const int MAX = 515 ;
 
using namespace std ;
 
int n , N ;
int arr[MAX] ;
vector< pair<int,int> > pairs ;
vector<int> _visit ;
 
void make_schedule(int i, int j )
{
	_visit.push_back(-1) ;
	pairs.push_back(make_pair(i,j) ) ;
	i = arr[i] , j = arr[j] ;
 
	if( i >= n || j >= n )
	{
		_visit.back() = (i > j )  ;
		return ;
	}	
 
	schedule(i+1,j+1) ;
}
 
void make_visit()
{
	vector<int> v = visit() ;
 
	for(int i = 0 , ptr = 0 ; i < sz(_visit) ; i++ )
	{
		if( _visit[i] == -1 ) _visit[i] = v[ptr++] ;
		if( _visit[i] ) swap( arr[ pairs[i].first ] , arr[ pairs[i].second ] ) ;
	}
 
	_visit.clear() ;
	pairs.clear() ;
}
 
void solve(int _n, int V) 
{
 
	n = _n ;
	int k = 0 ;
	while( (1<<k) < n ) k++ ;
	N = (1<<k) ;
 
	iota(arr, arr+N , 0 ) ;
 
	for(int i = 1 ; i <= k ; i++ )
	{
 
		for(int j = i-1 , p = (1<<j) ; j >= 0 ; j-- , p >>= 1)
		{
			for(int g = 0 ; g < N ; g++ )
			{
				int num = g/p ;
				if( (num&1) == 1 ) continue ;
 
				int dist = g-num*p ;
				int op = (num+2)*p - dist - 1 ;
 
				if(j < i-1 ) op = g+p ;
 
				make_schedule( g , op ) ;
			}
			make_visit() ;
		}
 
	}
 
	vector<int> r ;
	for(int i = n-1 ; i >= 0 ; i-- ) r.push_back(arr[i]+1 ) ;
 
	answer(r) ;
 
}   
