/*
  APIO 2019 - Street Lamps (Street Lamps)
*/

#include <bits/stdc++.h>

#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimization ("unroll-loops")
#pragma GCC optimization ("O2")


#define lp(i,a,b) for(int i = a; i < b; i++)
#define pb push_back
#define sz(x) (int)(x.size())
#define all(x) x.begin(),x.end()
#define debug printf
#define tiii tuple<int,int,int>
#define mkt make_tuple
#define pii pair<int,int>
#define mk make_pair
#define ll long long
#define ff first
#define ss second

const int MAXN = 3e5+10 ;
const int MAX = 1e7+100 ;

using namespace std ;

vector<int> e , d , soma ;
int cnt ;

struct SegNode
{

    void upd(int &pos, int l , int r, int k, int toSum )
    {
        if(!pos) pos = cnt++ ;

        soma[pos] += toSum ;

        if(l == r) return;

        int aux , mid = (l+r)>>1 ;

        if( k <= mid ) upd( e[pos] , l , mid , k , toSum ) ;
        else upd(d[pos] , mid+1, r, k , toSum ) ;

    }

    int qry(int pos, int l, int r, int k)
    {
        if(!pos) return 0 ;
        if(l == r) return soma[pos] ;

        int mid = (l+r)>>1 ;

        if( k <= mid ) return qry(e[pos] , l , mid , k ) ;
        return soma[ e[pos] ] + qry( d[pos] , mid+1, r, k ) ;

    }

};

int N , Q ;
set<pii> intervalos ;
char str[MAXN] , q[MAXN] ;

SegNode tree[MAXN] ;

void upd(int pos, int l, int r, int toSum) {

    for(int i = pos ; i <= N ; i+=(i&-i))
    {
        tree[i].upd( i ,1,N+5, l , toSum) ;
        tree[i].upd( i , 1 , N+5 , r+1, -toSum ) ;
    }
}
int qry(int x , int y )
{
    int tot = 0 ;
    for(int i = x ; i > 0 ; i -= (i&-i)) tot += tree[i].qry( i ,1,N+5, y) ;

    return tot ;
}

int main()
{

    scanf("%d%d", &N , &Q ) ;
    scanf("%s", str ) ;

    str[N] = '0';
    N++;

    for(int i = 0 ; i < MAX ; i++ )
    {
        e.pb(0);
        d.pb(0);
        soma.pb(0) ;
    }
    cnt = N+1 ;

    for(int i = 0 ; i < N ; i++ )
    {

        int j = i ;
        while( j < N && str[j] == '1' ) j++ ;

        //O intervalo eh [i,j]
        intervalos.insert( mk(i+1,j+1) ) ;

        upd( i+1 , i+1, j+1, -1 ) ;
        upd(j+2, i+1, j+1, 1 ) ;

        i = j ;


    }

    for(int i = 1 ; i <= Q ; i++ )
    {
        scanf("%s", q ) ;

        if(q[0] == 'q')
        {

            int a , b , segQuery ;
            scanf("%d%d", &a, &b );

            segQuery = qry(a,b);

            auto it = intervalos.upper_bound( mk(a,N+5) ) ;
            it-- ;

            if( it->ss >= b ) segQuery += i+1 ;

            printf("%d\n" , segQuery ) ;

        }

        else
        {
            int lamp ;
            scanf("%d", &lamp ) ;

            auto meContem = intervalos.upper_bound(mk(lamp,N+5)) ;
            meContem--;

            if( str[lamp-1] == '0' )
            {

                pii toInsert=*meContem ;
                auto prox = meContem ; prox++ ;

                toInsert.ss = prox->ss ;
                intervalos.erase(prox) ;

                meContem = intervalos.upper_bound(mk(lamp,N+5)) ; meContem-- ;
                intervalos.erase(meContem) ;

                intervalos.insert( toInsert ) ;
                upd( toInsert.ff, lamp+1, toInsert.ss , -i-1 ) ;
                upd(lamp + 1 , lamp+1, toInsert.ss , i+1 ) ;

                str[lamp-1] = '1' ;

            }

            else
            {

                pii toInsert1 = mk(meContem->ff,lamp) ;
                pii toInsert2 = mk(lamp+1, meContem->ss ) ;

                upd(toInsert1.ff, toInsert2.ff, toInsert2.ss , i+1 ) ;
                upd( toInsert1.ss + 1 , toInsert2.ff, toInsert2.ss , -i-1 ) ;


                intervalos.erase( meContem ) ;
                intervalos.insert(toInsert1) ;
                intervalos.insert(toInsert2) ;

                str[lamp-1] = '0' ;

            }

        }

    }

}
