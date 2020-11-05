#include "simurgh.h"
#include <bits/stdc++.h>

#define debug 
#define ll long long
#define all(x) x.begin(),x.end()
#define sz(x) (int)(x.size() )

const int MAXN = 505 ;
const int MAXM = MAXN*MAXN ;

using namespace std ;

int n , m , treeAns ;
int U[MAXM] , V[MAXM] , pai[MAXN] ;
int cumulativeFoundOnes[MAXN] , lvl[MAXN] , edgeFather[MAXN] ;
int edgeStatus[MAXM] ;
vector< pair<int,int> > adj[MAXN] ;
vector< pair<int,int> > tree[MAXN] ;
vector<int> treeIds ;
bool vis[MAXN] , isTree[MAXM] ;

int find(int x)
{
	if( x == pai[x] ) return x ;
	return pai[x] = find(pai[x]) ;
}

bool join(int x, int y )
{
	x = find(x) ;
	y = find(y) ;

	if(x == y ) return false ;

	if(rand() % 2 ) swap(x,y) ;

	pai[x] = y ;

	return true ;

}

void cleanTime() { for(int i = 0 ; i< n ; i++ ) pai[i] = i ; }

int getOther(int edgeId, int knownEnd )
{
	if( knownEnd == U[edgeId] ) return V[edgeId] ;
	return U[edgeId] ;
}

void findTree(int x)
{
	vis[x] = true ;

	for(auto e : adj[x] )
	{
		int j = e.first ;
		int id = e.second ;

		if( vis[j] ) continue ;

		edgeFather[j] = id ;
		isTree[id] = true ;
		treeIds.push_back(id) ;
		lvl[j] = lvl[x] + 1 ;

		tree[x].push_back(make_pair(j, id) ) ;

		findTree(j) ;

	}
}

void recalcCumulative(int x)
{
	
	for(auto e : tree[x] )
	{
		int j = e.first ;
		int id = e.second ;

		cumulativeFoundOnes[j] += cumulativeFoundOnes[x] ;
		if(edgeStatus[id] != -1 ) cumulativeFoundOnes[j]++ ;

		recalcCumulative(j) ;
	}

}

void bb(vector<int> v, int commonRoads )
{

	if( commonRoads == 0 || sz(v) == 0 ) 
	{
		for(auto e : v ) edgeStatus[e] = 0 ;
		return ;
	}

	if(sz(v) == commonRoads )
	{
		for(auto e : v ) edgeStatus[e] = 1 ;
		return ;
	}

	vector<int> l , r ;

	for(int i= 0 ; i < sz(v)/2 ; i++ ) l.push_back(v[i] ) ;
	for(int i = sz(v)/2 ; i < sz(v) ; i++ ) r.push_back(v[i] ) ;

	cleanTime() ;

	vector<int> vec = l ;

	int c = 0 ;

	for(auto e : l ) join(U[e] , V[e] ) ;
	for(auto e : treeIds ) 
		if(join(U[e] , V[e] ) ) 
		{
			vec.push_back(e) ;
			c -= edgeStatus[e] ;
		}

	c += count_common_roads(vec) ;

	bb(l, c) ;
	bb(r, commonRoads - c ) ;

}

vector<int> find_roads(int N, vector<int> u, vector<int> v) 
{
	n = N ;
	m = sz(u) ;

	for(int i = 0 ; i < m ; i++ )
	{
		adj[ u[i] ].push_back(make_pair(v[i],i) ) ;
		adj[ v[i] ].push_back( make_pair(u[i], i) ) ;

		U[i] = u[i] ;
		V[i] = v[i] ;

		edgeStatus[i] = -1 ;

	}


	edgeFather[0] = -1 ;
	findTree(0 ) ;
	
	treeAns = count_common_roads( treeIds ) ;

	for(auto e : treeIds ) debug("%d (which is %d %d) is in tree\n", e, U[e], V[e] ) ;
	debug("\n") ;

	for(int i = 0 ; i < m ; i++ )
	{
		if(isTree[i] ) continue ;

		int up = U[i] , down = V[i] ;

		if(lvl[up] > lvl[down] ) swap(up,down ) ;

		if( cumulativeFoundOnes[down] - cumulativeFoundOnes[up] == lvl[down]-lvl[up] ) continue ;

		vector<int> notFound ;
		vector<int> alreadyFound ;

		int x = down ;

		while( x != up )
		{

			if( edgeStatus[ edgeFather[x] ] == -1 ) notFound.push_back( edgeFather[x] ) ;
			else alreadyFound.push_back( edgeFather[x] ) ;

			x = getOther(edgeFather[x] , x ) ;

		}


		if( sz(alreadyFound) != 0 )
		{
			vector<int> r(1,i) ;

			for(int e : treeIds )
				if( e != alreadyFound[0] ) r.push_back( e ) ;

		  	if( count_common_roads(r) == treeAns-edgeStatus[ alreadyFound[0] ] )
		  		edgeStatus[i] = 0 ;
		 	else edgeStatus[i] = 1 ; 

		 	for(auto e : notFound )
		 	{
				r.clear() ;

				for(auto idx : treeIds )
					if(idx != e ) r.push_back(idx) ;

				r.push_back( i ) ;

				if( treeAns == count_common_roads(r) - edgeStatus[i] )
					edgeStatus[e] = 0 ;
				else edgeStatus[e] = 1 ;

		 	}

		}
		else 
		{
			//If I'm golden, as we can't all be golden, then I will increase at least once
			//If I'm not golden, I can never increase

			vector<int> ans ;

			edgeStatus[i] = 0 ;

			for(auto e : notFound ) 
			{
				vector<int> r(1,i) ;

				for(auto idx : treeIds )
					if(idx != e )	r.push_back(idx) ;

				ans.push_back(count_common_roads(r)) ;

				if( ans.back() == treeAns+1 ) edgeStatus[i] = 1 ;
			}

			for(int j = 0 ; j < sz(notFound) ; j++ )
			{
				if( treeAns == ans[j] - edgeStatus[i] )
					edgeStatus[ notFound[j] ] = 0 ;
				else edgeStatus[ notFound[j] ] = 1 ; 			
			}


		}

		for(int i = 0 ; i< n ; i++ ) cumulativeFoundOnes[i] = 0 ;

		recalcCumulative(0) ;

	}

	for(int e : treeIds )
		if(edgeStatus[e] == -1 ) edgeStatus[e] = 1 ; //I know for a fact they are golden (they are bridges)

	for(auto e : treeIds ) debug("edge %d (%d and %d) is %d\n", e, U[e] , V[e] , edgeStatus[e] ) ;
	for(int i = 0 ; i < m; i++ ) debug("%d ", edgeStatus[i] ) ;
	debug("\n") ;

  	for(int i = 0 ; i < n ; i++ )
  	{
  		vector<int> r ;

  		cleanTime() ;	

		for(auto e : adj[i] ) 
			if( edgeStatus[e.second] == -1 ) 
			{
				r.push_back(e.second) ;
				join(i , e.first ) ;
			}

		if(sz(r) == 0 ) continue ;

		int tot = 0 ;

		for(auto e : treeIds)
			if( join(U[e] , V[e] ) )
			{
				tot -= edgeStatus[e] ;
				r.push_back(e) ;
			}

		tot += count_common_roads(r) ;
	
		while( isTree[ r.back() ] ) r.pop_back() ;

		bb(r, tot ) ;

  	}

  	vector<int> goldenSet ;
  	for(int i = 0 ; i< m ; i++ )
  		if(edgeStatus[i] == 1 ) goldenSet.push_back(i) ;

  	return goldenSet ;

}
