 
const int MAXN = 5e5+10 ;
 
using namespace std ;
 
int N ;
int V[MAXN*2] , S[MAXN*2] ;
int best[MAXN] , vec[MAXN*2] ;
 
struct Seg
{
	int tree[MAXN*2*4] ;
 
	int m(int l, int r) { return (l+r)>>1 ; }
 
	void upd(int pos, int l , int r , int id , int val )
	{
		if( l == r ) return (void)( tree[pos] = val ) ;
		if(id <= m(l,r)) upd(pos<<1 , l ,m(l,r) , id, val ) ;
		else upd(pos<<1|1 , m(l,r)+1, r, id, val ) ;
 
		tree[pos] = max(tree[pos<<1] , tree[pos<<1|1]) ;
	}
 
	int qry(int pos, int l, int r, int beg, int en )
	{
		if( l > en || r < beg ) return -1 ;
		if( l >= beg && r <= en ) return tree[pos] ;
		return max(qry(pos<<1 , l , m(l,r), beg, en) , qry(pos<<1|1 , m(l,r)+1, r, beg, en )) ;
 	}
 
} seg ;
 
int main()
{
	scanf("%d", &N ) ;
	for(int i = 0 ; i < N ; i++ ) scanf("%d", &V[i] ) , V[i+N] = V[i] ;
	S[0] = V[0] ;
	for(int i = 1 ; i < 2*N ; i++ ) S[i] += S[i-1]+V[i] ;
 
	int k = N>>1 ;
 
	for(int i = 0 ; i+k-1 < 2*N ; i++ ) 
	{
		vec[i] = S[i+k-1]-S[i]+V[i] ;
		seg.upd(1,0,2*N-1,i, vec[i]) ;
	}
 
	for(int i = 0 ; i < N ; i++ )
	{
		int r = i+N-k ;
		best[i] = S[N-1]-seg.qry(1,0,2*N-1, i+1, r ) ;
	}
 
	printf("%d\n" , *max_element(best, best+N)) ;
 
}
