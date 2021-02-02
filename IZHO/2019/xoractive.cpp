#include "interactive.h"
#include <bits/stdc++.h>

#define sz(x) (int)(x.size() )
#define ll long long
#define all(x) x.begin(),x.end()
#define lp(i,a,b) for(int i= a ; i< b ; i++ )

using namespace std;

map<int,int> mp ;
map<int,int> trash ;

vector<int> guess(int n) 
{	
	vector<int> ans(n) ;

	ans[0] = ask(1) ;
	mp[ ans[0] ] = 1 ;


	for(int i = 0 ; i < 7 ; i++ )
	{
	   vector<int> v ;
		
		for(int j = 2 ; j <= n ; j++ )
			if( ((1<<i)&j) != 0 ) v.push_back(j) ;

		if( v.empty() ) continue ;

		trash.clear() ;

		vector<int> res = get_pairwise_xor(v) ;
		for(auto e : res ) trash[e]-- ;

		v.push_back(1) ;
		res = get_pairwise_xor(v) ;
		for(auto e : res ) trash[e]++ ;

		trash[0]-- ;

		for(auto e : trash )
		{
			if( e.second == 0 ) continue ;
			int num =e.first^ans[0] ;
			
			if(mp.find(num) == mp.end() ) mp.insert(make_pair(num , (1<<i) )) ;
			else mp[num] |= (1<<i) ;

		}

	}

	for(auto e : mp ) ans[e.second-1] = e.first ;

	return ans ;

}
