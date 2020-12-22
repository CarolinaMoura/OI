#include <bits/stdc++.h>

#define ll long long
#define sz(x) (int)(x.size() )
#define all(x) x.begin(),x.end()

const int MAXN = 3e5+10 ;

using namespace std ;

int N , M ;
int sub[MAXN] ;
vector< int > adj[MAXN] ;
ll sumOfEverything[MAXN] , edgeParent[MAXN] ;
map<ll,ll> *mp[MAXN] ; 

void dfs(int x)
{
	sub[x] = 1 ;
	int bc = -1 ;

	for(auto e : adj[x] )
	{
		dfs(e) ;
		sub[x] += sub[e] ;

		if( bc == -1 || sub[e] > sub[bc] ) bc = e ;
	}

	if(bc == -1) 
	{
		mp[x] = new map<ll,ll> ;
		
		(*mp[x]).insert(make_pair(0,-1) ) ;
		(*mp[x]).insert(make_pair(edgeParent[x],2) ) ;

		sumOfEverything[x] = 1 ;

		return ;

	}
	else 
	{
		mp[x] = mp[ bc ] ;
		sumOfEverything[x] = sumOfEverything[bc] ;
	}

  	map<ll,ll> &ptr = *mp[x] ;

  	for(auto e : adj[x] )
  	{
  		if(e == bc ) continue ;

  		for(auto ee : (*mp[e]) ) ptr[ee.first] += ee.second ;
  		(*mp[e]).clear() ;

  		sumOfEverything[x] += sumOfEverything[bc] ;

  	}

  	if(x == 1 ) return ;

  	ll threwAway = -1 ;

  	while( true )
  	{
  		auto it = ptr.end() ;
  		it-- ;

  		if( sumOfEverything[x] <= 0 ) break ;

  		sumOfEverything[x] -= it->second ;
  		threwAway = it->first ;
  		ptr.erase(it) ;
  	}

  	if( sumOfEverything[x] != 0 )
  	{
  		//That means it didn't have a zero to begin with
  		//So what?
  		ptr.insert( make_pair(threwAway, -1LL-sumOfEverything[x] ) ) ;
  		ptr.insert( make_pair(threwAway + edgeParent[x], 2) ) ;
  		sumOfEverything[x] = 1 ;
  	}
  	else 
  	{
  		auto it = ptr.end() ;
  		it-- ;

  		//There can be many zeroes!
  		//You dumb!

		while( it->second == 0 )
		{
			ptr.erase(it) ;
			it = ptr.end() ;
			it-- ;
		}

		auto aux = *it ;
		ptr.erase(it) ;
		aux.second-- ;

		ptr.insert(aux) ;
		ptr.insert( make_pair(aux.first + edgeParent[x],1) ) ;
		ptr.insert( make_pair(threwAway+edgeParent[x],1 ) ) ;

		sumOfEverything[x] = 1 ;

  	}


}

int main()
{
	ll _sum = 0LL ;

	scanf("%d %d", &N, &M ) ;
	for(int i = 2 , parent ; i <= N+M ; i++ )
	{
		scanf("%d %d", &parent, &edgeParent[i]) ;
		_sum += edgeParent[i] ;
		adj[ parent ].push_back( i ) ;
	}

	dfs(1) ;

	map<ll,ll> &ptr = (*mp[1]) ;

	ll slope = 0LL , last = 0 ;

	for(auto e : ptr )
	{
		_sum += slope * (e.first-last) ;
		slope += e.second ;
		last=e.first;

		if(slope >= 0 )
		{
			printf("%lld\n", _sum ) ;
			return 0 ;
		}
	}


}
