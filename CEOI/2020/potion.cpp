/*
  CEOI 2020 - The Potion of Great Power
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
#define debug
#define all(x) x.begin(),x.end()
#define tiii tuple<int,int,int>

const int MAXN = 1e5+10 ;
const int MAXU = 2e5+10 ;

using namespace std ;

struct Seg
{

    vector<pii> seg[MAXU*4] ;
    vector<int> q ;

    int m(int l, int r) { return (l+r)>>1 ; }

    void upd(int pos, int l,int r, int beg , int en, int u , int v)
    {

        if( l > en || r < beg ) return ;
        if( l >= beg && r <= en )
        {
            seg[pos].pb( mk(u,v) ) ;
            return ;
        }

        upd(pos<<1 , l, m(l,r) , beg, en ,u , v ) ;
        upd(pos<<1|1 , m(l,r)+1, r, beg, en ,u , v ) ;

    }

    void qry(int pos, int a, int b, int d , int idx )
    {

        if( a > d || b < d ) return ;

        int l = 0 , r = sz(seg[pos]) -1 , mid , L = sz(seg[pos]) ;

        while( l <= r )
        {
            mid = (l+r)>>1 ;

            if( seg[pos][mid].ff >= idx ) { L = mid ; r = mid - 1 ; }
            else l = mid + 1 ;

        }

        l = 0 , r = sz(seg[pos]) - 1 ;
        int R = -1 ;
        while(l <= r)
        {
            mid = (l+r)>>1 ;

            if(seg[pos][mid].ff <= idx ) { R = mid ; l = mid + 1 ; }
            else r = mid - 1 ;

        }

        for(int i = L ; i <= R ; i++ ) q.pb( seg[pos][i].ss ) ;

        if(a == b) return ;

        if(d <= m(a,b)) qry(pos<<1 , a, m(a,b) , d , idx ) ;
        else qry(pos<<1|1 , m(a,b)+1, b, d , idx ) ;

    }

} seg ;

int N , D , U , Q ;
int H[MAXN] ;
map< pair<int,int > , int > mp ;
vector< tuple<int,int,int,int> > edge ;

inline void giveAns(int x) { printf("%d\n" , x) ; fflush(stdout) ; }

int main()
{

    scanf("%d%d%d%d", &N , &D, &U , &Q ) ;
    lp(i,1,N+1) scanf("%d", &H[i]) ;

    for(int i = 1  , u , v ; i <= U ; i++ )
    {
        scanf("%d%d", &u, &v ) ;
        u++ ; v++ ;

        if(u > v) swap(u,v) ;

        if( mp.find( mk(u,v) ) == mp.end() ) mp[ mk(u,v) ] = i ;
        else
        {
            edge.pb( mkt(u,v,mp[mk(u,v)] ,i-1) ) ;
            mp.erase( mp.find(mk(u,v)) ) ;
        }

    }

    for(auto e : mp ) edge.pb( mkt( e.ff.ff, e.ff.ss, e.ss , U ) ) ;

    int t = sz(edge) ;
    for(int i = 0 ; i < t ; i++ ) edge.pb( mkt( get<1>(edge[i]) , get<0>( edge[i] ) , get<2>(edge[i]) , get<3>(edge[i]) ) ) ;

    sort(all(edge)) ;

    for(auto &e : edge ) seg.upd( 1 , 1 , U , get<2>(e) , get<3>(e) , get<0>(e) , get<1>(e) ) ;

    for(int i = 1 , a , b , v ; i <= Q ; i++ )
    {
        scanf("%d%d%d", &a, &b, &v ) ;

        a++ , b++ ;

        vector<pii> aux ;
        seg.q.clear() ;
        seg.qry(1,1,U, v, a) ;

        for(auto e : seg.q ) aux.pb( mk( H[e] , 0 ) ) ;

        seg.q.clear() ;
        seg.qry(1,1,U, v, b ) ;
        for(auto e : seg.q ) aux.pb( mk(H[e] , 1) ) ;

        sort(all(aux)) ;

      //  for(auto e : aux)  debug("%d %d, " ,e.ff, e.ss ) ;
       // debug("\n") ;

        int ans = 1000000000 ;
        int mx[2] = {-1,-1} ;

        for(auto e : aux )
        {
            mx[e.ss] = e.ff ;
            if( mx[0] == -1 || mx[1] == -1 ) continue ;
            ans = min(ans, abs(mx[0] - mx[1])) ;
        }

        giveAns(ans) ;

    }

}
