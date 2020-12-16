#include <bits/stdc++.h>

#define all(x) x.begin(),x.end()
#define sz(x) (int)(x.size())

const int MAXN = 2e5+20 ;

using namespace std ;

int N , subtask ;
int color[MAXN] , nxt[MAXN], bef[MAXN] ;
set< tuple<int,int,int> > diagonals ;

void invalidTriangulation()
{
	printf("neispravna triangulacija\n") ;
	exit(0) ;
}

int main()
{
	scanf("%d %d", &subtask , &N ) ;
	for(int i = 0 ; i < N ; i++ ) 
	{
		char c ;

		scanf(" %c", &c ) ;

		color[i] = c-'1' ;
	
		nxt[i] = ( i == N-1 ) ? 0 : i+1 ;
		bef[ nxt[i] ] = i ;
	}	
	for(int i= 0 , u, v, c ; i < N-3 ; i++ )
	{
		scanf("%d %d %d", &u, &v, &c ) ;

		--u ; --v ; --c ;

		diagonals.insert( make_tuple(u,v,c) ) ;
		diagonals.insert( make_tuple(v,u,c) ) ;

	}

	queue<int> q ;

	auto test = [&](int i)
	{
		auto it = diagonals.upper_bound( make_tuple(bef[i], nxt[i], -1) )  ;
		if( it != diagonals.end() && get<0>(*it) == bef[i] && get<1>(*it) == nxt[i] ) q.push(i) ;
	} ;

	for(int i= 0 ; i < N ; i++ ) test(i) ;

	bool ok = true ;

	while(N > 4 )
	{
		int x = q.front() ; q.pop() ;

		auto it = diagonals.upper_bound( make_tuple(x, -1, -1) ) ;
		if(it != diagonals.end() && get<0>(*it) == x ) invalidTriangulation() ;

		it = diagonals.upper_bound( make_tuple(bef[x], nxt[x], -1) ) ;

		ok &= ( color[x] + color[ bef[x] ] + get<2>(*it) == 3 ) ;

		nxt[ bef[x] ] = nxt[x] ;
		color[ bef[x] ] = get<2>(*it) ;
		bef[ nxt[x] ] = bef[x] ;

		diagonals.erase(*it) ;
		diagonals.erase( diagonals.find( make_tuple(nxt[x] , bef[x] , color[ bef[x] ] ) ) ) ;

		test(bef[x] ) ;
		test(nxt[x] ) ;

		N-- ;

	}

	auto tp = *diagonals.begin() ;

	ok &= (color[get<0>(tp)] + color[ nxt[get<0>(tp) ] ] + get<2>(tp) == 3 )  ;
	ok &= (color[get<1>(tp)] + color[ nxt[get<1>(tp) ] ] + get<2>(tp) == 3 ) ;

	if(ok) printf("tocno\n") ;
	else printf("neispravno bojenje\n") ;

}
