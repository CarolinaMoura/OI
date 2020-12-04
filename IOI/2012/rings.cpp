#include <bits/stdc++.h>

#define pii pair<int,int>
#define mk make_pair
#define lp(i,a,b) for(int i = a ; i < b ; i++)
#define ff first
#define ss second
#define pb push_back
#define ll long long
#define debug printf

const int MAXN = 1e6+10 ;

using namespace std ;


struct Graph
{

    int ans , N ;
    int pai[MAXN] , deg[MAXN] ;
    vector<int> adj[MAXN] ;
    bool marc[MAXN] , can_be[MAXN] , exist[MAXN] ;
    bool operational ;

    Graph()
    {
        N = MAXN - 5 ;
        lp(i,1,N+1)
        {
            deg[i] = 0 ;
            marc[i] = false ;
            can_be[i] = true ;
            pai[i] = i ;
            exist[i] = true ;
        }
        operational = true ;
        ans = N ;
    }

    int get_return() { return operational ; }

    int find(int x)
    {
        if( x == pai[x] ) return x ;
        return pai[x] = find( pai[x] ) ;
    }

    bool join(int x, int y)
    {
        x = find(x) ;
        y = find(y) ;

        if( x == y ) return false ;

        if( rand() % 2 ) swap(x,y) ;

        pai[x] = y ;

        return true ;

    }

    bool dfs(int x, int desired )
    {
        marc[x] = true ;
        bool can = ( x == desired ) ;

        for(int i : adj[x] )
            if( !marc[i] ) can |= dfs(i, desired) ;

        if(can) ans += can_be[x] ;
        else can_be[x] = false ;

        return can ;

    }

    void make_link(int A, int B)
    {

        if( !exist[A] || !exist[B] ) return ;

        if( !join(A,B) || max( ++deg[A] , ++deg[B] ) >= 3 ) operational = false ;

        adj[A].pb(B) ;
        adj[B].pb(A) ;

    }


} ;

int N , L ;
bool forest_ok ;
Graph graph[5] ;
vector<pii> edges ;

inline void make_partition(int center)
{

    vector<int> List ;

    List.pb(center) ;
    for(int i : graph[0].adj[center] ) List.pb( i ) ;

    for(int i = 0 , idx = 1 ; i < List.size() ; i++ , idx ++ )
    {
        graph[idx].exist[ List[i] ] = false ;
        for(auto p : edges ) graph[idx].make_link(p.ff, p.ss) ;
    }
    forest_ok = true ;
    graph[0].ans = 0 ;
    lp(i,1,5) graph[0].ans += graph[i].operational ;
}

int main()
{
    scanf("%d%d", &N , &L ) ;
    graph[0].ans = N ;

    while( L-- )
    {
        int A , B ;

        scanf("%d", &A ) ;

        if( A == -1 )
        {
            printf("%d\n",  graph[0].ans ) ;
            continue ;
        }

        scanf("%d", &B ) ;
        A++ ; B++ ;

        if( graph[0].ans == 0 ) continue ;

        edges.pb( mk(A,B) ) ;

        if( !forest_ok )
        {
            graph[0].deg[A] ++ ;
            graph[0].deg[B] ++ ;

            if( graph[0].deg[A] < graph[0].deg[B] ) swap(A,B) ;

            if( graph[0].deg[A] == 3 )
            {
                graph[0].adj[A].pb(B) ;
                graph[0].adj[B].pb(A) ;

                make_partition(A) ;
                continue ;
            }

            if( !graph[0].join(A,B) )
            {
                graph[0].ans = 0 ;
                lp(i,1,N+1) graph[0].marc[i] = false ;
                graph[0].dfs(A, B) ;
                lp(i,1,N+1)
                    if( !graph[0].marc[i] )
                        graph[0].dfs(i,A) ;
            }

            graph[0].adj[A].pb(B) ;
            graph[0].adj[B].pb(A) ;
            continue;
        }

        for(int i = 1 ; i <= 4 ; i++ )
        {
            graph[0].ans -= graph[i].operational ;
            graph[i].make_link(A,B) ;
            graph[0].ans += graph[i].operational ;
        }

    }
}
