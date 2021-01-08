#include <bits/stdc++.h>

#define ll long long
#define all(x) x.begin(),x.end()
#define sz(x) x.size()

const int MAXN = 1e6+10 ;
const int MOD = 1e9+7 ;

using namespace std ;

char c ;
void read(int &num)
{
	num = 0 ;
	for( c = getchar() ; ( c > 47 && c < 58 ) ; c = getchar() )
		num = num*10 + c-48 ;
}

int N , Q ;
ll fib[MAXN] , invFib[MAXN] ;
int isBlack[MAXN][2] ;

ll fastExpo( ll num , int expo )
{
	if( expo == 0 ) return 1LL ;

	ll aux = fastExpo( num , expo>>1 ) ;
	aux = (aux * aux ) % MOD ;

	if( expo&1 ) aux = (aux * num ) % MOD ;

	return aux ;
}

struct Seg
{

	struct Node
	{
		int beg, en , qttTiles ;
		int lefTile, rigTile ;
		ll spareFirst, regular ;

		void print()
		{
			printf("Beg = %d, en = %d\n", beg, en ) ;
			printf("lefTile = %d, rigTile = %d\n", lefTile, rigTile ) ;
			printf("regular = %lld, spareFirst = %lld\n", regular, spareFirst ) ;
		}

	} tree[MAXN*4] ;

	int m(int l, int r ) { return (l+r)>>1 ; }

	void build(int pos, int l, int r )
	{
		tree[pos].beg = l ;
		tree[pos].en = r ;
		tree[pos].lefTile = tree[pos].rigTile = -1 ;
		tree[pos].spareFirst = tree[pos].regular = fib[r-l+1] ;				

		if( l == r ) return ;

		build(pos<<1, l , m(l,r) ) ;
		build(pos<<1|1, m(l,r)+1, r ) ;

	}

	void merge( Node &res, Node &lef, Node &rig )
	{

		res.qttTiles = lef.qttTiles + rig.qttTiles ;
		res.beg = lef.beg ;
		res.en = rig.en ;
		res.lefTile = ( lef.lefTile == -1 ) ? rig.lefTile : lef.lefTile ;
		res.rigTile = ( rig.rigTile == -1 ) ? lef.rigTile : rig.rigTile ;

		bool ok = true ;

		if( rig.lefTile != -1 && lef.rigTile != -1 )
		{
			int lefRow = ( isBlack[lef.rigTile][0] ) ? 0 : 1 ;
			int rigRow = ( isBlack[rig.lefTile][0] ) ? 0 : 1 ;

			if( isBlack[lef.rigTile][!lefRow] || isBlack[rig.lefTile][!rigRow] || ( (lefRow+lef.rigTile)&1) == ( (rigRow+rig.lefTile)&1 ) ) 
				ok = false ;
		}


		//Calculating regular answer (which means no sparing the first one)
		int fakeRig = ( lef.qttTiles == 0 ) ? (res.beg-1) : lef.rigTile ;
		int fakeLef = ( rig.qttTiles == 0 ) ? (res.en+1) : rig.lefTile ;

		res.regular = ( lef.regular * invFib[ lef.en - fakeRig ] ) % MOD ;
		res.regular = (res.regular * invFib[ fakeLef - rig.beg] ) % MOD ;

		if( lef.qttTiles&1 ) 
		{
			if(ok)
			{
				if( rig.qttTiles ) ( res.regular *= rig.spareFirst ) %= MOD ;
				else 
				{
					( res.regular *= fib[ res.en - lef.rigTile ] ) %= MOD ;
					( res.regular *= rig.regular ) %= MOD ;
				}
			}
			else res.regular = 0 ;
		}
		else 
		{
			( res.regular  *= rig.regular ) %= MOD ;
			( res.regular *= fib[ fakeLef - fakeRig - 1 ] ) %= MOD ;			
		}

		//Calculating the sparing the first one
		if( lef.qttTiles == 0 )
		{
			res.spareFirst = ( invFib[ fakeLef - rig.beg ] * rig.spareFirst ) % MOD ;
			(res.spareFirst *= fib[ fakeLef - res.beg ] ) %= MOD ;
		}
		else
		{
			res.spareFirst = ( lef.spareFirst * invFib[ lef.en - lef.rigTile ] ) % MOD ;
			( res.spareFirst *= invFib[ fakeLef - rig.beg ] ) %= MOD ;


			if( lef.qttTiles&1 )	
			{

				if( rig.qttTiles) 
				{
					( res.spareFirst *= rig.regular ) %= MOD ;
					( res.spareFirst *= fib[fakeLef - fakeRig - 1 ] ) %= MOD ;
				}									
				else 
				{
					( res.spareFirst *= fib[ res.en - lef.rigTile ] ) %= MOD ;
					( res.spareFirst *= fib[ rig.en - rig.beg +1 ] ) %= MOD ;
				}
				
			}
			else 
			{
				if( ok  ) 
				{
					if( rig.qttTiles ) ( res.spareFirst *= rig.spareFirst ) %= MOD ;
					else 
					{
						( res.spareFirst *= fib[res.en-rig.beg+1] ) %= MOD ;
						( res.spareFirst *= fib[res.en - fakeRig ]) %= MOD ;
					}
				}
				else res.spareFirst = 0 ;
			}
		}
	}

