#include <bits/stdc++.h>

#define ll long long
#define all(x) x.begin(),x.end()
#define sz(x) (int)(x.size() )

const int MAXM = 50010;
const int MAXN = 310 ;

using namespace std ;

void setIO(string name) {
	ios_base::sync_with_stdio(0); cin.tie(0);
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);
}

int N , M ;
ll w ;
ll mx[MAXN][MAXN][MAXN] ;
ll dp[MAXN][MAXN] ;

int main()
{
	setIO("pieaters"); 

	cin >> N >> M ;
	for(int i = 1  , l, r ; i <= M ; i++ )
	{
		cin >> w >> l >> r ;
		for(int c = l ; c <= r ; c++ ) mx[c][l][r] = max(mx[c][l][r] , w) ;
	}

	for(int diff = 0 ; diff < N ; diff++ )
		for(int a = 1 , b = diff+1 ; b <= N ; a++, b++ )
			for(int c = a ; c <= b ; c++ ) mx[c][a][b] = max( {mx[c][a+1][b] , mx[c][a][b-1],mx[c][a][b]} ) ;

	for(int diff = 0 ; diff < N ; diff++ )
		for(int a = 1 , b = 1+diff ; b <= N ; a++ , b++ )
			for(int c = a ; c <= b ; c++ )
				dp[a][b] = max( dp[a][c-1] + dp[c+1][b] + mx[c][a][b] , dp[a][b] ) ;


	cout << dp[1][N] << endl ;

}
