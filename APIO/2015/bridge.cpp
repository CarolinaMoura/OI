#include <bits/stdc++.h>

#define ll long long
#define all(x) x.begin(),x.end()
#define sz(x) (int)(x.size() )

const int MAXN = 1e5+10 ;

using namespace std ;

int N , K ;
long long ans ;

vector<ll> solve(vector< pair<int,int> >  v )
{
	multiset<int> s[2] ;
	ll soma[2] = {0,0} ;

	vector<ll> dp( sz(v) , 0 ) ;
	s[0].insert( v[0].first ) ; soma[0] = (ll)v[0].first ;
	s[1].insert( v[0].second ) ; soma[1] = (ll)v[0].second ;
	dp[0] = soma[1] - soma[0] ;

	for(int i = 1 ; i < sz(v) ; i++ )
	{
		for(int e : { v[i].first, v[i].second } )
		{			
			if( e < *s[1].begin() ) s[0].insert(e) , soma[0] += (ll)e ;
			else s[1].insert(e) , soma[1] += (ll)e ;
		}

		while( sz(s[0]) > sz(s[1] ) )
		{
			auto it = prev(s[0].end() ) ;

			s[1].insert( *it ) ;
			soma[1] += *it ;	
			soma[0] -= *it ;
			s[0].erase(it) ;
		}

		while( sz(s[1]) > sz(s[0]) )
		{
			auto it = s[1].begin() ;

			soma[1] -= *it ;
			soma[0] += *it ;
			s[0].insert(*it) ;
			s[1].erase(it) ;
		}

		dp[i] = soma[1] - soma[0] ;

	}

	return dp ;
}

int main()
{

	scanf("%d %d", &K , &N ) ;

	vector< pair<int,int> > v ;

	for(int i = 0 , l , r ; i < N ; i++ )
	{
		char c1, c2 ;
		scanf(" %c %d %c %d", &c1, &l, &c2, &r ) ;

		if( l > r ) swap(l,r) ;

		if(c1 == c2 ) ans += (ll)(r-l);
		else v.push_back(make_pair(l,r) ) , ans++ ;
	}

	if( sz(v) == 0 )
	{
		printf("%lld\n", ans ) ;
		return 0 ;
	}

	sort(all(v) , [&](pair<int,int> a, pair<int,int> b ) { return a.first + a.second < b.first + b.second ; } ) ;

	vector<ll> dpPref = solve(v) ;
	reverse(all(v) ) ;
	vector<ll> dpSuf = solve(v) ;
	reverse(all(dpSuf) ) ;

	if(K == 1 || sz(dpSuf) <= 1 ) 
	{
		printf("%lld\n", ans + dpSuf[0] ) ;
		return 0 ;
	}

	ll mn = dpPref[0] + dpSuf[1] ;

	for(int i = 1 ; i < sz(dpPref)-1 ; i++ ) mn = min(mn, dpPref[i] + dpSuf[i+1] ) ;

	printf("%lld\n", ans + mn ) ;

}
