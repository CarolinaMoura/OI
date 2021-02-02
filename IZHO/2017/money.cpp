/*
I haven't submitted this yet
You should do it when no one will ever suspect you are a stalker
*/
#include <bits/stdc++.h>
 
#define ll long long
#define all(x) x.begin(),x.end()
#define sz(x) (int)(x.size() )
#define lp(i,a,b) for(int i = a;  i< b ; i++ )
#define pii pair<int,int> 

const int MAXN = 1e6+10 ;

using namespace std ;

int N ;
int arr[MAXN] ;
int bit[MAXN] ;

void upd(int pos, int x ) { for(; pos < MAXN ; pos += pos & -pos ) bit[pos] += x ; }
int qry(int pos)
{
	int tot = 0 ;
	for(; pos > 0 ; pos -= pos & -pos ) tot += bit[pos] ;
	return tot ;
}

int main()
{
	scanf("%d", &N ) ;
	for(int i= 1 ; i <= N ; i++ ) 
	{
		scanf("%d", &arr[i] ) ;
		upd(arr[i], 1) ;
	}
	
	int ans = 0 ;
	for(int i = N ; i > 0 ; ans++ )
	{
		upd(arr[i], -1 ) ;
		int j = i-1 ;
		while( j > 0 && arr[j] <= arr[j+1] )
		{
			if( qry(arr[i]-1) - qry(arr[j] ) > 0 ) break ;
			upd(arr[j] , -1 ) ;
			j-- ;
		}
		i = j ;

	}

	printf("%d\n", ans ) ;
}
