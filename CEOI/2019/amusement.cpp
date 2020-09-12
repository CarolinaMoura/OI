/*
  CEOI 2019 - Amusement Park
*/

#include <bits/stdc++.h>

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

const int MAXN = 20 ;
const int MOD = 998244353 ;
const int MAXM = 500 ;
const int MAX = 524298 ;

using namespace std ;

int N , M , tam ;
int adj[MAXN] ;
ll resp ;
vector< pair<int,ll> > DP[MAX] ;
ll dp[MAX] ;

inline void give_ans(ll resp)
{
    resp = (resp * M) % MOD ;

    if( resp % 2 == 1 ) resp += MOD ;
    resp /= 2LL ;

    printf("%lld\n" , resp%MOD ) ;

    exit(0) ;
}

int main()
{
    scanf("%d%d", &N , &M ) ;
    for(int i = 0 , y , x ; i < M ; i++ )
    {
        scanf("%d%d", &y, &x );

        --y , --x ;

        adj[y] |= (1<<x) ;
        adj[x] |= (1<<y) ;

    }

    DP[ (1<<N)-1 ].pb( {(1<<N)-1 ,1LL } ) ;

    for(int i = (1<<N)-1 ; i >= 0 ; i-- )
    {

        for(auto e : DP[i] ) ( dp[e.ff] += e.ss ) %= MOD ;

        for(int j = i ; j >= 0 ; j = (j-1)&i )
        {
            if(j == 0)
            {
                if( i == 0 ) give_ans(dp[0]) ;
                break ;
            }
            if(dp[j] == 0) continue ;


            int z = __builtin_ctz(j) ;
            int jj = j^(1<<z) ;

            ( dp[jj] += dp[j] ) %= MOD ;

            jj |= ( adj[z]&i ) ;

            DP[ i^(1<<z) ].pb( {jj,dp[j]} ) ;

            dp[j] = 0LL ;
        }

        dp[0] = 0LL ;
        DP[i].clear() ; DP[i].shrink_to_fit() ;
    }

}
