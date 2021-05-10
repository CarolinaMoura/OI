#include <bits/stdc++.h>
 
#define ll long long
#define all(x) x.begin(),x.end()
#define pb push_back
 
const int MAXN = 3010 ;
const int MAXM = 3010 ;
const int MAX = 1e6+10 ;
 
using namespace std ;
 
int N , M , K , S ;
int tin[MAXN*2] , tout[MAXN*2], decode[MAXN*2] , par[MAXN*2] ;
vector< int > freq[MAX] ;
vector<int> adj[MAXN] ; //tudo bem esse limite, neh?
ll path[MAXN*2] ;
bool outroFreq[MAX] ;
int fila[MAXN*2] ;
int ini , fim ;
 
int currTime ;
void dfs(int x)
{
	tin[x] = ++currTime ;
	decode[ tin[x] ] = x ;
 
	path[x] += (x <= N ) ;
 
	for(auto e : adj[x] ) 
	{
		path[e] += path[x] ;
		dfs(e) ;
	}
 
	tout[x] = currTime ;
}
 
bool isInside(int x, int y) { return tin[y] <= tin[x] && tout[x] <= tout[y] ; }
 
int main()
{
	scanf("%d %d %d %d", &N, &M , &K, &S  ) ;
	S++ ;
 
	for(int i = 1 , parent ; i <= N+M ; i++ )
	{
		scanf("%d %lld", &parent , &path[i]) ;
		adj[parent].push_back(i) ;
		par[i] = parent ;
	}
 
	par[0] = -1 ;
 
	dfs(0) ;
 
	freq[S].push_back(0) ;
 
	for(int i = 1 , u , v ; i <= currTime ; i++ )
		for(int j = i+1 ; j <= currTime ; j++ )
		{
			u = decode[i] ;
			v = decode[j] ;
 
			ll cycle = path[v]-path[u] + S ;
 
			if(cycle > K || u > N || v > N || !isInside(v,u) ) continue ;
			if( !freq[cycle].empty() && isInside(u, freq[cycle].back() ) ) continue ;
 
			freq[cycle].push_back( u ) ;
		}
	
	for(int i = N+1 ; i <= N+M ; i++ )
	{
		int aux = K-path[i] ;
 
		if(aux == 0) { printf("YES\n") ; continue ; }
 
		bool ok = false ;
 
		if(aux > 0 )
			for(int j = 1 ; j*j <= aux; j++ )
			{
				if( aux%j != 0 ) continue ;
 
				for(auto e : freq[j] ) 
					if( isInside(i,e) ) ok = true ;
 
				for(auto e : freq[aux/j] ) 
					if( isInside(i,e) ) ok = true ;				
			}
 
		int x = par[i] ;
		while(x)
		{
			if( path[i]-path[x] <= K )
				outroFreq[ path[i]-path[x] ] = true ;
 
			x = par[x] ;
		}
 
		x = par[i] ;
		int ant = i ;
 
		while(x != -1)
		{
			ini = 0 , fim = 1 ;
			fila[0] = x ;
 
			while(ini < fim)
			{
				int curr = fila[ini++ ];
 
				ll tenho = path[curr]+S ;
 
				if(tenho > K ) continue ;
				if( outroFreq[K-tenho] && K-tenho < (path[i]-path[x]) ) ok = true ;
 
				for(auto e : adj[curr] )
				{
					if(e == ant || e > N) continue ;
					fila[fim++] = e ;
				}
			}
 
			ant= x ;
			x = par[x] ;
		}
 
	 	x = par[i] ;
		while(x)
		{
			if( path[i]-path[x] <= K )
				outroFreq[ path[i]-path[x] ] = false ;
 
			x = par[x] ;
		}
 
		printf("%s\n", ok ? "YES" : "NO" ) ;
 
	}
 
}
