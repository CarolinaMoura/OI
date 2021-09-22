#include <bits/stdc++.h>
 
#define sz(x) (int)(x.size())
#define debug printf
#define lp(i,a,b) for(int i = a ; i < b; i++)
#define pb push_back
#define ff first
#define ss second
#define mk make_pair
#define pii pair<int,int>
#define ll long long 
#define all(x) x.begin(),x.end()
 
const int MAXN = 1010 ;
const int LOG = 20 ;
 
using namespace std ;
 
int N , M , P ;
int val[50] , valor[MAXN] ;
int tab[LOG+5][MAXN][MAXN]; 
int aux[MAXN][MAXN] ;
vector< pair<int,int> > v ;
char grid[MAXN][MAXN] ;
pair<int,int> amostra[MAXN*MAXN] ;
 
void constructTab()
{
	for(int i = 0 ; i < N ; i++ )
		for(int j = 0 ; j < M ; j++ )
			tab[0][i][j] = val[grid[i][j]] ;
						
	for(int i = 1 ; (1<<i) <= M ; i++ )
	{
		
		
		P = i ;
		
		sort( all(v) , [&](pair<int,int> p1, pair<int,int> p2)
		{
			if( tab[i-1][p1.first][p1.second] != tab[i-1][p2.first][p2.second] )	
				return tab[i-1][p1.first][p1.second] < tab[i-1][p2.first][p2.second] ;
				
			int idx1 = p1.second+(1<<(i-1)) ;
			if(idx1 >= M ) idx1 -= M ;
			
			int idx2 = p2.second+(1<<(i-1)) ;
			if(idx2 >= M ) idx2 -= M ;
			
			return tab[i-1][p1.first][idx1] < tab[i-1][p2.first][idx2] ;
		}
		) ;
		
		tab[i][ v[0].first ][ v[0].second ] = 0 ;
		for(int j = 1 ; j < sz(v) ; j++ )
		{
			int a = v[j].first, b = v[j].second , s = b ;
			int x = v[j-1].first , y = v[j-1].second ;
			
			if(tab[i-1][a][b] > tab[i-1][x][y])
			{
				tab[i][a][b] = tab[i][x][y]+1 ;
				continue ;
			}
			
			tab[i][a][b] = tab[i][x][y]; 
			
			b += (1<<(i-1)) ;
			if(b >= M) b -= M ;
			
			y += (1<<(i-1)) ;
			if(y >= M ) y -= M ;
			
			if( tab[i-1][a][b] > tab[i-1][x][y] ) tab[i][a][s]++ ;
		}
	}
	
	int cur = (1<<P) ;
	for(int pot = P-1 , K = M-(1<<P) ; pot >= 0 ; pot-- )
	{
		if( K < (1<<pot) ) continue ;
		K -= (1<<pot) ;
		
		sort( all(v) , [&](pair<int,int> p1, pair<int,int> p2)
		{
			if( tab[P][p1.first][p1.second] != tab[P][p2.first][p2.second] )	
				return tab[P][p1.first][p1.second] < tab[P][p2.first][p2.second] ;
				
			int idx1 = p1.second+cur ;
			if(idx1 >= M ) idx1 -= M ;
			
			int idx2 = p2.second+cur ;
			if(idx2 >= M ) idx2 -= M ;
			
			return tab[pot][p1.first][idx1] < tab[pot][p2.first][idx2] ;
		}
		) ;
		
		aux[ v[0].first ][ v[0].second ] = 0 ;
		for(int j = 1 ; j < sz(v) ; j++ )
		{
			int a = v[j].first, b = v[j].second , s = b ;
			int x = v[j-1].first , y = v[j-1].second ;
			
			if(tab[P][a][b] > tab[P][x][y])
			{
				aux[a][b] = aux[x][y]+1 ;
				continue ;
			}
			
			aux[a][b] = aux[x][y] ;
			
			b += cur ;
			if(b >= M) b -= M ;
			
			y += cur ;
			if(y >= M ) y -= M ;
			
			if( tab[pot][a][b] > tab[pot][x][y] ) aux[a][s]++ ;
		}
		
		for(int a = 0 ; a < N ; a++ )
			for(int b = 0 ; b < M ; b++ ) tab[P][a][b] = aux[a][b] ;
			
		cur += (1<<pot) ;
	} 
	
	for(int i = 0 ; i < N ; i++ )
		for(int j = 0 ; j < M ; j++ ) amostra[ tab[P][i][j] ] = make_pair(i,j) ;
	
}
 
vector<int> vv ;
int aux_valor[MAXN] ;
set< vector<int> > s ;
int suffixArray()
{
	int last = min_element(valor, valor+N)-valor ;
	
	for(int i = 1 ; (1<<(i-1)) < N ; i++ )
	{
		sort(all(vv), [&](int x, int y)
		{
			if( valor[x] != valor[y] ) return valor[x] < valor[y] ;
			int xx = x + (1<<(i-1)) ;
			int yy = y+(1<<(i-1)) ;
			
			if(xx >= N ) xx -= N ;
			if(yy >= N ) yy -= N ;
			
			return valor[xx] < valor[yy] ;
		}
		) ;
		aux_valor[ vv[0] ] = 0 ;
		last = vv[0] ;
		for(int j = 1 ; j < N ; j++ )
		{
			if( valor[vv[j]] != valor[vv[j-1]] ) 
			{
				aux_valor[vv[j]] = aux_valor[vv[j-1]]+1 ;
				continue ;
			}
			
			int x = vv[j]+(1<<(i-1)) ;
			int y = vv[j-1]+(1<<(i-1)) ;
			
			if(x >= N ) x -= N ;
			if(y >= N) y -= N ;
			
			if(valor[x] != valor[y]) aux_valor[vv[j]] = aux_valor[vv[j-1]]+1 ;
			else aux_valor[vv[j]] = aux_valor[vv[j-1]] ;
		}
		
		for(int j = 0 ; j < N ; j++ ) valor[j] = aux_valor[j] ;
	}
 
	return last ;
}
 
int main()
{
	val[42] = 0 ;
	val[46] = 1 ;
	
	scanf("%d %d", &N, &M ) ;
	for(int i = 0 ; i < N ;i++ )
		for(int j = 0 ; j < M ; j++ )
			scanf(" %c", &grid[i][j] ) ,v.push_back(make_pair(i,j)) ;
						
	constructTab() ;
	
	for(int i=  0 ; i < N ; i++ ) vv.push_back(i) ;
	
	for(int j = 0 ; j < M ; j++ )
	{
		for(int g = 0 ; g < N ; g++ ) valor[g] = tab[P][g][j] ;
		int guy = suffixArray() ;
		for(int g = 0 ; g < N ; g++ ) valor[g] = tab[P][g][j] ;
		
		vector<int> ans = {valor[guy]} ;
		for(int i = guy+1 ; i != guy ; i++ )
		{
			if(i >= N )
			{
				i = -1 ;
				continue ;
			}
			ans.push_back(valor[i]) ;
		}
		s.insert(ans) ;
	}
	
	
	vector<int> winner = *s.begin() ;
	for(auto e : winner )
	{
		int x = amostra[e].first ;
		int y= amostra[e].second ;
		
		printf("%c", grid[x][y] ) ;
		for(int i = y+1 ; i != y ; i++ )
		{
			if(i >= M)
			{
				i = -1 ;
				continue ;
			}
			printf("%c",grid[x][i]) ;
		}
		printf("\n") ;
	}
	
}
