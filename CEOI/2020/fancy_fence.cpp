/*
  CEOI 2020 - Fancy Fence
*/
#include <bits/stdc++.h>

#define sz(x) (int)x.size()
#define mkt make_tuple
#define lp(i,a,b) for(int i = a ; i < b ; i++ )
#define ff first
#define ss second
#define pb push_back
#define ll long long
#define mk make_pair
#define pii pair<int,int>
#define debug printf
#define all(x) x.begin(),x.end()
#define tiii tuple<int,int,int>

const int MAXN = 1e5+10 ;
const ll MOD = 1e9+7 ;

using namespace std ;

int N ;
ll ans , inv = 250000002 ;
ll H[MAXN] , W[MAXN] ;
int seg[MAXN*4] ;

int m(int l, int r) { return (l+r)>>1 ; }
void build(int pos, int l, int r )
{
    if(l == r) return (void)( seg[pos] = l ) ;

    build(pos<<1 , l, m(l,r)) ;
    build(pos<<1|1 , m(l,r)+1, r ) ;

    seg[pos] = H[ seg[pos<<1] ] < H[ seg[pos<<1|1] ] ? seg[pos<<1] : seg[pos<<1|1] ;

}

int qry(int pos, int l, int r, int beg, int en)
{

    if(l > en || r < beg) return 0 ;
    if( l >= beg && r <= en ) return seg[pos];

    int al = qry(pos<<1 , l, m(l,r) , beg, en ) ;
    int ar = qry(pos<<1|1 , m(l,r)+1, r, beg, en );

    return H[al] <= H[ar] ? al : ar ;

}

ll calc(ll w, ll h)
{
    ll prod = (w*(w+1) ) % MOD ;
    prod *= ( h * (h+1) ) % MOD ;
    prod %= MOD ;
    prod *= inv ;
    return prod % MOD ;
}

int main()
{

    H[0] = MOD ;

    scanf("%d", &N ) ;
    lp(i,1,N+1) scanf("%lld", &H[i] ) ;
    lp(i,1,N+1)
    {
        scanf("%lld", &W[i]) ;
        W[i] += W[i-1] ;
        if(W[i] >= MOD) W[i] -= MOD ;
    }

    build(1,1,N) ;

    vector<pii> fila ;
    fila.pb( mk(1,N) ) ;
    int ini = 0 ;

    while( ini < sz(fila) )
    {
        int L = fila[ini].ff ;
        int R = fila[ini].ss ;

        ini++ ;

        int idx = qry(1, 1 , N , L , R ) ;

        ll Y = H[idx] ;
        ll diffTotal = W[R] - W[L-1] ;
        ll diffEsq = W[idx-1] - W[L-1] ;
        ll diffDir = W[R] - W[idx] ;

        ans += calc(diffTotal, Y) ;
        if(ans >= MOD) ans -= MOD ;

        if( idx != L ) ans -= calc(diffEsq, Y) ;
        if(ans < 0) ans += MOD ;

        if(idx != R) ans -= calc(diffDir, Y) ;
        if(ans < 0) ans += MOD ;

        if( L != idx ) fila.pb( mk(L, idx-1) ) ;
        if(R != idx ) fila.pb( mk(idx+1, R) ) ;


    }

    printf("%lld\n" , ans ) ;

}

