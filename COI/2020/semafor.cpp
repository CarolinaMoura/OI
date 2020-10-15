#include <bits/stdc++.h>

#define debug printf
#define lp(i,a,b) for(int i = a; i < b; i++ )
#define pii pair<int,int>
#define sz(x) (int)(x.size())
#define ll long long 
#define ff first
#define ss second
#define all(x) x.begin(),x.end()

const ll MOD = 1e9+7 ;

using namespace std ;

struct Matrix
{

	vector< vector<ll> > vec ;

	Matrix(int n = 0)
	{
		vec.resize(n, vector<ll>(n,0) ) ;
	}

	Matrix operator * (Matrix other) const
	{
		int n = sz(vec) ;

		Matrix newMatrix(n) ;

		for(int i = 0 ; i < n ; i++ )
			for(int j = 0 ; j < n ; j++ )
				for(int g = 0 ; g < n ; g++ )
				{
					ll toSum = vec[i][g] * other.vec[g][j] ;
					toSum %= MOD ;

					newMatrix.vec[i][j] += toSum ;
					if(newMatrix.vec[i][j] >= MOD ) newMatrix.vec[i][j] -= MOD ;

				}

		return newMatrix ;
	}

} ;

int m, x ;
ll n , k ;
int myMask[10] = {10,2, 1+8, 1+2+4, 16+2, 1+16+4, 8+4, 1+2, 31-2, 31-8 } ;
int matDiff[120][120] ;

bool isOn(int i, int m) { return ((1<<i)&m) != 0 ; }

Matrix expo(Matrix x, ll num )
{
	if(num == 1) return x ;

	Matrix aux = expo(x, num>>1LL ) ;
	aux = aux*aux ;

	if(num&1) aux = aux*x ;

	return aux ;
}

int main()
{

	scanf("%d%lld%lld%d", &m, &n, &k , &x ) ;

	int lim = (m == 1) ? 6 : 11 ;
	Matrix findK(lim) ;
	Matrix findR(lim) ;
		
	for(int diff = 0 ; diff < lim ; diff++ )
	{
		if(diff)
			findK.vec[diff-1][diff] = diff ;

		if(diff+1 < lim)
			findK.vec[diff+1][diff] = lim-1-diff ;

	}


	Matrix base(lim) ;
	base.vec[0][0] = 1 ;

	if( (n%k) > 0 ) findR = base * expo( findK, n%k ) ;
	findK = base*expo(findK, k);

	lim = (m == 1) ? 10 : 100 ;

	Matrix findDp(lim) ;

	for(int i = 0 ; i < lim ; i++)
		for(int j = 0 ; j < lim ; j++ )
		{
			int bitmask1 = (myMask[i/10] << 5) + myMask[i%10] ;
			int bitmask2 = (myMask[j/10] << 5) + myMask[j%10] ;
			int diff = 0 ;

			for(int g = 0 ; g < 10 ; g++ )
				diff += (isOn(g,bitmask1) != isOn(g, bitmask2)) ;

			findDp.vec[i][j] = findK.vec[0][diff] ;
			matDiff[i][j] = diff ;

		}

	vector<ll> dp(lim+1,0LL) ;

	findDp = expo( findDp, n/k ) ;

	for(int i = 0 ; i < lim ; i++ ) 
	{
		if( n%k == 0 )
		{
			dp[i] = findDp.vec[x][i] ;
			continue ;
		}

		for(int g = 0 ; g < lim ; g++ )
		{
			ll toSum = findDp.vec[x][g] * findR.vec[0][ matDiff[i][g] ] ;
			dp[i] += toSum % MOD ;

			if( dp[i] >= MOD ) dp[i] -= MOD;
		}
	}

	for(int i = 0 ; i<lim ; i++ ) printf("%lld\n" , dp[i] ) ;

}
