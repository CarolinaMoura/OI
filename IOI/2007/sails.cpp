#include <bits/stdc++.h>

#define mkt make_tuple
#define debug
#define all(x) x.begin(),x.end()
#define lp(i,a,b) for(int i = a ; i< b ; i++)
#define ss second
#define ff first
#define ll long long
#define pb push_back
#define pii pair<int,int>
#define mk make_pair

const int MAXN = 1e5+10 ;
const int MAXH = 1e5+5 ;

using namespace std ;

struct Seg
{

    struct Node
    {
        int mx , mn , lz ;

        Node() { mx = mn = lz = 0 ; }

    };

    Node tree[MAXN*4] ;

    int lef(int x) { return x<<1 ; }
    int rig(int x) { return (x<<1)|1 ; }
    int m(int l, int r) { return (l+r)>>1 ; }

    inline void refresh(int pos, int l, int r)
    {

        tree[pos].mn += tree[pos].lz ;
        tree[pos].mx += tree[pos].lz ;

        if( l == r ) return (void)( tree[pos].lz = 0 ) ;

        tree[pos<<1].lz += tree[pos].lz ;
        tree[ (pos<<1)|1 ].lz += tree[pos].lz ;

        tree[pos].lz = 0 ;

    }


    inline void merge(int pos)
    {

        tree[pos].mn = min( tree[pos<<1].mn , tree[ (pos<<1)|1 ].mn ) ;
        tree[pos].mx = max( tree[pos<<1].mx , tree[ (pos<<1)|1 ].mx ) ;

    }

    inline void get_both(int pos, int l, int r)
    {
        refresh( lef(pos),l,m(l,r) ) ;
        refresh( rig(pos),m(l,r)+1,r );
        merge(pos) ;
    }

    void upd(int pos, int l, int r, int beg, int en )
    {

        refresh(pos,l,r) ;
        if( l > en || r < beg ) return ;
        if( l >= beg && r <= en )
        {
            tree[pos].lz ++ ;
            refresh(pos,l,r) ;
            return ;
        }

        upd( lef(pos) , l , m(l,r) , beg, en ) ;
        upd( rig(pos) , m(l,r)+1, r, beg, en ) ;
        merge(pos) ;

    }

    int qry(int pos, int l, int r, int idx)
    {
        refresh(pos,l,r) ;
        if( l == r ) return tree[pos].mx ;

        if( idx <= m(l,r) ) return qry( lef(pos) , l , m(l,r) , idx  );
        return qry( rig(pos) , m(l,r)+1, r, idx ) ;

    }


    int ultimo_igual( int pos, int l, int r, int v )
    {
        refresh(pos,l,r) ;

        if( l == r ) return l ;

        get_both(pos, l,r) ;

        if( tree[ rig(pos) ].mx < v ) return ultimo_igual(lef(pos),l,m(l,r),v) ;
        return ultimo_igual( rig(pos) , m(l,r)+1,r, v ) ;

    }

    int primeiro_igual(int pos, int l, int r, int v)
    {

        refresh(pos,l,r) ;
        if( l == r ) return l ;

        get_both(pos, l,r) ;

        if( tree[ lef(pos) ].mn > v ) return primeiro_igual( rig(pos) , m(l,r)+1, r, v ) ;
        return primeiro_igual( lef(pos) , l , m(l,r) , v ) ;

    }

    void print(int pos, int l , int r)
    {

        refresh(pos,l,r) ;
        if( l == r ) return (void)( printf("%d -> %d %d\n", l,  tree[pos].mn , tree[pos].mx) ) ;

        print( lef(pos) , l , m(l,r) ) ;
        print( rig(pos) , m(l,r)+1, r ) ;

    }

};


int N ;
pii v[MAXN] ;
Seg seg ;

int main()
{

    scanf("%d", &N ) ;
    lp(i,1,N+1) scanf("%d%d", &v[i].ff, &v[i].ss ) ;
    sort(v+1, v+1+N ) ;


    lp(i,1,N+1)
    {

        int l = v[i].ff - v[i].ss + 1 , r = v[i].ff ;

        int meu_val = seg.qry( 1 , 1 , MAXH , l ) ;
        int lef = seg.primeiro_igual(1,1,MAXH , meu_val ) ;
        int rig = seg.ultimo_igual( 1 , 1 , MAXH , meu_val ) ;

        if( l == lef ) seg.upd( 1 , 1 , MAXH , l , r ) ;
        else
        {
            if( rig >= r ) seg.upd( 1 , 1 , MAXH , lef , lef + v[i].ss - 1 ) ;
            else
            {
                int restinho = rig - l + 1 ;

                seg.upd( 1 , 1 , MAXH , lef , lef+restinho - 1) ;
                seg.upd( 1 , 1 , MAXH , rig+1, r ) ;
            }
        }


    }

    ll resp = 0LL ;

    lp(i,1, v[N].ff + 1 )
    {

        ll tot = 1LL*seg.qry( 1 , 1 , MAXH , i ) ;
        resp += (1LL*(tot-1)*tot)/2LL ;

    }

    printf("%lld\n" , resp ) ;

}
