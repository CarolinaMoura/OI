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

int n , k  ;
int prof[MAXN] , minToSheep[MAXN] ;
int cobertura[MAXN] , dist[MAXN] ;
vector<int> adj[MAXN] ;
bool hasSheep[MAXN] ;

void dfs1(int x, int father)
{

    prof[x] = (hasSheep[x]) ? 0 : (n+5) ;

    for(auto e : adj[x])
    {
        if(e == father) continue ;

        dfs1(e,x) ;
        prof[x] = min(prof[x] , prof[e]+1) ;

    }

}

void dfs2(int x, int father )
{
    int qtd = sz(adj[x]) ;
    vector<int> pref(qtd) , suf(qtd) ;

    prof[x] = hasSheep[x] ? 0 : (n+5) ;

    for(int i = 0 ; i < qtd ; i++ )
        pref[i] = suf[i] = prof[ adj[x][i] ] + 1 ;

    for(int i = 1 , ii = qtd-2 ; i < qtd ; i++ , ii-- )
    {
        pref[i] = min(pref[i-1] , pref[i]) ;
        suf[ii] = min(suf[ii], suf[ii+1]) ;
    }

    prof[x] = minToSheep[x] = min(prof[x], suf[0] ) ;

    for(int i = 0, neigh ; i < qtd ; i++ )
    {
        neigh = adj[x][i] ;
        
        if(neigh == father) continue ;

        int saveX = prof[x] ;
        int saveNeigh = prof[neigh] ;

        prof[x] = hasSheep[x] ? 0 : n+5 ;

        if(i) prof[x] = min(pref[i-1] , prof[x] ) ;
        if( i+1 < qtd ) prof[x] = min(prof[x] , suf[i+1] ) ;

        dfs2(neigh, x) ;

        prof[x] = saveX ;
        prof[neigh] = saveNeigh ;

    }

}

vector<int> ans ;
void dfs3(int x, int father)
{

    for(auto e : adj[x] ) 
        if(e != father) dfs3(e, x) ;

    if(hasSheep[x]) dist[x] = 0 ;

    if(cobertura[x] != -1 && cobertura[x] >= dist[x])
        dist[x] = -1 ;

    if( dist[x] != -1 )
    {

        if(father == -1 || minToSheep[father] != dist[x]+1 )
        {
            cobertura[x] = dist[x] ;
            ans.push_back(x) ;
        }
        else dist[father]=dist[x]+1;
    }

    if(father != -1 )
        cobertura[father] = max(cobertura[father], cobertura[x]-1) ;

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
    for(int i = 0 ,x  ; i < k ; i++ )
    {
        scanf("%d", &x ) ;
        hasSheep[x] = true ;
    }

    dfs1(1,-1) ;
    dfs2(1,-1) ;

 //   debug("Debugging minToSheep:\n") ;
   // lp(i,1,n+1) debug("%d%c", minToSheep[i], " \n"[i == n]) ;

    lp(i,1,n+1) dist[i] = cobertura[i] = -1 ;

    dfs3(1,-1) ;

    sort(all(ans)) ;
    printf("%d\n" , sz(ans)) ;
    for(int i = 0 ; i < sz(ans) ; i++ ) printf("%d%c", ans[i], " \n"[i == sz(ans)-1]) ;

}
