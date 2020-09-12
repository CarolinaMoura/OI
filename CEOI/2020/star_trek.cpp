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
const ll MOD = 1e9+7 ;

using namespace std ;

struct Matrix
{
    ll a[2][2] ;

    void fill(ll x = 0 , ll y = 0 , ll z = 0 , ll w = 0)
    {
        a[0][0]=x , a[0][1]=y , a[1][0]=z, a[1][1]=w ;
    }

    Matrix operator * (Matrix other) const
    {
        Matrix aux ;
        aux.fill(0,0,0,0) ;

        for(int i = 0 ; i < 2; i++ )
            for(int j = 0 ; j < 2 ; j++ )
                for(int g = 0 ; g < 2 ;g++ ) aux.a[i][j] = ( aux.a[i][j] + (a[i][g] * other.a[g][j] )%MOD ) % MOD ;

        return aux ;
    }

    void print()
    {
        for(int i = 0 ; i < 2 ; i++ ) printf("%lld %lld\n" , a[i][0] , a[i][1]) ;
    }

};

int N ;
int dpMudo[MAXN] , meuVal[MAXN] ;
bool dp[MAXN] , consagrado[MAXN] , vis[MAXN] ;
ll D , smv11, smv12, smv2 , Vit , Derr ;
vector<int> vec ;
vector<int> adj[MAXN] ;

void iniDfs(int x, int dad = -1 )
{

    dp[x] = true ;

    vector<int> zeroes ;
    dpMudo[x] = 0 ;

    for(auto e : adj[x] )
    {
        if(e == dad) continue ;

        iniDfs(e, x) ;

        dp[x] &= dp[e] ;
        dpMudo[x] += dpMudo[e] ;
        if(!dp[e]) zeroes.pb( e ) ;
    }

    dp[x] = !dp[x] ;

    dpMudo[x] += !dp[x] ;
    if( dp[x]  )
    {
        if(sz(zeroes) == 1)
            dpMudo[x] = dpMudo[ zeroes[0] ] ;
        else dpMudo[x] = 0 ;
    }

}

void spinDfs(int x )
{

    vis[x] = true ;

    vector<int> zeroes ;

    dp[x] = true ;
    dpMudo[x] = 0 ;
    int somaGeral = 0 ;

    for(auto e : adj[x] )
    {
        dp[x] &= dp[e] ;

        if(!dp[e]) zeroes.pb(e) ;

        somaGeral += dpMudo[e] ;
    }

    dp[x] = !dp[x] ;

    Vit += dp[x] ;
    Derr += !dp[x] ;

    if(dp[x] && sz(zeroes) == 1) dpMudo[x] = dpMudo[ zeroes[0] ] ;
    else if(!dp[x]) dpMudo[x] = somaGeral + 1 ;

    if(dp[x])
    {
        smv11 += (ll) N - dpMudo[x] ;
        smv12 += (ll) dpMudo[x] ;
    }
    else smv2 += (ll)dpMudo[x] ;

    if(smv11 >= MOD) smv11 -= MOD ;
    if(smv12 >= MOD) smv12 -= MOD ;
    if(smv2 >= MOD ) smv2 -= MOD ;

   /* debug("A dp de geral quando %d eh raiz:\n" , x ) ;
    lp(i,1,N+1) debug("%d %d\n" , dp[i] , dpMudo[i]) ;
    debug("\n") ; */

    int saveDpMudo = dpMudo[x] ;
    int saveDp = dp[x] ;

    for(int i = 0 ; i < sz(adj[x]) ; i++ )
    {

        int viz = adj[x][i] ;

        if( vis[viz] ) continue ;

        int childDpMudo = dpMudo[viz] ;
        int childDp = dp[viz] ;

        if(dp[x])
        {
            if(sz(zeroes) == 1 && dp[viz] == 0)
            {
                dpMudo[x] = somaGeral - dpMudo[viz] + 1 ;
                dp[x] = false ;
            }

            if(sz(zeroes) == 2 && dp[viz] == 0)
            {
                if(viz == zeroes[0]) swap(zeroes[0] , zeroes[1]) ;
                dpMudo[x] = dpMudo[ zeroes[0] ] ;
            }

        }
        else dpMudo[x] = somaGeral - dpMudo[viz] + 1 ;

        spinDfs(viz) ;

        dpMudo[viz] = childDpMudo ;
        dp[viz] = childDp ;
        dpMudo[x] = saveDpMudo ;
        dp[x] = saveDp ;

    }

}

Matrix expo(Matrix x, ll n )
{
    if(n == 0)
    {
        Matrix aux ;
        aux.fill(1,1,1,1) ;
        return aux ;
    }
    if(n == 1) return x ;

    Matrix aux = expo(x, n>>1LL ) ;
    aux = aux*aux ;

    if(n&1) aux = aux * x ;

    return aux ;
}

int main()
{
    scanf("%d %lld", &N , &D );
    for(int i = 0 , u ,v ; i < N-1 ; i++ )
    {
        scanf("%d%d", &u, &v ) ;
        adj[u].pb(v) ;
        adj[v].pb(u) ;
    }

    iniDfs(1) ;
    spinDfs(1) ;

    debug("Victories = %d and defeats = %d\nsmv11 = %lld and smv12 = %lld and smv2 = %lld\n" , Vit, Derr , smv11, smv12, smv2) ;

    Matrix base ;
    base.fill( Vit, Derr ,0, 0 ) ;

    Matrix T ;

    ll a11 = (smv11 + smv12 ) % MOD ;
    ll a12 = ( (ll)N * (ll)N ) % MOD ;
    ll a22 = a12 ;
    ll a21 = ( smv2 + smv11 ) % MOD ;

    a12 = (a12 - a11 + MOD) % MOD ;
    a22 = (a22 - a21 + MOD) % MOD ;

    T.fill(a11, a12, a21, a22) ;

    T = expo(T, D-1) ;

    base = base * T ;

    if(D != 1)
    {
        Vit = base.a[0][0] ;
        Derr = base.a[0][1] ;
    }


    ll captain = (Vit + Derr) * ((ll)N-dpMudo[1] ) ;
    captain %= MOD ;
    captain = (captain + (Vit * dpMudo[1] )%MOD ) % MOD ;

    if(!dp[1]) captain = ( Derr * dpMudo[1] ) % MOD ;

    printf("%lld\n" , captain ) ;

}
