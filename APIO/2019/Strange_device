/*
  APIO 2019 - Strange Device (Strange Device)
*/

#include <bits/stdc++.h>


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

using namespace std ;

int N ;
ll A , B , G , ans ;
vector< pair<ll,ll> > vectorInteiros , vectorParciais , intervalosInteiros ;
map< ll , vector< pair<ll,ll> > > miniLineSweep ;

bool pegueiInteiro(ll block)
{

    auto it = upper_bound( all(intervalosInteiros) , mk(block,G+5) ) ;

    if( it == intervalosInteiros.begin() ) return false ;
    it-- ;

    return (it->ff <= block && it->ss >= block) ;

}

int main()
{
    scanf("%d%lld%lld", &N , &A, &B ) ;

    G = __gcd(A,B+1);
    G = A/G ;

    const ll period = ( LLONG_MAX / B < G ) ? LLONG_MAX : B*G ;

    for(int i = 1 ; i <= N ; i++ )
    {
        ll L , R ;
        scanf("%lld %lld", &L , &R ) ;

        if(R - L + 1LL >= period )
        {
            printf("%lld\n" , period ) ;
            return 0 ;
        }

        ll actualL = ( (L+B)/B ) * B ;
        ll actualR = ( (R-B)/B ) * B + B-1 ;

        if(actualL - 1 >= L)
            vectorParciais.pb( mk(L, min(actualL-1, R) ) ) ;
        if(actualR+1 <= R)
            vectorParciais.pb( mk(max(L,actualR+1), R ) ) ;

        if( actualL > actualR ) continue ;

        actualL /= B ;
        actualR /= B ;

        actualL %= G ;
        actualR %= G ;

        if(actualL > actualR )
        {
            vectorInteiros.pb( mk(actualL, G-1) ) ;
            actualL = 0 ;
        }

        vectorInteiros.pb( mk(actualL, actualR) ) ;

    }

    if( sz(vectorInteiros) > 0 )
    {
        sort(all(vectorInteiros)) ;

        ll mn = vectorInteiros[0].ff ;
        ll mx = vectorInteiros[0].ss ;

        vectorInteiros.pb( mk(G+5, G+5) ) ;

        for(int i = 1 ; i < sz(vectorInteiros) ; i++ )
        {
            if( vectorInteiros[i].ff > mx )
            {

                intervalosInteiros.pb( mk(mn,mx) ) ;

                ans += (mx - mn + 1LL ) * B ;

                mn = vectorInteiros[i].ff ;
                mx = vectorInteiros[i].ss ;

            }
            else if( vectorInteiros[i].ss > mx ) mx = vectorInteiros[i].ss ;
        }

    }

    for(auto e : vectorParciais )
    {
        ll L = e.ff ;
        ll R = e.ss ;

        ll block = L/B ;
        block %= G ;

        L %= B ;
        R %= B ;

        miniLineSweep[ block ].pb( mk(L,R) ) ;

    }

    for(auto block : miniLineSweep )
    {

        if( pegueiInteiro(block.ff) ) continue ;

      //  debug("Estou vendo o modulo %d, e tenho nele:\n" , block.ff ) ;

        vector< pair<ll,ll> > &sweep = block.ss ;
        sort(all(sweep)) ;

      //  for(auto e :sweep ) debug("%lld %lld\n" ,e.ff, e.ss ) ;
      //  debug("\n") ;

        ll mn = sweep[0].ff ;
        ll mx = sweep[0].ss ;

        sweep.pb( mk(B+5, B+5) ) ;

        for(int i = 1 ;i  < sz(sweep) ; i++ )
        {

            if(sweep[i].ff > mx )
            {
                ans += mx - mn + 1LL ;
                mn = sweep[i].ff ;
                mx = sweep[i].ss ;
            }
            else if( mx < sweep[i].ss ) mx = sweep[i].ss ;

        }

    }

    printf("%lld\n" , ans ) ;

}
