#include "coprobber.h"
#include <bits/stdc++.h>

#define sz(x) (int)(x.size() )
#define all(x) x.begin(),x.end()
#define debug printf
#define ll long long

const int MAXN = 505 ;

using namespace std ;

int nxtMove[MAXN][MAXN] ;
int outDeg[MAXN][MAXN][2] ;
bool graph[MAXN][MAXN] ;
bool isWinner[MAXN][MAXN] ;
int myCurrent , n ;

int start(int N, bool A[MAX_N][MAX_N])
{
	n = N ;

	for(int i = 0 ; i < N ; i++ )
	{
		int deg = 0 ;

		for(int j = 0 ; j < N ; j++ )
			graph[i][j] = A[i][j] , deg += A[i][j] ;

		for(int j = 0 ; j < N ; j++ )
		{			
			outDeg[i][j][0] = deg+1 ;

			if(i != j )
				outDeg[j][i][1] = deg ;
		}
	}

	vector< tuple<int,int,int> > q ;
	int ini = 0 ;

	for(int i = 0 ; i < N ; i++ )
		for(int j = 0 ; j < N ; j++ )
			for(int k = 0 ; k < 2 ; k++ )
			{
				if( outDeg[i][j][k] == 0 ) 
				{
					q.push_back( make_tuple(i,j,k) ) ;
					outDeg[i][j][k] = -1 ;
				}
			}
	while( ini < sz(q) )
	{

		int x = get<0>( q[ini] ) ;
		int y = get<1>( q[ini] ) ;
		int z = get<2>( q[ini] ) ;

		ini++ ;

		if(z) isWinner[x][y] = true ;

		//cout << x << " " << y << " " << z << endl ;

		if(!z)
		{
			//I'm the cop's turn
			//That means my previous must be a robber's move

			for(int i = 0 ; i < N ; i++ )
				if( A[i][y] && (--outDeg[x][i][1]) == 0 ) q.push_back( make_tuple(x,i,1) ) ;

		}
		else
		{
			for(int i = 0 ; i < N ; i++ )
			{
				if( (!A[i][x] && i != x) || outDeg[i][y][0] <= 0 ) continue ;
				
				outDeg[i][y][0] = -1 ;
				nxtMove[i][y] = x ;

				q.push_back( make_tuple(i,y,0) ) ;

			}
		}	

	}

	for(int i = 0 ; i < N ; i++ )
	{
		bool theyWin = true ;

		for(int j = 0 ; j < N ; j++ )
			theyWin &= isWinner[i][j] ;

		if( theyWin ) return myCurrent = i ;	
	}

	return -1 ;

}

int nextMove(int R)
{

	//The state is (myCurrent, R, 0) 
	return myCurrent = nxtMove[myCurrent][R] ;

}
