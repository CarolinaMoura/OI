/*
  CEOI 2020 - Spring Cleaning
*/

/* Virtual tree solution to Spring Cleaning

* Let's root the tree at 1
* Each edge has a color, which is 1, if the subtree of the lower vertex is even, and 0, if it's odd
* The answer should be sum_of_colors + N-1
* I must know for each vertex the sum_of_colors in its path to the root
* When adding vertex to the tree, it must matter only if:
    * the vertex was a leaf and I added more than one vertex and the parity still remains odd
    * the vertex was not a leaf and the parity is odd
    Increase the answer by D
* Get all the vertices that matter and construct its virtual tree
* An edge u-v ' s weight in the virtual tree will be the distance u-v in the original tree
* When an edge in the virtual tree has its lower vertex with odd parity, then I change the answer to ans = ans - sum[u,v] + W[u,v] - sum[u,v]
* Don't forget to always include the root

*/


#include <bits/stdc++.h>

#define lp(i,a,b) for(int i = a; i < b; i++)
#define pb push_back
#define sz(x) (int)(x.size())
#define all(x) x.begin(),x.end()
#define debug //printf
#define tiii tuple<int,int,int>
#define mkt make_tuple

const int MAXN = 3e5+10 ;
const int LOG = 20 ;

using namespace std ;

int N , Q , ansOriginal , curAns ;
int fim[MAXN ] ;
int parityChange[MAXN] , ini[MAXN] , reversoIni[MAXN] , idx[MAXN] , temp[MAXN] ;
int edgeColor[MAXN] , qtdLeaves[MAXN] , sumColors[MAXN] , lvl[MAXN] , meuPai[MAXN] ;
vector<int> adj[MAXN] , tree[MAXN] ;
bool vis[MAXN] ;

struct RMQ
{
    int vet[LOG][MAXN] , _log[MAXN] ;

    void calc()
    {
        lp(i,2,MAXN) _log[i] = _log[i>>1] + 1 ;

        lp(i,1,LOG)
            for(int j = 1 ; j + (1<<i) - 1 < MAXN ; j++ )
                vet[i][j] = min( vet[i-1][j] , vet[i-1][ j + (1<<(i-1)) ] ) ;
    }

    int qry(int l, int r)
    {
        int t = _log[ r - l + 1 ] ;
        return min( vet[t][l] , vet[t][ r - (1<<t) + 1 ] ) ;
    }

} lca ;

struct Bit
{
    int bit[MAXN] ;
    void upd(int pos, int val ) { for(int i = pos ; i < MAXN ; i += (i&-i)) bit[i] += val ; }
    int qry(int pos )
    {
        int tot = 0 ;
        for(int i = pos ; i > 0 ; i -=  (i&-i) ) tot += bit[i] ;
        return tot ;
    }
} bit ;

int currTime ;
vector<int> vecT ;
void dfs1(int x, int dad = -1)
{
    ini[x] = fim[x] = ++currTime ;
    reversoIni[currTime] = x ;
    idx[x] = sz(vecT) ;
    vecT.pb(ini[x]) ;

    for(auto e : adj[x])
    {
        if(e == dad) continue ;

        lvl[e] = lvl[x] + 1 ;

        dfs1(e,x) ;

        ansOriginal += edgeColor[e] ;
        qtdLeaves[x] += qtdLeaves[e] ;

        vecT.pb(ini[x]) ;

    }

    qtdLeaves[x] += ( sz(adj[x]) == 1 ) ;
    edgeColor[x] = (qtdLeaves[x] % 2 == 0 ) ;

    fim[x] = currTime ;

}

void dfs2(int x, int dad = -1 )
{

    sumColors[x] += edgeColor[x] ;

    for(auto e : adj[x])
    {
        if(e==dad) continue ;
        sumColors[e] = sumColors[x] ;
        dfs2(e,x) ;
    }

}

