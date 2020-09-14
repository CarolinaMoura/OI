#include "fun.h"
#include <bits/stdc++.h>

#define sz(x) (int)(x.size())
#define lp(i,a,b) for(int i = a; i < b ;i++)
#define all(x) x.begin(),x.end()
#define debug printf
#define mk make_pair
#define pii pair<int,int>
#define ss second
#define ff first

const int MAXN = 1e5+10 ;

using namespace std ;

vector<int> createFunTour(int n , int q ) 
{
	int centroid = 0 , lastTaken = -1 ;
	vector<int> ans , available(3) ;
	vector<int> distCentroid(n,0) ;
	vector<int> groups[3] ;

	for(int i = 1 ; i < n ; i++ )
		if(attractionsBehind(centroid,i) > n/2 ) centroid = i ; 


	for(int i = 0 ; i < n ; i++ )
		if(i != centroid ) distCentroid[i] = hoursRequired( i, centroid ) ;

	for(int i = 0 ; i < n ; i++ )
	{
		if(i == centroid ) continue ;

		for(int j = 0 ; j < 3 ; j++ )
			if( j == 2 || sz(groups[j]) == 0 || hoursRequired( groups[j][0] , i ) != (distCentroid[i] + distCentroid[ groups[j][0] ]) )
			{
				groups[j].push_back(i) ;
				break ;
			}

	}


	iota(all(available),0) ;
	for(int i = 0 ; i < 3 ; i++ )
		sort(all(groups[i]) , [&](int i, int j){ return distCentroid[i] < distCentroid[j]; }  );

	while(true)
	{

		sort(all(available) , [&](int i, int j) { return sz(groups[i]) > sz(groups[j]); } ) ;

		if( sz( groups[ available[0] ] ) >= sz( groups[available[1]] )  + sz( groups[ available[2] ] ))
			break ;

		sort(all(available) , [&](int i, int j) { return distCentroid[ groups[i].back() ] > distCentroid[ groups[j].back() ] ;} ) ;		

		lastTaken = ( lastTaken == available[0] ) ? available[1] : available[0] ;

		ans.push_back( groups[lastTaken].back() ) ;
		groups[ lastTaken ].pop_back() ;

	}


	groups[ available[1] ].insert( groups[ available[1] ].end() , all( groups[ available[2] ] ) ) ;
	sort( all( groups[ available[1] ] ) , [&](int i, int j) { return distCentroid[i] < distCentroid[j]; } );

	int l = 0 ;

	if( sz(ans) > 1 && distCentroid[ ans.back() ] < distCentroid[ groups[available[1]].back() ] )
		l = 1 ;

	for(; groups[available[l]].size(); l^=1) {
		ans.push_back(groups[available[l]].back());
		groups[available[l]].pop_back();
	}

	ans.push_back(centroid) ;

	return ans ;
} 
