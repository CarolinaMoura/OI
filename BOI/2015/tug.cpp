#include <bits/stdc++.h>

#define sz(x) (int)(x.size())

const int MAXN = 6e4+10 ;
const int MAX = 3e4+10 ;

using namespace std ;

int N , K , s_left , s_tudo ;
int S[MAXN] , unnamed[MAX*40] ;
pair<int,int> p[MAXN] , loc[MAXN] ;
vector<int> freq[MAXN] ;
bool dp[MAX*20] ;

bool cmp(int x, int y) { return make_pair(sz(freq[x]),x) < make_pair(sz(freq[y]),y) ; }
set<int, bool(*)(int, int) > s(cmp) ;

void impossible()
{
	printf("NO\n") ;
	exit(0) ;
}

int solve()
{
	int lef = 0 , rig = 0 ;

	while(!s.empty() && sz(freq[*s.begin()]) <= 1 )
	{
		int id = *s.begin() ;
		s.erase(s.begin());

		if( sz(freq[id]) == 0 ) impossible() ;
		
		int P = freq[id][0] ;

		if( id == p[P].first ) 
		{
			swap(p[P].first, p[P].second ) ;
			swap(loc[P].first ,loc[P].second ) ;
		}

		int otherId = p[P].first;

		if( id<= N ) lef += S[P] ;
		else rig += S[P] ;

		if( s.find(otherId) == s.end() ) continue ;

		s.erase( s.find(otherId) ) ;
		int tam = sz(freq[otherId]) ;

		int V = freq[otherId][tam-1] ;
		if( otherId == p[V].second )
		{
			swap(p[V].first, p[V].second ) ;
			swap(loc[V].first, loc[V].second ) ;
		}

		loc[ V ].first = loc[P].first; 
		freq[otherId][ loc[V].first ] = V ;
		freq[otherId].pop_back() ;

		s.insert(otherId) ;

	}

	return lef-rig ;
}

int main()
{
	scanf("%d %d", &N, &K ) ;

	for(int i = 1 , a , b ; i <= (N<<1) ; i++ )
	{
		scanf("%d %d %d", &a, &b , &S[i]  ) ;

		b += N ;

		p[i] = make_pair(a,b) ;
		loc[i] = make_pair( sz(freq[a]) , sz(freq[b]) ) ;

		freq[a].push_back(i) ;
		freq[b].push_back(i) ;		
	}
	for(int i = 1 ; i <= (N<<1); i++ ) s.insert(i) ;

	int S = abs(solve()) ;
	dp[S] = dp[0] = true ;

	while(!s.empty())
	{
		int x = *s.begin() ;
		
		s.erase(s.find(x)) ;

		freq[x].pop_back() ;

		s.insert(x) ;

		int k= abs(solve()) ;
		unnamed[ k ]++ ;
		S += k ;
	}
	
	for(int i = 0 ; i <= 20*N ; i++ )
	{
		if( unnamed[i] == 0 ) continue ;

		for(int j = 20*N ; j >= i ; j-- )
			if( dp[j-i] )	
				for(int b = j , q = 0 ; b <= 20*N && q < unnamed[i] && !dp[b] ; b += i , q++ )
					dp[ b ] = true ;

	}

	for(int i = 0 ; i <= 20*N ; i++ )
	{
		int ans = i-(S-i) ;
		if( ans < -K || ans > K || !dp[i] ) continue ;
		
		printf("YES\n") ;
		return 0 ;
	}

	impossible() ; 
	
}



