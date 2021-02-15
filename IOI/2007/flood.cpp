#include <bits/stdc++.h>

#define ll long long
#define all(x) x.begin(),x.end()
#define pb push_back
#define sz(x) (int)(x.size() )

const int MAXN = 1e5+5 ;

using namespace std ;

int N , M , ans ;
vector< tuple<short int,int, int> > adj[MAXN] ;
pair<int,int> p[MAXN] ;
short int idx[4] ;
pair<short int,int> a ;
int p_idx[MAXN] ;
bool wall[2*MAXN] ;

void dfs(int x, short int dir, int yy, short int ddir )
{

	for(int i= 0 ; i < 4 ; i++ ) idx[i] = -1 ;
	
	for(int i = 0 ; i < sz(adj[x] ) ; i++ )
		idx[ get<0>(adj[x][i] ) ] = i ;	

	a = make_pair(0,0) ;

	for(int i = dir-1 , c = 0 ; c < 4 ; c++ , i++ )
	{
		if( i < 0 ) i += 4 ;
		if( i >= 4 ) i = 0 ;

		if( x == yy && i == ddir && idx[i] == -1 ) return ;
		if( idx[i] == -1 ) continue ;

		int y = get<1>(adj[x][idx[i] ]) ;

		adj[x].erase( adj[x].begin()+idx[i] , adj[x].begin()+idx[i]+1 ) ;

		dfs(y, i, yy, ddir ) ;

		a = make_pair( (i+2)%4, y ) ;

		break ;

	}

	if(!a.second) return;

	for(int i = 0 ; i < sz(adj[ a.second ] ) ; i++ )
	{
		if( get<0>(adj[a.second][i] ) != a.first ) continue ;
		
		wall[ get<2>(adj[a.second][i]) ] = true ;
		ans-- ;
		adj[a.second].erase( adj[a.second].begin() + i , adj[a.second].begin()+i+1 ) ;

		return ;
	}

}

int main()
{
	scanf("%d", &N ) ;
	for(int i= 1 ; i <= N ; i++ ) scanf("%d %d", &p[i].first, &p[i].second ) ;
	
	scanf("%d", &M ) ; ans = M ;
	for(int i = 1 , a , b  ; i<= M ; i++ )
	{
		scanf("%d %d", &a, &b ) ;

		if( p[a] > p[b] ) swap(a,b) ;

		if( p[a].first == p[b].first )
		{
			adj[a].push_back( make_tuple(0,b, i) ) ;
			adj[b].push_back( make_tuple(2,a,i) ) ;
		}
		else
		{
  			adj[a].push_back( make_tuple(1,b, i) ) ;
  			adj[b].push_back( make_tuple(3,a,i) ) ;
		}

	}

	for(int i = 1 ; i <= N ; i++ ) p_idx[i] = i ;
	sort(p_idx+1, p_idx+1+N, [&](int a, int b ) { return p[a] < p[b] ; } ) ;

	for(int j= 1 ; j <= N ; j++ )
	{
		int x = p_idx[j] ;

		sort(all(adj[x] ) ) ;

		for(int i = 0 ; i < sz(adj[x] ) ; i++ )
		{
			if( get<0>( adj[x][i] ) > 1 ) continue ;

			dfs(x, get<0>(adj[x][i])+1, x, get<0>(adj[x][i]) ) ;
			
			break ;

		}

	}

	printf("%d\n", ans ) ;

	for(int i = 1 ; i <= M ; i++ )
		if( !wall[i] ) printf("%d\n", i ) ;

}
