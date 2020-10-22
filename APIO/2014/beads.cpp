#include <bits/stdc++.h>

#define ll long long
#define all(x) x.begin(),x.end()
#define sz(x) (int)(x.size())

const int MAXN = 2e5+10 ;
const int inf = 1e9+7 ;

using namespace std ;

int n ;
int ans ;
int dp[MAXN][2] ;
vector< pair<int,int> > adj[MAXN] ;

void dfs(int x, int father )
{
	int edgeFather = -inf ;
	vector< pair<int,int> > children ;

	for(auto e : adj[x] ) 
	{
		if(e.first == father)
			edgeFather = e.second ;
		else 
		{
			dfs(e.first, x) ;
			children.push_back(e) ;
		}
	}

	dp[x][0] = 0;
	dp[x][1] = edgeFather ;
	int maxCte = -inf ;

	for(auto e : children )
	{
		int pos1 = dp[e.first][1] ;
		int pos2 = dp[e.first][0] ;

		dp[x][0] += max(pos1, pos2) ;
		dp[x][1] += max(pos1,pos2) ;

		maxCte = max(maxCte, -max(pos1,pos2) + e.second + pos2 ) ;

	}

	dp[x][1] += maxCte ;
	
}

void dfsSpin(int x, int father)
{

	vector< pair<int,int> > children ;

	for(auto e : adj[x] ) 
		children.push_back(e) ;

	int m = sz(children) ;
	int soma = 0 ;

	vector<int> pref(m) , suf(m) ;

	for(int i = 0 , ii = m-1 ; i < m ; i++ , ii-- )
	{
		int vert = children[i].first ;
		int edge = children[i].second ;

		soma += max( dp[vert][0] , dp[vert][1] ) ;

		pref[i] = -max(dp[vert][0] , dp[vert][1]) + edge + dp[vert][0] ;
		
		vert = children[ii].first ;
		edge = children[ii].second ;

		suf[ii] = -max(dp[vert][0] , dp[vert][1]) + edge + dp[vert][0] ;

		if(!i) continue ;

		pref[i] = max(pref[i-1], pref[i]) ;
		suf[ii] = max(suf[ii+1] , suf[ii]) ;

	}

	ans = max(ans, soma ) ;

	for(int i = 0 ; i < m ; i++ )
	{
		int vert = children[i].first ;
		int edge = children[i].second ;

		if(vert == father) continue ;

		int save0 = dp[vert][0] ;
		int save1 = dp[vert][1] ;

		int cte = -inf ;
		if(i) cte = max(cte, pref[i-1]) ;
		if(i+1 < m) cte = max(cte, suf[i+1]) ;

		dp[x][0] = soma-max(save0,save1) ;
		dp[x][1] = soma-max(save0,save1) + cte + edge ;

		dfsSpin(vert, x) ;

		dp[vert][0] = save0 ;
		dp[vert][1] = save1 ;

	}

}

int main()
{

	scanf("%d", &n ) ;

	if(n == 1)
	{
		printf("0\n") ;
		return 0 ;
	}

	for(int i = 1 , a , b , c ; i < n ; i++ )
	{
		scanf("%d%d%d", &a, &b, &c ) ;

		adj[a].push_back(make_pair(b,c)) ;
		adj[b].push_back( make_pair(a,c) ) ;

	}

	dfs(1,-1);
	dfsSpin(1,-1) ;

	printf("%d\n" , ans ) ;

}
