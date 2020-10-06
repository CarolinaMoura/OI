#include "books.h"
#include <bits/stdc++.h>
 
#define debug printf
#define lp(i,a,b) for(int i = a ; i < b; i++)
#define pb push_back
#define ff first
#define ss second
#define mk make_pair
#define pii pair<int,int>
#define ll long long 
#define all(x) x.begin(),x.end()
#define sz(x) (int)(x.size())
 
const int MAX = 1e6+10 ;
 
using namespace std ;
 
//Tentando uma ideia (provavelmente vai dar errado mas vamos nessa)
 
 
long long minimum_walk(vector<int> p, int s) 
{
 
	int n = sz(p) ;
	ll ans = 0LL ;
 
	lp(i,0,n) ans += (ll)(abs(p[i]-i)) ;
 
	int L = 0  ;
	int R = n-1 ;
 
	while(L < s && p[L] == L ) L++ ;
	while(R > s && p[R] == R) R-- ;
 
	vector<bool> vis( n, false ) ;
	vector<pii> intervalo(n, make_pair(-1,-1) ) ;
 
	for(int i = L ; i <= R ; i++ )
	{
		if(vis[i]) continue ;
 
		vector<int> List ;
 
		int x = i , l = i , r = i;
		while(!vis[x])
		{
			vis[x] = true ;
			List.push_back(x) ;
			
			l = min(l,x) ;
			r = max(r,x) ;
 
			x = p[x] ;
		}
 
		for(auto e : List ) intervalo[e] = make_pair(l,r) ;
 
	}
 
	int l = s , r = s ;
	int lmin = intervalo[s].ff, rmax = intervalo[s].ss ;
	ll lastTime = ans ;
 
	while( !(l <= L && r >= R) )
	{
 
		while( l > lmin || r < rmax )
		{
 
			if( l > lmin )
			{
				l-- ;
 
				if( intervalo[l].ff <= lmin && intervalo[l].ss >= rmax )
					lastTime = ans ;
 
				lmin = min( lmin , intervalo[l].ff ) ;
				rmax = max(rmax, intervalo[l].ss ) ;
			}
 
			if(r < rmax )
			{
				r++ ;
 
				if(intervalo[r].ff <= lmin && intervalo[r].ss >= rmax)
					lastTime = ans ;
 
				lmin = min(lmin, intervalo[r].ff );
				rmax = max(rmax , intervalo[r].ss ) ;
			}
 
		}
 
		//Agora custa
 
		if( l <= L && r >= R ) break ;
 
		int auxl=  lmin ;
		int auxr = rmax ;
 
		int mnr = auxr, mxl = auxl ;
		int cost = 0 ;
 
		bool ok = false ;
 
		while( auxl > L &&  auxr < R )
		{
			cost += 2LL ;
 
			auxl-- ;
			auxr++ ;
 
			for(int i = auxl ; i >= intervalo[auxl].ff ; i--)
			{
				auxl = min(auxl, intervalo[i].ff ) ;
				mxl = max(mxl, intervalo[i].ss ) ;
			}
 
			for(int i = auxr ; i <= intervalo[auxr].ss ; i++ )
			{
				auxr = max(auxr, intervalo[i].ss ) ;
				mnr = min(mnr, intervalo[i].ff ) ;
			}
 
			if(mnr < lmin || mxl > rmax ) 
			{
				lmin = mnr ;
				rmax = mxl ;
				ans += cost ;
				ok = true ;
				break ;
			}
 
		}
 
		if(!ok) break ;
 
	}
 
	while( l > L )
	{
		ans += 2LL ;
		l-- ;
		for(int i = l ; i >= intervalo[l].ff ; i-- )
			l = min(l, intervalo[i].ff ) ;
	}
	while(r < R)
	{
		ans += 2LL ;
		r++ ;
		for(int i = r ; i <= intervalo[r].ss ; i++ )
			r = max(r, intervalo[i].ss ) ;
	}
 
	return ans ;
}
