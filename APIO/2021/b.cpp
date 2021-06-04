#include "jumps.h"
#include <bits/stdc++.h>

#define sz(x) (int)(x.size() )
#define all(x) x.begin(),x.end()
#define debug printf

const int MAXN = 2e5+10 ;
const int LOG = 20 ;

using namespace std ;

int N ;
int lef[MAXN], rig[MAXN] ;
int tab[LOG][MAXN] , dir[LOG][MAXN] , esq[LOG][MAXN] ;
int dist[MAXN] , H[MAXN] ;
int rmq[LOG][MAXN] ;
int _log[MAXN] ;
int mostRight[LOG][MAXN] ;

int getMax(int l, int r , bool isIndex = false )
{
	int t = _log[r-l+1 ] ;
	int x = rmq[t][l] ;
	int y = rmq[t][r-(1<<t)+1] ;

	x = ( H[x] > H[y] ) ? x : y ;

	if( isIndex ) return x ;
	return H[x] ;
}


void init(int _N, vector<int> _H) 
{
	N = _N ;
	for(int i = 0 ; i < N ; i++ ) H[i] = _H[i] ;

	for(int i = 0 ; i < N ; i++ )
	{
		lef[i] = i-1 ;
		while( lef[i] != -1 && H[ lef[i] ] <= H[i] ) lef[i] = lef[ lef[i] ] ;
	}			
	for(int i = N-1 ; i >= 0 ; i-- )
	{
		rig[i] = i+1 ;
		while( rig[i] < N && H[rig[i] ] <= H[i] ) rig[i] = rig[ rig[i] ] ;
	}

	for(int i = 2 ; i <= N ; i++ ) _log[i] = 1+_log[i>>1] ;

	for(int i = 0 ; i < N ; i++ ) rmq[0][i] = i ;
	for(int i = 1 ; i < LOG ; i++ )
		for(int j = 0 ; j + (1<<i) - 1 < N ; j++ )
		{
			rmq[i][j] = rmq[i-1][j+(1<<(i-1))] ;
			if( H[ rmq[i-1][j] ] > H[ rmq[i][j] ] ) rmq[i][j] = rmq[i-1][j] ;
		}

	//for(int i = 0 ;i < N ; i++ ) debug("%d %d\n", lef[i], rig[i] ) ;

	vector<int> idx(N) ; iota(all(idx), 0) ;
	sort(all(idx), [&](int a, int b ) { return H[a] > H[b] ; } ) ;

	memset(tab, -1, sizeof tab) ;
	memset(dir, -1, sizeof dir) ;

	for( auto e : idx )
	{
		if( rig[e] == N ) rig[e] = -1 ;

		dir[0][e] = rig[e] ;

		for(int i = 1 ; i < LOG ; i++ )
		{
			if( dir[i-1][e] == -1 ) continue ;
			dir[i][e] = dir[i-1][ dir[i-1][e] ] ;
		}

		if( lef[e] == -1 && rig[e] == -1 ) continue ;

		if( lef[e] == -1 || (rig[e] != -1 && H[ lef[e] ] <= H[ rig[e] ] ) ) 
		{
			tab[0][e] = rig[e] ;
			mostRight[0][e] = rig[rig[e]] ;
		}
		else
		{
			tab[0][e] = lef[e] ;
			mostRight[0][e] = rig[ lef[e] ] ;
		}

		for(int i = 1 ; i < LOG && tab[i-1][e] != -1 ; i++ )
		{
			tab[i][e] = tab[i-1][ tab[i-1][e] ] ;
			mostRight[i][e] = max( mostRight[i-1][e] , mostRight[i-1][ tab[i-1][e] ] ) ;
		}
	}

}

int minimum_jumps(int A, int B, int C, int D) 
{

	D = getMax(C,D, true) ;

	int l = A , r = B , mid , best = -1 ;

	while( l <= r )
	{
		mid = (l+r)>>1 ;
		if( getMax(mid, B) < H[D] )
		{
			best =  mid ; 
			r = mid-1 ;
		}	
		else l = mid+1 ;
	}

	if( best == -1 ) return -1 ;

	A = B = getMax(best, B, true) ;

	if( getMax(B, C-1) >= H[D] ) return -1 ;

	int ans = 0 ;

	for(int i = LOG-1 ; i >= 0 && rig[A] < C ; i-- )
	{
		if( tab[i][A] == -1 || tab[i][A] >= C ) continue ;
		if( mostRight[i][A] >= C ) continue ;
		if( H[ tab[i][A] ] >= H[D] ) continue ;

		A = tab[i][A] ;
		ans += (1<<i) ;
	}

	int ans1 = ans+N ;
	int ans2 = ans ;

	if( lef[A] != -1 && H[lef[A] ] < H[D] && rig[lef[A] ] >= C )  ans1 = ans+2 ;

	for(int i = LOG-1 ; i >= 0 ; i-- )
	{
		if( dir[i][A] == -1 || dir[i][A] >= C ) continue ;
		A = dir[i][A] ;
		ans2 += (1<<i) ;
	}

	return min(ans1, ans2+1) ;

 }
