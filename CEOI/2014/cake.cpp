#include <bits/stdc++.h>
 
#define sz(x) (int)(x.size())
#define ff first
#define ss second
#define pb push_back
#define ll long long
#define mk make_pair
#define all(x) x.begin(),x.end()
#define pii pair<int,int:
#define debug printf 
 
const int MAXN = 25e4 +10 ;
 
using namespace std ;
 
struct Seg
{
 
	int mx[MAXN*4] ;
	int a[MAXN] ;
 
	int m(int l, int r ) { return (l+r)>>1 ; }
 
	void upd( int pos, int l, int r, int k, int val )
	{
 
		if(l == r) 
		{
			mx[pos] = l ;
			a[l] = val ;
			return ;
		}
 
		if( k <= m(l,r) ) upd(pos<<1 , l, m(l,r) , k , val ) ;
		else upd(pos<<1|1 , m(l,r)+1, r, k, val ) ;
 
		mx[pos] = ( a[ mx[pos<<1] ] > a[ mx[pos<<1|1] ] ) ? mx[pos<<1] : mx[pos<<1|1] ;
 
	}
 
	int getBiggest(int pos, int l, int r, int beg, int en )
	{
 
		if( l > en || r < beg ) return 0 ;
		if( l >= beg && r <= en ) return mx[pos] ;
 
		int al = getBiggest(pos<<1 , l, m(l,r) , beg, en ) ;
		int ar = getBiggest(pos<<1|1 , m(l,r)+1, r, beg, en ) ;
 
		return a[al] > a[ar] ? al : ar ;
 
	}
 
	int getLeftmost(int pos, int l , int r, int k)
	{
 
		if(l == r) return l ;
 
		if( a[mx[pos<<1]] > k ) return getLeftmost(pos<<1 , l, m(l,r) ,k ) ;
		return getLeftmost(pos<<1|1 , m(l,r)+1, r , k ) ;
 
	}
 
	int getRightmost(int pos, int l, int r , int k )
	{
 
		if( l == r) return l ;
 
		if( a[ mx[pos<<1|1] ] > k )
			return getRightmost(pos<<1|1 , m(l,r)+1, r,  k ) ;
		return getRightmost(pos<<1 , l , m(l,r), k ) ;
 
	}
 
	void print(int pos, int l, int r)
	{
		if( l != r )
		{
			print(pos<<1 , l,m(l,r)) ;
			print(pos<<1|1,m(l,r)+1, r) ;
		}
		else debug("Posicao %d -> %d\n", l, a[l] ); 
	}
 
} seg , segRight, segLeft ;
 
int N , Q , firstPiece ;
int A[MAXN] ;
int firstTen[15] ;
 
int main()
{
 
	scanf("%d%d", &N, &firstPiece ) ;
	for(int i = 1 ; i <= N ; i++ ) scanf("%d", &A[i]) ;
 
	for(int i = 1 ; i <= N ; i++ ) seg.upd(1,1,N,  i, A[i] ) ;
 
	vector<int> vec(N) ; iota(all(vec),1) ;
	sort(all(vec) , [&](int a, int b){ return A[a] > A[b] ; }) ;
 
	for(int i = 0 ; i < min(10,N) ; i++ )
		firstTen[i+1] = vec[i] ;
 	
 	for(int i = 1 ; i < firstPiece ; i++ ) segLeft.upd(1,1,N, i, A[i]) ;
 	for(int i = firstPiece+1 ; i <= N ; i++  ) segRight.upd(1,1,N, i, A[i]) ;

	scanf("%d", &Q ) ;
	while(Q--)
	{
 
		char c ;
		scanf(" %c", &c ) ;
 
		if( c == 'F' )
		{
			int x , eatenCake = 0 ;
			scanf("%d", &x ) ;
 
			if( x < firstPiece )
			{
 
				eatenCake += firstPiece - x ;
 
				x = seg.getBiggest(1,1,N, x, firstPiece-1) ;
				int y = segRight.getLeftmost(1,1,N,seg.a[x]  ) ;
 
				if( seg.a[y] < seg.a[x] ) y = N+1 ;
 
				eatenCake += y - firstPiece - 1 ;
 
			}
			else if( x > firstPiece )
			{
 
				eatenCake += x-firstPiece;
 
				x = seg.getBiggest(1,1,N, firstPiece+1 , x ) ;
				int y = segLeft.getRightmost( 1 , 1 , N, seg.a[x] ) ;
 
				if(seg.a[y] < seg.a[x]) y = 0 ;
 
				eatenCake += firstPiece-y-1 ;
 
			}
 
			printf("%d\n" , eatenCake ) ;
 
		}
 
		if( c == 'E' )
		{
 
			int piece, newPos ;
 
			scanf("%d %d", &piece, &newPos ) ;
 
			if(firstTen[newPos] == piece ) continue ;
 
			int newVal = seg.a[ firstTen[newPos] ] + 1 ;
			
			for(int i = 1 ; i < newPos ; i++ )
			{
				seg.upd(1,1,N, firstTen[i], seg.a[ firstTen[i] ]+1  ) ;

				if( firstTen[i] < firstPiece ) segLeft.upd(1,1,N, firstTen[i], seg.a[ firstTen[i] ] ) ;
				else if( firstTen[i] > firstPiece ) segRight.upd(1,1,N, firstTen[i], seg.a[ firstTen[i] ] ) ;

			}
 
			int idx = min(N,10) ;
 
			for(int i = 1 ; i <= min(N, 10) ; i++ )
				if( firstTen[i] == piece ) idx = i ;
 
			for(int i = idx; i > newPos ; i-- )
				firstTen[i] = firstTen[i-1] ;
 
			firstTen[newPos] = piece ;
			seg.upd( 1,1,N, piece, newVal ) ;

			if( piece < firstPiece ) 
				segLeft.upd(1,1,N, piece, seg.a[piece] ) ;

 			else if( piece > firstPiece )
 				segRight.upd(1,1,N, piece, seg.a[piece ]) ;
 
		}
 
	} 
 
}
