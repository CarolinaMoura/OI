#include <bits/stdc++.h>

#define sz(x) (int)(x.size())
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

const int MAXN = 5e5+10 ;

using namespace std ;

int n , k ;
int dist[MAXN] , lvl[MAXN] , ancestor[MAXN] ;
vector<int> sheep ;
vector<int> adj[MAXN] ;
bool hasSheep[MAXN] ;
bool prot[MAXN] ;

void bfs()
{

    lp(i,1,n+1) dist[i] = n+5 ;

    vector<int> fila ;
    int ini = 0 ;

    for(auto e : sheep ) 
    {
        dist[e] = 0 ;
        fila.pb(e) ;
    }

    while(ini < sz(fila))
    {
        int x = fila[ini++] ;
        for(auto e : adj[x])
        {
            if(dist[e] <= dist[x]+1) continue ;
            dist[e] = dist[x]+1 ;
            fila.pb(e) ;
        }
    }
}

void dfs(int x, int father, int curMax ) 
{

    if(lvl[x]+dist[x] > lvl[curMax]+dist[curMax])
        curMax = x ;

    if( hasSheep[x] )
        ancestor[x] = curMax ;

    for(auto e : adj[x])
    {
        if(e == father) continue ;
        
        lvl[e] = lvl[x]+1 ;
        dfs(e,x,curMax) ;

    }
}

void dfsProtect(int x)
{
    prot[x] = true ;
    for(auto e :adj[x])
    {
        if(prot[e] || dist[e] != dist[x]-1) continue ;
        dfsProtect(e) ;
    }
}

int main()
{
    scanf("%d%d", &n, &k ) ;
    for(int i = 0 , a , b ; i <n-1 ; i++ )
    {
        scanf("%d%d", &a, &b ) ;

        adj[a].pb(b); 
        adj[b].pb(a) ;
    }

    sheep.resize(k) ;

    for(int i = 0 ; i < k ; i++ )
    {
        scanf("%d", &sheep[i]) ;
        hasSheep[ sheep[i] ] = true ;
    }

    bfs() ;
    dfs(1,-1, 1 ) ;

    sort(all(sheep), [&](int a, int b){return lvl[a] > lvl[b] ;}) ;

    vector<int> ans ;

    for(int s : sheep)
    {
        if(prot[s]) continue ;
        ans.push_back(ancestor[s]) ;
        dfsProtect( ancestor[s] ) ;
    }

    sort(all(ans)) ;
    printf("%d\n", sz(ans) ) ;
    for(int i = 0 ; i < sz(ans) ; i++ ) printf("%d%c", ans[i], " \n"[i+1 == sz(ans)] ) ;
}
