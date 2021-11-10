#include <bits/stdc++.h>
 
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

const int MAXN = 310 ;

using namespace std ;

void setIO(string name) {
	ios_base::sync_with_stdio(0); cin.tie(0);
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);
}

int N , ans ;
int sv[MAXN][MAXN] , g[MAXN][MAXN] ;

int getQry(int x2, int y2, int x1, int y1)
{

	int diff = x2-y2 ;

	if(abs(diff) >= N ) return 0 ;

	if( x2 > N ) x2 = N , y2 = N-diff ;
	if( y2 > N ) y2 = N , x2 = N+diff ;

	if(x1 < 1 ) x1 = 1 , y1 = 1-diff ;
	if(y1 < 1 ) y1 = 1 , x1 = 1+diff ;

	if(y2 < y1 || x2 < x1) return 0 ;

	return sv[x2][y2]-sv[x1-1][y1-1] ;
}

void solve(bool aberto)
{

	lp(i,1,N+1)
		lp(j,1,N+1) sv[i][j]+=sv[i-1][j-1] ;

	for(int i = 1 ; i <= N ; i++ )
		for(int j= 1 ; j <= N ; j++ )
			for(int ni=i-1,nj=j-1, diff=1 ; ni > 0 && nj > 0 ; ni--, nj--, diff++ )
			{
				if(!getQry(i,j,i,j) || !getQry(ni,nj,ni,nj) ) continue ;
				
				ans += getQry( i-diff-aberto, j+diff-aberto, ni-diff+aberto, nj+diff+aberto) ;
				ans += getQry(i+diff-aberto, j-diff-aberto, ni+diff+aberto, nj-diff+aberto) ;
			}   

}

int main()
{
	setIO("triangles"); 

	scanf("%d", &N ) ;
	lp(i,1,N+1)
		lp(j,1,N+1)
		{
			char c ;
			scanf(" %c", &c ) ;
			g[i][j] = sv[i][j] = (c == '*' ) ;
		}

	solve(false) ;

	lp(i,1,N+1) 
		lp(j,1,N+1) sv[N-j+1][i] = g[i][j] ;

	solve(true) ;

	printf("%d\n", ans ) ;

}
