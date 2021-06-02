#include <bits/stdc++.h>

#define debug printf
#define ll long long
#define all(x) x.begin(),x.end()
#define sz(x) (int)(x.size() )
#define pb push_back
#define pii pair<int,int>
#define ff first
#define ss second
#define mk make_pair

const int MAXN = 55 ;
const int MAXT = 2e4+10 ;
const ll inf = 1e17+10LL ;

using namespace std ;

struct Intervals
{
	int l , r , id ;

	Intervals(int l = 0 , int r = 0 , int id = 0 ) : l(l), r(r), id(id) {}

} ;

struct minQueue
{
	deque< pair<ll, int> > dq ;
	int l , r ;

	void clean()
	{
		while( !dq.empty() ) dq.pop_back() ;
		l = 1 ;
		r = 0 ;
	}

	void add( ll val )
	{
		while( !dq.empty() && dq.back().first >= val )
			dq.pop_back() ;
		
		dq.push_back( make_pair(val, ++r) ) ;
	}
	void pop()
	{
		if( dq.front().second == l ) dq.pop_front() ;
		l++ ;
	}

	ll getMin() { return dq.front().first ; }

} q ;

int N , T , S , toGet, toFill = 1 ;
int tab[MAXN][MAXT] ;
int firstZero[MAXN] ;
int freq[MAXT] ;
ll sv[MAXT] ;
ll dp[2][MAXT] ;
vector< pair<int,int> > vec[MAXT] ;
vector< Intervals > intervals[MAXN] ;

ll getCost(int l, int r ) { return sv[r]-sv[l-1] ; }

void solve()
{
	for(int i = 0 ; i <= T ; i++ ) dp[toFill][i] = inf ;

   for(int i = 0 ; i <= N ; i++ )
   {
   	if( intervals[i].empty() ) continue ;

   	q.clean() ;

		int l = 1 , r = 0 ;

		for(auto e : intervals[i] )
		{
			while( r < e.r )
			{
				r++ ;
				q.add( dp[toGet][r-1]-sv[r-1]*(ll)i ) ;
			}			

			while( l < e.l )
			{
				q.pop() ;
				l++ ;
			}

			dp[toFill][e.id] = min( dp[toFill][e.id] , sv[e.id]*(ll)i + q.getMin() ) ;

		}

   }

}

int main()
{
	scanf("%d %d %d", &N, &T , &S ) ;
	for(int i = 1 ; i <= T ; i++ ) 
	{
		scanf("%lld", &sv[i] ) ;
		sv[i] += sv[i-1] ;
	}
	
	char c ;
	for(int i = 1 ; i <= N ; i++ )
		for(int j = 1 ; j<= T ; j++ )
		{
			scanf(" %c", &c ) ;
			tab[i][j] = (c == '1') ;
		}

	for(int i = 1 ; i <= T ; i++ )
	{
		for(int j = 1 ; j<= N ; j++ )
			if( !tab[j][i] ) firstZero[j] = i ;

		for(int j = 1 ; j <= N ; j++ )  freq[ firstZero[j] ]++ ;
		for(int j = 1 ; j <= N ; j++ ) vec[i].push_back( make_pair( firstZero[j] , freq[ firstZero[j] ] ) ) ;

		vec[i].push_back( make_pair(0, freq[0] ) ) ;

		sort(all(vec[i] ) ) ;
		vec[i].erase( unique(all(vec[i] ) ) , vec[i].end() ) ;

		for(auto e : vec[i] ) freq[e.first] = 0 ;
	
	   int tot = N ;
		int r = i ;

		for(int j = sz(vec[i])-1 ; j >= 0 ; j-- )
		{
			int l = vec[i][j].first+1 ;

			if( l <= r ) intervals[tot].push_back( Intervals(l,r, i) ) ;

			tot -= vec[i][j].second ;
			r = vec[i][j].first ;
		}
		
	}
  
	//Base da dp
	for(int i = 1 ; i <= T ; i++ )
	{
		ll qtdOn = (vec[i][0].first == 0 )	? vec[i][0].second : 0 ;	
		dp[0][i] = getCost(1,i)*qtdOn ;
	}
	dp[1][0] = dp[0][0] = inf ;

	printf("%lld\n", dp[0][T] ) ;

	for(int i = 2 ; i <= S ; i++  , swap(toGet, toFill ) )
	{
		solve() ;
		printf("%lld\n", dp[toFill][T] ) ;
	}	

}
