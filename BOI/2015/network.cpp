#include <bits/stdc++.h>
 
#define sz(x) (int)(x.size())
#define all(x) x.begin(),x.end()
 
const int MAXN = 5e5+10 ;
 
using namespace std ;
 
int N , rt , q ;
int sub[MAXN] ;
vector<int> adj[MAXN] ;
vector<int> v ;
 
void dfs(int x, int par )
{
	if(sz(adj[x]) == 1) v.push_back(x) ;
 
	for(auto e : adj[x] )
		if(e != par ) dfs(e,x) ;
}
 
int main()
{
	scanf("%d", &N ) ;
	for(int i = 1 , a , b ; i < N ;i++ )
	{
		scanf("%d %d", &a, &b ) ;
		adj[a].push_back(b) ;
		adj[b].push_back(a) ;
	}
 
	for(int i = 1 ; i <= N ; i++ )
		if(sz(adj[i]) > 1 ) rt =i ;
 
	dfs(rt,-1) ;
 
	int p = sz(v) ;
 
	printf("%d\n", (p+1)>>1 ) ;
 
	for(int i = 0 ; i+( (p+1)>>1 ) < p ; i++ ) printf("%d %d\n", v[i] , v[i+((p+1)>>1) ] ) ;
	if(p&1) printf("%d %d\n" , rt , v[p>>1] ) ;
 
}
