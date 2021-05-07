#include <bits/stdc++.h>
 
#define ff first
#define ss second
#define sz(x) (int)(x.size())
 
const int MAXN = 3e5+10 ;
const int LOG = 20 ;

using namespace std ;
 
int N ;
int vet[MAXN] , lvl[MAXN]; 
int tab[LOG][MAXN] , mn[LOG][MAXN] ;
int fim[MAXN] ;
bool par[MAXN];
set<int> s ;

int main()
{
	scanf("%d", &N ) ;
	for(int i = 1 ; i <= N ; i++ )
	{
		scanf("%d", &vet[i]) ;

		if( vet[i] > 0 ) continue ;

		lvl[i] = -vet[i] ;

		int x = i-1 ;

		for(int j = LOG-1 ; j >= 0 ; j-- )
			if( mn[j][x] >= lvl[i] )
				x = tab[j][x] ;

		if( lvl[i-1] < lvl[i] ) x = i-2 ;
		else x = tab[0][x] - 1 ;
		
		tab[0][i] = x ;
		mn[0][i] = min(lvl[x] , lvl[i] ) ;

		for(int j = 1 ; j < LOG ; j++ ) 
		{
			tab[j][i] = tab[j-1][ tab[j-1][i] ] ;
			mn[j][i] = min(mn[j-1][i],mn[j-1][ tab[j-1][i] ]) ;
		}

	}

	s.insert(0) ;
	for(int i = 1 ; i <= N ; i++ )
	{
		if(vet[i] > 0 ) 
		{
			s.insert(i) ;
			par[i] = true ;
			fim[i] = i ;
			printf("%d\n" , vet[i] );
			continue ;
		}

		fim[i] = fim[ tab[0][i]+1 ] ;
		par[i] = !par[ tab[0][i]+1 ] ;

		if( par[i] ) s.insert(fim[i]) ;
		else if( !par[i] && s.find(fim[i]) != s.end() ) s.erase(s.find(fim[i])) ;

		printf("%d\n", vet[ *prev(s.end()) ] );

	}
}
