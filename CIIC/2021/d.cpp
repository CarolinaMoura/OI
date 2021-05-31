#include <bits/stdc++.h>

#define sz(x) (int)(x.size())

const int MAXN = 1e5+10 ;

using namespace std ;

int N ;
char type[MAXN] ;
vector<int> adj[MAXN] ;
set<int> *s[MAXN] ;
vector<int> toDelete ;

void dfs(int x)
{
	if(type[x] == 'E') return ;

	int bc = -1 ;

	for(auto e : adj[x] )
	{
		dfs(e) ;

		if( bc == -1 || sz((*s[e])) > sz((*s[bc])) )
			bc = e ;

	}	

	if( type[x] == 'L' ) 
	{
		s[x] = s[bc] ;
		return ;
	}

	toDelete.clear() ;
	if( adj[x][0] == bc ) swap(adj[x][0] , adj[x][1] ) ;

	if(type[x] == 'A')
	{

		for(auto e : (*s[adj[x][0]]) )
			if( (*s[bc]).find(e) == (*s[bc]).end() ) toDelete.push_back(e) ;

		for(auto e : toDelete ) (*s[adj[x][0]]).erase( (*s[adj[x][0]]).find(e) ) ;

		s[x] = s[ adj[x][0] ] ;
	}
	else if( type[x] == 'O' )
	{
		for(auto e : (*s[ adj[x][0] ]) )
			(*s[bc]).insert(e) ;

		s[x] = s[bc] ;
	}
	else 
	{

		for(auto e : (*s[adj[x][0]]) )
		{
			if( (*s[bc]).find(e) == (*s[bc]).end() ) 
				(*s[bc]).insert(e) ;
			else (*s[bc]).erase( (*s[bc]).find(e) ) ;
		}

		s[x] = s[bc] ;

	}


}

int main()
{
	scanf("%d", &N ) ;
	for(int i = 0 ; i < N ; i++ ) scanf(" %c", &type[i] ) ;

	for(int i = 0 ,  x ; i < N ; i++ )
	{
		scanf("%d", &x ) ;

		if( type[i] == 'E' ) 
		{
			s[i] = new set<int>() ;

			for(int j = 0 , t ; j < x ; j++ )
			{
				scanf("%d", &t ) ;
				(*s[i]).insert(t) ;
			}
		}
		else if( type[i] == 'L' )
		{
			int y ;
			scanf("%d", &y ) ;
			adj[i].push_back(y) ;
		}
		else
		{
			int a, b ;
			scanf("%d %d", &a, &b ) ;
			adj[i].push_back(b) ;
			adj[i].push_back(a) ;
		}
	}

	for(int i = 0 ; i < N ; i++ )
	{
		if( type[i] != 'L' ) continue ;
		dfs(i) ;
	}

	for(int i = 0 ; i < N ; i++ )
	{
		if( type[i] != 'L' )
		{
			printf("\n") ;
			continue ;
		}
		for(auto e : (*s[i])) printf("%d " , e ) ;
		printf("\n") ;
	}
