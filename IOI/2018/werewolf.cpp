#include "werewolf.h"
#include <bits/stdc++.h>

#define sz(x) (int)(x.size())
#define all(x) x.begin(),x.end()
#define ll long long

const int MAXN = 2e5+10 ;
const int LOG = 20 ;

using namespace std ;

struct Tree
{
	vector<int> tree[MAXN] ;
	int currTime ;
	int tin[MAXN] , tout[MAXN] , rep[MAXN] ;   
	int dp[LOG][MAXN] ;
	int dsu[MAXN] , label[MAXN] ;

	Tree()
	{
		for(int i = 0 ; i < MAXN ; i++ ) dsu[i] =rep[i] = i ;
		memset(dp, -1, sizeof dp );
	}

	int find(int x)
	{
		if( x == dsu[x] ) return x ;
		return dsu[x] = find(dsu[x] ) ;
	}

	void join(int x, int y )
	{
		x = find(x) ;
		y = find(y) ;

		if( x == y ) return ;

		if(rand() % 2 ) swap(x,y) ;

		dsu[x] = y ;
		
		if(label[ rep[x] ] > label[ rep[y] ] ) 
		{	
			tree[ rep[x] ].push_back(rep[y] ) ;
			rep[y] = rep[x] ;
		}
		else tree[ rep[y] ].push_back(rep[x] ) ;

	}


	void dfs(int x)
	{
		
		for(int i = 1 ; i < LOG && dp[i-1][x] != -1 ; i++ )
			dp[i][x] = dp[i-1][ dp[i-1][x] ] ;

	  	tin[x] = tout[x] = currTime++ ;

		for(auto child : tree[x] )
		{
			dp[0][child] = x ;
			dfs(child) ;
			tout[x] = tout[child] ;
		}

	}

} leftToRight, rightToLeft ;

struct SegmentTree
{

	vector< int > tree[MAXN*4] ;

	int m(int l, int r ) { return (l+r)>>1 ; }

	void upd(int pos, int l, int r, int idx , int k )
	{
		tree[pos].push_back(k) ;

		if( l == r ) return ;

		if(idx <= m(l,r) ) upd(pos<<1 , l, m(l,r) , idx , k ) ;
		else upd(pos<<1|1 , m(l,r)+1 , r , idx , k ) ;

	}

	void qry(int pos, int l, int r, int beg, int en , pair<int,int> interval , bool &ok )
	{
		if( l > en || r < beg ) return ;
		if( !(l >= beg && r <= en ) )
		{	
			qry(pos<<1 , l , m(l,r) , beg, en, interval, ok ) ;
			qry(pos<<1|1 , m(l,r)+1, r, beg, en, interval, ok ) ;
			return ;
		}

		int low = 0 , high = sz(tree[pos])-1 , best = interval.second+1 , mid ;

		while(low <= high )
		{
			mid = (low+high)>>1 ;

			if(tree[pos][mid] >= interval.first )
			{
				best = tree[pos][mid] ;
				high = mid-1 ;
			}
			else low = mid+1 ;

		}

		ok |= ( best <= interval.second ) ;

	}

} seg ;

vector<int> check_validity(int N, vector<int> X, vector<int> Y,vector<int> S,vector<int> E, vector<int> L, vector<int> R) 
{

	int M = sz(X) ;

	vector< vector<int> > biggerThanMe(N, vector<int>() ) ;
	vector< vector<int> > smallerThanMe(N, vector<int>() ) ;

	for(int i = 0 ; i < M ; i++ )
	{
		if(X[i] > Y[i] ) swap(X[i], Y[i]) ;

		biggerThanMe[X[i]].push_back(Y[i]) ;
		smallerThanMe[Y[i]].push_back(X[i]) ;	

	}
	
	for(int i = 0 ; i < N ; i++ )
	{
		leftToRight.label[i] = i ;
		rightToLeft.label[i] = -i ;
	}
	
	for(int i = 0 ; i < N ; i++ ) 
		for(auto neighbor : smallerThanMe[i] ) 
			leftToRight.join(neighbor, i) ;

	leftToRight.dfs(N-1) ;

	for(int i = N-1 ; i >= 0 ; i-- )
		for(auto neighbor : biggerThanMe[i] )
			rightToLeft.join(neighbor, i) ;

  	rightToLeft.dfs(0) ; 

	vector<int> inRightToLeft(N) ;

	for(int i = 0 ; i < N ; i++ )
		inRightToLeft[ leftToRight.tin[i] ] = rightToLeft.tin[i] ; 

	for(int i= 0 ; i < N ; i++ ) seg.upd(1,0,N-1, inRightToLeft[i], i ) ;

	vector<int> ans ;

	for(int i = 0 ; i < sz(S) ; i++ )
	{
		
		if( !( S[i] >= L[i] && E[i] <= R[i]) )
		{
			ans.push_back(0) ;
			continue ;
		}

		int bestAncestor = S[i] ;

		for(int j = LOG-1 ; j >= 0 ; j-- )
			if( rightToLeft.dp[j][bestAncestor] >= L[i] )
				bestAncestor = rightToLeft.dp[j][bestAncestor] ;

		pair<int,int> intervalHuman = make_pair( rightToLeft.tin[bestAncestor], rightToLeft.tout[bestAncestor] ) ;

		bestAncestor = E[i] ;

		for(int j = LOG-1 ; j >= 0 ; j-- )
		{
			int anc = leftToRight.dp[j][bestAncestor] ;
			if(anc != -1 && anc <= R[i] ) bestAncestor=anc; 
		}

		pair<int,int> intervalWolf = make_pair( leftToRight.tin[bestAncestor], leftToRight.tout[bestAncestor] ) ;

		bool ok = false ;

		seg.qry(1, 0, N-1, intervalHuman.first, intervalHuman.second, intervalWolf, ok ) ;

		ans.push_back( ok ? 1 : 0 ) ;

	}

	return ans ;
}
