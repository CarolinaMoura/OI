#include <bits/stdc++.h>

#define mk make_pair
#define pii pair<int,int>
#define ll long long

const int MAXN = 2e5+10 ;

using namespace std ;

int N , Q ;
int v[MAXN] , val[MAXN] ;
int mn[MAXN] , last[MAXN] , ans[MAXN] ;
vector<int> vec[MAXN] ;

void limpa(int cor) { for(auto e : vec[cor]) val[e] = vec[cor][0] ; }

int bit[MAXN] ;
void upd(int i , int x ) { for(; i < MAXN ; i += i &-i ) bit[i] += x ; }
int qry(int i)
{
	int tot = 0 ;
	for(; i > 0 ; i -= i &-i ) tot += bit[i] ;
	return tot ;
}

int main()
{
	scanf("%d %d", &N, &Q ) ;
	for(int i = 1 ; i <= N ; i++ ) 
	{
		scanf("%d", &v[i] ) ;
		mn[i] = i-1 ;
		while(mn[i] && v[mn[i]] >= v[i]) mn[i] = mn[mn[i]] ;
	}
	for(int i = 1 ; i <= N ; i++ )
	{		
		if( !vec[v[i]].empty() && mn[i] < vec[v[i]][0] )
		{
			vec[v[i]].push_back(i) ;
			continue ;	
		}
		
		limpa(v[i]) ;
		vec[v[i]] = {i} ;
	}
	for(int i = 1 ; i <= N ; i++ ) limpa(i) ;
	
	vector<tuple<int,int,int> > q ;
	for(int i = 1 , a , b ; i <= Q ; i++ )
	{
		scanf("%d %d", &a, &b ) ;
		q.push_back(make_tuple(b,a,i)) ;
	}	
	
	sort(q.begin() , q.end() ) ;
	
	int ptr = 0 ;
	for(int i = 1 ; i <= N ; i++ )
	{
		if(last[val[i]]) upd(last[val[i]],-1) ;
		
		last[val[i]] = i ;
		upd(i, 1) ;
		
		while(ptr < Q && get<0>(q[ptr]) == i )
		{
			ans[ get<2>(q[ptr]) ] = qry( N ) - qry( get<1>(q[ptr])-1 ) ;
			ptr++ ;
		}
	}
	
	for(int i = 1 ; i <= Q ; i++ ) printf("%d\n" , ans[i]) ;
}
