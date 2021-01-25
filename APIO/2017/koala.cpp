#include "koala.h"
#include <bits/stdc++.h>

#define all(x) x.begin(),x.end()
#define ll long long
#define sz(x) (int)(x.size() )

using namespace std ;

int b[100] , r[100] ;

void clean() { for(int i = 0 ; i < 100 ; i++ ) b[i] = 0 ; }

int minValue(int N, int W) 
{
	clean() ;

	b[0] = 1 ;
	playRound(b, r) ;

	if(r[0] < 2 ) return 0 ;

	for(int i = 1 ; i< 100 ; i++ )
		if( !r[i] ) return i ;
}

int maxValue(int N, int W) 
{

	vector<int> v(N) ; iota(all(v),0) ;	
	vector<int> aux ;

	while( sz(v) > 1 )
	{
		clean() ;
		
		for(auto e : v ) b[e] = 100/sz(v) ;
	
		playRound(b, r) ;

		aux.clear() ;
		for(auto e : v ) 
			if( r[e] > b[e] ) aux.push_back(e) ;

		swap(v,aux) ;
	}

	return v[0] ;

}

int greaterValue(int N, int W) 
{
	clean() ;
	b[0] = b[1] = 5 ;

	playRound(b,r) ;

	if( (b[0] < r[0] ) != (b[1] < r[1] ) ) return (b[1] < r[1] ) ;

	if( b[0] < r[0] )
	{
		b[0] = b[1] = 7 ;
		playRound(b,r) ;

		if( (b[0] < r[0] ) != (b[1] < r[1] ) ) return (b[1] < r[1] ) ;

		b[0] = b[1] = 8 ;
		playRound(b,r) ;

		return (b[1] < r[1] ) ;

	}
	else
	{
		b[0] = b[1] = 2 ;
		playRound(b,r) ;
		
		if( (b[0] < r[0] ) != (b[1] < r[1] ) ) return (b[1] < r[1] ) ;
		if(b[0] < r[0] )
		{
			b[0] = b[1] = 3 ;
			playRound(b,r) ;
			return (b[1] < r[1] ) ;
		}
		else
		{
			b[0] = b[1] = 1 ;
			playRound(b,r) ;
			return (b[1] < r[1] ) ;
		}

	}

}

int p[100] ;

bool isLarger(int x , int y, int t = 100  )
{
	clean() ;

	b[x] = b[y] = t ;
	playRound(b,r) ;

	return (b[x] < r[x] ) ;
}

vector<pair<int,int> > forbidden = {make_pair(92,96), make_pair(87,91), make_pair(84,86),
make_pair(76,79), make_pair(66,69), make_pair(61,64),
make_pair(58,60), make_pair(51,54), make_pair(47,49),
make_pair(39,41), make_pair(36,38), make_pair(31,33),
make_pair(26,28), make_pair(92, 95),  make_pair(87, 90),  
make_pair(76, 78), make_pair(66, 68),  make_pair(61, 63), 
make_pair(51, 53), make_pair(92, 94), make_pair(87, 89) } ;
vector<int> costs = {17, 16, 14, 15, 14, 13, 12, 12, 11, 10, 10, 9, 8, 16, 15, 13, 13, 12, 11, 15, 14} ;

vector<int> func(vector<int> idx , int x )
{
	vector<int> v = {idx[0], idx[1] } ;
	if( isLarger(idx[0], idx[1], x ) ) swap(v[0], v[1] );	

	for(int i = 2 ; i < sz(idx) ; i++ )
	{
		int l = 0 , r = sz(v)-1 , mid , best = -1 ;
		while( l <= r )
		{
			mid = (l+r)>>1 ;
			if( isLarger(idx[i], v[mid],x  ) )
			{
				best = mid ;
				l = mid+1 ;
			}
			else r = mid-1 ;
		}			

		vector<int> newV ;
		if( best == -1 ) newV.push_back(idx[i]) ;
			
		for(int j = 0 ; j < sz(v) ; j++ )
		{
			newV.push_back(v[j] ) ;
			if( j == best ) newV.push_back( idx[i] ) ;
		}

		swap(newV, v) ;

	}

	return v ;

}


void solve(vector<int> v, int R )
{

	if(sz(v) == 1 ) return (void)( p[ v[0] ] = R ) ;

	int w ;
	if( R <= 2 ) w = 1 ;
	else if(R <= 8 ) w = 2 ; 
	else if( R <= 30 ) w = 4 ;
	else if( R <= 84 ) w = 7 ;
	else w = 8 ;

	if( sz(v) == 2 )
	{
		clean() ;
		b[ v[0] ] = b[ v[1] ] = w ;
		p[ v[1] ] = R , p[ v[0] ] = R-1 ;

		playRound(b,r);

		if( b[ v[0] ] < r[ v[0] ] ) swap(p[v[1]], p[v[0]] ) ;

		return ;

	}

	int cost = R/sz(v) ;
	int L = R - sz(v) + 1 ;

	for(int i = 0 ; i < sz(forbidden) ; i++ )
		if(make_pair(L,R) == forbidden[i] ) cost = costs[i] ;

	clean() ;

	for(int i : v ) b[i] = cost ;

	playRound(b,r) ;

	vector<int> lef, rig ;

	for(int i : v ) 
	{
		if( b[i] < r[i] ) rig.push_back(i) ; 
		else lef.push_back(i) ;
	}

	if(sz(rig) ) solve(rig, R) ;
	if(sz(lef) ) solve(lef, R-sz(rig) ) ;

}

void allValues(int N, int W, int *P) 
{

    if (W == 2*N) 
    {
		vector<int> idx(N) ; iota(all(idx),0) ;
		vector<int> v = func(idx, 100 ) ;
 
		for(int i = 0 ; i < N ; i++ ) P[ v[i] ] = i+1 ;
    } 
    else 
    {
    	
		for(int i = 0 ; i < N ; i++ ) p[i] = 0 ;

		vector<int> v(N) ; iota(all(v), 0) ;
		solve(v,100) ;

		for(int i = 0 ; i < N ; i++ ) P[i] = p[i] ;

    }       	
}