void dfs3(int x )
{
    vis[x] = true ;

    for(auto e : tree[x])
    {
        if(vis[e]) continue ;

        dfs3(e) ;
        temp[x] += temp[e] ;

        if(temp[e] % 2 == 0) continue ;

        int qtd = sumColors[e] - sumColors[x] ;
        curAns = curAns - qtd + (lvl[e]-lvl[x] - qtd) ;

        debug("Eu tava visitando %d e descobri que %d flipou para %d\n" , x , e , temp[e]) ;
        debug("Eu sabia que antes eu tinha %d arestas com %d coloridas\n", lvl[e] - lvl[x] , sumColors[e] - sumColors[x] ) ;

    }

}

int main()
{


    vecT.pb(0) ;

    scanf("%d%d", &N  , &Q ) ;
    for(int i = 1 , u , v ; i < N ; i++ )
    {
        scanf("%d%d", &u, &v ) ;
        adj[u].pb(v) ;
        adj[v].pb(u) ;
    }

    dfs1(1) ;
    dfs2(1) ;

    ansOriginal += N-1 ;

    for(int i = 1 ; i < sz(vecT ) ;i++ ) lca.vet[0][i] = vecT[i] ;
    lca.calc() ;

    for(int trash = 0 , D ; trash < Q ; trash++ )
    {
        scanf("%d", &D  ) ;

        vector<int> vec , vecFake ;

        for(int i = 0 , x ; i < D ; i++ )
        {
            scanf("%d", &x ) ;

            vec.pb(x) ;

            parityChange[x] ^= 1 ;

        }

        sort(all(vec)) ;
        vec.erase( unique(all(vec)) , vec.end() ) ;

        for(auto e : vec )
        {
            if( sz(adj[e]) == 1  ) parityChange[e] ^= 1 ;
            if( parityChange[e] ) vecFake.pb(e) ;
        }

        swap(vec, vecFake ) ;
        sort( all(vec), [&](int i, int j) { return idx[i] < idx[j] ; } ) ;

        for(auto e : vec ) temp[e] = 1 ;

        int leaves = qtdLeaves[1] + sz(vec) ;
        int T = sz(vec) ;

        for(int i = 1 ; i < T ; i++ )
        {

            int A = vec[i-1] , B = vec[i] ;
            int L = reversoIni[ lca.qry( idx[A] , idx[B] ) ] ;

            vec.pb(L) ;

        }

        vec.pb(1) ;
        sort(all(vec)) ;
        vec.erase( unique(all(vec)) , vec.end() ) ;

        sort( all(vec) , [&](int i, int j) { return lvl[i] < lvl[j] ; } ) ;

        debug("Debugging o vec: ") ;
        for(auto e : vec) debug("%d " , e ) ;
        debug("\n") ;

        vector<tiii> updates ;

        for(auto e : vec )
        {
            int toUpd = bit.qry(ini[e]) ;

            if(e != 1) meuPai[e] = toUpd ;
            else meuPai[1] = 1;

            toUpd = e - toUpd ;

            bit.upd( ini[e] , toUpd ) ;
            bit.upd( fim[e] + 1 , -toUpd ) ;

            updates.pb( mkt(ini[e] , fim[e] + 1 , toUpd) ) ;
        }

        for(auto e : vec ) tree[ meuPai[e] ].pb(e) ;
        for(auto e : updates )
        {
            bit.upd( get<0>(e) , -get<2>(e) ) ;
            bit.upd( get<1>(e) , get<2>(e ) );
        }


       // debug("Printing virtual tree:\n") ;
       // for(auto e : vec) debug("%d e pai %d\n" , e , meuPai[e]) ;

        curAns = ansOriginal + D ;

        dfs3(1) ;

        for(auto e : vec )
        {
            parityChange[e] = temp[e] = 0 ;
            tree[e].clear() ;
            vis[e] = false ;
        }

        printf("%d\n", (leaves&1) ? -1 : curAns ) ;

    }

}

/*
5 5
2 1
3 2
4 2
5 4
5 3 5 3 2 5
1 5
5 1 4 3 4 5
3 5 3 4
5 2 2 3 3 3
*/
