#include "tickets.h"
#include <bits/stdc++.h>
 
#define ff first
#define ss second
#define mk make_pair
#define all(x) x.begin(),x.end()
#define pii pair<int,int>
 
using namespace std ;
 
long long find_maximum(int k, std::vector<std::vector<int>> x) {
	
	int n = x.size();
	int m = x[0].size();
	long long tot = 0LL ;
	
	vector< vector<int> > answer( n , vector<int>(m,-1) ) ;
	vector< vector<int> > idx(n , vector<int>(m) ) ;
	vector< pair<long long, int> > somas ;
	vector<int> peguei(n,0) ;
 
	for(int i = 0 ; i < n ; i++ )
	{
		iota(all(idx[i]) , 0 ) ;
		sort( all(idx[i]) , [&](int a, int b) { return x[i][a] < x[i][b] ; } ) ;
 
		for(int j = 0 ; j < k ; j++ ) tot -= x[i][ idx[i][j] ] ;
 
		for(int j = k-1 , g = m-1 ; j >= 0 ; j-- , g-- )
			somas.push_back( mk(x[i][j] + x[i][g] , i) ) ;
 
	}
 
	sort(all(somas)) ;
	reverse(all(somas)) ;
	
	for(int i = 0 ; i < (n * k)/2 ; i++ )
	{
		peguei[ somas[i].second ]++ ;
		tot += somas[i].first;
	}
 
	set< pii > s ;
 
	for(int i = 0 ; i < n ; i++ ) 
		if( peguei[i] ) s.insert( mk( -peguei[i] , i ) ) ;
 
	for(int round=0 ; round < k ; round++ )
	{
 
		vector<pii> toReInsert ;
 
		for(int i = 0 ; i < n/2 ; i++ )
		{
			auto topo = *s.begin() ;
			s.erase(s.begin()) ;
 
			if(-topo.ff != 1)
				toReInsert.push_back( mk( topo.ff +1 , topo.ss ) ) ;
 
			answer[ topo.ss ][ idx[topo.ss].back() ] = round ;
			idx[topo.ss].pop_back() ;
 
		}
 
		for(auto p : toReInsert) s.insert(p) ;
 
	}
 
	vector<bool> freq(m,false) ;
 
	for(int i = 0 ; i < n ; i++ )
	{	
		for(int j = 0 ; j < m ; j++ )
			if(answer[i][j] != -1) freq[ answer[i][j] ] = true ;
 
		int ptr = 0 ;
 
		for(int j = 0 ; j < k - peguei[i]; j++ )
		{
			while( ptr < k && freq[ptr] ) ptr++ ;
			answer[i][ idx[i][j] ] =  ptr ;
			freq[ptr] = true ;
		}
 
		for(int j = 0 ; j < k ; j++ ) freq[j] =false ;
 
	}
	
	allocate_tickets(answer);
	return tot ;
}
