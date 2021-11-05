#include <bits/stdc++.h>

#define sz(x) (int)(x.size() )
#define debug printf
#define ll long long
#define pb push_back        
#define all(x) x.begin(),x.end()
#define mk make_pair
#define pii pair<int,int>
#define ff first
#define ss second
#define tiii tuple<int,int,int>

const int MAXN = 1010 ;
const int MAX = 1e6+10 ;
const ll MOD = 1e9+7 ;

using namespace std ;

int N , M ;
ll qtd[MAX] ;
char grid[MAXN][MAXN] ;
int code[MAXN][MAXN] ;
int dsu[MAX] ;
pair<int,int> decode[MAX] ;
int marc[MAX] ;

int find(int x) { return dsu[x] = ( dsu[x] == x ) ? x : find(dsu[x]) ; }
void join(int x, int y )
{
	x = find(x) ;
	y = find(y) ;
	if(x == y ) return ;

	if(rand()%2) swap(x,y) ;

	qtd[x] = (qtd[x]*qtd[y] ) % MOD ;
	dsu[y] = x ;
}

bool valid(int x, int y ) { return 1 <= min(x,y) && x <= N && y <= M ; }

void setIO(string name) {
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);
}

int main()
{
	setIO("cave"); 

	scanf("%d %d", &N, &M ) ;
	for(int i = 1 , c = 1 ; i <= N ; i++ )
		for(int j = 1 ; j <= M ; j++ ,c++ ) 
		{
			scanf(" %c", &grid[i][j] ) ;
			code[i][j] = c ;
			decode[c] = make_pair(i,j) ;
			dsu[c] = c ;
			marc[c] = N+1 ;
			qtd[c] = 1 ;
		}


	for(int i = N-1 ; i > 0 ; i-- )
	{
		for(int j = 2 ; j < M ; j++ )
		{
			if( grid[i][j] != '.' ) continue ;
			if( valid(i,j-1) && grid[i][j-1] == '.' ) join( code[i][j-1], code[i][j] ) ;
			if( valid(i, j+1) && grid[i][j+1] == '.' ) join(code[i][j] , code[i][j+1] ) ;
			if( valid(i+1, j) && grid[i+1][j] == '.' ) join(code[i][j] , code[i+1][j] ) ;				
		}		
		for(int j = 2 ; j < M ; j++ )
		{
			if( grid[i][j] == '#' ) continue ;
			int p = find(code[i][j]) ;
			if( marc[p] == i ) continue ;
			marc[p] = i ;
			qtd[p]++ ;
			qtd[p] %= MOD ;
		}

	}

	ll ans = 1 ;

	for(int i = 1 ; i <= N ; i++ )
		for(int j = 1 ; j <= M ; j++ )
		{
			if( grid[i][j] == '#' ) continue ;
			int p = find(code[i][j]) ;
			if(marc[p] == 0 ) continue ;
			marc[p] = 0 ;
			ans *= qtd[p] ;
			ans %= MOD ;
		}

	printf("%lld\n", ans ) ;


}
