#include <bits/stdc++.h>
 
#define ll long long
#define all(x) x.begin(),x.end()
#define sz(x) (int)(x.size() )
#define lp(i,a,b) for(int i = a;  i< b ; i++ )
#define pii pair<int,int> 
#define P 37LL

const ll MOD = 1e9+7 ; 
const int MAX = 1e5+10 ;

using namespace std ;

string str ;
ll pot[MAX] ;
ll h[MAX] ;
char ans[MAX] ;
set< pair<ll, int> > alph[30] ;
  
void solve(int l, int r)
{
	if(l > r ) return ;

	set< pair<ll,int> > &ptr = alph[str[l]-'a' ] ;

	auto it = ptr.lower_bound( make_pair(h[l], -r ) ) ;

 	if( it == ptr.end() || it->first != h[l] ) 
 	{
		cout << "-1" << endl ;
		exit(0) ;
 	}

 	int newr = -it->second ;

 	ans[l] = '(' ;
 	ans[ newr ] = ')' ;

	ptr.erase( it ) ;
	ptr.erase( ptr.find( make_pair(h[l+1], -l ) ) ) ;

	solve(l+1, newr-1) ;
	solve(newr+1, r) ;

}

int main()
{	

	ios_base::sync_with_stdio(false) ;
	cin.tie(NULL) ;
 
	cin >> str ;
	
	int n = sz(str) ;

	pot[0] = 1LL ;
	for(int i = 1 ; i < n ; i++ ) pot[i] = (pot[i-1] * P ) % MOD ;

	stack<char> st ;

	ll curHash = 0LL ;

	for(int i = n-1 ; i >= 0 ; i-- )
	{
		alph[ str[i] - 'a' ].insert( make_pair( curHash, -i) ) ;

		if( !st.empty() && st.top() == str[i] )
		{
			curHash -= ( pot[ sz(st)-1 ]*( st.top()-'a'+1 ) )% MOD ;	
			if(curHash < 0 ) curHash += MOD ;
			st.pop() ;
		}				
		else
		{
			curHash += ( pot[sz(st) ] * ( str[i]-'a'+1) ) % MOD ;
			if(curHash >= MOD ) curHash -= MOD ;
			st.push( str[i] ) ;
		}

		h[i] = curHash ;

	}

	solve(0, n-1) ;

	for(int i = 0 ; i <n ; i++ ) cout << ans[i] ; 
	cout << endl ;
	
}
