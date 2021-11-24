#include <bits/stdc++.h>
 
#define sz(x) (int)(x.size())
#define mkt make_tuple
#define all(x) x.begin(),x.end()
#define sz(x) (int)(x.size())
#define ll long long
#define lp(i,a,b) for(int i = a ; i < b ; i++ )
#define pii pair<int,int>
#define mk make_pair
#define ff first
#define ss second
#define pb push_back

const int MAX = 2010 ;
const ll MOD = 1e9+7 ;

using namespace std ;

int N ;
ll dp[MAX][MAX][2] , qtd[MAX][MAX] ;
char grid[MAX][MAX] ;
ll pot[MAX] ;
ll inv= (MOD+1)>>1LL ;

ll q(int a, int b, int x)
{
	if(a > b ) return 1LL ;
	ll z = qtd[x][b]-qtd[x][a-1] ;
	return pot[z] ;
}
void setIO(string name) {
	ios_base::sync_with_stdio(0); cin.tie(0);
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);
}

int main()
{

	setIO("sprinklers2"); 

	pot[0] = 1LL ;
	for(int i = 1 ; i < MAX ; i++ )
	{
		pot[i] = pot[i-1]+pot[i-1] ;
		if(pot[i] >= MOD ) pot[i] -= MOD ;
	}

	scanf("%d", &N ) ;
	lp(i,1,N+1)
		lp(j,1,N+1) 
		{
			scanf(" %c", &grid[i][j] ) ;
			qtd[j][i] += qtd[j][i-1] + (grid[i][j] == '.' ) ;
		}

	lp(i,0,N+2) dp[N+1][i][1] = 1 ;
	dp[N+1][N][0] = 1 ;
			
	for(int j= N ; j > 0 ; j-- )
		for(int i = N ; i >= 0 ; i-- )
		{
			if( i+1 <= N && grid[i+1][j] == '.' )
				dp[j][i][0]= ( ( (dp[j+1][i+1][1]*q(i+2,N,j) )%MOD )*q(1,i,j) ) % MOD ;
			( dp[j][i][0] += ( ((dp[j+1][i][0]*q(i+1,N,j))%MOD)*q(1,i,j) ) % MOD ) %= MOD ;
				
			if( grid[i][j] == '.' )	dp[j][i][1] = (dp[j][i][0]*inv)%MOD ;
			if(i == 0 ) dp[j][i][1]=dp[j][i][0] ;

			( dp[j][i][1] += dp[j][i+1][1] ) %= MOD ;
		}

	printf("%lld\n", dp[1][0][1] ) ;
}
