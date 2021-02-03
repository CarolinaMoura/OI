#include <bits/stdc++.h>

#define sz(x) (int)(x.size() )
#define all(x) x.begin(),x.end()

using namespace std ;

int n , m , p , cur_node ;
vector< pair<int,int > > edges ;

void div_and_conquer( vector<int> &v_in, vector<int> &v_out )
{
	int t = sz(v_in ) ;

	if( t == 1 )
	{
		edges.push_back( make_pair( v_in[0] , v_out[0] ) ) ;
		return ;
	}

	vector<int> middle_esq , esq , dir , middle_dir ;
	for(int c = 0 ; c < (t>>1) ; c++ ) 
	{
		middle_esq.push_back( ++cur_node ) ;
		esq.push_back( v_out[c] ) ;
	}
	for(int c = (t>>1) ; c < t ; c++ )
	{
		middle_dir.push_back( ++cur_node ) ;
		dir.push_back( v_out[c] ) ;
	}

	div_and_conquer( middle_esq , esq ) ;
	div_and_conquer( middle_dir, dir ) ;

	for(int i = 0, j_esq = 0, j_dir = 0 ; i < t ; i++ , j_esq++, j_dir++ )
	{
		if( j_esq == sz(middle_esq) ) j_esq = 0 ;
		if( j_dir == sz(middle_dir) ) j_dir = 0 ;		

		edges.push_back( make_pair(v_in[i], middle_esq[j_esq] ) ) ;
		edges.push_back( make_pair(v_in[i] , middle_dir[j_dir] ) ) ;
	}

}

void solve()
{
	edges.clear() ;

	cin >> n >> m >> p ;

	cur_node = 2*n ;

	vector<int> v_in , v_out ;

	for(int i = 1 , c = 4 ; i <= n ; i++,  c++ )
	{
		if(c == 4 ) 
		{
			v_in.push_back( ++cur_node ) ;
			c = 0 ;
		}
		edges.push_back( make_pair(i, cur_node) ) ;
	}
	for(int i= n+1 , c = 4 ; i <= 2*n ; i++ , c++ )
	{
		if(c == 4 )
		{
			v_out.push_back( ++cur_node ) ;
			c = 0 ;
		}
		edges.push_back( make_pair(cur_node, i) ) ;
	}

	div_and_conquer(v_in, v_out ) ;

	cout << cur_node << " " << sz(edges) << endl ;
	for(auto e : edges ) cout << e.first << " " << e.second << endl ;
}

int main()
{
	ios_base::sync_with_stdio(false) ;
	cin.tie(NULL) ;

	string aux[8] = { "" , "1", "2", "3", "4", "5", "6", "7" } ;

	for(int t = 1 ; t <= 7 ; t++ )
	{
		freopen( ( aux[t] + "-router.in").c_str() , "r", stdin ) ;
		freopen( ( aux[t] + "-router.out").c_str() , "w", stdout ) ;
		solve() ;
	}
}
