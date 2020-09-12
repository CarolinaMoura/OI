/*
  CEOI 2019 - Magic Tree
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

const int MAXN = 1e5+10 ;

using namespace std ;

int N , M , K ;
int dia[MAXN] , sub[MAXN] ;
vector<int> adj[MAXN] ;
ll W[MAXN] ;
map<int,ll> *mp[MAXN] ;

void dfs(int x)
{

    sub[x] = 1 ;
    int bc = -1 ;

    for(auto e : adj[x])
    {
        if( e < x ) continue ;
        dfs(e) ;
        sub[x] += sub[e] ;
        if( bc == -1 || sub[e] > sub[bc] ) bc = e ;
    }

    if(bc == -1)
    {
        mp[x] = new map<int,ll> ;
        (*mp[x]).insert( mk( dia[x] , W[x] ) ) ;
        return ;
    }
    else mp[x] = mp[bc] ;

    for(auto e : adj[x] )
    {
        if( e < x || e == bc ) continue ;

        for( auto it = (*mp[e]).begin() ; it != (*mp[e]).end() ; it++ )
            (*mp[x])[it->ff] += it->ss ;

    }

    if(dia[x] == 0) return ;

    (*mp[x])[dia[x]] += W[x] ;
    auto it = (*mp[x]).find(dia[x]) ;
    it++ ;

    vector<int> toDelete ;
    ll cnt = 0LL ;

    while( it != (*mp[x]).end() && cnt + it->ss <= W[x] )
    {
        toDelete.pb( it->ff ) ;
        cnt += it->ss ;
        it++ ;
    }

    if(it != (*mp[x]).end() )
        (*mp[x])[it->ff] += cnt - W[x] ;

    for(auto e : toDelete ) (*mp[x]).erase( (*mp[x]).find(e) ) ;

   /* printf("Mp de %d -> " , x ) ;
    for(auto e : (*mp[x])) printf("(%d,%lld) ", e.ff, e.ss ) ;
    printf("\n") ; */

}

int main()
{
    scanf("%d%d%d", &N , &M , &K ) ;
    for(int i = 2 , x ; i <= N ; i++ )
    {
        scanf("%d", &x ) ;
        adj[x].pb(i) ;
    }
    for(int i = 1 , x , y ; i <= M ; i++ )
    {
        ll z ;

        scanf("%d%d%lld", &x, &y, &z ) ;

        dia[x] = y ;
        W[x] = z ;
    }

    dfs(1) ;

    ll cnt = 0LL ;
    for(auto e : (*mp[1])) cnt += e.ss ;

    printf("%lld\n" , cnt ) ;
}
