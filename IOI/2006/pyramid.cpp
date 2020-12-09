#include <bits/stdc++.h>

const int MAX = 1100 ;
const int inf = 1e9+10 ;

using namespace std ;

struct minQueue
{

	deque< pair<int,int> > dq ;
	int l , r ;

	minQueue() { l = 0 , r = -1 ; }

	void add(int x )
	{
		while(!dq.empty() && dq.back().first >= x ) dq.pop_back() ;
		dq.push_back( make_pair(x,++r) ) ;
	}

	void pop()
	{
		if( !dq.empty() && dq[0].second == l ) dq.pop_front() ;
		l++ ; 
	}

	int getMin() { return dq[0].first ; }

} column[MAX] ;

int n , m , a , b , c , d ;
int grid[MAX][MAX];

int getRectangle(int rMin ,int cMin, int rMax, int cMax)
{ return grid[rMax][cMax] - grid[rMax][cMin-1] - grid[rMin-1][cMax] + grid[rMin-1][cMin-1] ; }

int main()
{
	scanf("%d %d %d %d %d %d", &m, &n , &b, &a, &d, &c ) ;
	for(int i = 1; i<= n ; i++ )
		for(int j = 1 ; j <= m ;j++ )
		{
			scanf("%d", &grid[i][j] ) ;
			grid[i][j] += grid[i-1][j] + grid[i][j-1] - grid[i-1][j-1] ;
		}			
	
	int ans = 0 ;
	pair<int,int> outer , inner ;

	for(int i = 2 ; i+c-1 < a ; i++ )
		for(int j = 2 ; j+d-1 < m ; j++ )		
			column[j].add( getRectangle(i, j, i+c-1 , j+d-1 ) ) ;	

	for(int i = 1 ; i + a - 1 <= n ; i++ )
	{
		minQueue myQueue ;

		for(int j = 2 ; j+d-1 <= b-2 ; j++ ) myQueue.add( column[j].getMin() ) ;
		for(int j = 1 ; j+b-1 <= m ; j++ )
		{
			myQueue.add( column[j+b-1-d].getMin() ) ;

			int ansMine = getRectangle(i, j, i+a-1, j+b-1) - myQueue.getMin() ;
			myQueue.pop() ;

			if( ans >= ansMine ) continue ;
			
			ans = ansMine ;
			outer = make_pair(i,j) ;

		}

		for(int j = 2 ; j+d-1 < m ; j++ ) 
		{
			column[j].pop() ;
			column[j].add( getRectangle(i+a-c,j , i+a-1 , j+d-1 ) ) ; 
		}

	}

	int target = -(ans-getRectangle(outer.first, outer.second, outer.first+a-1, outer.second+b-1) ) ;

	for(int i = outer.first + 1 ; i + c - 1 < outer.first + a - 1 ; i++ )
		for(int j = outer.second + 1 ; j + d - 1 < outer.second + b - 1 ; j++ )
			if( getRectangle(i,j,i+c-1, j+d-1 ) == target ) inner = make_pair(i,j) ;

	printf("%d %d\n%d %d\n", outer.second, outer.first, inner.second, inner.first ) ;

}
