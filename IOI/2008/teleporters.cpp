#include <bits/stdc++.h>

#define ll long long
#define all(x) x.begin(),x.end()
#define sz(x) (int)(x.size() )

const int inf = 2e6+10 ;
const int MAX = 2e6+10 ;

using namespace std ;

int n , m ;
vector<int> adj ;
bool vis[MAX] ;

int getCycle(int x)
{
	vis[x] = true ;

	if( !vis[ adj[x] ] ) 
		return 1 + getCycle(adj[x] ) ;

	return 1 ;
}

int main()
{
	scanf("%d %d", &n, &m) ;

	vector< pair<int,int> > sweep(2) ;

	sweep[0] = make_pair(0, -1) ;
	sweep[1] = make_pair(inf, 0) ;

	for(int i = 0 , x , y ; i < n ; i++ )
	{
		scanf("%d %d", &x, &y ) ;

		sweep.push_back(make_pair(x,y) ) ;
		sweep.push_back(make_pair(y, x) ) ;
	}

	sort(all(sweep) ) ;

	vector<int> arriving(inf+5 ) ;
	vector<int> leaving(inf+5 ) ;

	for(int i = 1 ; i < sz(sweep) ; i++ )
		leaving[ sweep[i-1].first ] = arriving[ sweep[i].first ] = i ;

	adj.resize(sz(sweep)) ;

	for(int i = 1 ; i < sz(sweep) ; i++ )
		adj[i] = leaving[ sweep[i].second ] ;

	int ans = getCycle(1) - 1 ;

	priority_queue<int> fila ;

	for(int i = 2 ; i < sz(sweep) ; i++ )
		if( !vis[i] ) fila.push( getCycle(i) ) ;

	while( m && !fila.empty() )
	{
		ans += fila.top() + 2 ;
		fila.pop() ;
		m-- ;
	}

	ans += 2*m - (m&1) ;

	printf("%d\n", ans ) ;

}
