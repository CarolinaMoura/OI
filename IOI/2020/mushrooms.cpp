#include "mushrooms.h"
#include <bits/stdc++.h>
 
#define sz(x) (int)(x.size())
#define debug //printf
#define lp(i,a,b) for(int i = a ; i < b; i++)
#define pb push_back
#define ff first
#define ss second
#define mk make_pair
#define pii pair<int,int>
#define ll long long 
#define all(x) x.begin(),x.end()
 
const int CTE = 103 ;
 
using namespace std ;
 
int count_mushrooms(int n) 
{
 
	vector<int> type(n,1) ;
	vector<int> known[2] ;
	int res ;
 
	if( n <= 226 )
	{
 
		for(int i = 1 ; i < n ; i++ )
		{
			type[i] = type[i-1] ;
			if(use_machine( {i,i-1} )) type[i] ^= 1 ;
		}
 
		int cnt = 0 ;
		lp(i,0,n) cnt += type[i] ;
		return cnt ;
	}
 
	//Finding out about 5
	if(use_machine( {0,1} )) type[1] = 0 ;
	if( use_machine({0,2}) ) type[2] = 0 ;
	lp(i,0,3) known[type[i]].push_back(i); 
 
	lp(i,0,2)
	{
		if(sz(known[i]) < 2) continue ;
 
		res = use_machine( {known[i][0] , 3 , known[i][1] ,4} ) ;
		
		if( res&1 ) type[4] = !i , res-- ;
		else type[4] = i ;
 
		if(res == 0) type[3] = i ;
		else type[3] = !i ;
 
	}
 
	lp(i,3,5) known[ type[i] ].push_back(i) ;
 
	int undiscovered =  5;
 
	while( max( sz(known[0])  , sz(known[1]) ) < CTE )
	{
		//debug("Printando os tamanhos: %d %d\n" , sz(known[0]) , sz(known[1])) ;
 
		int idx = ( sz(known[0]) > sz(known[1]) ) ? 0 : 1 ;
		
		vector<int> q ;
		
		q.pb( known[idx][0] ) ;
		q.pb(undiscovered); 
		q.pb( known[idx][1] ) ;
		q.pb(undiscovered+1); 
		q.pb( known[idx][2] ) ;
		q.pb(undiscovered+2); 
 
		res = use_machine(q) ;
 
		if(res&1) type[undiscovered+2] = !idx , res-- ;
		else type[undiscovered+2] = idx ;
 
		known[ type[undiscovered+2] ].pb(undiscovered+2) ;
 
		if(res == 0 || res == 4) 
		{
			type[undiscovered] = type[undiscovered+1] = (res == 0) ? idx : !idx ;
			
			lp(i,0,2) known[ type[undiscovered+i] ].pb(undiscovered+i) ;
 
			undiscovered += 3 ;
 
			continue ;
		}
 
		if( min(sz(known[0]) , sz(known[1])) < 2 )
		{
			res = use_machine({ undiscovered, known[idx][0] }) ;
			
			if(res == 0 ) type[undiscovered] = idx ;
			else type[undiscovered] = !idx ;
 
			type[undiscovered+1] = !type[undiscovered ];
 
			lp(i,0,2) known[ type[undiscovered+i] ].pb(undiscovered+i) ;
 
			undiscovered += 3 ;
			continue ;
		}
 
		q.clear() ;
		q.push_back(known[!idx][0]) ;
		q.push_back(undiscovered) ;
		q.push_back(known[!idx][1]) ;
		q.push_back(known[idx][0]) ;
		q.push_back(undiscovered+1); 
		q.push_back(known[idx][1] ) ;
		q.push_back(undiscovered+3); 
		q.push_back(known[idx][2] ) ;
		q.push_back(undiscovered+4); 
 
		res = use_machine(q) - 1;
 
		if(res&1 ) type[undiscovered+4] = !idx , res-- ;
		else type[undiscovered+4] = idx ;
 
		if(res <= 2)
		{
			type[ undiscovered ] = !idx ;
			type[ undiscovered+1 ] = idx ;
			type[undiscovered+3] = (res == 2) ? !idx : idx ;
		}
		else
		{
			type[undiscovered] = idx ;
			type[undiscovered+1] = !idx ;
			type[undiscovered+3] = ( res == 4 ) ? idx : !idx ;
		}
 
		lp(i,0,5)
			if(i != 2 ) known[ type[undiscovered+i] ].push_back(undiscovered+i) ;
 
		undiscovered += 5 ;
 
	}
 
 
	int ans = 0 ;
 
	//lp(i,0,undiscovered) cout << !type[i] << " " ;
	//cout << endl ;
 
	while( n - undiscovered )
	{
 
		int idx = 0 ;
		if( sz(known[1]) > sz(known[0]) ) idx = 1 ;
 
		int qtd = min( n-undiscovered, sz(known[idx]) ) ;
 
		vector<int> q ;
		lp(i,0,qtd )
			q.pb( known[idx][i] ) , q.pb(undiscovered + i) ;
 
		res = use_machine(q) ;
 
		int last = undiscovered+qtd-1 ;
 
		if(res&1) type[last] = !idx , res-- ;
		else type[last] = idx ;
 
		known[type[last]].pb(last); 
 
		res /= 2 ;
		
		if(idx == 1) ans += qtd-1-res ;
		else ans += res ;
 
		undiscovered += qtd ;
 
	}
 
	ans += sz(known[1]) ;
 
	return ans ;
}
