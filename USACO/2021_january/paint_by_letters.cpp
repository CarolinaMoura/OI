#include <bits/stdc++.h>

#define debug //printf
#define pii pair<int,int>
#define mk make_pair
#define ff first
#define ss second
#define lp(i,a,b) for(int i = a ; i < b ; i++)

const int MAX = 1010 ;

using namespace std;

int N , M , Q ;
int dx[4]={0,0,1,-1} , dy[4] = {1,-1,0,0} ;
char grid[MAX][MAX] ;
int dsu[MAX*MAX] , code[MAX][MAX] , sv[MAX][MAX] , freq[MAX*MAX] ;
pii decode[MAX*MAX] ;

bool valid(int x, int y) { return 0 <= min(x,y) && x <= N && y <= M ; }

int find(int x) { return dsu[x] = (dsu[x] == x) ? x : find(dsu[x]) ; }
void join(int x, int y)
{
    x = find(x) ;
    y = find(y) ;

    if(x ==y ) return ;

    if(rand() % 2 ) swap(x,y) ;
    dsu[x] = y ;
}
bool isRep(int x) { return find(x) == x ; }

void createEdge(int x, int y, int a, int b)
{
    debug("Created edge %d %d with %d %d\n" , x , y , a , b ) ;
    join(code[x][y] , code[a][b]) ;
    sv[a][b]++ ;
}

void makeEdges()
{
    lp(i,0,N+1)
        lp(j,0,M+1)
        {
        if(valid(i-1,j) && grid[i][j] != grid[i][j+1])
            createEdge( i-1, j , i,j ) ;
        if( valid(i,j-1) && grid[i][j] != grid[i+1][j] )
            createEdge( i, j-1 , i , j ) ;
        }

    for(int i = 0 ; i <= N+1 ; i++ )
        for(int j = 0 ; j <= M+1 ; j++ )
            sv[i][j] += isRep(code[i][j]) ;

    lp(i,0,N+1)
        lp(j,0,M+1)
        {
            if(valid(i-1, j)) sv[i][j] += sv[i-1][j] ;
            if(valid(i,j-1)) sv[i][j] += sv[i][j-1] ;
            if(valid(i-1, j-1)) sv[i][j] -= sv[i-1][j-1] ;
        }
}

bool verify(int x, int y, int a, int b)
{
    if(x != a) return grid[a][b] != grid[a][b+1] ;
    return grid[a][b] != grid[a+1][b] ;
}

int get(int x1, int y1, int x2, int y2)
{
    int ans = sv[x2][y2] ;
    ans -= sv[x2][y1] ;
    ans -= sv[x1][y2] ;
    ans += sv[x1][y1] ;
    return ans ;
}

int check(int x, int y, int a1, int b1, int a2, int b2, int id )
{
    int k = find(code[x][y]) ;

   if( freq[k] == id ) return 0 ;

   int _x = decode[k].first ;
   int _y = decode[k].second ;

   freq[k] = id ;

   if( _x >= a1 && _x <= a2 && _y >= b1 && _y <= b2 ) return -1 ;
   return 0 ;
}

int main()
{
    scanf("%d %d %d", &N, &M , &Q ) ;

    for(int i = 0 , c = 0 ; i <= N+2 ; i++ )
        for(int j = 0 ; j <= M+2 ; j++ , c++ )
        {
            code[i][j] = c ;
            dsu[c] = c ;
            grid[i][j] = '*' ;
            decode[c] = mk(i,j) ;
        }

    getchar() ;
    for(int i = 1 ; i <= N ; i++ , getchar() )
        for(int j = 1 ; j <= M ; j++ ) grid[i][j] = getchar() ;

    makeEdges() ;

    for(int idQuery = 1 , x1 , y1 , x2 , y2 ; idQuery <= Q ; idQuery++ )
    {
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2 ) ;

        x1-- ; y1-- ;

        int v = (x2-x1+1)*(y2-y1+1) ;
        int c_plus_e = get(x1, y1, x2, y2)+1 ;

        //pegando as arestas complementares da borda
        for(int i = x1 ; i < x2 ; i++ )
        {
            c_plus_e++ ;
            c_plus_e += !verify(i, y2, i+1, y2) ;
        }
        for(int i = y1 ; i < y2 ; i++ )
        {
            c_plus_e++ ;
            c_plus_e += !verify(x2, i, x2, i+1 ) ;
        }
        for(int i = x1 ; i <= x2 ; i++ ) c_plus_e += isRep(code[i][y1]) ;
        for(int i = y1+1 ; i <= y2 ; i++ ) c_plus_e += isRep(code[x1][i]) ;

        debug("Vertices: %d and edges %d\n" , v , c_plus_e ) ;

        for(int i = x1 ; i <= x2 ; i++ )
        {
            c_plus_e += check(i, y1, x1, y1, x2, y2, idQuery) ;
            c_plus_e += check(i, y2, x1, y1, x2, y2, idQuery) ;
        }
        for(int i = y1 ; i <= y2 ; i++ )
        {
            c_plus_e += check(x1, i, x1, y1, x2, y2, idQuery) ;
            c_plus_e += check(x2, i, x1, y1, x2, y2, idQuery) ;
        }

        printf("%d\n" , c_plus_e-v ) ;

    }

}

/*
4 8 1
ABBAAAAA
ABAAAABA
CAADABBA
AAAAAAAA
4 4 4 4

AAB
BBA
BBB
1 1 1 2
*/