	void upd(int pos, int l, int r, int col )
	{
		if( l == r )
		{
			if( isBlack[col][0]|isBlack[col][1] )
				tree[pos].lefTile= tree[pos].rigTile = col ;
			else tree[pos].lefTile= tree[pos].rigTile = -1 ;
			
			tree[pos].spareFirst = !(isBlack[col][0]&isBlack[col][1]) ;

			tree[pos].qttTiles = isBlack[col][0] + isBlack[col][1] ;

			return ;

		}

		if( col <= m(l,r) ) upd(pos<<1 , l , m(l,r) , col ) ;
		else upd(pos<<1|1, m(l,r)+1, r, col ) ;

		merge(tree[pos] , tree[pos<<1] , tree[pos<<1|1] ) ;

	}

	void qry(int pos, int l, int r, Node &ans, int beg, int en )
	{
		if( l > en || r < beg ) return ;
		if( l >= beg && r <= en ) return (void)( ans = tree[pos] ) ;

		if( m(l,r) < beg ) return (void)( qry(pos<<1|1, m(l,r)+1, r, ans, beg, en ) ) ;
		if( m(l,r)+1 > en ) return (void)( qry(pos<<1 , l, m(l,r) , ans ,beg, en ) ) ;

		Node lef, rig ;

		qry( pos<<1 , l , m(l,r) , lef, beg, en ) ;
		qry(pos<<1|1, m(l,r)+1, r, rig , beg, en ) ;

		merge(ans, lef, rig ) ;

	}

	void print(int pos, int l, int r )
	{

		printf("Printing info on node [%d;%d]\n", l, r) ;
		tree[pos].print() ;

		if( l == r ) return ;

		print(pos<<1 , l , m(l,r) ) ;
		print(pos<<1|1, m(l,r)+1, r) ;

	}

} seg ;

int main()
{

	read(N) ;
	read(Q) ;

	fib[0] = fib[1] = 1LL ;
	invFib[0] = invFib[1] = 1LL ;

	for(int i = 1 ; i <= N ; i++ )
	{
		fib[i] = fib[i-1] + fib[i-2] ;
		if( fib[i] >= MOD ) fib[i] -= MOD ;

		invFib[i] = fastExpo( fib[i] , MOD-2 ) ;
	}

	seg.build(1,1,N) ;

	for(int i = 1 , t , a , b ; i <= Q ;i++ )
	{
		read(t) ;
		read(a) ;
		read(b) ;

		if( t == 1 )
		{
			isBlack[b][a-1] = !isBlack[b][a-1] ;			
			seg.upd(1,1,N, b) ;
		}
		else 
		{
			seg.qry( 1 , 1 , N, seg.tree[0] , a , b ) ;
			if( seg.tree[0].qttTiles&1 ) seg.tree[0].regular = 0 ;
			printf("%lld\n", seg.tree[0].regular ) ;					
		}
	}	
//	seg.print(1,1,N) ;
}
