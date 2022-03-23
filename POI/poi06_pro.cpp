#include <bits/stdc++.h>

#define pb push_back
#define sz(x) (int)(x.size() )
#define pii pair<int,int>
#define ll long long
#define mk make_pair
#define lp(i,a,b) for(int i = a ; i < b ; i++ )

const int MAXN =1e6+1 ;
const unsigned short int INF = 36500 ;

using namespace std ;

int N , M , ptr , fim ;
int deg[MAXN] , fila[MAXN] , adj[MAXN] ;
unsigned short int dp[MAXN] ;
pair<int,int> edg[MAXN] ;

void DFS(int x){
	dp[x] = 1 ;
	for(int i = adj[x] ; i <= M && edg[i].first == x ; i++ )
		if( !dp[ edg[i].second] ) DFS(edg[i].second) ;
}

int main()
{
   ios_base::sync_with_stdio(false) ;
   cin.tie(0) ;

   cin >> N >> M ;
   for(int i = 1 ; i <= M ; i++ ) cin >> edg[i].second >> edg[i].first ;

   sort(edg+1, edg+1+M ) ;

   ptr = 1; 
   for(int i = 1 ; i <= N+1 ; i++ ){
		if( ptr <= M && edg[ptr].first == i ) adj[i] = ptr ;
		while( ptr <= M && edg[ptr].first == i ) ptr++ ; 
   }                                        	

   DFS( N+1 ) ;
	
	for(int i = 1 ; i <= N+1 ; i++ )
		for(int j = adj[i] ; j <= M && edg[j].first == i ; j++ )
			if( dp[i] && dp[ edg[j].second ] ) deg[ edg[j].second ]++ ;
	
	for(int i = 1 ; i <= N+1 ; i++ ) dp[i] = 0 ;

	if( deg[N+1] == 0 ) fila[fim++] = N+1 , dp[N+1] = 1 ;
	
	ptr = 0 ;
	while( ptr < fim ){
		int x = fila[ptr++] ;
		for(int i = adj[x] ; i <= M && edg[i].first == x ; i++ ){
			int e = edg[i].second ;
			if((--deg[e] ) == 0 ) fila[fim++] = e ;
			if( dp[x] >= INF-dp[e] ) dp[e] = INF ;
			else dp[e] += dp[x] ;
		}
	}

	ptr = 0 ;
	for(int i = 1 ; i <= N+1 ; i++ ){
		if(!deg[i]  ) continue ;
		while( ptr < fim && fila[ptr] < i ) ptr++ ;
		if( ptr == fim || fila[ptr] > i ) dp[i] = INF ;
	}

	unsigned short int ans = *max_element( dp+1, dp+2+N ) ;

	ptr = fim = 0 ;

	for(int i = 1 ; i <= N ; i++ )
		if( dp[i] == ans ) fila[fim++] = i ;

	if(ans == INF ) cout << "zawsze" ;
	else cout << ans ;
	cout << "\n" << fim << "\n" ;
	for(int i = 0 ; i < fim ; i++ ) cout << fila[i] << " " ;
	cout << "\n" ;
}
