#include <bits/stdc++.h>

#define mk make_pair
#define pii pair<int,int>
#define ll long long

const int MAXM = 2e5+10 ;
const int MAXQ = 2e5+10 ;

using namespace std ;

int N , M , Q , en ;
int custo[MAXM] ;
vector<pair<int,int> > queries[MAXM] ;
int lz ;
int qtd[MAXM] , l[MAXM] , r[MAXM] ;
ll ans_beginning[MAXM] , c[MAXM] , ans[MAXQ] ;

int getInterval(int row) { return upper_bound( l+1, l+1+en , row ) - l - 1 ; }

ll getCost(int row )
{
	
	int idx = getInterval(row) ;
	
	ll ans = ans_beginning[idx] ;
	ans += c[idx]*( row-l[idx] ) ;
	ans += (ll)(row)*(ll)(row)*(ll)(lz-qtd[idx]) ;
			
	return ans ;
}

void solve(int x)
{
	for(auto e : queries[x] ) ans[e.second] = getCost(e.first) ;
}

int main()
{
	scanf("%d %d", &N, &M ) ;
	for(int i = 1 ; i <= M ; i++ ) scanf("%d", &custo[i] ) ;
	scanf("%d", &Q ) ;
	for(int i = 1 , x , y ; i <= Q ; i++ )
	{
		scanf("%d %d", &x ,&y ) ;
		queries[y].push_back(mk(x,i)) ;
	}
		
	l[1] = 1 , r[1] = N ;
	c[1] = custo[1] ;
	en = 1 ;
	
	solve(1) ;
	
	for(int i = 2 ; i <= M ; i++ )
	{
		lz++ ;
		
		int lo = 2 , hi = N , mid , best = -1 ;
		while(lo <= hi)
		{
			mid = (lo+hi)>>1 ;
			if( getCost(mid)-getCost(mid-1) > custo[i] ) 
			{
				best = mid ;
				hi = mid-1 ;
			}
			else lo = mid+1 ;
		}
		
		if(best != -1 ) 
		{		
			int idx = getInterval(best) ;
			if( l[idx] < best ) idx++ ;
			
			ans_beginning[idx] = getCost( best-1 ) + custo[i] ;
			l[idx] = best; 
			r[idx] = N ;
			l[idx+1] = N+5 ;
	 		en = idx ;
			qtd[idx] = lz ;
			c[idx] = custo[i] ;	
		}
		
		solve(i) ;
		
	}
	
	for(int i = 1 ; i <= Q ; i++ ) printf("%lld\n", ans[i] ) ;
	
}
