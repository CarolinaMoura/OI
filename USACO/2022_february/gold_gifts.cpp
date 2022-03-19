#include <bits/stdc++.h>

#define ll long long
#define pb push_back
#define lp(i,a,b) for(int i = a ;i < b ; i++)
#define sz(x) (int)(x.size())
#define all(x) x.begin(),x.end()
#define mk make_pair

const int MAX = 18 ;

using namespace std;

int N ;
vector<int> adj[MAX] ;
ll dp[(1<<MAX)][MAX] ;
int lsb(int x) { return __builtin_ctz(x); }

int main(){
	ios_base::sync_with_stdio(false) ;
	cin.tie(0) ;

	cin >> N ;
	for(int i = 0 ; i < N ; i++){
		for(int j = 0 , k = 0 , x ; j < N ; j++ ){
			cin >> x ;
			--x ;
			if(k) continue ;
			if(x == i ) k = 1 ;
			adj[i].pb(x) ;
		}
	}

	for(int i = 0 ; i < (1<<N) ; i++ ){
		for(int j = N-1 ; j >= 0 ; j-- ){

			if(i == 0){
				dp[i][j] = 1 ;
			}
			else if(j < lsb(i)){
				dp[i][j] += dp[i][lsb(i)] ;
			}
			else{
				for(auto viz : adj[j]){
					if((i>>viz)&1){
						dp[i][j] += dp[i^(1<<viz)][viz] ;
					}
				}
			}

		}
	}

	int Q ;
	cin >> Q ;
	for(int i = 1 ; i <= Q ; i++ ){
		string str ;
		cin >> str ;
		int m = 0 ;
		for(int j = 0 ; j < N ; j++ )
			if(str[j] == 'H') m |= (1<<j) ;

		int c = (1<<N)-1 ; c ^= m ;

		if(c == 0 ) cout << dp[m][lsb(m)] << "\n" ;
		else cout << (dp[m][lsb(m)]*dp[c][lsb(c)]) << "\n" ;
	}
}
