#include <bits/stdc++.h>

#define ff first
#define ss second
#define debug
#define pb push_back
#define pii pair<int,int>
#define all(x) x.begin(),x.end()
#define ll long long
#define sz(x) (int)(x.size())

using namespace std ;

void giveAns(vector<pii> ans )
{


	vector<pii> unequalX ;

	for(int i = 0 ; i < sz(ans) ; i++ )
	{
		int j = i+1 ;

		while( j < sz(ans) && ans[j].first == ans[i].first ) j++ ;

		unequalX.push_back(ans[i]) ;

		j-- ;

		if( i != j ) i = j-1 ;

	}

	vector<pii> unequalY ;


	for(int i = 0 ; i < sz(unequalX) ; i++ )
   {
   	
   	int j = i+1 ;

   	while( j < sz(unequalX)  && unequalX[j].second == unequalX[i].second ) j++ ;
   			
		j-- ;
   	unequalY.push_back(unequalX[i] ) ;

   	if(i != j ) i = j-1 ;

   } 

	swap(ans, unequalY ) ;

	printf("%d\n", sz(ans)-1 ) ;
	for(int i = 1 ; i < sz(ans) ; i++ ) printf("%d %d\n", ans[i].ff, ans[i].ss ) ;

	exit(0) ;


}

void makeInsertion(vector<pii> &vec , pii nxt , bool amVert )
{
	pii last = vec.back() ;

	if(amVert) vec.push_back(make_pair(last.first, nxt.second) ) ;
	else vec.push_back(make_pair(nxt.first, last.second) ) ;

}

int main()
{
	vector< pii > decLef , decRig ;
	vector<pii> inLef, inRig ; 
	vector< vector<pii> > layers ;

	int n ; 

	scanf("%d", &n ) ;

	vector<pii> points(n) ;

	for(int i= 0 ; i < n ; i++ ) scanf("%d %d", &points[i].first, &points[i].second ) ;

	set< pii > xs , ys ;

	for(int i = 0 ; i < n ; i++ )
	{
		xs.insert(make_pair(points[i].first, i ) ) ;
		ys.insert(make_pair(points[i].second,i) ) ;
	}


	auto remove = [&](int id)
	{
		xs.erase(xs.find(make_pair(points[id].first, id) ) ) ;
		ys.erase( ys.find(make_pair(points[id].second, id) ) ) ;
	};

	while( !xs.empty() )
	{

		if(sz(xs) == 1 )
		{
			inLef.pb( points[xs.begin() -> second ] ) ;
			break ;
		}

		vector<int> x , y;

		x.pb( xs.begin() -> second ) ;
		x.pb( prev(xs.end() )->second ) ;

		y.pb( ys.begin() -> second ) ;
		y.pb( prev(ys.end() )->second );
		
		bool ok = false ;

		for(int i = 0 ;i < 2 ; i++ )
			for(int j = 0 ; j < 2 ; j++ )
				if( x[i] == y[j] )
				{
					if(i == 0 && j == 0 ) inLef.pb( points[x[i]] ) ;
					if( i == 0 && j == 1 ) decLef.pb(points[x[i]] ) ;
					if( i == 1 && j == 0 ) decRig.pb(points[x[i]] );
					if(i == 1 && j == 1 ) inRig.pb( points[x[i]] ) ;

					ok = true ;

					xs.erase( xs.find(make_pair(points[x[i]].first, x[i]) ) ) ;
					ys.erase( ys.find( make_pair(points[x[i]].second, x[i]) ) ) ;

				}

		if(ok) continue ;

		for(auto e : x ) remove(e) ;
		for(auto e : y) remove(e) ;

		layers.push_back( {points[x[0]], points[y[1]], points[x[1]], points[y[0]]} ) ;

	}

	reverse(all(inRig) ) ;
	reverse(all(decLef) );

	vector<pii> myPath(1,make_pair(0,0) ) ;
	vector<pii> increasing, decreasing ;
	                                    
	for(auto e : inLef ) increasing.pb(e) ;
	for(auto e : inRig ) increasing.pb(e) ;
	for(auto e : decRig ) decreasing.pb(e) ;
	for(auto e : decLef ) decreasing.pb(e) ;		

	if( sz(increasing) > 0 && sz(decreasing) > 0 && increasing.back().second < decreasing.back().second )
		swap(increasing, decreasing) ;

	reverse(all(decreasing) ) ;

	bool amVert= false ;
	if(sz(increasing)%2 == 0 ) amVert = true ;

	for(int i = 0 ; i < sz(increasing) ; i++, amVert = !amVert )
	{
		makeInsertion(myPath, increasing[i] , amVert ) ;
		myPath.pb(increasing[i] ) ;
	}

	if(sz(increasing) == 0 && sz(decreasing)>0 )
	{
		myPath.pb(make_pair(0,decreasing[0].ss+1 ) ) ;
	}

	if(sz(decreasing) > 0 )
		amVert = false ;

	for(int i = 0 ; i < sz(decreasing) ; i++, amVert = !amVert )
	{
		makeInsertion(myPath, decreasing[i] , amVert ) ;
		myPath.pb(decreasing[i] ) ;
	}

	giveAns(myPath) ;

	amVert = !amVert ;

	while( sz(layers) > 0 )
	{

		if( amVert )
		{

			vector<int> lista = {3,0,1,2} ;

			if( myPath.back().first < layers.back()[3].first ) lista = {3,2,1,0} ;

			for(auto e : lista )
			{
				makeInsertion(myPath , layers.back()[e] , amVert ) ;
				amVert = !amVert ;
				myPath.pb(layers.back()[e] ) ;
			}
		}
		else 
		{
			vector<int> lista = {0,1,2,3} ;
			
			if( myPath.back().second > layers.back()[0].second ) lista = {0,3,2,1} ;

			for(auto e : lista )
			{

				makeInsertion(myPath, layers.back()[e], amVert ) ;
				amVert = !amVert ;
				myPath.pb(layers.back()[e]) ;
			}

		}

		layers.pop_back() ;

	} 

	giveAns(myPath) ;

}
