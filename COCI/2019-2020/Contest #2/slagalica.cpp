#include <bits/stdc++.h>

#define all(x) x.begin(),x.end()
#define sz(x) (int)(x.size())

using namespace std ;

bool check(int beg, int en, int freq1 , int freq2 , int freq3 , int freq4 )
{
	if(beg == 5 && en == 7 ) return freq1 == ( freq4 - 1 ) ;
	if(beg == 5 && en == 8 )
	{
	   if( freq2 && (!freq1 || !freq4 ) ) return false ;
		if( freq1 == freq4 ) return true ;
	}
	if(beg == 6 && en == 7 )
	{	
		if( freq3 && (!freq1 || !freq4 ) ) return false ;
		if( freq1 == freq4 ) return true ;
	}
	if(beg == 6 && en == 8 ) return freq1 - 1 == freq4 ;

}

void noAnswer()
{
	printf("-1\n") ;
	exit(0) ;
}

int N ;
int val[9] = {0,5, 6, 5, 6, 5, 6, 7, 8 } ;

int main()
{

	scanf("%d", &N ) ;

	vector< vector<int> > freq(9, vector<int>() ) ;
	vector<int> ans ;

	for(int i = 0 , u , v ; i < N ; i++ )
	{
		scanf("%d %d", &u, &v ) ;
		freq[u].push_back(v) ;
	}

	for(int i = 1 ; i < 9 ; i++ ) 
	{
		sort(all(freq[i]) ) ;
		reverse( all(freq[i]) ) ;
	}

	int beg = 5 , en = 7 , last ;

	if( sz(freq[6]) ) beg = 6 ;
	if( sz(freq[8] ) ) en = 8 ;

	ans.push_back( freq[beg][0] ) ;

	if( !check(beg, en, sz(freq[1]) , sz(freq[2]) , sz(freq[3]), sz(freq[4] ) ) ) noAnswer() ;

	last = beg ;

	for(int i = 1 ; i < N-1 ; i++ )
	{
		vector< pair<int,int> > nxt ;

		if( last == 5 || last == 1 || last == 3 ) 
		{
			if( sz(freq[3] ) ) nxt.push_back( make_pair(freq[3].back() , 3 ) ) ;
			if( sz(freq[4] ) ) nxt.push_back( make_pair(freq[4].back(), 4 ) ) ;
		}
		if( last == 6 || last == 2 || last == 4 ) 
		{
			if( sz(freq[1] ) ) nxt.push_back( make_pair(freq[1].back(), 1 ) ) ;
			if( sz(freq[2] ) ) nxt.push_back( make_pair(freq[2].back(), 2 ) ) ;
		}

		sort(all(nxt) ) ;

		bool madeIt = false ;

		for(int j = 0 ; j < sz(nxt) ; j++ )
		{
			freq[ nxt[j].second ].pop_back() ;

			if( check(val[ nxt[j].second] , en, sz(freq[1]) , sz(freq[2]) , sz(freq[3]), sz(freq[4] ) ) ) 
			{
				madeIt = true ;
				last = nxt[j].second ;
				ans.push_back( nxt[j].first ) ;
				break ;
			}

			freq[ nxt[j].second ].push_back( nxt[j].first ) ;

		}

		if(!madeIt) noAnswer() ;
	}

	ans.push_back( freq[en][0] ) ;

	for(auto e : ans ) printf("%d ", e ) ;
	printf("\n") ;

}
