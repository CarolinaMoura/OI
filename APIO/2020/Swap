/*
  APIO 2020 - Swapping Cities (Swap)
*/

#include <bits/stdc++.h>
#include "swap.h"

#define debug printf
#define all(x) x.begin(),x.end()
#define pii pair<int,int>
#define ff first
#define ss second
#define pb push_back
#define mk make_pair
#define sz(x) (int)(x.size())

const int MAXN = 1e5+10 ;
const int LOG = 20 ;

using namespace std ;

int pai[MAXN] , val[MAXN] , pai2[MAXN] , lvl[MAXN] ;
int dp[LOG][MAXN] , tab[LOG][MAXN] ,ehPonta[MAXN] ;
bool naoEhLinha[MAXN] ;
vector<pii> adj[MAXN] ;

void dfs(int x, int dad = -1 )
{

    for(auto e : adj[x])
    {
        if(e.ff == dad ) continue ;

        dp[0][e.ff] = x ;
        tab[0][e.ff] = e.ss ;
        lvl[e.ff] = lvl[x] + 1 ;

        dfs(e.ff, x) ;

    }

}

int find2(int x)
{
    if(x == pai2[x]) return x ;
    return pai2[x] = find2(pai2[x]) ;
}
bool join2(int x, int y)
{
    x=find2(x) ;
    y =find2(y) ;
    if(x == y) return false ;

    if(rand()%2) swap(x,y);

    pai2[x] = y ;

    return true ;
}

int find(int x)
{
    if(x == pai[x]) return x ;
    return pai[x] = find(pai[x]) ;
}

void join(int x, int y)
{
    x = find(x) ;
    y = find(y) ;

    if(x == y) return ;

    if(rand() % 2)swap(x,y) ;

    pai[x] = y;

}

void init(int n , int m , vector<int> u , vector<int> v, vector<int>w )
{

    for(int i = 0 ; i < n ; i++ )
    {
        pai[i] = i ;
        ehPonta[i] = 2 ;
    }

    vector<int> idx(m) ;
    iota(all(idx) , 0 ) ;

    sort(all(idx) , [&](int i, int j) { return w[i] < w[j] ; } ) ;

    for(int i : idx )
    {

        int a = u[i] ;
        int b = v[i] ;
        int c = w[i] ;

        int aa = find(a) ;
        int bb = find(b) ;

        if( !naoEhLinha[aa] && !naoEhLinha[bb] )
        {

            join(a,b) ;
            val[ find(a) ] = c ;

            if( !ehPonta[a] || !ehPonta[b] || aa == bb ) naoEhLinha[find(a)] = true ;
            ehPonta[a]-- ;
            ehPonta[b]-- ;

        }
        else
        {

            if( naoEhLinha[aa] && !naoEhLinha[bb] )
            {
                naoEhLinha[bb] = true ;
                val[bb] = c ;

            }
            else if( !naoEhLinha[aa] && naoEhLinha[bb] )
            {
                naoEhLinha[aa] = true ;
                val[aa] = c ;
            }
        }
    }

    vector<int> vec ;
    for(int i = 0 ; i < n ; i++ )
        if( i== find(i) ) vec.push_back(i) ;

  //  for(int i = 0 ; i < n ; i++ )debug("Minha comp %d %d\n" , find(i), val[ find(i) ]) ;

    for(int i = 0 ; i < n ; i++ ) pai2[i] = i ;

    for(int i : idx )
    {
        int a = u[i];
        int b = v[i] ;

        a = find(a);
        b = find(b) ;

        if(join2(a,b))
        {
            adj[ a ].pb( mk(b , w[i]) ) ;
            adj[ b ].pb( mk(a , w[i]) ) ;
         //   debug("Add %d %d\n" , a , b ) ;
        }

    }

    if(sz(vec) == 0) return ;

    memset(dp, -1, sizeof dp) ;

    dfs(vec[0] , -1 ) ;

    for(int i = 1 ; i < LOG ; i++ )
        for(int j = 0 ; j < n ; j++ )
            if( dp[i-1][j] != -1 )
            {
                dp[i][j] = dp[i-1][ dp[i-1][j] ] ;
                tab[i][j] = max(tab[i-1][ dp[i-1][j] ] , tab[i-1][j] ) ;
            }

}

int getMinimumFuelCapacity(int X, int Y) {

    X = find(X) ;
    Y = find(Y) ;

    if( !naoEhLinha[X] || !naoEhLinha[Y] ) return -1 ;

    if( X == Y ) return val[X] ;

    int ans = -1 ;

    if( lvl[X] < lvl[Y] ) swap(X,Y) ;

    for(int i = LOG ; i >= 0 ; i-- )
        if( lvl[X] - (1<<i) >= lvl[Y] )
        {
            ans = max(ans, tab[i][X]) ;
            X = dp[i][X] ;
        }

    if(X == Y) return ans ;

    for(int i = LOG ; i >= 0 ; i-- )
        if( dp[i][X] != -1 && dp[i][X] != dp[i][Y] )
    {
        ans = max(ans, max(tab[i][X] , tab[i][Y]) ) ;
        X = dp[i][X] ;
        Y = dp[i][Y] ;
    }

    return max( ans , max(tab[0][X],tab[0][Y]) ) ;

}

