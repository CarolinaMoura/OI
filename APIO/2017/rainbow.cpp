#include "rainbow.h"
#include <bits/stdc++.h>
 
#define mk make_pair
#define pii pair<int,int>
#define pb push_back
#define ff first
#define ss second
#define all(x) x.begin(),x.end()
#define sz(x) (int)(x.size() )
#define ll long long
 
const int MAX = 2e5+10 ;
 
using namespace std ;
 
/*
I need two types of persistent segment trees:
 
* +1 in the opening and -1 in the closure
* +1 in everything
 
*/
 
struct persistentSeg
{
 
	//don't forget to create the dummy node
 
	vector<int> lef, rig , _sum ;
	int roots[MAX] ;
	
	int create()
	{
		lef.push_back(0) ;
		rig.push_back(0) ;
		_sum.push_back(0) ;
 
		return sz(lef) - 1 ;
	}
 
	int createAndCopy(int pos )
	{
		lef.push_back( lef[pos] ) ;
		rig.push_back( rig[pos] ) ;
		_sum.push_back( _sum[pos] ) ;
 
		return sz(lef) - 1 ;
	}
 
	int m(int l, int r ) { return (l+r)>>1 ; }
 
	int upd(int pos, int l, int r, int idx, int val )
	{
		int newPos = createAndCopy(pos) ;
 
		_sum[newPos] += val ;
 
		if( l== r ) return newPos ;
 
		if( idx <= m(l,r) ) 
		{
			int novo = upd(lef[newPos] , l , m(l,r) , idx, val ) ; 
			lef[newPos] = novo ;
		}
		else 
		{
			int novo = upd(rig[newPos] , m(l,r) + 1 , r , idx , val ) ; 
			rig[newPos] = novo ;			
		}
 
		return newPos ;
 
	}
 
	void qryTogether(int pos1, int pos2, int l, int r, int beg, int en, int &z, int &x  )
	{
		if( l > en || r < beg ) return ;
		if( l >= beg && r <= en ) 
		{
			z += _sum[pos1] ;
			x += _sum[pos2] ;
			return ;
		}
 
	   qryTogether( lef[pos1], lef[pos2] , l , m(l,r) , beg, en , z, x ) ;
	   qryTogether( rig[pos1], rig[pos2], m(l,r)+1, r, beg, en, z, x ) ;
 
	}
 
	void subtraction(int pos1, int pos2, int l, int r ,int beg, int en, int &y )
	{
		if( l > en || r < beg ) return ;
		if( l >= beg && r <= en ) 
		{
			y += _sum[pos1] - _sum[pos2] ;
			return ;
		}
 
		subtraction(lef[pos1], lef[pos2], l, m(l,r), beg, en, y ) ;
		subtraction(rig[pos1], rig[pos2], m(l,r)+1, r, beg, en, y ) ;
 
	}
 
} ;
 
struct Event
{
 
	//Type
	// 0 = opening
	// 1 = closure
 
	int r , c , type ;
 
	Event(int r = 0 , int c = 0 , int type = 0 ) : r(r)  ,c(c) , type(type) {} 
	
	bool operator < ( Event other ) const 
	{
		if( c != other.c ) return c < other.c ;
		return type < other.type ;
	}
 
	void print() { printf("%d %d %d\n", r, c , type ) ; }
 
} ;
 
int R, C ;
int maxR, minR, maxC, minC ;
persistentSeg vertices[2] , edges[2] ;
 
