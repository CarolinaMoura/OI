#include <bits/stdc++.h>

#define lp(i,a,b) for(int i = a ; i < b ; i++ )
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

const int MAXN = 5e4+10 ;
const int MAXK = 25 ;
const ll MOD = 1e9+7 ;

using namespace std ;

void setIO(string name) {
	ios_base::sync_with_stdio(0); cin.tie(0);
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);
}

int N , K , Q ;
ll mat[2][MAXK][MAXK] , invMat[2][MAXK][MAXK] ;
ll a[MAXN][MAXK] , invA[MAXN][MAXK] ;
ll cte = (MOD+1LL)>>1LL ;
ll opCte = (MOD-cte) ;

ll getNormal(int x, int i , int j ) { return (i==j)+(j==x && i <= x) ; }
ll getInv(int x, int i, int j) 
{
	if(i == j && i != x ) return 1LL ;
	if(i == j && i == x) return cte ;
	if( j == x && i <= x ) return (MOD-cte)%MOD ;
	return 0LL ;
}

void makeCopies(int toFill, int g )
{
	for(int i = 1 ; i <= K ; i++ )
	{
		invA[g][i] = invMat[toFill][1][i] ;
		for(int j = 1 ; j <= K ; j++ ) 
		{
			( a[g][i] += mat[toFill][i][j] ) ;
			if( a[g][i] >= MOD ) a[g][i] -= MOD ;
		}
	}
}

int main()
{
	setIO("nondec"); 

	scanf("%d %d", &N, &K ) ;

	lp(i,1,K+1) mat[0][i][i] = invMat[0][i][i] = 1LL ;

	makeCopies(0,0) ;

	for(int g = 1 ,x, toGet =0, toFill = 1 ; g <= N ; g++ , swap(toGet, toFill ) )
   {
		scanf("%d", &x ) ;

   	lp(i, 1, K+1 )
   		lp(j,1,K+1)
			{
				mat[toFill][i][j] = mat[toGet][i][j] ;
				invMat[toFill][i][j] = invMat[toGet][i][j] ;
			}

		lp(i,1,x+1)
			lp(j,1,K+1)
			{
				(invMat[toFill][i][j] += (opCte*invMat[toGet][x][j])%MOD ) %= MOD ;
				(mat[toFill][j][x] += mat[toGet][j][i] ) %= MOD ;
			}
			
		makeCopies(toFill, g) ;
   }

   scanf("%d", &Q ) ;
   for(int i = 1 , L , R ; i <= Q ; i++ )
   {
   	scanf("%d %d", &L, &R ) ;
		ll ans = 0LL ;
		for(int j = 1 ; j <= K ; j++ ) 
		{
			( ans += (invA[L-1][j]*a[R][j])%MOD ) ;
			if( ans >= MOD ) ans -= MOD ;
		}
		printf("%lld\n", ans ) ;
   }
}
