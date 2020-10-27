#include <bits/stdc++.h>
 
#define ll long long
#define all(x) x.begin(),x.end()
#define sz(x) (int)(x.size())

const int MAXN = 1e5+10 ;

using namespace std ;

int n ,  m;
int height[MAXN] , low[MAXN] ;
int szTree[MAXN] ;
int dsu[2][MAXN] ;
vector<int> adj[MAXN] ;

//The first says about connexity
//The second says about vertices in tree
int find(int type , int x)
{
	if(x == dsu[type][x] ) return x ;
	return dsu[type][x] = find(type, dsu[type][x] ) ;
}

void dfs(int x, int depth, int father)
{

	height[x] = low[x] = depth ;
	int cnt = 0 ;

	for(auto e : adj[x])
	{
		if( e == father ) 
		{
			cnt++ ;
			if(cnt == 1) continue ;
		}

		if(height[e] != -1)
		{
			low[x] = min(low[x] , height[e]) ;
			continue ;
		}

		dfs(e, depth+1, x) ;

		low[x] = min(low[x] , low[e]) ;

		if(low[e] >= height[e]) printf("%d %d\n" , x, e) ;

	}

}

int main()
{

	scanf("%d%d", &n, &m ) ;
	
	for(int i = 1 ; i <= n ; i++ ) 
	{
		dsu[0][i] = dsu[1][i] = i ;
		szTree[i]++ ;
	}

	for(int i = 0 , a , b ; i < m ; i++ )
	{
		scanf("%d%d", &a, &b ) ;

		int treeA = find(0,a) ;
		int treeB = find(0,b) ;

		int vertexA = find(1,a) ;
		int vertexB = find(1,b) ;

		if(vertexA == vertexB ) continue ;

		//cout << " ----- " << a << " " << b << endl ;

		adj[a].push_back(b) ;
		adj[b].push_back(a) ;

		if(treeA != treeB )
		{

			if( szTree[treeA] > szTree[treeB] ) swap(treeA, treeB ) ;

			dsu[0][treeA] = treeB ;
			szTree[treeB] += szTree[treeA] ;

		}
		else if(vertexA != vertexB )
		{
			if(rand() % 2 ) swap(vertexA,vertexB) ;

			dsu[1][vertexA] = dsu[1][ vertexB ] ;

		}

	}

	for(int i = 1 ; i <= n ; i++ ) height[i] = -1 ;
	for(int i = 1 ; i <= n ; i++ )
		if(height[i] == -1) dfs(i,1,-1) ;

}
