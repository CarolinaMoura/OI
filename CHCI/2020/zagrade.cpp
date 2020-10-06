#include <bits/stdc++.h>

#define sz(x) (int)(x.size())
#define mkt make_tuple
#define lp(i,a,b) for(int i = a ; i < b ; i++ )
#define ff first
#define ss second
#define pb push_back
#define ll long long
#define mk make_pair
#define pii pair<int,int>
#define debug printf
#define all(x) x.begin(),x.end()

using namespace std ;

int ask(int l, int r)
{
	cout << "? "<<l << " "<< r << endl ;
	int x ; cin >> x ;
	return x ;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL) ;

	int n , q ;
	cin >> n >> q ;

	vector<int> vec(1,1) ;
	vector<char> ans(n+1, '*') ;

	for(int i = 2 ; i <= n ; i++ )
	{
		if( sz(vec) > 0 && ask(vec.back(),i) == 1)
		{
			ans[ vec.back() ] = '(' ;
			ans[i] = ')' ;
			vec.pop_back() ;
		}
		else vec.push_back(i) ;
	}

	for(int i = 0 ; i < sz(vec)/2 ; i++ )
		ans[ vec[i] ] = ')' ;
	for(int i = sz(vec)/2 ; i < sz(vec) ; i++ )
		ans[ vec[i] ] = '(' ;

	cout <<  "! " ;
	lp(i,1,n+1) cout << ans[i] ;
	cout << endl ;
}
