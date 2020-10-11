#include <bits/stdc++.h>

#define sz(x) (int)(x.size())
#define ff first
#define ss second
#define pb push_back
#define ll long long
#define mk make_pair
#define all(x) x.begin(),x.end()
#define pii pair<int,int:
#define debug printf 

const int MAXN = 2e5+10 ;

using namespace std ;

int N , M , S , D , A , B ;
vector<int> adj[MAXN] ;

vector<int> bfs(int comeco)
{

	vector<int> fila(1,comeco); 
	vector<int> dist(N+1, M+10 ) ;

	dist[comeco] = 0 ;

	int ini = 0 ;
	while(ini < sz(fila))
	{
		int x = fila[ini++] ;

		for(auto e : adj[x])
			if(dist[x]+1 < dist[e])
			{
				dist[e] = dist[x]+1 ;
				fila.push_back(e) ;
			}

	}

	return dist; 

}

int main()
{
	scanf("%d%d%d%d%d%d", &N, &M, &S, &D, &A, &B ) ;
	for(int i = 0 , x , y ; i < M ; i++ )
	{
		scanf("%d%d", &x, &y ) ;
		adj[x].push_back(y) ;
		adj[y].push_back(x) ;
	}

	vector<int> ds = bfs(S) ;
	vector<int> dd = bfs(D) ;
	vector<int> da = bfs(A) ;
	vector<int> db = bfs(B) ;

	if( da[D] < da[S] || db[D] < db[S] )
	{
		printf("-1\n") ;
		return 0 ;
	}

	if( da[S] != db[S] || da[D] != db[D] )
	{
		//Porque minha estrategia eh sempre a mesma,
		//eu preciso chegar no mais perto de mim primeiro

		int ans = M+10 ;

		ans = min(ans, db[D] - db[S] ) ;
		ans = min(ans, da[D] - da[S] ) ;

		printf("%d\n", ans ) ;

		return 0 ;

	}

	
	int intermedS = S , intermedD = D ;

	for(int i = 1 ; i <= N ; i++ )
		if( da[i] == db[i] && da[i] + ds[i] == da[S] && ds[i] > ds[intermedS] )
			intermedS = i ;

	for(int i = 1 ; i <= N ; i++ )
		if( db[i] == da[i] && da[i]+dd[i] == da[D] && dd[i] > dd[intermedD] )
			intermedD = i ;

	int ans = max(0, db[D]-db[S]-1) ;

	//Testar se consigo com db[D]-db[S]

	int holdOn = db[D]-db[S] ;

	if( ds[intermedS]+holdOn >= dd[intermedD] )
		ans = holdOn ;

	printf("%d\n" , ans ) ;

}
