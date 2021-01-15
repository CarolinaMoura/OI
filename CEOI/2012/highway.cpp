#include <bits/stdc++.h>
#include "office.h"

#define sz(x) (int)(x.size())
#define all(x) x.begin(),x.end()
#define ll long long

const int MAX = 1e5+10 ;

using namespace std ;

int GetN(void);
int isOnLine(int x, int y, int z);
void Answer(int a1, int b1, int a2, int b2);

int dsu[MAX] ;
int find(int x) 
{
	if( x == dsu[x]) return x ;
	return dsu[x] = find(dsu[x]) ;
}
void join(int x, int y)
{
	x =find(x) ;
	y = find(y) ;
	if(x == y) return ;

	if(rand() % 2 ) swap(x,y) ;

	dsu[x] = y ;
}

bool isOn(int m, int i) { return ((1<<i)&m) != 0 ; }

/*int N ;
set<int> s1 ;
int GetN() { return N ; }
int isOnLine(int a, int b, int c )
{
	if( (s1.find(a) != s1.end() ) == (s1.find(b) != s1.end() ) && (s1.find(b) != s1.end() ) == (s1.find(c) != s1.end()) )
		return 1 ;
	return 0 ;
}
void incorrect()
{
	printf("Incorrect\n") ;
	exit(0) ;
}
void Answer(int a, int b, int c, int d )
{
	if( (s1.find(a) != s1.end() ) != (s1.find(b) != s1.end()) ) incorrect() ;
	if( (s1.find(c) != s1.end() ) != (s1.find(d) != s1.end()) ) incorrect() ;
	if( (s1.find(a) != s1.end() ) == ( s1.find(c) != s1.end() ) ) incorrect() ;
	printf("Correct (%d %d %d %d)\n" , a , b , c , d ) ;
	exit(0) ;
}*/


int main()
{
	
	/*scanf("%d", &N ) ;
	int t ;
	scanf("%d", &t ) ;
	for(int i = 0 , x ;i < t ; i++ )
	{
		scanf("%d", &x ) ;
		s1.insert(x) ;
	}
	*/ 

	int n = GetN() ;

	vector<int> vec = { isOnLine(1,2,3) } ;

	if(!vec[0]) vec.push_back(isOnLine(4,5,6)) ;

	if( vec[0] || vec[1] )
	{

		vector< pair<int,int> > secondLine ;

		int a1 , a2 ;

		vector<int> e ;

		for(int i = 7 ; i <= n ; i++ ) e.push_back(i) ;

		if(vec[0])
		{
			a1 = 1 , a2 = 2; 
			for(int i = 4 ; i <= 6 ; i++ ) e.push_back(i) ;
		}
		else
		{
			a1 = 4 , a2 = 5 ;
			for(int i = 1 ; i <= 3 ; i++ )e.push_back(i ) ;
		}

		for(int i = 0 ; i < sz(e ) ; i += 2 )
		{
			if( i+1 == sz(e) )
			{
				Answer(a1,a2, secondLine[0].first, secondLine[0].second ) ;
				return 0 ;
			}
			if( isOnLine(a1, e[i] , e[i+1]) ) continue ;

			if( isOnLine(a1, a2, e[i]) ) secondLine.push_back(make_pair(e[i+1],e[i])) ;
			else secondLine.push_back( make_pair(e[i] , e[i+1]) ) ;

			if(sz(secondLine) == 2 )
			{
				Answer(a1, a2, secondLine[0].first, secondLine[1].first ) ;
				return 0 ;
			}
		}
	}

	iota(dsu+1, dsu+7, 1) ;

	for(int i = 1 ; i < (1<<3) ; i++ )
		for(int j = 1 ; j < (1<<3) ; j++ )
		{
			if( __builtin_popcount(i) + __builtin_popcount(j) != 3 ) continue ;
			vector<int> vec ;
			for(int k = 0 ; k < 3 ; k++ )
				if(isOn(i,k)) vec.push_back(k+1) ;
			for(int k = 0 ;  k < 3 ; k++)	
				if(isOn(j,k)) vec.push_back(k+4) ;

			if(isOnLine(vec[0] , vec[1] ,vec[2])) 
			{
				join(vec[0] , vec[1]) ;
				join(vec[1] , vec[2]) ;
			}
		}



	vector<int> groups[7] ;

	for(int i = 1 ; i <= 6 ; i++ ) groups[find(i)].push_back(i) ;

	vector<int> a ;

	for(int i = 1 ; i <= 6 ; i++ )
		if(find(i) == i ) a.push_back(groups[i][0]) , a.push_back(groups[i][1]) ;


	Answer(a[0] , a[1] , a[2] , a[3] ) ;

}