void init(int _R, int _C, int sr, int sc, int M, char *S) 
{
	
	R = _R ;
	C = _C ;
 
	vector< pii > serpentPath(1, make_pair(sr, sc) ) ;
 
	maxR = minR = sr ;
	maxC = minC = sc ;
 
	for(int i = 0 ; i < M ; i++ ) 
	{
		if( S[i] == 'N' ) sr-- ;
		if( S[i] == 'E' ) sc++ ;
		if(S[i] == 'S' ) sr++ ;
		if(S[i] == 'W' ) sc-- ;
 
		serpentPath.push_back(make_pair(sr, sc) ) ;
 
		maxR = max(maxR, sr ) ;
		minR = min(minR, sr) ;
		maxC = max(maxC, sc ) ;
		minC = min(minC, sc) ;
 
	}
	
	vector<int> freq[R+1] ;
	for(auto p : serpentPath ) freq[ p.first ].push_back( p.second ) ;
 
	vector<Event> sweep ;
 
	for(int i = 1 ; i <= R ; i++ )
	{
		if( sz(freq[i] ) == 0 )
		{
			sweep.push_back( Event(i , 1 , 0 ) ) ;
			sweep.push_back( Event(i, C , 1 ) ) ;	
			continue ;
		}
		
		sort(all(freq[i] ) ) ;
		freq[i].push_back(C+1) ;
 
		int formerColumn = 0 ;
 
		for(auto e : freq[i] )
		{
			if( formerColumn+1 <= e-1 )
			{
				sweep.push_back(Event(i, formerColumn+1, 0 ) ) ;
				sweep.push_back( Event(i, e-1, 1 ) ) ;
			}
				
			formerColumn =  e ;
		}
 
	}
 
 
	sort(all(sweep ) ) ;
 
	set<int> currentRows ;
 
	vertices[0].create() ; vertices[0].roots[0] = 0 ;
	vertices[1].create() ; vertices[1].roots[0] = 0 ;
	edges[0].create() ; edges[0].roots[0] = 0 ;
	edges[1].create() ; edges[1].roots[0] = 0 ;
 
	for(int i = 1 , ptr=0 ; i <= C ; i++ )
	{
		vertices[0].roots[i] = vertices[0].roots[i-1] ;
		vertices[1].roots[i] = vertices[1].roots[i-1] ;
		edges[0].roots[i] = edges[0].roots[i-1] ;
		edges[1].roots[i] = edges[1].roots[i-1] ;
 
		while( ptr < sz(sweep ) && sweep[ptr].c == i )
		{
 
			vertices[1].roots[i] = vertices[1].upd( vertices[1].roots[i] , 1 , R , sweep[ptr].r , 1 ) ;
 
			if(sweep[ptr].type == 0 )
			{
				vertices[0].roots[i] = vertices[0].upd( vertices[0].roots[i] , 1 , R , sweep[ptr].r , 1 ) ; 
				currentRows.insert( sweep[ptr].r ) ;
 
				auto it = currentRows.find( sweep[ptr].r ) ;
 
				if( it != currentRows.begin() ) 
				{
					it-- ;
 
					if( *it == sweep[ptr].r-1)
					{
						edges[0].roots[i] = edges[0].upd( edges[0].roots[i] , 1 , R  , *it , 1 ) ;
						edges[1].roots[i] = edges[1].upd( edges[1].roots[i] , 1 , R  , *it , 1 ) ;
					}
					it++ ;
				}
				it++ ;
				if(it != currentRows.end() && *it == sweep[ptr].r+1 )
				{
					edges[0].roots[i] = edges[0].upd( edges[0].roots[i] , 1 , R  , sweep[ptr].r , 1 ) ;
					edges[1].roots[i] = edges[1].upd( edges[1].roots[i] , 1 , R  , sweep[ptr].r , 1 ) ;					
				}
 
			}
			else
			{
				vertices[0].roots[i] = vertices[0].upd( vertices[0].roots[i] , 1 , R , sweep[ptr].r , -1 ) ;
 
				auto it = currentRows.find( sweep[ptr].r ) ;
 
				if( it != currentRows.begin() ) 
				{
					it-- ;
					if(*it == sweep[ptr].r-1 )
					{
						edges[0].roots[i] = edges[0].upd( edges[0].roots[i] , 1 , R  , *it , -1 ) ;
						edges[1].roots[i] = edges[1].upd( edges[1].roots[i] , 1 , R  , *it , 1 ) ;
					}
					it++ ;
				}
				it++ ;
				if(it != currentRows.end() && *it == sweep[ptr].r+1 )
				{
					edges[0].roots[i] = edges[0].upd( edges[0].roots[i] , 1 , R  , sweep[ptr].r , -1 ) ;
					edges[1].roots[i] = edges[1].upd( edges[1].roots[i] , 1 , R  , sweep[ptr].r , 1 ) ;					
				}
				it-- ;
 
				currentRows.erase(it) ;
 
			}                  
 
			ptr++ ;
		} 
 
	}
 
}
 
int colour(int ar, int ac, int br, int bc) 
{
	 
	int toSum = 0 ;
 
	if( ar < minR && br > maxR && ac < minC && bc > maxC )
	{
		ar = minR-1 ;
		br = maxR+1 ;
		ac = minC-1 ;
		bc = maxC+1 ;
		toSum = 1 ;	
	}
 
	//Count of vertices
	int z = 0 , x = 0 , y = 0 ;
	vertices[0].qryTogether(vertices[0].roots[bc], vertices[0].roots[ac-1], 1, R, ar, br , z, x ) ;
	vertices[1].subtraction( vertices[1].roots[bc] , vertices[1].roots[ac-1], 1 , R , ar , br , y ) ;
 
	y = (y - x - z )/2 ;
 
	int qtdVert = x + y + z ;
 
	//Count of edges
	br-- ;
	z = x =  y = 0 ;
	edges[0].qryTogether(edges[0].roots[bc], edges[0].roots[ac-1] , 1 , R , ar , br , z, x ) ;
	edges[1].subtraction( edges[1].roots[bc], edges[1].roots[ac-1] , 1 , R , ar , br, y ) ;
	y = (y-x-z)/2 ;
 
	int qtdEdges = x + y + z ;
 
	return qtdVert - qtdEdges + toSum ;
 
}
