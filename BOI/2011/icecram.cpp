#include <bits/stdc++.h>
 
using namespace std ;
 
int main(){
	ios_base::sync_with_stdio(false );
	cin.tie(0) ;
 
	int N , M ;
	cin >> N >> M ;
 
	vector< vector<bool> > adj(N, vector<bool>(N, false) ) ;
 
	for(int i = 0 , a , b ;i < M ; i++ ) {
		cin >> a >> b ;
		adj[--a][--b] = true ;
		adj[b][a] = true ;
	} 
 
	int ans = 0 ;
 
	for(int i= 0 ; i < N ; i++ )
		for(int j = i+1 ; j < N ; j++ )
			for(int g = j+1 ; g < N ; g++ ){
				if( adj[i][j] || adj[i][g] || adj[j][g] ) continue ;
				ans++ ;
			}
 
	cout << ans << "\n" ;
 
}
