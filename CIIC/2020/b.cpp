/*
Eligiendo el horario
*/
#include <bits/stdc++.h>

#define pb push_back
#define ff first
#define ss second
#define all(x) x.begin(),x.end()
#define lp(i,a,b) for(int i = a ; i < b ; i++ )
#define ll long long
#define mk make_pair
#define debug //printf

const int MAXN = 2e5+10 ;

using namespace std ;

struct Edge
{
    int v ;
    ll t , i , w ;

    Edge(int v = 0 , ll t = 0 , ll i = 0 , ll w = 0) :  v(v) , t(t) ,  i(i), w(w) {}

};

int N , M ;
ll L ;
ll dist[MAXN] ;
vector<Edge> adj[MAXN] ;

ll teto(ll num , ll den )
{
    if(num % den == 0) return num/den ;
    return (num/den) + 1LL ;
}


int main()
{
    scanf("%d%d %lld", &N , &M , &L ) ;
    for(int i = 1 , u , v ; i <= M ; i++ )
    {
        ll t , ini , w ;

        scanf("%d%d %lld %lld %lld", &u, &v , &w, &ini, &t ) ;

        adj[v].pb( Edge(u,t,ini,w) ) ;

    }

    lp(i,0,N) dist[i] = -1 ;
    dist[N-1] = L ;

    priority_queue< pair<ll,int> > fila ;
    fila.push( mk(L,N-1) ) ;

    while(!fila.empty())
    {

        int x = fila.top().ss ;
        ll d = fila.top().ff ;

        fila.pop() ;

        if(d != dist[x]) continue ;

        debug("%d %lld\n" , x , d ) ;

        for(auto e : adj[x])
        {
            ll dd = d - e.w ;

            if(dd < e.i ) continue ;

            dd = ( ( dd - e.i )/e.t ) * e.t + e.i ;

            if(dd <= dist[e.v]  ) continue ;

            dist[e.v] = dd ;
            fila.push( mk(dd,e.v) ) ;

        }

    }

    printf("%lld\n" , dist[0] ) ;

}
