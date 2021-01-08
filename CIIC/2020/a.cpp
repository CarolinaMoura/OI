/*
Is it rated?
*/

#include <bits/stdc++.h>

#define sz(x) (int)( x.size() )
#define all(x) x.begin(),x.end()
#define debug printf
#define ll long long
#define ff first
#define ss second
#define pii pair<int,int>
#define lp(i,a,b) for(int i = a ; i < b ; i++ )
#define pb push_back
#define mkt make_tuple
#define mk make_pair

const int MAXN = 1010 ;
const int MAXT = 2010 ;

using namespace std ;


struct Task 
{
	ll p , f , t ;

	Task(ll p = 0 , ll f=0 , ll t = 0 ) : p(p) , f(f) , t(t) {}
	bool operator < ( Task other ) const 
	{
		if( f * other.t == t * other.f ) return p < other.p ;
		return f * other.t < t * other.f ;
	}

} ;

int N , T ;
Task task[MAXN] ;
ll dp[MAXT][MAXN] ;

int main()
{
	scanf("%d%d", &N , &T ) ;
	for(int i = 1 ; i <= N ; i++ )
	{
		scanf("%lld %lld %lld", &task[i].p , &task[i].f, &task[i].t ) ;
		task[i].p -= task[i].t * task[i].f ;
	}

	sort(task+1, task+1+N) ;
	reverse(task+1, task+1+N) ;

	for(int i = T ; i >= 0 ; i-- )
		for(int j = N ; j > 0 ; j-- )
		{
			ll &ptr = dp[i][j] ;

			ptr = 0LL ;

			if( i + task[j].t <= T ) 
				ptr = max(task[j].p - task[j].f * i , 0LL) + dp[i+task[j].t][j+1] ;

			ptr = max( ptr , dp[i][j+1] ) ;

		}

	printf("%lld\n" , dp[0][1] ) ;
}
